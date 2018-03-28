#ifndef opengl_hpp
#define opengl_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <GL/glew.h>
  #include <math.h>
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtx/transform.hpp>
  #include <glm/gtx/vector_angle.hpp>
  #include <glm/gtx/quaternion.hpp>

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

  #define SIZE_WINDOW_X 800
  #define SIZE_WINDOW_Y 600

  extern  GLFWwindow*				window;
  extern  int								window_x;
  extern  int								window_y;
  extern  int								size_window_x;
  extern  int								size_window_y;
  extern  float							aspect_ratio;
  extern  char*             vertex_source;
  extern  size_t            size_vertex;
  extern  char*             fragment_source;
  extern  size_t            size_fragment;
  extern  double            mouse_x;
  extern  double            mouse_y;
  extern  double            mouse_x_old;
  extern  double            mouse_y_old;
  extern  int								mouse_button;
  extern  int								mouse_action;
  extern  bool							mouse_1st_left_click;
  extern  double						scroll_x;
  extern  double						scroll_y;
  extern  bool							mouse_right_button;
  extern  bool							key_ctrl_L;

  extern  glm::vec3					I3;															                    // 3x1 ones vector.
  extern  glm::vec4					I4;												                          // 4x1 ones vector.
  extern  glm::mat4					I4x4;																		         		// 4x4 identity matrix.

  extern  glm::vec3					S3; 	   																						// 3x1 scale vector.
  extern  glm::vec3					R3;																									// 3x1 rotation vector.
  extern  glm::vec3					T3;																									// 3x1 translation vector.

  extern  glm::quat					R4;                         												// 4x1 rotation quaternion.
  extern  glm::vec4					viewport;																						// 4x1 viewport vector.

  extern  glm::mat4 				S4x4; 	   																					// 4x4 scale matrix.
  extern  glm::mat4					R4x4;																								// 4x4 rotation matrix.
  extern  glm::mat4 				T4x4;																								// 4x4 translation matrix.
  extern  glm::mat4 				M4x4;																								// 4x4 model matrix.
  extern  glm::mat4 				V4x4;																								// 4x4 view matrix.
  extern  glm::mat4 				P4x4;																								// 4x4 projection matrix.

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
