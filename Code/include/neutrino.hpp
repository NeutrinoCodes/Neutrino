#ifndef neutrino_hpp
#define neutrino_hpp

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS                                                           // Allows the usage of "OpenCL 1.2" functions in newer versions.

#ifdef WIN32
  #define GLFW_EXPOSE_NATIVE_WIN32                                                                  // Enabling Windows native access functions...
  #define GLFW_EXPOSE_NATIVE_WGL                                                                    // Enabling Windows native access functions...
#endif

#ifdef __linux__
  #define GLFW_EXPOSE_NATIVE_X11                                                                    // Enabling Linux native access functions...
  #define GLFW_EXPOSE_NATIVE_GLX                                                                    // Enabling Linux native access functions...
#endif

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// TERMINAL PARAMETERS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define NU_TERMINAL_REFRESH               20000                                                     // Terminal refresh time [us].
#define NU_COLOR_NORMAL                   "\x1B[0m"                                                 // Default terminal color.
#define NU_COLOR_RED                      "\x1B[31m"                                                // Red.
#define NU_COLOR_GREEN                    "\x1B[32m"                                                // Green.
#define NU_COLOR_YELLOW                   "\x1B[33m"                                                // Yellow.
#define NU_COLOR_BLUE                     "\x1B[34m"                                                // Blue.
#define NU_COLOR_MAGENTA                  "\x1B[35m"                                                // Magenta.
#define NU_COLOR_CYAN                     "\x1B[36m"                                                // Cyan.
#define NU_COLOR_WHITE                    "\x1B[37m"                                                // White.
#define NU_ERASE                          "\33[2K\r"                                                // Erase character.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// WINDOW PARAMETERS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define NU_ZOOM_INCREMENT                 0.1                                                       // Mouse wheel zoom increment [].
#define NU_ZOOM_INCREMENT_PS4             0.02                                                      // PS4 gamepad zoom increment [].
#define NU_ZOOM_THRESHOLD_PS4             -0.95                                                     // PS4 gamepad zoom threshold [].
#define NU_INITIAL_ZOOM                   -3.0                                                      // Initial zoom factor [+.]
#define NU_PAN_FACTOR                     0.01                                                      // Mouse pan translation factor [].
#define NU_ROTATION_FACTOR                2.0                                                       // Mouse orbit rotation factor [].
#define NU_ROTATION_FACTOR_PS4            4.0                                                       // PS4 gampad rotation factor [].
#define NU_ROTATION_THRESHOLD_PS4         0.1                                                       // PS4 gampad rotation thrshold [].
#define NU_NEAR_Z_CLIP                    0.1                                                       // Near z-clipping distance [small, but > 0.0].
#define NU_FAR_Z_CLIP                     100.0                                                     // Far z-clipping distance [big, but < +inf].
#define NU_FOV                            60.0                                                      // Field of view [deg].
#define NU_IOD                            0.02                                                      // Intraocular distance.
#define NU_SCREEN_DISTANCE                -2.5                                                      // Screen distance.
#define NU_INITIAL_SCENE_POSITION         {0.0, 0.0, NU_INITIAL_ZOOM}                               // Initial scene position.
#define NU_LINE_WIDTH                     3                                                         // Line width [px].
#define NU_KERNEL_NAME                    "thekernel"                                               // OpenCL kernel function name.
#define NU_MAX_TEXT_SIZE                  128                                                       // Maximum # of characters in a text string.
#define NU_MAX_MESSAGE_SIZE               64                                                        // Maximum # of characters in a text message.
#define NU_MAX_PATH_SIZE                  32768                                                     // Maximum # of characters in a text file path.

#define NU_GAMEPAD_MIN_DECAYTIME          0.01                                                      // Minimum decay time for LP filter [s].
#define NU_GAMEPAD_MAX_DECAYTIME          10.0                                                      // Maximum decay time for LP filter [s].
#define NU_GAMEPAD_MIN_AXES               -1.0                                                      // Minimum axes value.
#define NU_GAMEPAD_MAX_AXES               +1.0                                                      // Maximum axes value.
#define NU_GAMEPAD_MIN_ORBIT_RATE         0.01                                                      // Minimum orbit angular rate [rev/s].
#define NU_GAMEPAD_MAX_ORBIT_RATE         10.0                                                      // Maximum orbit angular rate [rev/s].
#define NU_GAMEPAD_MIN_PAN_RATE           0.01                                                      // Minimum orbit angular rate [rev/s].
#define NU_GAMEPAD_MAX_PAN_RATE           10.0                                                      // Maximum orbit angular rate [rev/s].

