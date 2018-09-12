/// @file

#include "utilities.hpp"

char*   NEUTRINO_PATH;                                                          // Neutrino path variable...
int     ascii_spin_phase = 0;
int     n_old = 0;

void get_neutrino_path()
{
  NEUTRINO_PATH = getenv("NEUTRINO_PATH");

  if (NEUTRINO_PATH != NULL)
  {
    printf("Action: loading NEUTRINO_PATH environmental variable...\n");
  }
  else
  {
    printf("Error:  NEUTRINO_PATH environmental variable not defined!\n");
    exit(1);
  }
}

double getCPUTime()
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

void load_file(char* neutrino_path, const char* file_name, char** file_buffer, size_t* file_size)
{
	FILE* handle;
  char full_name[32768];

  snprintf(full_name, sizeof full_name, "%s%s", neutrino_path, file_name);

  handle = fopen(full_name, "rb");

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

void free_file(char* buffer)
{
  free(buffer);                                                                                                               ///< Freeing buffer...
}

void ascii_spin(const char* text, double tic, double toc)
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
      printf("%s %d us", text, loop_time);
      fflush(stdout);
      n_old = n;
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

      for (i = 0; i < n_old; i++)
      {
        printf("\b");
        printf(" ");
        printf("\b");
      }

      printf("%d us", loop_time);
      fflush(stdout);
      n_old = n;
      break;
  }

  ascii_spin_phase++;

  if (ascii_spin_phase == 2)
  {
    ascii_spin_phase = 1;
  }
}

void ascii_spin_stop()
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

  for (i = 0; i < n_old; i++)
  {
    printf("\b");
    printf(" ");
    printf("\b");
  }

  printf("DONE!\n");
}
