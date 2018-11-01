#ifndef neutrino_hpp
#define neutrino_hpp

  

  /*
  #include "opengl.hpp"
  #include "opencl.hpp"

  #include "window.hpp"
  #include "platform.hpp"
  #include "device.hpp"
  #include "queue.hpp"
  #include "kernel.hpp"

  #include "int1.hpp"
  #include "int4.hpp"
  #include "float1.hpp"
  #include "float4.hpp"
  #include "point4.hpp"
  #include "color4.hpp"
  #include "text4.hpp"

  #include "path.hpp"
  #include "info.hpp"
  #include "font.hpp"

  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"

  #include "utilities.hpp"

  #include "program.hpp"
  */


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
