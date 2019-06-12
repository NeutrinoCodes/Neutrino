#ifndef neutrino_hpp
#define neutrino_hpp

/// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE                 "/Code/shader/point_vertex.vert"    // Plot style POINT vertex shader.
  #define POINT_GEOMETRY_FILE               "/Code/shader/point_geometry.geom"  // Plot style POINT geometry shader.
  #define POINT_FRAGMENT_FILE               "/Code/shader/point_fragment.frag"  // Plot style POINT fragment shader.

  #define VOXEL_VERTEX_FILE                 "/Code/shader/voxel_vertex.vert"    // Plot style VOXEL vertex shader.
  #define VOXEL_GEOMETRY_FILE               "/Code/shader/voxel_geometry.geom"  // Plot style VOXEL geometry shader.
  #define VOXEL_FRAGMENT_FILE               "/Code/shader/voxel_fragment.frag"  // Plot style VOXEL fragment shader.

  #define WIREFRAME_VERTEX_FILE \
  "/Code/shader/wireframe_vertex.vert"                                          // Plot style POINT vertex shader.
  #define WIREFRAME_GEOMETRY_FILE \
  "/Code/shader/wireframe_geometry.geom"                                        // Plot style POINT geometry shader.
  #define WIREFRAME_FRAGMENT_FILE \
  "/Code/shader/wireframe_fragment.frag"                                        // Plot style POINT fragment shader.

  #define SHADED_VERTEX_FILE                "/Code/shader/shaded_vertex.vert"   // Plot style POINT vertex shader.
  #define SHADED_GEOMETRY_FILE \
  "/Code/shader/shaded_geometry.geom"                                           // Plot style POINT geometry shader.
  #define SHADED_FRAGMENT_FILE \
  "/Code/shader/shaded_fragment.frag"                                           // Plot style POINT fragment shader.

  #define TEXT_VERTEX_FILE                  "/Code/shader/text_vertex.vert"     // Print style TEXT vertex shader.
  #define TEXT_GEOMETRY_FILE                "/Code/shader/text_geometry.geom"   // Print style TEXT fragment shader.
  #define TEXT_FRAGMENT_FILE                "/Code/shader/text_fragment.frag"   // Print style TEXT fragment shader.

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
  #define COLOR_NORMAL                      "\x1B[0m"                           // Default terminal color.
  #define COLOR_RED                         "\x1B[31m"                          // Red.
  #define COLOR_GREEN                       "\x1B[32m"                          // Green.
  #define COLOR_YELLOW                      "\x1B[33m"                          // Yellow.
  #define COLOR_BLUE                        "\x1B[34m"                          // Blue.
  #define COLOR_MAGENTA                     "\x1B[35m"                          // Magenta.
  #define COLOR_CYAN                        "\x1B[36m"                          // Cyan.
  #define COLOR_WHITE                       "\x1B[37m"                          // White.

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FONT PARAMETERS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  #define ASCII_33                          33                                  // 1st printable ascii character ("!"), [DEC].
  #define ASCII_126                         126                                 // Last printable ascii character ("~"), [DEC].
  #define ASCII_SCALE                       0.01                                // Ascii character scale factor [].
  #define ASCII_SPACE_LITTLE                4                                   // Hershey's vector font little space [pt].
  #define ASCII_SPACE_BIG                   16                                  // Hershey's vector font big space [pt].

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// WINDOW PARAMETERS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  #define ZOOM_INCREMENT                    0.1                                 // Mouse wheel zoom increment [].
  #define ZOOM_INCREMENT_PS4                0.02                                // PS4 gamepad zoom increment [].
  #define ZOOM_THRESHOLD_PS4                -0.95                               // PS4 gamepad zoom threshold [].
  #define INITIAL_ZOOM                      -3.0                                // Initial zoom factor [+.]
  #define PAN_FACTOR                        0.01                                // Mouse pan translation factor [].
  #define ROTATION_FACTOR                   2.0                                 // Mouse orbit rotation factor [].
  #define ROTATION_FACTOR_PS4               4.0                                 // PS4 gampad rotation factor [].
  #define ROTATION_THRESHOLD_PS4            0.1                                 // PS4 gampad rotation thrshold [].
  #define NEAR_Z_CLIP                       0.1                                 // Near z-clipping distance [small, but > 0.0].
  #define FAR_Z_CLIP                        100.0                               // Far z-clipping distance [big, but < +inf].
  #define FOV                               60.0                                // Field of view [deg].
  #define IOD                               0.02                                // Intraocular distance.
  #define SCREEN_DISTANCE                   -2.5                                // Screen distance.
  #define INITIAL_SCENE_POSITION            {0.0, 0.0, INITIAL_ZOOM}            // Initial scene position.
  #define LINE_WIDTH                        3                                   // Line width [px].
  #define KERNEL_NAME                       "thekernel"                         // OpenCL kernel function name.
  #define MAX_TEXT_SIZE                     128                                 // Maximum # of characters in a text string.
  #define MAX_MESSAGE_SIZE                  64                                  // Maximum # of characters in a text message.
  #define MAX_PATH_SIZE                     32768                               // Maximum # of characters in a text file path.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PS4 GAMEPAD BUTTONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #define SQUARE                          0
    #define CROSS                           1
    #define CIRCLE                          2
    #define TRIANGLE                        3

    #define L1                              4
    #define R1                              5
    #define L2                              6
    #define R2                              7

    #define SHARE                           8
    #define OPTIONS                         9
    #define L_ANALOG                        10
    #define R_ANALOG                        11

    #define PS                              12
    #define TOUCH                           13

    #define DPAD_UP                         14
    #define DPAD_RIGHT                      15
    #define DPAD_DOWN                       16
    #define DPAD_LEFT                       17
  #endif

  #ifdef __linux__
    #define SQUARE                          3
    #define CROSS                           0
    #define CIRCLE                          1
    #define TRIANGLE                        2

    #define L1                              4
    #define R1                              5
    #define L2                              6
    #define R2                              7

    #define SHARE                           8
    #define OPTIONS                         9
    #define L_ANALOG                        11
    #define R_ANALOG                        12

    #define PS                              10
    #define TOUCH                           13

    #define DPAD_UP                         14
    #define DPAD_RIGHT                      15
    #define DPAD_DOWN                       16
    #define DPAD_LEFT                       17
  #endif

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PS4 GAMEPAD AXES //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #ifdef __APPLE__
    #define L_ANALOG_H                      0
    #define L_ANALOG_V                      1
    #define R_ANALOG_H                      2
    #define L2_ANALOG                       3
    #define R_ANALOG_V                      5
    #define R2_ANALOG                       4
  #endif

  #ifdef __linux__
    #define L_ANALOG_H                      0
    #define L_ANALOG_V                      1
    #define R_ANALOG_H                      3
    #define L2_ANALOG                       2
    #define R_ANALOG_V                      4
    #define R2_ANALOG                       5
  #endif

