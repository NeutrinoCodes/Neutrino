/// @file

#ifndef window_hpp
#define window_hpp

  #include "neutrino.hpp"
  #include "point4.hpp"
  #include "color4.hpp"
  #include "text4.hpp"
  #include "font.hpp"

  #define ZOOM_FACTOR 1.05f                                                     // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                                  // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                      // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                                     // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                             // Field of view [deg].
  #define LINE_WIDTH 3                                                          // Line width [px].

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class window
  {
    private:
      double            mouse_x_old;                                            // Mouse x-coordinate backup [px].
      double            mouse_y_old;                                            // Mouse y-coordinate backup [px].
      bool 			        arcball_on;                                             // Arcball activation flag.

      // Rotation matrix backup:
      float             R_old[16] = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      float             initial_translation[3] = {0.0, 0.0 , -3.0};             // Initial translation vector.

      GLuint 						point_shader;                                           // Point shader program.
      GLuint 						text_shader;                                            // Point shader program.

      // OpenGL shader compilation:
      GLuint            compile_shader  (
                                          neutrino* loc_neutrino,
                                          const char* loc_shader_filename,
                                          shader_type loc_shader_type
                                        );

      // OpenGL shader build:
      GLuint            build_shader    (
                                          neutrino* loc_neutrino,
                                          const char* filename_vertex,
                                          const char* filename_fragment
                                        );

      void              grasp(float* p, int x, int y);                          // Grasp arcball action.
      void              arcball();                                              // Arcball computation.

      // Key-pressed callback:
      inline static auto refresh_callback(GLFWwindow* win)->void
      {
        window* thewindow = static_cast<window*>(glfwGetWindowUserPointer(win));
        thewindow->refresh();
      }

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
      GLFWwindow*       glfw_window;                                            // Window handle.
      const char*       title;                                                  // Window title.
      int               window_size_x;                                          // Window x-size [px].
      int               window_size_y;                                          // Window y-size [px].
      double            aspect_ratio;                                           // Window aspect ratio [].
      double            mouse_x;                                                // Mouse x-coordinate [px].
      double            mouse_y;                                                // Mouse y-coordinate [px].
      double		        scroll_x;                                               // Scroll x-coordinate [px].
      double		        scroll_y;                                               // Scroll y-coordinate [px].
      double		        zoom;                                                   // Zoom coefficient.

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

      // Window initialization:
      void              init            (
                                          neutrino* 	loc_neutrino,
                                          int         loc_window_size_x,        // Window x-size [px].
                                          int         loc_window_size_y,        // Window y-size [px].
                                          const char* loc_title
                                        );

      // Window "closed" function:
      bool              closed();

      // Window "clear" function:
      void              clear();

       // Window "refresh" function:
      void              refresh();

       // Key-pressed retpoline:
      auto              key_pressed     (
                                          int key,
                                          int scancode,
                                          int action,
                                          int mods
                                        )->void;

      // Mouse-pressed retpoline:
      auto              mouse_pressed   (
                                          int button,
                                          int action,
                                          int mods
                                        )->void;

      // Mouse-moved retpoline:
      auto              mouse_moved     (
                                          double xpos,
                                          double ypos
                                        )->void;

      // Mouse-scrolled retpoline:
      auto              mouse_scrolled  (
                                          double xoffset,
                                          double yoffset
                                        )->void;

      // Window "plot" function:
      void              plot            (
                                          point4* points,
                                          color4* colors,
                                          plot_style ps
                                        );

      // Window "print" function:
      void              print           (
                                          text4* text
                                        );

                        ~window();
  };

#endif
