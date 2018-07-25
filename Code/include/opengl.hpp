#ifndef opengl_hpp
#define opengl_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <GL/glew.h>
  #include <math.h>

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

  #include "data.hpp"
  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"
  #include "utilities.hpp"

  #define SIZE_WINDOW_X 800                                                     // Window x-size [px].
  #define SIZE_WINDOW_Y 600                                                     // Window y-size [px].
  #define ZOOM_FACTOR 1.05f                                                     // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                                  // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                      // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                                     // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                             // Field of view [deg].
  #define LINE_WIDTH 3                                                          // Line width [px].

  extern  GLFWwindow*				window;                                             // Window handle.
  extern  GLuint 						point_shader;                                       // Point shader program.
  extern  GLuint 						text_shader;                                        // Text shader program.

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// FILES ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        load_point_vertex(const char* filename_vertex);
  void        load_point_fragment(const char* filename_fragment);
  void        load_text_vertex(const char* filename_vertex);
  void        load_text_fragment(const char* filename_fragment);

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// WINDOW ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        init_window();
  void        init_shaders();
  void        init_screen();
  void        refresh_screen();
  void        clear_screen();
  void        get_arcball_vector(float* p, int x, int y);
  void        arcball();
  void        plot(point4* points, color4* colors);
  void        print(text4* text);

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WINDOW's CALLBACKS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void        mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void        cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void        scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  void        window_refresh_callback(GLFWwindow* window);

#endif