// Projection mode:
typedef enum
{
  MODE_MONO,                                                                    // Projection mode set as 2D.
  MODE_STEREO                                                                   // Projection mode set as 3D.
} projection_mode;

// Plot styles:
typedef enum
{
  STYLE_POINT,                                                                  // Plot style set as points.
  STYLE_VOXEL,                                                                  // Plot style set as voxels.
  STYLE_WIREFRAME,                                                              // Plot style set as lines.
  STYLE_SHADED                                                                  // Plot style set as shaded surfaces.
} plot_style;

// Shader types:
typedef enum
{
  VERTEX,                                                                       // GLSL shader interpretation set as vertex.
  FRAGMENT,                                                                     // GLSL shader interpretation set as fragment.
  GEOMETRY                                                                      // GLSL shader interpretation set as geometry.
} shader_type;

// Kernel modes:
typedef enum
{
  WAIT,                                                                         // OpenCL kernel set as blocking mode.
  DONT_WAIT                                                                     // OpenCL kernel set as non-blocking mode.
} kernel_mode;

// Data types:
typedef enum
{
  INT,                                                                          // OpenCL "int".
  INT4,                                                                         // OpenCL "int4".
  FLOAT,                                                                        // OpenCL "float".
  FLOAT4,                                                                       // OpenCL "float4".
  MESH,                                                                         // Mesh data, re-indexed for OpenGL plot.
  COLOR                                                                         // Color data, re-indexed for OpenGL plot.
} data_type;

