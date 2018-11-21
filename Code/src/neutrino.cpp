/// @file

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "NEUTRINO" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
neutrino::neutrino()
{
  ascii_spin_phase = 0;
  ascii_spin_n_old = 0;

  neutrino_path = NULL;                                                         // NEUTRINO_PATH environmental variable.
  neutrino_font = NULL;                                                         // Neutrino font.
  tic = 0.0;                                                                    // Tic time [ms].
  toc = 0.0;                                                                    // Toc time [ms].
  loop_time = 0.0;                                                              // Loop time [ms].

  context_id = NULL;                                                            // OpenCL context ID.
  platform_id = NULL;                                                           // OpenCL platfomr ID.
  device_id = NULL;                                                             // OpenCL device ID.
}

// PRIVATE METHODS:
path* neutrino::get_neutrino_path()
{
  path* temp_neutrino_path = new path;

  temp_neutrino_path->value = getenv("NEUTRINO_PATH");                          // Getting neutrino path...
  temp_neutrino_path->size = strlen(temp_neutrino_path->value) + 1;             // Getting neutrino path length...

  if (temp_neutrino_path->value == NULL)
  {
    printf("Error:  NEUTRINO_PATH environmental variable not defined!\n");
    exit(1);

  }

  return(temp_neutrino_path);
}

font* neutrino::get_neutrino_font()
{
  font* temp_neutrino_font = new font;

  return(temp_neutrino_font);
}

double neutrino::get_cpu_time()
{
  double time;

  #if defined(__WINDOWS__)
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;

    if (
          GetProcessTimes(GetCurrentProcess(),
                          &createTime,
                          &exitTime,
                          &kernelTime,
                          &userTime)
          != -1
        )
    {
      SYSTEMTIME userSystemTime;
      if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
      {
        time =  (double)userSystemTime.wHour*3600.0 +
                (double)userSystemTime.wMinute*60.0 +
                (double)userSystemTime.wSecond +
                (double)userSystemTime.wMilliseconds/1000.0;
        return time;
      }
    }

  #elif defined(__linux__) || defined(__APPLE__)

    #if _POSIX_TIMERS > 0
    {
      clockid_t id;
      struct timespec ts;

      #if _POSIX_CPUTIME > 0

      if (clock_getcpuclockid(0, &id) == -1)
      #endif

      #if defined(CLOCK_PROCESS_CPUTIME_ID)
      id = CLOCK_PROCESS_CPUTIME_ID;

      #elif defined(CLOCK_VIRTUAL)
      id = CLOCK_VIRTUAL;

      #else
      id = (clockid_t) - 1;

      #endif

      if (id != (clockid_t) - 1 && clock_gettime(id, &ts) != -1)
      {
        time = (double)ts.tv_sec + (double)ts.tv_nsec/1000000000.0;
        return time;
      }
    }
    #endif

    #if defined(RUSAGE_SELF)
        {
          struct rusage rusage;
          if (getrusage(RUSAGE_SELF, &rusage) != -1)
          {
            time = (double)rusage.ru_utime.tv_sec + (double)rusage.ru_utime.tv_usec/1000000.0;
            return time;
          }
        }
    #endif

    #if defined(_SC_CLK_TCK)
      {
        const double ticks = (double)sysconf( _SC_CLK_TCK );
        struct tms tms;
        if (times(&tms) != (clock_t) - 1)
        {
          time = (double)tms.tms_utime/ticks;
          return time;
        }
      }
    #endif

    #if defined(CLOCKS_PER_SEC)
      {
        clock_t cl = clock();
        if (cl != (clock_t) - 1)
        {
          time = (double)cl / (double)CLOCKS_PER_SEC;
          return time;
        }
      }
    #endif

  #endif

  return -1.0;
}

