#ifndef neutrino_hpp
#define neutrino_hpp

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "font.hpp"
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
      char*   neutrino_path;                                                    // NEUTRINO_PATH environmental variable.
      opengl* theopengl;                                                        // The OpenGL object.
      opencl* theopencl;                                                        // The OpenCL object.
      window* thewindow;                                                        // The window object.
      font*   thefont;                                                          // The font object.
      double  tic;                                                              // Tic time [ms].
      double  toc;                                                              // Toc time [ms].
      double  loop_time;                                                        // Loop time [ms].

              neutrino();
      void    get_tic();
      void    get_toc();
              ~neutrino();
  };

#endif
