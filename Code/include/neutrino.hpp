#ifndef neutrino_hpp
#define neutrino_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS                                     // Allows the usage of "OpenCL 1.2" functions in newer versions.

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32                                            // Enabling Windows native access functions...
    #define GLFW_EXPOSE_NATIVE_WGL                                              // Enabling Windows native access functions...
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11                                              // Enabling Linux native access functions...
    #define GLFW_EXPOSE_NATIVE_GLX                                              // Enabling Linux native access functions...
  #endif

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// TERMINAL PARAMETERS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #define NU_TERMINAL_REFRESH               20000                               // Terminal refresh time [us].
  #define NU_COLOR_NORMAL                   "\x1B[0m"                           // Default terminal color.
  #define NU_COLOR_RED                      "\x1B[31m"                          // Red.
  #define NU_COLOR_GREEN                    "\x1B[32m"                          // Green.
  #define NU_COLOR_YELLOW                   "\x1B[33m"                          // Yellow.
  #define NU_COLOR_BLUE                     "\x1B[34m"                          // Blue.
  #define NU_COLOR_MAGENTA                  "\x1B[35m"                          // Magenta.
  #define NU_COLOR_CYAN                     "\x1B[36m"                          // Cyan.
  #define NU_COLOR_WHITE                    "\x1B[37m"                          // White.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// WINDOW PARAMETERS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #define NU_ZOOM_INCREMENT                 0.1                                 // Mouse wheel zoom increment [].
  #define NU_ZOOM_INCREMENT_PS4             0.02                                // PS4 gamepad zoom increment [].
  #define NU_ZOOM_THRESHOLD_PS4             -0.95                               // PS4 gamepad zoom threshold [].
  #define NU_INITIAL_ZOOM                   -3.0                                // Initial zoom factor [+.]
  #define NU_PAN_FACTOR                     0.01                                // Mouse pan translation factor [].
  #define NU_ROTATION_FACTOR                2.0                                 // Mouse orbit rotation factor [].
  #define NU_ROTATION_FACTOR_PS4            4.0                                 // PS4 gampad rotation factor [].
  #define NU_ROTATION_THRESHOLD_PS4         0.1                                 // PS4 gampad rotation thrshold [].
  #define NU_NEAR_Z_CLIP                    0.1                                 // Near z-clipping distance [small, but > 0.0].
  #define NU_FAR_Z_CLIP                     100.0                               // Far z-clipping distance [big, but < +inf].
  #define NU_FOV                            60.0                                // Field of view [deg].
  #define NU_IOD                            0.02                                // Intraocular distance.
  #define NU_SCREEN_DISTANCE                -2.5                                // Screen distance.
  #define NU_INITIAL_SCENE_POSITION         {0.0, 0.0, NU_INITIAL_ZOOM}         // Initial scene position.
  #define NU_LINE_WIDTH                     3                                   // Line width [px].
  #define NU_KERNEL_NAME                    "thekernel"                         // OpenCL kernel function name.
  #define NU_MAX_TEXT_SIZE                  128                                 // Maximum # of characters in a text string.
  #define NU_MAX_MESSAGE_SIZE               64                                  // Maximum # of characters in a text message.
  #define NU_MAX_PATH_SIZE                  32768                               // Maximum # of characters in a text file path.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PS4 GAMEPAD BUTTONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #define NU_SQUARE                       0
    #define NU_CROSS                        1
    #define NU_CIRCLE                       2
    #define NU_TRIANGLE                     3

    #define NU_L1                           4
    #define NU_R1                           5
    #define NU_L2                           6
    #define NU_R2                           7

    #define NU_SHARE                        8
    #define NU_OPTIONS                      9
    #define NU_L_ANALOG                     10
    #define NU_R_ANALOG                     11

    #define NU_PS                           12
    #define NU_TOUCH                        13

    #define NU_DPAD_UP                      14
    #define NU_DPAD_RIGHT                   15
    #define NU_DPAD_DOWN                    16
    #define NU_DPAD_LEFT                    17
  #endif

  #ifdef __linux__
    #define NU_SQUARE                       3
    #define NU_CROSS                        0
    #define NU_CIRCLE                       1
    #define NU_TRIANGLE                     2

    #define NU_L1                           4
    #define NU_R1                           5
    #define NU_L2                           6
    #define NU_R2                           7

    #define NU_SHARE                        8
    #define NU_OPTIONS                      9
    #define NU_L_ANALOG                     11
    #define NU_R_ANALOG                     12

    #define NU_PS                           10
    #define NU_TOUCH                        13

    #define NU_DPAD_UP                      14
    #define NU_DPAD_RIGHT                   15
    #define NU_DPAD_DOWN                    16
    #define NU_DPAD_LEFT                    17
  #endif

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PS4 GAMEPAD AXES //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #define NU_L_ANALOG_H                   0
    #define NU_L_ANALOG_V                   1
    #define NU_R_ANALOG_H                   2
    #define NU_L2_ANALOG                    3
    #define NU_R_ANALOG_V                   5
    #define NU_R2_ANALOG                    4
  #endif

  #ifdef __linux__
    #define NU_L_ANALOG_H                   0
    #define NU_L_ANALOG_V                   1
    #define NU_R_ANALOG_H                   3
    #define NU_L2_ANALOG                    2
    #define NU_R_ANALOG_V                   4
    #define NU_R2_ANALOG                    5
  #endif

