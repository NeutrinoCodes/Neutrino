/// @file

#ifndef utilities_hpp
#define utilities_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <math.h>

  #if defined(__WINDOWS__)
    #include <Windows.h>
  #elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/resource.h>
    #include <sys/times.h>
    #include <time.h>
  #else
    #error "Unable to define getCPUTime() for an unknown OS."
  #endif

  extern int     ascii_spin_phase;
  extern int     n_old;

  double  getCPUTime();
  void    load_file(char* neutrino_path, const char* file_name, char** file_buffer, size_t* file_size);
  void    write_file(const char* file_name, char* file_buffer);
  void    free_file(char* buffer);
  int     query_numeric(char* caption, int min, int max);
  void    ascii_spin(const char* text, double tic, double toc);
  void    ascii_spin_stop();
#endif
