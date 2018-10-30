/// @file

#ifndef opengl_hpp
#define opengl_hpp

  #define SIZE_WINDOW_X 800                                                     // Window x-size [px].
  #define SIZE_WINDOW_Y 600                                                     // Window y-size [px].
  #define ZOOM_FACTOR 1.05f                                                     // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                                  // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                      // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                                     // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                             // Field of view [deg].
  #define LINE_WIDTH 3                                                          // Line width [px].

  /// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE       "/Code/shader/vertex.vert"
  #define POINT_FRAGMENT_FILE     "/Code/shader/fragment.frag"
  #define TEXT_VERTEX_FILE        "/Code/shader/text_vertex.vert"
  #define TEXT_FRAGMENT_FILE      "/Code/shader/text_fragment.frag"

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <GL/glew.h>

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
  #endif

  #include <GLFW/glfw3.h>
  #include <GLFW/glfw3native.h>

  #ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
  #else
    #include <GL/gl.h>
  #endif

  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"
  #include "utilities.hpp"
  #include "path.hpp"

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

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "OPENGL" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class opengl
  {
    private:
      GLuint  compile_shader();                                                 // OpenGL shader compilation.
      GLuint  build_shader();                                                   // OpenGL shader build.
      path*   neutrino_path;                                                    // Neutrino path.

    public:
              opengl();

      GLuint  compile_shader  (
                                const char* loc_shader_filename,
                                shader_type loc_shader_type
                              );

      GLuint  build_shader    (
                                const char* loc_filename_vertex,
                                const char* loc_filename_fragment
                              );

      void    init(path* loc_neutrino_path);                                    // OpenGL initialization.
              ~opengl();
  };

#endif
