/// @file

#ifndef window_hpp
#define window_hpp

  #include "neutrino.hpp"
  #include "point4.hpp"
  #include "color4.hpp"
  #include "text4.hpp"
  #include "font.hpp"

  #define ZOOM_FACTOR 1.05f                                                     // Mouse wheel zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                                  // Mouse arcball rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                      // Near z-clipping distance [small, but > 0.0].
  #define FAR_Z_CLIP 100.0f                                                     // Far z-clipping distance [big, but < +inf].
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

      // Initial translation vector:
      float             initial_translation[3] = {0.0, 0.0 , -3.0};

      GLuint 						point_shader;                                           // Point shader program.
      GLuint 						text_shader;                                            // Point shader program.

      // OpenGL shader compilation:
      GLuint            compile_shader  (
                                          neutrino*   loc_neutrino,             // Neutrino baseline.
                                          const char* loc_shader_filename,      // Shader file name.
                                          shader_type loc_shader_type           // Shader type.
                                        );

      // OpenGL shader build:
      GLuint            build_shader    (
                                          neutrino*   loc_neutrino,             // Neutrino baseline.
                                          const char* loc_vertex_filename,      // Shader file name.
            															const char* loc_fragment_filename     // Shader type.
                                        );

      // Grasp arcball action:
      void              grasp           (
                                          float*      p,
                                          int         x,
                                          int         y
                                        );

      // Arcball computation:
      void              arcball();

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// CALLBACKS /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Refresh callback:
      static void       refresh_callback        (
      																				    GLFWwindow* loc_window
      														              );

      // Key-pressed callback:
      static void       key_pressed_callback    (
                                                  GLFWwindow* loc_window,
                                                  int         loc_key,
                                                  int         loc_scancode,
                                                  int         loc_action,
                                                  int         loc_mods
                                                );

      // Mouse-pressed callback:
      static void       mouse_pressed_callback  (
                                              		GLFWwindow* loc_window,
              																		int 				loc_button,
                                              		int 				loc_action,
              																		int 				loc_mods
              																	);

      // Mouse-moved callback:
      static void       mouse_moved_callback		(
                                                	GLFWwindow* loc_window,
                                                	double 			loc_xpos,
                                                	double 			loc_ypos
                                                );

      // Mouse-scrolled callback:
      static void       mouse_scrolled_callback	(
                                                  GLFWwindow*	loc_window,
                                                	double 			loc_xoffset,
                                                	double 			loc_yoffset
                                                );

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// RETPOLINES ////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Refresh retpoline:
      void              refresh();

      // Key-pressed retpoline:
      void              key_pressed           (
                                                int           loc_key,
                                                int           loc_scancode,
                                                int           loc_action,
                                                int           loc_mods
                                              );

      // Mouse-pressed retpoline:
      void              mouse_pressed				  (
                                                int           button,
                                              	int           action,
                                              	int           mods
                                              );

      // Mouse-moved retpoline:
      void              mouse_moved						(
                                              	double        xpos,
                                              	double        ypos
                                              );

      // Mmouse-scrolled retpoline:
      void              mouse_scrolled				(
                                              	double        xoffset,
                                              	double        yoffset
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
