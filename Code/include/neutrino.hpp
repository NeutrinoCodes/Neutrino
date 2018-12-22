#ifndef neutrino_hpp
#define neutrino_hpp

  /// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE       "/Code/shader/vertex.vert"                    // Plot style POINT vertex shader.
  #define POINT_FRAGMENT_FILE     "/Code/shader/fragment.frag"                  // Plot style POINT fragment shader.
  #define TEXT_VERTEX_FILE        "/Code/shader/text_vertex.vert"               // Print style TEXT vertex shader.
  #define TEXT_FRAGMENT_FILE      "/Code/shader/text_fragment.frag"             // Print style TEXT fragment shader.

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS                                     // Allows the usage of "OpenCL 1.2" functions in newer versions.

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32                                            // Enabling Windows native access functions...
    #define GLFW_EXPOSE_NATIVE_WGL                                              // Enabling Windows native access functions...
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11                                              // Enabling Linux native access functions...
    #define GLFW_EXPOSE_NATIVE_GLX                                              // Enabling Linux native access functions...
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// TERMINAL COLORS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #define COLOR_NORMAL      "\x1B[0m"                                           // Default terminal color.
  #define COLOR_RED         "\x1B[31m"                                          // Red.
  #define COLOR_GREEN       "\x1B[32m"                                          // Green.
  #define COLOR_YELLOW      "\x1B[33m"                                          // Yellow.
  #define COLOR_BLUE        "\x1B[34m"                                          // Blue.
  #define COLOR_MAGENTA     "\x1B[35m"                                          // Magenta.
  #define COLOR_CYAN        "\x1B[36m"                                          // Cyan.
  #define COLOR_WHITE       "\x1B[37m"                                          // White.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// FONT PARAMETERS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #define ASCII_33            33                                                // 1st printable ascii character ("!"), [DEC].
  #define ASCII_126           126                                               // Last printable ascii character ("~"), [DEC].
  #define ASCII_SCALE         0.01                                              // Ascii character scale factor [].
  #define ASCII_SPACE_LITTLE  4                                                 // Hershey's vector font little space [pt].
  #define ASCII_SPACE_BIG     16                                                // Hershey's vector font big space [pt].

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
  #define MAX_TEXT_SIZE       128                                               // Maximum # of characters in a text string.
  #define MAX_MESSAGE_SIZE    64                                                // Maximum # of characters in a text message.
  #define MAX_PATH_SIZE       32768                                             // Maximum # of characters in a text file path.

  // Plot styles:
  typedef enum
  {
    STYLE_POINT,                                                                // Plot style set as points.
    STYLE_WIREFRAME,                                                            // Plot style set as lines.
    STYLE_SHADED                                                                // Plot style set as shaded surfaces.
  } plot_style;

  // Shader types:
  typedef enum
  {
    VERTEX,                                                                     // GLSL shader interpretation set as vertex.
    FRAGMENT                                                                    // GLSL shader interpretation set as fragment.
  } shader_type;

  // Kernel modes:
  typedef enum
  {
    WAIT,                                                                       // OpenCL kernel set as blocking mode.
    DONT_WAIT                                                                   // OpenCL kernel set as non-blocking mode.
  } kernel_mode;

  // Compute device types:
  typedef enum
  {
    CPU,                                                                        // OpenCL CPU device.
    GPU,                                                                        // OpenCL GPU device.
    ACCELERATOR,                                                                // OpenCL ACCELERATOR device.
    DEFAULT,                                                                    // OpenCL DEFAULT device.
    ALL                                                                         // OpenCL ALL devices.
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
  #include <GL/glew.h>                                                          // http://glew.sourceforge.net

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// GLFW header files //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #include <GLFW/glfw3.h>                                                       // https://www.glfw.org
  #include <GLFW/glfw3native.h>                                                 // https://www.glfw.org

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// OpenGL header files /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #include <OpenGL/OpenGL.h>                                                  // Apple deprecated the OpenGL framework in 2018, OS-X 10.14 Mojave.
  #else
    #include <GL/gl.h>                                                          // https://www.opengl.org
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// OpenCL header files /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #include <OpenCL/opencl.h>                                                  // Apple deprecated the OpenCL framework in 2018, OS-X 10.14 Mojave.
  #else
    #include <CL/cl.h>                                                          // https://www.opengl.org
    #include <CL/cl_gl.h>                                                       // https://www.opengl.org
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
      path*             temp_neutrino_path;
      font*             temp_neutrino_font;
      size_t            terminal_time;

      path*             get_neutrino_path();                                    // Gets NEUTRINO_PATH environmental variable.
      font*             get_neutrino_font();                                    // Gets neutrino font.
      double            get_cpu_time();                                         // Gets CPU time [us].

      char*             prefix_buffer;                                          // Buffer for Neutrino path prefix.

    public:
      path*             neutrino_path;                                          // NEUTRINO_PATH environmental variable.
      font*             neutrino_font;                                          // Font object.
      bool				use_cl_gl_interop;										// Use OpenCL-OpenGL interop.
      double            tic;                                                    // Tic time [us].
      double            toc;                                                    // Toc time [us].
      size_t            loop_time;                                              // Loop time [us].

      cl_context        context_id;                                             // OpenCL context id.
      cl_platform_id    platform_id;                                            // OpenCL platform ID.
      cl_device_id      device_id;                                              // OpenCL device id.
      size_t            q_num;                                                  // # of OpenCL queues.
      size_t            k_num;                                                  // # of OpenCL kernels.
      cl_kernel*        kernel_id;                                              // OpenCL kernel ID array.

                        neutrino();

      // Initialization:
      void              init(size_t loc_q_num, size_t loc_k_num,
    		  	  	  	  	 bool loc_use_cl_gl_interop);

      // Neutrino path add prefix function:
      char*             prefix        (
                                        const char* loc_path                    // Path.
                                      );

      // Get "tic" time:
      void              get_tic();

      // Get "toc" time:
      void              get_toc();

      // Load file:
      void              load_file     (
                                        const char* file_name,                  // File name.
                                        char**      file_buffer,                // File buffer (char array).
                                        size_t*     file_size                   // File size.
                                      );

      // Write file:
      void              write_file    (
                                        const char* file_name,                  // File name.
                                        char*       file_buffer                 // File buffer.
                                      );

      // Free file:
      void              free_file     (
                                        char*       buffer                      // File buffer.
                                      );

      // Query numeric input from stdin:
      int               query_numeric (
                                        const char* caption,                    // Text query caption.
                                        int         min,                        // Minimum queried numeric value.
                                        int         max                         // Maximum queried numeric value.
                                      );

      // Current stdout terminal line erase function:
      void              erase         ();

      void              action        (
                                        const char* loc_text                    // Message.
                                      );

      void              error         (
                                        const char* loc_text                    // Message.
                                      );

      void              list          (
                                        char*       loc_text,
                                        size_t      loc_length,
                                        char        loc_delimiter,
                                        size_t      loc_tab
                                      );

      void              done();

                        ~neutrino();
  };

#endif
