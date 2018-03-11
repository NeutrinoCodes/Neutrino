#ifndef opengl_hpp
#define opengl_hpp

  #include <stdio.h>
  #include <stdlib.h>
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

  #include "utils.hpp"

  extern  GLFWwindow*				window;

  void window_refresh_callback(GLFWwindow* window);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void init_glfw();
  void init_hints();
  void create_window();
  void init_glew();
  void init_shaders(const char* vertex_shader, const char* fragment_shader);

#endif
