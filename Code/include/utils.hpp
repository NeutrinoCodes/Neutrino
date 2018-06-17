#ifndef utils_hpp
#define utils_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #include <ft2build.h>
  #include FT_FREETYPE_H

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

  extern int            ascii_spin_phase;
  extern FT_Library     ft_library;
  //extern FT_GlyphSlot   ft_glyph;

  double  getCPUTime();
  void    load_file(const char* file_name, char** file_buffer, size_t* file_size);
  void    free_file(char* buffer);
  void    ascii_spin(const char* text);
  void    ascii_spin_stop();
  void    init_freetype();
#endif
