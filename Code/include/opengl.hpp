/// @file   opengl.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declaration of the "opengl" class.

#ifndef opengl_hpp
#define opengl_hpp

  #include "neutrino.hpp"
  #include "shader.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "opengl" class //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class opengl
{
private:
  neutrino*        baseline;                                                                        ///< @brief **Neutrino baseline.**
  GLFWgamepadstate gamepad;                                                                         ///< @brief **Gamepad state.**
  bool             orbit_on;                                                                        ///< @brief **Orbit activation flag.**
  float            orbit_x;                                                                         ///< @brief **Orbit x movement (current).**
  float            orbit_y;                                                                         ///< @brief **Orbit y movement (current).**
  float            orbit_x_old;                                                                     ///< @brief **Orbit x movement (previous).**
  float            orbit_y_old;                                                                     ///< @brief **Orbit y movement (previous).**
  bool             pan_on;                                                                          ///< @brief **Pan activation flag.**
  float            pan_x;                                                                           ///< @brief **Pan x movement (current).**
  float            pan_y;                                                                           ///< @brief **Pan y movement (current).**
  float            pan_z;                                                                           ///< @brief **Pan z movement (current).**
  float            pan_x_old;                                                                       ///< @brief **Pan x movement (previous).**
  float            pan_y_old;                                                                       ///< @brief **Pan y movement (previous).**
  float            pan_z_old;                                                                       ///< @brief **Pan z movement (previous).**

  float            T_mat_old[16]             = {1.0f, 0.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 0.0f,
                                                0.0f, 0.0f, 1.0f, 0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f};                            ///< @brief **Translation matrix backup.**

  float            R_mat_old[16]             = {1.0f, 0.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 0.0f,
                                                0.0f, 0.0f, 1.0f, 0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f};                            ///< @brief **Rotation matrix backup.**

  float            q_old[4]                  = {1.0f, 0.0f, 0.0f, 0.0f};                            ///< @brief **Rotation quaternion backup.**

  float            initial_scene_position[3] = {0.0f, 0.0f, 0.0f};                                  ///< @brief **Initial scene position.**

  GLuint           point_shader;                                                                    ///< @brief **Point shader program.**
  GLuint           voxel_shader;                                                                    ///< @brief **Voxel shader program.**
  GLuint           wireframe_shader;                                                                ///< @brief **Wireframe shader program.**
  GLuint           shaded_shader;                                                                   ///< @brief **Shaded shader program.**
  GLuint           text_shader;                                                                     ///< @brief **Point shader program.**
  projection_mode  PR_mode;                                                                         ///< @brief **Projection mode.**

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// PRIVATE METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenGL shader set method.**
  /// @details It sets an OpenGL shader.
  void set_shader (
                   shader* loc_shader,                                                              ///< Shader.
                   float   view_matrix[16],                                                         ///< View matrix.
                   float   projection_matrix[16]                                                    ///< Projection matrix.
                  );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// CALLBACKS //////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **Refresh callback.**
  /// @details It is automatically called by GLFW when the window needs to be refreshed.
  static void refresh_callback (
                                GLFWwindow* loc_window                                              ///< Window.
                               );

  /// @brief **Window resize callback.**
  /// @details It is automatically called by GLFW when the window needs to be resized.
  static void window_resize_callback (
                                      GLFWwindow* loc_window,                                       ///< Window.
                                      int         loc_x_size,                                       ///< Window x-size [screen coordinates].
                                      int         loc_y_size                                        ///< Window y-size [screen coordinates].
                                     );

  /// @brief **Framebuffer resize callback.**
  /// @details It is automatically called by GLFW when the framebuffer of the window needs to be
  /// resized.
  static void framebuffer_resize_callback (
                                           GLFWwindow* loc_window,                                  ///< Window.
                                           int         loc_x_size,                                  ///< Framebuffer x-size [px].
                                           int         loc_y_size                                   ///< Framebuffer y-size [px].
                                          );

  /// @brief **Key-pressed callback.**
  /// @details It is automatically called by GLFW when a key on the keyboard has been pressed.
  static void key_pressed_callback (
                                    GLFWwindow* loc_window,                                         ///< Window.
                                    int         loc_key,                                            ///< Key.
                                    int         loc_scancode,                                       ///< Scancode.
                                    int         loc_action,                                         ///< Action.
                                    int         loc_mods                                            ///< Mods.
                                   );

  /// @brief **Mouse-pressed callback.**
  /// @details It is automatically called by GLFW when a button on the mouse has been pressed.
  static void mouse_button_callback (
                                     GLFWwindow* loc_window,                                        ///< Window.
                                     int         loc_button,                                        ///< Button.
                                     int         loc_action,                                        ///< Action.
                                     int         loc_mods                                           ///< Mods.
                                    );

  /// @brief **Mouse-moved callback.**
  /// @details It is automatically called by GLFW when the mouse has been moved.
  static void mouse_moved_callback (
                                    GLFWwindow* loc_window,                                         ///< Window.
                                    double      loc_xpos,                                           ///< Mouse x-position [px].
                                    double      loc_ypos                                            ///< Mouse y-position [px].
                                   );

  /// @brief **Mouse-scrolled callback.**
  /// @details It is automatically called by GLFW when the mouse has been scrolled.
  static void mouse_scrolled_callback (
                                       GLFWwindow* loc_window,                                      ///< Window.
                                       double      loc_xoffset,                                     ///< Mouse scroll x-offset [px].
                                       double      loc_yoffset                                      ///< Mouse scroll y-offset [px].
                                      );

  /// @brief **Joystick-connected callback.**
  /// @details It is automatically called by GLFW when a joystick has been connected.
  void        joystick_connected_callback (
                                           int loc_joystick,                                        ///< Joystick.
                                           int loc_event                                            ///< Joystick-connected event.
                                          );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// PRIVATE RETPOLINES ///////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **Key-pressed retpoline.**
  /// @details It is invoked by the @link key_pressed_callback @endlink when the latter one is
  /// automatically called by GLFW.
  void key_pressed (
                    int loc_key,                                                                    ///< Key.
                    int loc_scancode,                                                               ///< Scancode.
                    int loc_action,                                                                 ///< Action.
                    int loc_mods                                                                    ///< Mods.
                   );

  /// @brief **Mouse-pressed retpoline.**
  /// @details It is invoked by the @link mouse_button_callback @endlink when the latter one is
  /// automatically called by GLFW.
  void mouse_button (
                     int loc_button,                                                                ///< Button.
                     int loc_action,                                                                ///< Action.
                     int loc_mods                                                                   ///< Mods.
                    );

  /// @brief **Mouse-moved retpoline.**
  /// @details It is invoked by the @link mouse_moved_callback @endlink when the latter one is
  /// automatically called by GLFW.
  void mouse_moved (
                    double loc_xpos,                                                                ///< Mouse x-position [px].
                    double loc_ypos                                                                 ///< Mouse y-position [px].
                   );

  /// @brief **Mouse-scrolled retpoline.**
  /// @details It is invoked by the @link mouse_button_scrolled @endlink when the latter one is
  /// automatically called by GLFW.
  void mouse_scrolled (
                       double loc_xoffset,                                                          ///< Mouse scroll x-offset [px].
                       double loc_yoffset                                                           ///< Mouse scroll y-offset [px].
                      );

public:
  GLFWwindow* glfw_window;                                                                          ///< @brief **Window handle.**
  std::string title;                                                                                ///< @brief **Window title.**
  int         window_size_x;                                                                        ///< @brief **Window x-size [screen coordinates].**
  int         window_size_y;                                                                        ///< @brief **Window y-size [screen coordinates].**
  int         framebuffer_size_x;                                                                   ///< @brief **Window x-size [px].**
  int         framebuffer_size_y;                                                                   ///< @brief **Window y-size [px].**
  float       aspect_ratio;                                                                         ///< @brief **Window aspect ratio [].**

  /// @details Quaternion used in the implementation of an [arcball]
  /// (https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball) pointing the
  /// current rotation of the view.
  float       q[4]       = {1.0, 0.0, 0.0, 0.0};                                                    ///< @brief **Arcball quaternion.**
  float       roll       = 0.0;                                                                     ///< @brief **Euler (Tait-Byran) "roll" view angle [rad].**
  float       pitch      = 0.0;                                                                     ///< @brief **Euler (Tait-Byran) "pitch" view angle [rad].**
  float       yaw        = 0.0;                                                                     ///< @brief **Euler (Tait-Byran) "yaw" view angle [rad].**

  float       R_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Rotation matrix.**

  float       T_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Translation matrix.**

  /// @details OpenGL [view matrix]
  /// (https://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/).
  /// @f$ V = T \cdot R @f$
  float       V_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **View matrix.**

  /// @details Monoscopic [perspective]
  /// (https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix)
  /// projection matrix.
  float       P_mat[16]  = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Perspective projection matrix.**

  /// @details To be used in stereoscopic vision modality.
  float       TL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Left eye stereoscopic translation matrix.**

  /// @details To be used in stereoscopic vision modality.
  float       TR_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Right eye stereoscopic translation matrix.**

  /// @details To be used in stereoscopic vision modality.
  /// @f$ VL = TL \cdot V @f$
  float       VL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Left eye stereoscopic view matrix.**

  /// @details To be used in stereoscopic vision modality.
  /// @f$ VR = TR \cdot V @f$
  float       VR_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief  **Right eye stereoscopic view matrix.**

  /// @details [Perspective]
  /// (https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix)
  /// projection matrix to be used in stereoscopic vision modality for the left eye.
  float       PL_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Left eye stereoscopic perspective projection matrix.**

  /// @details [Perspective]
  /// (https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix)
  /// projection matrix to be used in stereoscopic vision modality for the right eye.
  float       PR_mat[16] = {1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0};                                                    ///< @brief **Right eye stereoscopic perspective projection matrix.**

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////// GAMEPAD //////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // BUTTONS:
  bool        button_A;                                                                             ///< @brief **Button "A".**
  bool        button_B;                                                                             ///< @brief **Button "B".**
  bool        button_X;                                                                             ///< @brief **Button "X".**
  bool        button_Y;                                                                             ///< @brief **Button "Y".**
  bool        button_CROSS;                                                                         ///< @brief **Button "CROSS" = "A".**
  bool        button_CIRCLE;                                                                        ///< @brief **Button "CIRCLE" = "B".**
  bool        button_SQUARE;                                                                        ///< @brief **Button "SQUARE" = "X".**
  bool        button_TRIANGLE;                                                                      ///< @brief **Button "TRIANGLE" = "Y".**
  bool        button_LEFT_BUMPER;                                                                   ///< @brief **Button "LEFT BUMPER".**
  bool        button_RIGHT_BUMPER;                                                                  ///< @brief **Button "RIGHT BUMPER".**
  bool        button_BACK;                                                                          ///< @brief **Button "BACK".**
  bool        button_START;                                                                         ///< @brief **Button "START".**
  bool        button_GUIDE;                                                                         ///< @brief **Button "GUIDE".**
  bool        button_LEFT_THUMB;                                                                    ///< @brief **Button "LEFT THUMB".**
  bool        button_RIGHT_THUMB;                                                                   ///< @brief **Button "RIGHT THUMB".**
  bool        button_DPAD_UP;                                                                       ///< @brief **Button "DPAD UP".**
  bool        button_DPAD_RIGHT;                                                                    ///< @brief **Button "DPAD RIGHT".**
  bool        button_DPAD_DOWN;                                                                     ///< @brief **Button "DPAD DOWN".**
  bool        button_DPAD_LEFT;                                                                     ///< @brief **Button "DPAD LEFT".**

  // AXES:
  float       axis_RIGHT_X;                                                                         ///< @brief **Axis "RIGHT X".**
  float       axis_RIGHT_Y;                                                                         ///< @brief **Axis "RIGHT Y".**
  float       axis_RIGHT_TRIGGER;                                                                   ///< @brief **Axis "RIGHT TRIGGER".**
  float       axis_LEFT_X;                                                                          ///< @brief **Axis "LEFT X".**
  float       axis_LEFT_Y;                                                                          ///< @brief **Axis "LEFT Y".**
  float       axis_LEFT_TRIGGER;                                                                    ///< @brief **Axis "LEFT TRIGGER".**

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////// MOUSE ///////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  bool        mouse_LEFT;                                                                           ///< @brief **Mouse "LEFT" button.**
  bool        mouse_RIGHT;                                                                          ///< @brief **Mouse "RIGHT" button.**

  double      mouse_X;                                                                              ///< @brief **Mouse x-coordinate [px].**
  double      mouse_Y;                                                                              ///< @brief **Mouse y-coordinate [px].**

  double      scroll_X;                                                                             ///< @brief **Mouse scroll x-coordinate [px].**
  double      scroll_Y;                                                                             ///< @brief **Mouse scroll y-coordinate [px].**

  /// @brief **Class constructor.**
  /// @details It does nothing.
  opengl();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// PUBLIC METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **GUI initialization.**
  /// @details Initializes GLFW, GLAD and OpenGL contexts.
  void init (
             neutrino*   loc_baseline,
             int         loc_window_size_x,                                                         ///< Window x-size [px].
             int         loc_window_size_y,                                                         ///< Window y-size [px].
             std::string loc_title,                                                                 ///< Windows title.
             float       loc_orbit_x_initial,                                                       ///< Initial "near clipping-plane" x-coordinate.
             float       loc_orbit_y_initial,                                                       ///< Initial "near clipping-plane" y-coordinate.
             float       loc_pan_x_initial,                                                         ///< Initial pan-x coordinate.
             float       loc_pan_y_initial,                                                         ///< Initial pan-x coordinate.
             float       loc_pan_z_initial                                                          ///< Initial pan-x coordinate.
            );

  /// @brief **GUI poll events function.**
  /// @details **Polls GLFW events.** To be inkoved by the user.
  void poll_events ();

  /// @brief **Orbit movement.**
  /// @details Rotates the view matrix according to an orbit movement.
  void orbit (
              float loc_orbit_x,                                                                    ///< "Near clipping-plane" x-coordinates.
              float loc_orbit_y,                                                                    ///< "Near clipping-plane" y-coordinates.
              float loc_orbit_rate,                                                                 ///< Orbit angular rate coefficient [rev/s].
              float loc_orbit_deadzone,                                                             ///< Orbit deadzone threshold coefficient.
              float loc_orbit_decaytime                                                             ///< Orbit low pass decay time [s].
             );

  /// @brief **Pan movement.**
  /// @details Translates the view matrix according to a pan movement.
  void pan (
            float loc_pan_x,                                                                        ///< World x-pan.
            float loc_pan_y,                                                                        ///< World y-pan.
            float loc_pan_z,                                                                        ///< World z-pan.
            float loc_pan_rate,                                                                     ///< Pan rate [units/s].
            float loc_pan_deadzone,                                                                 ///< Pan deadzone threshold coefficient.
            float loc_pan_decaytime                                                                 ///< Pan low pass decay time [s].
           );

  /// @brief **GUI close function.**
  /// @details Closes the GUI. To be invoked by the user.
  void close ();

  /// @brief **GUI "closed" function.**
  /// @details Checks whether the GUI is closed or not. To be invoked by the user.
  bool closed ();

  /// @brief **Clear method.**
  /// @details To be invoked by the user in order to clear the window. It deletes all graphics
  /// present in the framebuffer.
  void clear ();

  /// @brief **GUI "plot" function.**
  /// Plots graphics in the GUI. TO be invoked by the user.
  void plot (
             shader* loc_shader                                                                     ///< OpenGL shader.
            );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////// PUBLIC RETPOLINES /////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **Refresh retpoline.**
  /// @details ** To be invoked by the user in order to refresh the window. It redraws the current
  /// graphics in the framebuffer. Also automatically invoked by the @link refresh_callback @endlink
  /// function when the window needs to be refreshed.
  void refresh ();

  /// @brief **Window resize retpoline.**
  /// @details Automatically invoked by the @link window_resize_callback @endlink
  /// function when the window needs to be resized.
  void window_resize (
                      int loc_x_size,                                                               ///< Window x-size [screen coordinates].
                      int loc_y_size                                                                ///< Window y-size [screen coordinates].
                     );

  /// @brief **Framebuffer resize retpoline.**
  /// @details Automatically invoked by the @link framebuffer_resize_callback @endlink
  /// function when the framebuffer needs to be resized.
  void framebuffer_resize (
                           int loc_x_size,                                                          ///< Framebuffer x-size [px].
                           int loc_y_size                                                           ///< Framebuffer y-size [px].
                          );

  /// @brief **Class destructor.**
  /// @details Terminates the GLFW context.
  ~opengl();

};

#endif
