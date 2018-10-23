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
    public:
              opengl();
      void    init();                                                           // OpenGL initialization.
              ~opengl();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class window
  {
    private:
      GLFWwindow*			    glfw_window;                                          // Window handle.
      double              mouse_x_old;                                          // Mouse x-coordinate backup [px].
      double              mouse_y_old;                                          // Mouse y-coordinate backup [px].
      bool 			          arcball_on;                                           // Arcball activation flag.
      float               R_old[16];                                            // Rotation matrix backup.
      float               initial_translation[3];                               // Initial translation vector.

      GLuint 						  point_shader;                                         // Point shader program.
      GLuint 						  text_shader;                                          // Point shader program.

      void grasp(float* p, int x, int y);                                       // Grasp arcball action.
      void arcball();                                                           // Arcball computation.

      // Key-pressed callback:
      inline static auto key_pressed_callback(GLFWwindow* win, int key, int scancode, int action, int mods)->void
      {
        window* thewindow = static_cast<window*>(glfwGetWindowUserPointer(win));
        thewindow->key_pressed(key, scancode, action, mods);
      }

      // Mouse-pressed callback:
      inline static auto mouse_pressed_callback(GLFWwindow* win, int button, int action, int mods)->void
      {
        window* thewindow = static_cast<window*>(glfwGetWindowUserPointer(win));
        thewindow->mouse_pressed(button, action, mods);
      }

      // Mouse-moved callback:
      inline static auto mouse_moved_callback(GLFWwindow* win, double xpos, double ypos)->void
      {
        window* thewindow = static_cast<window*>(glfwGetWindowUserPointer(win));
        thewindow->mouse_moved(xpos, ypos);
      }

      // Mouse-scrolled callback:
      inline static auto mouse_scrolled_callback(GLFWwindow* win, double xoffset, double yoffset)->void
      {
        window* thewindow = static_cast<window*>(glfwGetWindowUserPointer(win));
        thewindow->mouse_scrolled(xoffset, yoffset);
      }

    public:
      int       window_sx;                                                      // Window x-size [px].
      int       window_sy;                                                      // Window y-size [px].
      double    aspect_ratio;                                                   // Window aspect ratio [].
      double    mouse_x;                                                        // Mouse x-coordinate [px].
      double    mouse_y;                                                        // Mouse y-coordinate [px].
      double		scroll_x;                                                       // Scroll x-coordinate [px].
      double		scroll_y;                                                       // Scroll y-coordinate [px].
      double		zoom;                                                           // Zoom coefficient.

      float     q[4];                                                           // Arcball quaternion.
      float     R[16];                                                          // Rotation matrix.
      float     T[16];                                                          // Translation matrix.
      float     V[16];                                                          // View matrix.
      float     P[16];                                                          // Projection matrix.

            window(int window_size_x, int window_size_y, const char* title);
      void  init();                                                             // Window initialization.
      bool  closed();
      void  clear();                                                            // Window clearance.
      void  refresh();                                                          // Window refresh.
      auto  key_pressed(int key, int scancode, int action, int mods)->void;     // Key-pressed trampoline.
      auto  mouse_pressed(int button, int action, int mods)->void;              // Mouse-pressed retpoline
      auto  mouse_moved(double xpos, double ypos)->void;                        // Mouse-moved retpoline.
      auto  mouse_scrolled(double xoffset, double yoffset)->void;               // Mouse-scrolled retpoline.
            ~window();
  };

#endif
