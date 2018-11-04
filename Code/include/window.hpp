/// @file

#ifndef window_hpp
#define window_hpp

  #define ZOOM_FACTOR 1.05f                                               // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                            // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                               // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                       // Field of view [deg].
  #define LINE_WIDTH 3                                                    // Line width [px].

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class window
  {
    private:
      double            mouse_x_old;                                                  // Mouse x-coordinate backup [px].
      double            mouse_y_old;                                                  // Mouse y-coordinate backup [px].
      bool 			        arcball_on;                                                   // Arcball activation flag.

      // Rotation matrix backup:
      float             R_old[16] = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      float             initial_translation[3] = {0.0, 0.0 , -3.0};                   // Initial translation vector.

      GLuint 						point_shader;                                                 // Point shader program.
      GLuint 						text_shader;                                                  // Point shader program.

      void grasp(float* p, int x, int y);                                             // Grasp arcball action.
      void arcball();                                                                 // Arcball computation.

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
      GLFWwindow*       glfw_window;                                                  // Window handle.
      int               window_sx;                                                    // Window x-size [px].
      int               window_sy;                                                    // Window y-size [px].
      double            aspect_ratio;                                                 // Window aspect ratio [].
      double            mouse_x;                                                      // Mouse x-coordinate [px].
      double            mouse_y;                                                      // Mouse y-coordinate [px].
      double		        scroll_x;                                                     // Scroll x-coordinate [px].
      double		        scroll_y;                                                     // Scroll y-coordinate [px].
      double		        zoom;                                                         // Zoom coefficient.

      // Arcball quaternion:
      float             q[4]      = {1.0, 0.0, 0.0, 0.0};

      // Rotation matrix:
      float             R[16]     = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      // Translation matrix:
      float             T[16]     = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      // View matrix:
      float             V[16]     = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      // Projection matrix:
      float             P[16]     = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

                        window();

      void              init            (
                                          int window_size_x,
                                          int window_size_y,
                                          const char* title
                                        );                                            // Window initialization.

      bool              closed();                                                     // Window closure.
      void              clear();                                                      // Window clearance.
      void              refresh();                                                    // Window refresh.

      auto              key_pressed     (
                                          int key,
                                          int scancode,
                                          int action,
                                          int mods
                                        )->void;                                      // Key-pressed trampoline.

      auto              mouse_pressed   (
                                          int button,
                                          int action,
                                          int mods
                                        )->void;                                      // Mouse-pressed retpoline

      auto              mouse_moved     (
                                          double xpos,
                                          double ypos
                                        )->void;                                      // Mouse-moved retpoline.

      auto              mouse_scrolled  (
                                          double xoffset,
                                          double yoffset
                                        )->void;                                      // Mouse-scrolled retpoline.

      void              plot            (
                                          point4* points,
                                          color4* colors,
                                          plot_style ps
                                        );

      void              print           (
                                          text4* text
                                        );

                        ~window();
  };

#endif