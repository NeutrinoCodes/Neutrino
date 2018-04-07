#ifndef utils_hpp
#define utils_hpp

  #include <stdio.h>
  #include <stdlib.h>

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

  double  getCPUTime();
  void    load_file(const char* file_name, char* file_buffer, size_t file_size);

#endif