// Projection mode:
typedef enum
{
  NU_MODE_MONO,                                                                 // Projection mode set as 2D.
  NU_MODE_STEREO                                                                // Projection mode set as 3D.
} projection_mode;

// Shader types:
typedef enum
{
  NU_VERTEX,                                                                    // GLSL shader interpretation set as vertex.
  NU_FRAGMENT,                                                                  // GLSL shader interpretation set as fragment.
  NU_GEOMETRY                                                                   // GLSL shader interpretation set as geometry.
} shader_type;

// Kernel modes:
typedef enum
{
  NU_WAIT,                                                                      // OpenCL kernel set as blocking mode.
  NU_DONT_WAIT                                                                  // OpenCL kernel set as non-blocking mode.
} kernel_mode;

// Compute device types:
typedef enum
{
  NU_CPU,                                                                       // OpenCL NU_CPU device.
  NU_GPU,                                                                       // OpenCL NU_GPU device.
  NU_ACCELERATOR,                                                               // OpenCL NU_ACCELERATOR device.
  NU_DEFAULT,                                                                   // OpenCL NU_DEFAULT device.
  NU_ALL                                                                        // OpenCL NU_ALL devices.
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
/////////////////////////////// GLAD header files //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <glad/glad.h>                                                        // https://glad.dav1d.de
  #include <glad/gl.h>

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

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Geometry header files /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "NEUTRINO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class neutrino
{
private:
  size_t         terminal_time;                                                 // Terminal time (for refresh) [us].

public:
  bool           interop;                                                       // Use OpenCL-OpenGL interop.
  double         tic;                                                           // Tic time [us].
  double         toc;                                                           // Toc time [us].
  size_t         loop_time;                                                     // Loop time [us].
  size_t         q_num;                                                         // # of OpenCL queues.
  size_t         k_num;                                                         // # of OpenCL kernels.
  cl_context     context_id;                                                    // OpenCL context id.
  cl_platform_id platform_id;                                                   // OpenCL platform ID.
  cl_device_id   device_id;                                                     // OpenCL device id.
  cl_kernel*     kernel_id;                                                     // OpenCL kernel ID array.

  neutrino();
  // Initialization:
  void        init (
                    size_t loc_q_num,
                    size_t loc_k_num,
                    bool   loc_interop
                   );
  // Get "tic" time:
  void        get_tic ();
  // Get "toc" time:
  void        get_toc ();
  // Load file:
  void        load_file (
                         const char* file_name,                                 // File name.
                         char**      file_buffer,                               // File buffer (char array).
                         size_t*     file_size                                  // File size.
                        );
  // Write file:
  void        write_file (
                          const char* file_name,                                // File name.
                          char*       file_buffer                               // File buffer.
                         );
  // Free file:
  void        free_file (
                         char* buffer                                           // File buffer.
                        );
  // Query numeric input from stdin:
  int         query_numeric (
                             const char* caption,                               // Text query caption.
                             int         min,                                   // Minimum queried numeric value.
                             int         max                                    // Maximum queried numeric value.
                            );
  // Current stdout terminal line erase function:
  void        erase ();
  void        action (
                      const char* loc_text                                      // Message.
                     );
  void        error (
                     const char* loc_text                                       // Message.
                    );
  void        list (
                    char*  loc_text,
                    size_t loc_length,
                    char   loc_delimiter,
                    size_t loc_tab
                   );
  void        done ();
  void        terminated ();
  // OpenCL error get function:
  const char* get_error (
                         cl_int loc_error                                       // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                     // Error code.
                          );

  ~neutrino();
};

#endif
