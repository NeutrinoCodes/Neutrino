/// @file

#ifndef window_hpp
#define window_hpp

  #include "neutrino.hpp"
  #include "point4.hpp"
  #include "color4.hpp"
  #include "float4.hpp"
  #include "text4.hpp"
  #include "memory_orb.hpp"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "WINDOW" CLASS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class window
{
private:
  neutrino*       baseline;                                                     // Neutrino baseline.
  bool            orbit_on;                                                     // Orbit activation flag.
  bool            pan_on;                                                       // Pan activation flag.


  // Translation matrix backup:
  float           T_old[16]                 = {1.0, 0.0, 0.0, 0.0,
                                               0.0, 1.0, 0.0, 0.0,
                                               0.0, 0.0, 1.0, 0.0,
                                               0.0, 0.0, 0.0, 1.0};

  // Rotation matrix backup:
  float           R_old[16]                 = {1.0, 0.0, 0.0, 0.0,
                                               0.0, 1.0, 0.0, 0.0,
                                               0.0, 0.0, 1.0, 0.0,
                                               0.0, 0.0, 0.0, 1.0};

  // Rotation quaternion backup:
  float           q_old[4]                  = {1.0, 0.0, 0.0, 0.0};

  // Initial scene position:
  float           initial_scene_position[3] = INITIAL_SCENE_POSITION;

  GLuint          point_shader;                                                 // Point shader program.
  GLuint          text_shader;                                                  // Point shader program.
  projection_mode PR_mode;                                                      // Projection mode.
  // OpenGL shader compilation:
  GLuint      compile_shader (
                              const char* loc_shader_filename,                  // Shader file name.
                              shader_type loc_shader_type                       // Shader type.
                             );
  // OpenGL shader build:
  GLuint      build_shader (
                            const char* loc_vertex_filename,                    // Shader file name.
                            const char* loc_fragment_filename                   // Shader type.
                           );
  // Arcball computation:
  void        arcball (
                       float* p,                                                // Point on unitary ball.
                       double x,                                                // "Near clipping-plane" x-coordinate.
                       double y                                                 // "Near clipping-plane" y-coordinate.
                      );
  // Orbit movement:
  void        orbit ();
  // Grasp computation:
  void        grasp (
                     float  position[3],
                     double x,
                     double y
                    );
  // Pan movement:
  void        pan ();
  // Zoom movement:
  void        zoom ();
  // Plot style:
  void        set_plot_style (
                              plot_style ps,                                    // Plot style.
                              float      view_matrix[16],                       // View matrix.
                              float      projection_matrix[16]                  // Projection matrix.
                             );
  ////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// CALLBACKS /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Refresh callback:
  static void refresh_callback (
                                GLFWwindow* loc_window                          // Window.
                               );
  // Window resize callback:
  static void window_resize_callback (
                                      GLFWwindow* loc_window,                   // Window.
                                      int         loc_x_size,                   // Window x-size [screen coordinates].
                                      int         loc_y_size                    // Window y-size [screen coordinates].
                                     );
  // Framebuffer resize callback:
  static void framebuffer_resize_callback (
                                           GLFWwindow* loc_window,              // Window.
                                           int         loc_x_size,              // Framebuffer x-size [px].
                                           int         loc_y_size               // Framebuffer y-size [px].
                                          );
  // Key-pressed callback:
  static void key_pressed_callback (
                                    GLFWwindow* loc_window,                     // Window.
                                    int         loc_key,                        // Key.
                                    int         loc_scancode,                   // Scancode.
                                    int         loc_action,                     // Action.
                                    int         loc_mods                        // Mods.
                                   );
  // Mouse-pressed callback:
  static void mouse_button_callback (
                                     GLFWwindow* loc_window,                    // Window.
                                     int         loc_button,                    // Button.
                                     int         loc_action,                    // Action.
                                     int         loc_mods                       // Mods.
                                    );
  // Mouse-moved callback:
  static void mouse_moved_callback (
                                    GLFWwindow* loc_window,                     // Window.
                                    double      loc_xpos,                       // Mouse x-position [px].
                                    double      loc_ypos                        // Mouse y-position [px].
                                   );
  // Mouse-scrolled callback:
  static void mouse_scrolled_callback (
                                       GLFWwindow* loc_window,                  // Window.
                                       double      loc_xoffset,                 // Mouse scroll x-offset [px].
                                       double      loc_yoffset                  // Mouse scroll y-offset [px].
                                      );
  ////////////////////////////////////////////////////////////////////////////
  //////////////////////////// PRIVATE RETPOLINES ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Key-pressed retpoline:
  void        key_pressed (
                           int loc_key,                                         // Key.
                           int loc_scancode,                                    // Scancode.
                           int loc_action,                                      // Action.
                           int loc_mods                                         // Mods.
                          );
  // Mouse-pressed retpoline:
  void        mouse_button (
                            int loc_button,                                     // Button.
                            int loc_action,                                     // Action.
                            int loc_mods                                        // Mods.
                           );
  // Mouse-moved retpoline:
  void        mouse_moved (
                           double loc_xpos,                                     // Mouse x-position [px].
                           double loc_ypos                                      // Mouse y-position [px].
                          );
  // Mouse-scrolled retpoline:
  void        mouse_scrolled (
                              double loc_xoffset,                               // Mouse scroll x-offset [px].
                              double loc_yoffset                                // Mouse scroll y-offset [px].
                             );

public:
  GLFWwindow* glfw_window;                                                      // Window handle.
  const char* title;                                                            // Window title.
  int         window_size_x;                                                    // Window x-size [screen coordinates].
  int         window_size_y;                                                    // Window y-size [screen coordinates].
  int         framebuffer_size_x;                                               // Window x-size [px].
  int         framebuffer_size_y;                                               // Window y-size [px].

  double      aspect_ratio;                                                     // Window aspect ratio [].

  double      mouse_x;                                                          // Mouse x-coordinate [px].
  double      mouse_y;                                                          // Mouse y-coordinate [px].

  double      scroll_x;                                                         // Scroll x-coordinate [px].
  double      scroll_y;                                                         // Scroll y-coordinate [px].

  double      orbit_x_old;
  double      orbit_y_old;
  double      orbit_x;
  double      orbit_y;

  double      pan_x_old;
  double      pan_y_old;
  double      pan_x;
  double      pan_y;

  double      zoom_z_old;
  double      zoom_z;                                                           // Zoom coefficient.

  // Arcball quaternion:
  float       q[4]   = {1.0, 0.0, 0.0, 0.0};

  // Euler (Tait-Byran) angles:
  float       roll   = 0.0;
  float       pitch  = 0.0;
  float       yaw    = 0.0;

  // Rotation matrix:
  float       R[16]  = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Translation matrix:
  float       T[16]  = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // View matrix:
  float       V[16]  = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Projection matrix:
  float       P[16]  = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic translation matrix:
  float       TL[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic translation matrix:
  float       TR[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic view matrix:
  float       VL[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic view matrix:
  float       VR[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic projection matrix:
  float       PL[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic projection matrix:
  float       PR[16] = {1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};
  ////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// PUBLIC RETPOLINES ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Clear retpoline:
  void clear ();
  // Refresh retpoline:
  void refresh ();
  // Window resize retpoline:
  void window_resize (
                      int loc_x_size,                                           // Window x-size [screen coordinates].
                      int loc_y_size                                            // Window y-size [screen coordinates].
                     );
  // Framebuffer resize retpoline:
  void framebuffer_resize (
                           int loc_x_size,                                      // Framebuffer x-size [px].
                           int loc_y_size                                       // Framebuffer y-size [px].
                          );
  // Event polling retpoline:
  void poll_events ();

  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// PUBLIC METHODS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  window();
  // Window initialization:
  void init (
             neutrino*   loc_baseline,
             int         loc_window_size_x,                                     // Window x-size [px].
             int         loc_window_size_y,                                     // Window y-size [px].
             const char* loc_title
            );
  // Window "closed" function:
  bool closed ();
  // Window "plot" function:
  void plot (
             point4*    points,
             color4*    colors,
             plot_style ps
            );
  // Window "print" function:
  void print (
              text4* text
             );
  // Window "cockpit_AI" function:
  void cockpit_AI (
                   memory_orb* controller
                  );

  ~window();


};

#endif
