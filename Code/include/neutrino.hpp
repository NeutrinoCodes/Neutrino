#ifndef neutrino_hpp
#define neutrino_hpp

  #define LAYOUT_0 0
  #define LAYOUT_1 1

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
  #define KERNEL_NAME             "thekernel"
  #define SIZE_TEXT_MAX 128                                               // Maximum number of characters in a text string.

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
  #endif

  #define ASCII_33 33
  #define ASCII_126 126
  #define ASCII_SCALE 0.01
  #define ASCII_SPACE_LITTLE 4
  #define ASCII_SPACE_BIG 16

  #define SIZE_WINDOW_X 800                                               // Window x-size [px].
  #define SIZE_WINDOW_Y 600                                               // Window y-size [px].
  #define ZOOM_FACTOR 1.05f                                               // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                            // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                               // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                       // Field of view [deg].
  #define LINE_WIDTH 3                                                    // Line width [px].

  /// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE       "/Code/shader/vertex.vert"
  #define POINT_FRAGMENT_FILE     "/Code/shader/fragment.frag"
  #define TEXT_VERTEX_FILE        "/Code/shader/text_vertex.vert"
  #define TEXT_FRAGMENT_FILE      "/Code/shader/text_fragment.frag"

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

  typedef enum
  {
    WAIT,
    DONT_WAIT
  } blocking_mode;

  typedef enum
  {
    CPU,
    GPU,
    ACCELERATOR,
    DEFAULT,
    ALL
  } compute_device_type;

  typedef enum
  {
    STYLE_POINT,
    STYLE_WIREFRAME,
    STYLE_SHADED
  } plot_style;

  typedef enum
  {
    VERTEX,
    FRAGMENT
  } shader_type;

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
