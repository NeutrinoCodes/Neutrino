#ifndef neutrino_hpp
#define neutrino_hpp

  #define LAYOUT_0 0
  #define LAYOUT_1 1

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

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

  #include "opengl.hpp"
  #include "window.hpp"
  #include "font.hpp"
  #include "opencl.hpp"
  #include "path.hpp"

  #include "utilities.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "NEUTRINO" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class neutrino
  {
    private:
      int     ascii_spin_phase;
      int     ascii_spin_n_old;

      path*   get_neutrino_path();
      double  get_cpu_time();
      void    ascii_spin();
      void    ascii_spin_stop();

    public:
      opengl* opengl_context;                                                   // The OpenGL context object.
      window* gui_window;                                                       // The gui window object.
      font*   gui_font;                                                         // The gui font object.
      opencl* opencl_context;                                                   // The OpenCL contxet object.

      path*   neutrino_path;                                                    // NEUTRINO_PATH environmental variable.
      double  tic;                                                              // Tic time [ms].
      double  toc;                                                              // Toc time [ms].
      double  loop_time;                                                        // Loop time [ms].

              neutrino();
      void    init();
      void    get_tic();
      void    get_toc();
              ~neutrino();
  };

#endif
