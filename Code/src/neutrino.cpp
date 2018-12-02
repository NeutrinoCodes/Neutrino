/// @file

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "NEUTRINO" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
neutrino::neutrino()
{
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
  temp_neutrino_path = new path;

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
  temp_neutrino_font = new font;

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

// PUBLIC METHODS:
void neutrino::init()
{
  first_run = true;
  last_run = false;

  // Initializing NEUTRINO_PATH:
  action      (
                "initializing neutrino path...",
                MAX_MESSAGE_SIZE
              );

  neutrino_path = get_neutrino_path();
  done();           																														// Printing message...

  // Initializing font:
  action      (
                "initializing neutrino font...",
                MAX_MESSAGE_SIZE
              );

  neutrino_font = get_neutrino_font();                                          // Font object.
	done();	             																													// Printing message...
}

void neutrino::get_tic()
{
  tic = get_cpu_time();
}

void neutrino::get_toc()
{
  size_t    padding;                                                            // Text padding.
  size_t    i;                                                                  // Index.
  char      buffer[MAX_TEXT_SIZE];                                              // Text buffer.
  char      text[MAX_TEXT_SIZE];                                                // Text buffer.

  toc = get_cpu_time();
  loop_time = size_t(round(1000000.0*(toc - tic)));                             // Loop execution time [us].

  printf("\r");

  // Compiling message string:
  snprintf  (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sAction:%s %s%d",                                               // Compiled string.
              COLOR_CYAN,                                                       // Red color.
              COLOR_NORMAL,                                                     // Normal color.
              "running OpenCL program. Host loop time = ",                      // Source string.
              loop_time
            );

  printf("%s", buffer);                                                         // Printing buffer...
  fflush(stdout);                                                               // Flushing stdout...

  if (last_run)
  {
    padding = MAX_MESSAGE_SIZE - strlen(buffer);                                  // Computing text padding...

    if(padding >= 0)                                                              // Checking padding...
    {
      for(i = 0; i < padding; i++)                                                // Compiling padding...
      {
        printf(" ");                                                              // Printing padding...
        fflush(stdout);                                                           // Flushing stdout...
      }
    }

    else                                                                          // Generating error message...
    {
      printf("Error: string too big!\n");                                         // Printing message...
      exit(1);                                                                    // Exiting...
    }

    done();
  }
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
  char  buffer[MAX_TEXT_SIZE];                                                  // Input buffer.
  int   numeric;                                                                // Numeric value.
  bool  valid_choice = false;                                                   // User's choice.

  printf("%s", caption);                                                        // Printing caption...

  while (!valid_choice)                                                         // Checking choice validity...
  {
    fgets(buffer, MAX_TEXT_SIZE, stdin);                                        // Reading string from stdin...
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

void neutrino::erase()
{
  int i;

  printf("\r");
  fflush(stdout);

  for(i = 0; i < MAX_MESSAGE_SIZE; i++)
  {
    printf(" ");
  }

  fflush(stdout);
  printf("\r");
  fflush(stdout);
}

void neutrino::action (
                        const char* loc_text,
                        size_t      loc_max_text_size
                      )
{
  char      buffer[MAX_TEXT_SIZE];                                              // Text buffer.
  size_t    padding;                                                            // Text padding.
  size_t    i;                                                                  // Index.

  padding = loc_max_text_size - strlen(loc_text);                               // Computing text padding...

  // Compiling message string:
  snprintf  (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sAction:%s %s",                                                 // Compiled string.
              COLOR_CYAN,                                                       // Red color.
              COLOR_NORMAL,                                                     // Normal color.
              loc_text                                                          // Source string.
            );

  printf("%s", buffer);                                                         // Printing buffer...

  if(padding >= 0)                                                              // Checking padding...
  {
    for(i = 0; i < padding; i++)                                                // Compiling padding...
    {
      printf(" ");                                                              // Printing padding...
      fflush(stdout);                                                           // Flushing stdout...
    }
  }

  else                                                                          // Generating error message...
  {
    printf("Error: string too big!\n");                                         // Printing message...
    exit(1);                                                                    // Exiting...
  }
}

void neutrino::error  (
                        const char* loc_text,
                        size_t      loc_max_text_size
                      )
{
  char      buffer[MAX_TEXT_SIZE];                                              // Text buffer.
  size_t    padding;                                                            // Text padding.
  size_t    i;                                                                  // Index.

  padding = loc_max_text_size - strlen(loc_text);                               // Computing text padding...

  // Compiling message string:
  snprintf  (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sError:%s  %s",                                                 // Compiled string.
              COLOR_RED,                                                        // Red color.
              COLOR_NORMAL,                                                     // Normal color.
              loc_text                                                          // Source string.
            );

  printf("%s", buffer);                                                         // Printing buffer...

  if(padding >= 0)                                                              // Checking padding...
  {
    for(i = 0; i < padding; i++)                                                // Compiling padding...
    {
      printf(" ");                                                              // Printing padding...
      fflush(stdout);                                                           // Flushing stdout...
    }
  }

  else                                                                          // Generating error message...
  {
    printf("Error: string too big!\n");                                         // Printing message...
    exit(1);                                                                    // Exiting...
  }

  // Compiling message string:
  snprintf  (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sTERMINATED!%s",                                                // Compiled string.
              COLOR_RED,                                                        // Red color.
              COLOR_NORMAL                                                      // Normal color.
            );

  printf("%s\n", buffer);                                                       // Printing buffer...
}

void neutrino::done()
{
  char      buffer[MAX_TEXT_SIZE];                                              // Text buffer.

  // Compiling message string:
  snprintf  (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sDONE!%s",                                                      // Compiled string.
              COLOR_GREEN,                                                      // Green color.
              COLOR_NORMAL                                                      // Normal color.
            );

  printf("%s\n", buffer);                                                       // Printing buffer...
}

neutrino::~neutrino()
{
  delete temp_neutrino_path;
  delete temp_neutrino_font;
}
