/// @file

#ifndef window_hpp
#define window_hpp

  #include "neutrino.hpp"
  #include "point4.hpp"
  #include "color4.hpp"
  #include "float4.hpp"
  #include "text4.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class window
  {
    private:
      neutrino*         baseline;                                               // Neutrino baseline.
      double            mouse_x_old;                                            // Mouse x-coordinate backup [px].
      double            mouse_y_old;                                            // Mouse y-coordinate backup [px].
      bool 			        arcball_on;                                             // Arcball activation flag.

      // Rotation matrix backup:
      float             R_old[16] = {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0};

      // Initial translation vector:
      float             initial_translation[3] = {0.0, 0.0 , -3.0};

      GLuint 						point_shader;                                           // Point shader program.
      GLuint 						text_shader;                                            // Point shader program.

      // OpenGL shader compilation:
      GLuint            compile_shader  (
                                          const char* loc_shader_filename,      // Shader file name.
                                          shader_type loc_shader_type           // Shader type.
                                        );

      // OpenGL shader build:
      GLuint            build_shader    (
                                          const char* loc_vertex_filename,      // Shader file name.
            															const char* loc_fragment_filename     // Shader type.
                                        );

      // Grasp arcball action:
      void              grasp           (
                                          float*      p,                        // Point on unitary ball.
                                          int         x,                        // "Near clipping-plane" x-coordinate.
                                          int         y                         // "Near clipping-plane" y-coordinate.
                                        );

      // Arcball computation:
      void              arcball();

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// CALLBACKS /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Refresh callback:
      static void       refresh_callback        (
      																				    GLFWwindow* loc_window        // Window.
      														              );

      // Resize callback:
      static void       resize_callback	        (
                                                  GLFWwindow*	loc_window,       // Window.
                                                  int         loc_x_size,       // Window x-size [px].
                                                  int         loc_y_size        // Window y-size [px].
                                                );

      // Key-pressed callback:
      static void       key_pressed_callback    (
                                                  GLFWwindow* loc_window,       // Window.
                                                  int         loc_key,          // Key.
                                                  int         loc_scancode,     // Scancode.
                                                  int         loc_action,       // Action.
                                                  int         loc_mods          // Mods.
                                                );

      // Mouse-pressed callback:
      static void       mouse_pressed_callback  (
                                              		GLFWwindow* loc_window,       // Window.
              																		int 				loc_button,       // Button.
                                              		int 				loc_action,       // Action.
              																		int 				loc_mods          // Mods.
              																	);

      // Mouse-moved callback:
      static void       mouse_moved_callback		(
                                                	GLFWwindow* loc_window,       // Window.
                                                	double 			loc_xpos,         // Mouse x-position [px].
                                                	double 			loc_ypos          // Mouse y-position [px].
                                                );

      // Mouse-scrolled callback:
      static void       mouse_scrolled_callback	(
                                                  GLFWwindow*	loc_window,       // Window.
                                                	double 			loc_xoffset,      // Mouse scroll x-offset [px].
                                                	double 			loc_yoffset       // Mouse scroll y-offset [px].
                                                );

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////// PRIVATE RETPOLINES ////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Key-pressed retpoline:
      void              key_pressed           (
                                                int           loc_key,          // Key.
                                                int           loc_scancode,     // Scancode.
                                                int           loc_action,       // Action.
                                                int           loc_mods          // Mods.
                                              );

      // Mouse-pressed retpoline:
      void              mouse_pressed				  (
                                                int           loc_button,       // Button.
                                              	int           loc_action,       // Action.
                                              	int           loc_mods          // Mods.
                                              );

      // Mouse-moved retpoline:
      void              mouse_moved						(
                                              	double        loc_xpos,         // Mouse x-position [px].
                                              	double        loc_ypos          // Mouse y-position [px].
                                              );

      // Mouse-scrolled retpoline:
      void              mouse_scrolled				(
                                              	double        loc_xoffset,      // Mouse scroll x-offset [px].
                                              	double        loc_yoffset       // Mouse scroll y-offset [px].
                                              );

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

      ////////////////////////////////////////////////////////////////////////////
      ///////////////////////////// PUBLIC RETPOLINES ////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Clear retpoline:
      void              clear();

      // Refresh retpoline:
      void              refresh();

      // Resize retpoline:
      void              resize                  (
                                                  int         loc_x_size,       // Window x-size [px].
                                                  int         loc_y_size        // Window y-size [px].
                                                );

      // Event polling retpoline:
      void              poll_events();

      ////////////////////////////////////////////////////////////////////////////
      /////////////////////////////// PUBLIC METHODS /////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
                        window();

      // Window initialization:
      void              init            (
                                          neutrino* 	loc_baseline,
                                          int         loc_window_size_x,        // Window x-size [px].
                                          int         loc_window_size_y,        // Window y-size [px].
                                          const char* loc_title
                                        );

      // Window "closed" function:
      bool              closed();

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
