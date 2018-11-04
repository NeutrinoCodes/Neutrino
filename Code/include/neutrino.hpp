#ifndef neutrino_hpp
#define neutrino_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
  #endif

  #define LAYOUT_0 0
  #define LAYOUT_1 1

  #define KERNEL_NAME             "thekernel"
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.


  //////////////////////////////////////////////////////////////////////////
  //////////////////////// Standard C header files /////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

  //////////////////////////////////////////////////////////////////////////
  ////////////////////////// Timing C header files /////////////////////////
  //////////////////////////////////////////////////////////////////////////
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

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////// GLEW header files ///////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #include <GL/glew.h>

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////// GLFW header files ///////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #include <GLFW/glfw3.h>
  #include <GLFW/glfw3native.h>

  //////////////////////////////////////////////////////////////////////////
  /////////////////////////// OpenGL header files //////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
  #else
    #include <GL/gl.h>
  #endif

  //////////////////////////////////////////////////////////////////////////
  /////////////////////////// OpenCL header files //////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
  #endif

  #include "path.hpp"
  #include "info.hpp"
  #include "font.hpp"

  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"

  #include "program.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "NEUTRINO" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class neutrino
  {
    private:
      int               ascii_spin_phase;
      int               ascii_spin_n_old;

      path*             get_neutrino_path();
      double            get_cpu_time();
      void              ascii_spin();
      void              ascii_spin_stop();

    public:
      path*             neutrino_path;                                          // NEUTRINO_PATH environmental variable.
      double            tic;                                                    // Tic time [ms].
      double            toc;                                                    // Toc time [ms].
      double            loop_time;                                              // Loop time [ms].

      cl_context        context_id;                                             // OpenCL context id.
      cl_device_id      device_id;                                              // OpenCL device id.

                        neutrino();

      // Initialization:
      void              init();

      // Get "tic" time:
      void              get_tic();

      // Get "toc" time:
      void              get_toc();

      // Load file:
      void              load_file     (
                                        const char* file_name,
                                        char**      file_buffer,
                                        size_t*     file_size
                                      );

      // Write file:
      void              write_file    (
                                        const char* file_name,
                                        char*       file_buffer
                                      );

      // Free file:
      void              free_file     (
                                        char*       buffer
                                      );

      // Query numeric input from stdin:
      int               query_numeric (
                                        const char* caption,
                                        int         min,
                                        int         max
                                      );

                        ~neutrino();
  };

#endif
