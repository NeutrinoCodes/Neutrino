#ifndef neutrino_hpp
#define neutrino_hpp

  /// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE       "/Code/shader/vertex.vert"
  #define POINT_FRAGMENT_FILE     "/Code/shader/fragment.frag"
  #define TEXT_VERTEX_FILE        "/Code/shader/text_vertex.vert"
  #define TEXT_FRAGMENT_FILE      "/Code/shader/text_fragment.frag"

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS                                     // Allows the usage of "OpenCL 1.2" functions in newer versions.

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// TERMINAL COLORS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #define COLOR_NORMAL      "\x1B[0m"
  #define COLOR_RED         "\x1B[31m"
  #define COLOR_GREEN       "\x1B[32m"
  #define COLOR_YELLOW      "\x1B[33m"
  #define COLOR_BLUE        "\x1B[34m"
  #define COLOR_MAGENTA     "\x1B[35m"
  #define COLOR_CYAN        "\x1B[36m"
  #define COLOR_WHITE       "\x1B[37m"

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// FONT PARAMETERS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #define ASCII_33            33                                                // 1st printable ascii character ("!"), [DEC].
  #define ASCII_126           126                                               // Last printable ascii character ("~"), [DEC].
  #define ASCII_SCALE         0.01                                              // Ascii character scale factor [].
  #define ASCII_SPACE_LITTLE  4                                                 // Hershey's vector font little space [pt].
  #define ASCII_SPACE_BIG     16                                                // Hershy's vecotr font big space [pt].

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WINDOW PARAMETERS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #define LAYOUT_0            0                                                 // 1st variable ("location = 0") in vertex shader.
  #define LAYOUT_1            1                                                 // 2nd variable ("location = 1") in vertex shader.
  #define ZOOM_FACTOR         1.05f                                             // Mouse wheel zoom factor [> 1.0].
  #define ROTATION_FACTOR     2.0f                                              // Mouse arcball rotation factor [].
  #define NEAR_Z_CLIP         0.1f                                              // Near z-clipping distance [small, but > 0.0].
  #define FAR_Z_CLIP          100.0f                                            // Far z-clipping distance [big, but < +inf].
  #define FOV                 60.0f                                             // Field of view [deg].
  #define LINE_WIDTH          3                                                 // Line width [px].
  #define KERNEL_NAME         "thekernel"                                       // OpenCL kernel function name.
  #define SIZE_TEXT_MAX       128                                               // Maximum number of characters in a text string.

  // Plot styles:
  typedef enum
  {
    STYLE_POINT,
    STYLE_WIREFRAME,
    STYLE_SHADED
  } plot_style;

  // Shader types:
  typedef enum
  {
    VERTEX,
    FRAGMENT
  } shader_type;

  // Kernel modes:
  typedef enum
  {
    WAIT,
    DONT_WAIT
  } kernel_mode;

  // Compute device types:
  typedef enum
  {
    CPU,
    GPU,
    ACCELERATOR,
    DEFAULT,
    ALL
  } compute_device_type;

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// Standard C header files ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// Timing C header files ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
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

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// GLEW header files //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #include <GL/glew.h>

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// GLFW header files //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #include <GLFW/glfw3.h>
  #include <GLFW/glfw3native.h>

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// OpenGL header files /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
  #else
    #include <GL/gl.h>
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// OpenCL header files /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
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

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "NEUTRINO" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class neutrino
  {
    private:
      int               ascii_spin_phase;
      int               ascii_spin_n_old;
      path*             temp_neutrino_path;
      font*             temp_neutrino_font;

      path*             get_neutrino_path();                                    // Gets NEUTRINO_PATH envinromentatl variable.
      font*             get_neutrino_font();                                    // Gets neutrino font.
      double            get_cpu_time();                                         // Gets CPU time [us].
      void              ascii_spin();
      void              ascii_spin_stop();

    public:
      path*             neutrino_path;                                          // NEUTRINO_PATH environmental variable.
      font*             neutrino_font;                                          // Font object.
      double            tic;                                                    // Tic time [us].
      double            toc;                                                    // Toc time [us].
      double            loop_time;                                              // Loop time [us].

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
