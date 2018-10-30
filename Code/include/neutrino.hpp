#ifndef neutrino_hpp
#define neutrino_hpp

  #include <stdio.h>

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "window.hpp"
  #include "font.hpp"
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

      void    get_neutrino_path();
      double  get_cpu_time();
      void    ascii_spin();
      void    ascii_spin_stop();

    public:
      path*   neutrino_path;                                                    // NEUTRINO_PATH environmental variable.
      opengl* opengl_context;                                                   // The OpenGL context object.
      opencl* opencl_context;                                                   // The OpenCL contxet object.
      window* gui_window;                                                       // The gui window object.
      font*   gui_font;                                                         // The gui font object.
      double  tic;                                                              // Tic time [ms].
      double  toc;                                                              // Toc time [ms].
      double  loop_time;                                                        // Loop time [ms].

              neutrino();
      void    get_tic();
      void    get_toc();
              ~neutrino();
  };

#endif