// Compute device types:
typedef enum
{
  CPU,                                                                          // OpenCL CPU device.
  GPU,                                                                          // OpenCL GPU device.
  ACCELERATOR,                                                                  // OpenCL ACCELERATOR device.
  DEFAULT,                                                                      // OpenCL DEFAULT device.
  ALL                                                                           // OpenCL ALL devices.
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
//#include <GL/glew.h>                                                          // http://glew.sourceforge.net
  #include <glad/glad.h>                                                        // https://glad.dav1d.de

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
/////////////////////////////// Baseline header file /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #include "baseline.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Utility header files //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  #include "path.hpp"
  #include "info.hpp"
  #include "font.hpp"

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
  path*          temp_neutrino_path;
  font*          temp_neutrino_font;
  size_t         terminal_time;
  path*  get_neutrino_path ();                                                  // Gets NEUTRINO_PATH environmental variable.
  font*  get_neutrino_font ();                                                  // Gets neutrino font.
  double get_cpu_time ();                                                       // Gets CPU time [us].

  char*          prefix_buffer;                                                 // Buffer for Neutrino path prefix.

public:
  path*          neutrino_path;                                                 // NEUTRINO_PATH environmental variable.
  font*          neutrino_font;                                                 // Font object.
  bool           use_cl_gl_interop;                                             // Use OpenCL-OpenGL interop.
  double         tic;                                                           // Tic time [us].
  double         toc;                                                           // Toc time [us].
  size_t         loop_time;                                                     // Loop time [us].

  cl_context     context_id;                                                    // OpenCL context id.
  cl_platform_id platform_id;                                                   // OpenCL platform ID.
  cl_device_id   device_id;                                                     // OpenCL device id.
  size_t         q_num;                                                         // # of OpenCL queues.
  size_t         k_num;                                                         // # of OpenCL kernels.
  cl_kernel*     kernel_id;                                                     // OpenCL kernel ID array.

  neutrino();
  // Initialization:
  void  init (
              size_t loc_q_num,
              size_t loc_k_num
             );
  // Neutrino path add prefix function:
  char* prefix (
                const char* loc_path                                            // Path.
               );
  // Get "tic" time:
  void  get_tic ();
  // Get "toc" time:
  void  get_toc ();
  // Load file:
  void  load_file (
                   const char* file_name,                                       // File name.
                   char**      file_buffer,                                     // File buffer (char array).
                   size_t*     file_size                                        // File size.
                  );
  // Write file:
  void  write_file (
                    const char* file_name,                                      // File name.
                    char*       file_buffer                                     // File buffer.
                   );
  // Free file:
  void  free_file (
                   char* buffer                                                 // File buffer.
                  );
  // Query numeric input from stdin:
  int   query_numeric (
                       const char* caption,                                     // Text query caption.
                       int         min,                                         // Minimum queried numeric value.
                       int         max                                          // Maximum queried numeric value.
                      );
  // Current stdout terminal line erase function:
  void  erase ();
  void  action (
                const char* loc_text                                            // Message.
               );
  void  error (
               const char* loc_text                                             // Message.
              );
  void  list (
              char*  loc_text,
              size_t loc_length,
              char   loc_delimiter,
              size_t loc_tab
             );
  void  done ();

  ~neutrino();
};

#endif
