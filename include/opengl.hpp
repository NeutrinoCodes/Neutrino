#ifndef opengl_hpp
#define opengl_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <GL/glew.h>
  #include <math.h>
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>

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

  #include "utils.hpp"

  extern  GLFWwindow*				window;
  extern  char*             vertex_source;
  extern  size_t            size_vertex;
  extern  char*             fragment_source;
  extern  size_t            size_fragment;
  extern  double            mouse_x;
  extern  double            mouse_y;
  extern  bool							mouse_left_button;

  void window_refresh_callback(GLFWwindow* window);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

  void init_glfw();
  void init_hints();
  void create_window();
  void init_glew();
  void load_vertex(const char* filename_vertex);
  void load_fragment(const char* filename_fragment);
  void init_shaders();

#endif