void neutrino::ascii_spin()
{
  int loop_time;
  int num;
  int n;
  int i;

  loop_time = int(round(1000000*(toc - tic)));                                  // Loop execution time [us].

  num = loop_time;
  n = 0;

  while (num > 0)
  {
    num /= 10;
    n++;
  }

  switch (ascii_spin_phase)
  {
    case 0:
      printf("Action: running      OpenCL program... %d us", loop_time);
      fflush(stdout);
      ascii_spin_n_old = n;
      break;
    case 1:
      printf("\b");
      printf(" ");
      printf("\b");
      printf("\b");
      printf(" ");
      printf("\b");
      printf("\b");
      printf(" ");
      printf("\b");

      for (i = 0; i < ascii_spin_n_old; i++)
      {
        printf("\b");
        printf(" ");
        printf("\b");
      }

      printf("%d us", loop_time);
      fflush(stdout);
      ascii_spin_n_old = n;
      break;
  }

  ascii_spin_phase++;

  if (ascii_spin_phase == 2)
  {
    ascii_spin_phase = 1;
  }
}

void neutrino::ascii_spin_stop()
{
  int i;

  printf("\b");
  printf(" ");
  printf("\b");
  printf("\b");
  printf(" ");
  printf("\b");
  printf("\b");
  printf(" ");
  printf("\b");

  for (i = 0; i < ascii_spin_n_old; i++)
  {
    printf("\b");
    printf(" ");
    printf("\b");
  }

  printf("DONE!\n");
}

// PUBLIC METHODS:
void neutrino::init()
{
  ascii_spin_phase = 0;                                                         // Initializing ascii_spin_phase...
  ascii_spin_n_old = 0;                                                         // Initializing ascii_spin_n_old...

  // Initializing NEUTRINO_PATH:
  printf("Action: initializing neutrino path...  ");											      // Printing message...
  neutrino_path = get_neutrino_path();
  printf("DONE!\n");																														// Printing message...

  // Initializing font:
  printf("Action: initializing neutrino font...  ");                            // Printing message...
  neutrino_font = get_neutrino_font();                                          // Font object.
	printf("DONE!\n");																														// Printing message...
}

void neutrino::get_tic()
{
  tic = get_cpu_time();
}

void neutrino::get_toc()
{
  toc = get_cpu_time();
  loop_time = toc - tic;
  ascii_spin();
}

void neutrino::load_file(const char* file_name, char** file_buffer, size_t* file_size)
{
	FILE* handle;

  handle = fopen(file_name, "rb");

  if(handle == NULL)
  {
    printf("\nError:  could not find the file!\n");
    exit(1);
  }

  fseek(handle, 0, SEEK_END);
  *file_size = (size_t)ftell(handle);
  rewind(handle);
  *file_buffer = (char*)malloc(*file_size + 1);

  if (!*file_buffer)
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(*file_buffer, sizeof(char), *file_size, handle);
  fclose(handle);
  file_buffer[0][*file_size] = '\0';
}

void neutrino::write_file(const char* file_name, char* file_buffer)
{
	FILE* handle;

	printf("Action: writing file \"%s\"...", file_name);

  handle = fopen(file_name, "a");

  if(handle == NULL)
  {
    printf("\nError:  could not write the file!\n");
    exit(1);
  }

  fputs(file_buffer, handle);
  fclose(handle);

	printf(" DONE!\n");
}

void neutrino::free_file(char* buffer)
{
  free(buffer);                                                                                                               ///< Freeing buffer...
}

int neutrino::query_numeric(const char* caption, int min, int max)
{
  char  buffer[128];                                                            // Input buffer.
  int   numeric;                                                                // Numeric value.
  bool  valid_choice = false;                                                   // User's choice.

  printf("%s", caption);                                                        // Printing caption...

  while (!valid_choice)                                                         // Checking choice validity...
  {
    fgets(buffer, 128, stdin);                                                  // Reading string from stdin...
    numeric = strtol(buffer, NULL, 10);                                         // Parsing stdin...

    if ((min <= numeric) && (numeric <= max) && (errno != ERANGE))
    {
      valid_choice = true;                                                      // Setting flag...
    }

    else
    {
      printf("\nError:  invalid input! Please, try again!\n");                  // Printing message...
      printf("\n");                                                             // Printing message...
      printf("%s", caption);                                                    // Printing question...

      errno = 0;
    }
  }

  return(numeric);                                                              // Returning numeric choice...
}

neutrino::~neutrino()
{
  ascii_spin_stop();

  delete temp_neutrino_path;
  delete temp_neutrino_font;
}
