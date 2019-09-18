/// @file

#ifndef opengl_hpp
#define opengl_hpp

  #include "neutrino.hpp"
  #include "shader.hpp"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "OPENGL" CLASS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class opengl
{
private:
  neutrino*        baseline;                                                                        // Neutrino baseline.
  bool             orbit_on;                                                                        // Orbit activation flag.
  bool             pan_on;                                                                          // Pan activation flag.
  GLFWgamepadstate gamepad;                                                                         // Gamepad state.

  // Translation matrix backup:
  float            T_mat_old[16]             = {1.0, 0.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0, 0.0,
                                                0.0, 0.0, 1.0, 0.0,
                                                0.0, 0.0, 0.0, 1.0};

  // Rotation matrix backup:
  float            R_mat_old[16]             = {1.0, 0.0, 0.0, 0.0,
                                                0.0, 1.0, 0.0, 0.0,
                                                0.0, 0.0, 1.0, 0.0,
                                                0.0, 0.0, 0.0, 1.0};

  // Rotation quaternion backup:
  float            q_old[4]                  = {1.0, 0.0, 0.0, 0.0};

  // Initial scene position:
  float            initial_scene_position[3] = NU_INITIAL_SCENE_POSITION;

  GLuint           point_shader;                                                                    // Point shader program.
  GLuint           voxel_shader;                                                                    // Voxel shader program.
  GLuint           wireframe_shader;                                                                // Wireframe shader program.
  GLuint           shaded_shader;                                                                   // Shaded shader program.
  GLuint           text_shader;                                                                     // Point shader program.
  projection_mode  PR_mode;                                                                         // Projection mode.
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// PRIVATE METHODS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OpenGL shader compilation:
  GLuint      compile_shader (
                              std::string loc_shader_filename,                                      // Shader file name.
                              shader_type loc_shader_type                                           // Shader type.
                             );
  // OpenGL shader build:
  GLuint      build_shader (
                            std::string loc_vertex_filename,                                        // Vertex shader file name.
                            std::string loc_geometry_filename,                                      // Geometry shader file name.
                            std::string loc_fragment_filename                                       // Fragment shader file name.
                           );
  // Plot style:
  void        set_shader (
                          shader* loc_shader,                                                       // Shader.
                          float   view_matrix[16],                                                  // View matrix.
                          float   projection_matrix[16]                                             // Projection matrix.
                         );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CALLBACKS ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Refresh callback:
  static void refresh_callback (
                                GLFWwindow* loc_window                                              // Window.
                               );
  // Window resize callback:
  static void window_resize_callback (
                                      GLFWwindow* loc_window,                                       // Window.
                                      int         loc_x_size,                                       // Window x-size [screen coordinates].
                                      int         loc_y_size                                        // Window y-size [screen coordinates].
                                     );
  // Framebuffer resize callback:
  static void framebuffer_resize_callback (
                                           GLFWwindow* loc_window,                                  // Window.
                                           int         loc_x_size,                                  // Framebuffer x-size [px].
                                           int         loc_y_size                                   // Framebuffer y-size [px].
                                          );
  // Key-pressed callback:
  static void key_pressed_callback (
                                    GLFWwindow* loc_window,                                         // Window.
                                    int         loc_key,                                            // Key.
                                    int         loc_scancode,                                       // Scancode.
                                    int         loc_action,                                         // Action.
                                    int         loc_mods                                            // Mods.
                                   );
  // Mouse-pressed callback:
  static void mouse_button_callback (
                                     GLFWwindow* loc_window,                                        // Window.
                                     int         loc_button,                                        // Button.
                                     int         loc_action,                                        // Action.
                                     int         loc_mods                                           // Mods.
                                    );
  // Mouse-moved callback:
  static void mouse_moved_callback (
                                    GLFWwindow* loc_window,                                         // Window.
                                    double      loc_xpos,                                           // Mouse x-position [px].
                                    double      loc_ypos                                            // Mouse y-position [px].
                                   );
  // Mouse-scrolled callback:
  static void mouse_scrolled_callback (
                                       GLFWwindow* loc_window,                                      // Window.
                                       double      loc_xoffset,                                     // Mouse scroll x-offset [px].
                                       double      loc_yoffset                                      // Mouse scroll y-offset [px].
                                      );
  // Joystick-connected callback:
  void        joystick_connected_callback (
                                           int loc_joystick,                                        // Joystick.
                                           int loc_event                                            // Joystick-connected event.
                                          );
  ////////////////////////////////////////////////////////////////////////////
  //////////////////////////// PRIVATE RETPOLINES ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Key-pressed retpoline:
  void        key_pressed (
                           int loc_key,                                                             // Key.
                           int loc_scancode,                                                        // Scancode.
                           int loc_action,                                                          // Action.
                           int loc_mods                                                             // Mods.
                          );
  // Mouse-pressed retpoline:
  void        mouse_button (
                            int loc_button,                                                         // Button.
                            int loc_action,                                                         // Action.
                            int loc_mods                                                            // Mods.
                           );
  // Mouse-moved retpoline:
  void        mouse_moved (
                           double loc_xpos,                                                         // Mouse x-position [px].
                           double loc_ypos                                                          // Mouse y-position [px].
                          );
  // Mouse-scrolled retpoline:
  void        mouse_scrolled (
                              double loc_xoffset,                                                   // Mouse scroll x-offset [px].
                              double loc_yoffset                                                    // Mouse scroll y-offset [px].
                             );

public:
  GLFWwindow* glfw_window;                                                                          // Window handle.
  std::string title;                                                                                // Window title.
  int         window_size_x;                                                                        // Window x-size [screen coordinates].
  int         window_size_y;                                                                        // Window y-size [screen coordinates].
  int         framebuffer_size_x;                                                                   // Window x-size [px].
  int         framebuffer_size_y;                                                                   // Window y-size [px].
  float       aspect_ratio;                                                                         // Window aspect ratio [].

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// GAMEPAD ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // BUTTONS:
  bool        button_A;
  bool        button_B;
  bool        button_X;
  bool        button_Y;
  bool        button_CROSS;                                                                         // = A;
  bool        button_CIRCLE;                                                                        // = B;
  bool        button_SQUARE;                                                                        // = X;
  bool        button_TRIANGLE;                                                                      // = Y;
  bool        button_LEFT_BUMPER;
  bool        button_RIGHT_BUMPER;
  bool        button_BACK;
  bool        button_START;
  bool        button_GUIDE;
  bool        button_LEFT_THUMB;
  bool        button_RIGHT_THUMB;
  bool        button_DPAD_UP;
  bool        button_DPAD_RIGHT;
  bool        button_DPAD_DOWN;
  bool        button_DPAD_LEFT;

  // AXES:
  double      axis_RIGHT_X;
  double      axis_RIGHT_Y;
  double      axis_RIGHT_TRIGGER;
  double      axis_LEFT_X;
  double      axis_LEFT_Y;
  double      axis_LEFT_TRIGGER;
  // Orbit movement:
  void orbit (
              float loc_orbit_x,                                                                    // "Near clipping-plane" x-coordinates.
              float loc_orbit_y,                                                                    // "Near clipping-plane" y-coordinates.
              float loc_orbit_rate,                                                                 // Orbit angular rate coefficient [rev/s].
              float loc_orbit_deadzone,                                                             // Orbit deadzone threshold coefficient.
              float loc_orbit_decaytime                                                             // Orbit low pass decay time [s].
             );

  float       orbit_x;
  float       orbit_y;
  float       orbit_x_old;
  float       orbit_y_old;
  // Pan movement:
  void pan (
            float loc_pan_x,                                                                        // World x-pan.
            float loc_pan_y,                                                                        // World y-pan.
            float loc_pan_z,                                                                        // World z-pan.
            float loc_pan_rate,                                                                     // Pan rate [units/s].
            float loc_pan_deadzone,                                                                 // Pan deadzone threshold coefficient.
            float loc_pan_decaytime                                                                 // Pan low pass decay time [s].
           );
  float       pan_x;
  float       pan_y;
  float       pan_z;
  float       pan_x_old;
  float       pan_y_old;
  float       pan_z_old;

  bool        mouse_left;
  bool        mouse_right;

  double      mouse_x;                                                                              // Mouse x-coordinate [px].
  double      mouse_y;                                                                              // Mouse y-coordinate [px].

  double      scroll_x;                                                                             // Scroll x-coordinate [px].
  double      scroll_y;                                                                             // Scroll y-coordinate [px].

  // Arcball quaternion:
  float       q[4]       = {1.0, 0.0, 0.0, 0.0};

  // Euler (Tait-Byran) angles:
  float       roll       = 0.0;
  float       pitch      = 0.0;
  float       yaw        = 0.0;

  // Rotation matrix:
  float       R_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Translation matrix:
  float       T_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // View matrix:
  float       V_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Projection matrix:
  float       P_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic translation matrix:
  float       TL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic translation matrix:
  float       TR_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic view matrix:
  float       VL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic view matrix:
  float       VR_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Left eye stereoscopic projection matrix:
  float       PL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};

  // Right eye stereoscopic projection matrix:
  float       PR_mat[16] = {1.0, 0.0, 0.0, 0.0,
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
                      int loc_x_size,                                                               // Window x-size [screen coordinates].
                      int loc_y_size                                                                // Window y-size [screen coordinates].
                     );
  // Framebuffer resize retpoline:
  void framebuffer_resize (
                           int loc_x_size,                                                          // Framebuffer x-size [px].
                           int loc_y_size                                                           // Framebuffer y-size [px].
                          );
  // Event polling retpoline:
  void poll_events ();

  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// PUBLIC METHODS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  opengl();
  // Window initialization:
  void init (
             neutrino*   loc_baseline,
             int         loc_window_size_x,                                                         // Window x-size [px].
             int         loc_window_size_y,                                                         // Window y-size [px].
             std::string loc_title
            );
  // Window close function:
  void close ();
  // Window "closed" function:
  bool closed ();
  // Window "plot" function:
  void plot (
             shader* loc_shader                                                                     // OpenGL shader.
            );

  ~opengl();
};

#endif