// Projection mode:
typedef enum
{
  NU_MODE_MONO,                                                                                     // Projection mode set as 2D.
  NU_MODE_STEREO                                                                                    // Projection mode set as 3D.
} projection_mode;

// Shader types:
typedef enum
{
  NU_VERTEX,                                                                                        // GLSL shader interpretation set as vertex.
  NU_FRAGMENT,                                                                                      // GLSL shader interpretation set as fragment.
  NU_GEOMETRY                                                                                       // GLSL shader interpretation set as geometry.
} shader_type;

// Kernel modes:
typedef enum
{
  NU_WAIT,                                                                                          // OpenCL kernel set as blocking mode.
  NU_DONT_WAIT                                                                                      // OpenCL kernel set as non-blocking mode.
} kernel_mode;

// Compute device types:
typedef enum
{
  NU_CPU,                                                                                           // OpenCL NU_CPU device.
  NU_GPU,                                                                                           // OpenCL NU_GPU device.
  NU_ACCELERATOR,                                                                                   // OpenCL NU_ACCELERATOR device.
  NU_DEFAULT,                                                                                       // OpenCL NU_DEFAULT device.
  NU_ALL                                                                                            // OpenCL NU_ALL devices.
} compute_device_type;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Standard C header files ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cerrno>

#ifdef __APPLE__
  #include <math.h>
#endif

#ifdef __linux__
  #include <math.h>
#endif

#ifdef WIN32
  #include <windows.h>
  #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
  #define DISABLE_NEWLINE_AUTO_RETURN        0x0008

//#define _USE_MATH_DEFINES
#include <cmath>
  #ifndef M_PI
    #define M_PI                             3.14159265358979323846
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// GLAD header files //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <glad/glad.h>                                                                              // https://glad.dav1d.de

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// GLFW header files //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <GLFW/glfw3.h>                                                                             // https://www.glfw.org
#include <GLFW/glfw3native.h>                                                                       // https://www.glfw.org

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// OpenGL header files /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__
  #include <OpenGL/OpenGL.h>                                                                        // Apple deprecated the OpenGL framework in 2018, OS-X 10.14 Mojave.
#else
  #include <GL/gl.h>                                                                                // https://www.opengl.org
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// OpenCL header files /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__
  #include <OpenCL/opencl.h>                                                                        // Apple deprecated the OpenCL framework in 2018, OS-X 10.14 Mojave.
#else
  #include <CL/cl.h>                                                                                // https://www.opengl.org
  #include <CL/cl_gl.h>                                                                             // https://www.opengl.org
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
  size_t         terminal_time;                                                                     // Terminal time (for refresh) [us].

public:
  bool           interop;                                                                           // Use OpenCL-OpenGL interop.
  double         tic;                                                                               // Tic time [us].
  double         toc;                                                                               // Toc time [us].
  size_t         loop_time;                                                                         // Loop time [us].
  size_t         q_num;                                                                             // # of OpenCL queues.
  size_t         k_num;                                                                             // # of OpenCL kernels.
  cl_context     context_id;                                                                        // OpenCL context id.
  cl_platform_id platform_id;                                                                       // OpenCL platform ID.
  cl_device_id   device_id;                                                                         // OpenCL device id.
  cl_kernel*     kernel_id;                                                                         // OpenCL kernel ID array.

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
  std::string load_file (
                         std::string loc_file_name
                        );
  // Write file:
  void        write_file (
                          std::string file_name                                                     // File name.
                         );
  // Query numeric input from stdin:
  int         query_numeric (
                             std::string caption,                                                   // Text query caption.
                             int         min,                                                       // Minimum queried numeric value.
                             int         max                                                        // Maximum queried numeric value.
                            );
  // Current stdout terminal line erase function:
  void        erase ();
  void        action (
                      std::string loc_text                                                          // Message.
                     );
  void        error (
                     std::string loc_text                                                           // Message.
                    );
  void        list (
                    std::string loc_text,
                    std::string loc_delimiter,
                    size_t      loc_tab
                   );
  void        done ();
  void        terminated ();
  double      constrain_double (
                                double loc_input,
                                double loc_min,
                                double loc_max
                               );
  float       constrain_float (
                               float loc_input,
                               float loc_min,
                               float loc_max
                              );
  // OpenCL error get function:
  std::string get_error (
                         cl_int loc_error                                                           // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                                         // Error code.
                          );

  ~neutrino();
};

#endif
