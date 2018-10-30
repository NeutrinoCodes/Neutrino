/// @file

#ifndef window_hpp
#define window_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class window
  {
    private:
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
      GLFWwindow* glfw_window;                                                  // Window handle.
      int         window_sx;                                                    // Window x-size [px].
      int         window_sy;                                                    // Window y-size [px].
      double      aspect_ratio;                                                 // Window aspect ratio [].
      double      mouse_x;                                                      // Mouse x-coordinate [px].
      double      mouse_y;                                                      // Mouse y-coordinate [px].
      double		  scroll_x;                                                     // Scroll x-coordinate [px].
      double		  scroll_y;                                                     // Scroll y-coordinate [px].
      double		  zoom;                                                         // Zoom coefficient.

      float       q[4];                                                         // Arcball quaternion.
      float       R[16];                                                        // Rotation matrix.
      float       T[16];                                                        // Translation matrix.
      float       V[16];                                                        // View matrix.
      float       P[16];                                                        // Projection matrix.

            window(int window_size_x, int window_size_y, const char* title);
      void  init();                                                             // Window initialization.
      bool  closed();
      void  clear();                                                            // Window clearance.
      void  refresh();                                                          // Window refresh.
      auto  key_pressed(int key, int scancode, int action, int mods)->void;     // Key-pressed trampoline.
      auto  mouse_pressed(int button, int action, int mods)->void;              // Mouse-pressed retpoline
      auto  mouse_moved(double xpos, double ypos)->void;                        // Mouse-moved retpoline.
      auto  mouse_scrolled(double xoffset, double yoffset)->void;               // Mouse-scrolled retpoline.
      void  plot(point4* points, color4* colors, plot_style ps);
      void  print(text4* text);

            ~window();
  };

#endif
