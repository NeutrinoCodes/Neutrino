#ifndef opengl_hpp
#define opengl_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <GL/glew.h>
  #include <math.h>
  #include <glm/glm.hpp>
  #include <glm/gtc/matrix_transform.hpp>
  #include <glm/gtc/random.hpp>
  #include <glm/gtx/transform.hpp>
  #include <glm/gtx/vector_angle.hpp>
  #include <glm/gtx/quaternion.hpp>
  #include <ft2build.h>
  #include FT_FREETYPE_H

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
  #define ROTATION_FACTOR 2.0f
  #define NEAR_Z_CLIP 0.1f
  #define FAR_Z_CLIP 100.0f
  #define FOV 60.0f
  #define LINE_WIDTH 3

  typedef struct truetype
  {
    GLuint      texture;                                                        // ID handle of the glyph texture.
    glm::ivec2  size;                                                           // Size of glyph.
    glm::ivec2  bearing;                                                        // Offset from baseline to left/top of glyph.
    GLuint      advance;                                                        // Horizontal offset to advance to next glyph.
  } truetype;

  class text
  {
    private:
      int               err;
      unsigned int      i;
      unsigned int      j;

    public:
      text(int num_data);
      ~text();

      char**    data;
      GLfloat   x;                                                              // "x" text position [-1.0 ... 1.0]...
      GLfloat   y;                                                              // "y" text position [-1.0 ... 1.0]...
      GLfloat   sx;                                                             // "sx" character dimension [-1.0 ... 1.0]...
      GLfloat   sy;                                                             // "sy" character dimension [-1.0 ... 1.0]...
      int       size;
      GLuint    vao;
      GLuint    vbo;
  };

  extern  GLFWwindow*				window;                                             // Window handle.
  extern  GLuint 						point_shader;                                       // Point shader program.
  extern  GLuint 						text_shader;                                        // Text shader program.
  extern  GLuint            text_texture;                                       // Text texture.
  extern  GLuint            text_vao;                                           // Text VAO.
  extern  GLuint            text_vbo;                                           // Text VBO.
  extern  GLint             pack_alignment;                                     // OpenGL data pack alignment status.
  extern  glm::mat4					Rotation_matrix;																	  // Rotation matrix.
  extern  glm::mat4 				Translation_matrix;																	// Translation matrix.
  extern  glm::mat4 				Model_matrix;																				// Model matrix.
  extern  glm::mat4 				View_matrix;																				// View matrix.
  extern  glm::mat4 				Projection_matrix;																	// Projection matrix.
  extern  struct truetype   font[128];                                          // Text font.

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// REFRESH ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        screen_refresh();

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// ARCBALL ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  glm::vec3   get_arcball_vector(int x, int y);
  void        arcball();

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// CALLBACKS //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void        mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void        cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void        scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  void        window_refresh_callback(GLFWwindow* window);

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

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// SHADERS ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        init_shaders();

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// SCREEN ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        init_screen();

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// TEXT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        init_text();

#endif
