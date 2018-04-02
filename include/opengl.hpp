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
  #define ZOOM_FACTOR 1.05f
  #define ROTATION_FACTOR 5.0f

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
  extern  GLuint 						shader;
  extern  GLint 						scale_shader;
  extern  GLint 						view_shader;
  extern  GLint 						projection_shader;
  extern  double            mouse_x;
  extern  double            mouse_y;
  extern  double            mouse_x_old;
  extern  double            mouse_y_old;
  extern  bool              arcball_on;
  extern  double						scroll_x;
  extern  double						scroll_y;
  extern  bool							mouse_right_button;
  extern  bool							key_ctrl_L;
  extern  double						zoom;

  extern  glm::quat					arcball_axis;                         							// 4x1 rotation quaternion.
  extern  glm::vec4					viewport;																						// 4x1 viewport vector.

  extern  glm::mat4 				Scale; 	   																					// 4x4 scale matrix.
  extern  glm::mat4					Rotation;																					  // 4x4 rotation matrix.
  extern  glm::mat4 				Translation;																				// 4x4 translation matrix.
  extern  glm::mat4 				Model;																							// 4x4 model matrix.
  extern  glm::mat4 				View;																								// 4x4 view matrix.
  extern  glm::mat4 				Projection;																					// 4x4 projection matrix.

  void        window_refresh_callback(GLFWwindow* window);
  void        key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  glm::vec3   get_arcball_vector(int x, int y);
  void        arcball();
  void        mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void        cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void        scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

  void        init_glfw();
  void        init_hints();
  void        create_window();
  void        init_glew();
  void        load_vertex(const char* filename_vertex);
  void        load_fragment(const char* filename_fragment);
  void        init_shaders();

#endif
