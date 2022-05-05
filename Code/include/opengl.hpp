/// @file   opengl.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declaration of the "opengl" class.

#ifndef opengl_hpp
#define opengl_hpp

#include "neutrino.hpp"
#include "shader.hpp"
#include "linear_algebra.hpp"
#include "projective_geometry.hpp"
#include "logfile.hpp"                                                                              // Neutrino's logfile declarations.

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// IMGUI header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// IMPLOT header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <implot.h>
#include <implot_internal.h>

namespace nu
{
// Projection mode:
typedef enum
{
  MONOCULAR,                                                                                        ///< Projection mode set as monocular.
  BINOCULAR                                                                                         ///< Projection mode set as binocular.
} projection_mode;

// View mode:
typedef enum
{
  DIRECT,                                                                                           ///< View mode set as direct.
  INVERSE                                                                                           ///< View mode set as inverse (View matrix is inverted).
} view_mode;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "opengl" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class opengl : public neutrino                                                                      /// @brief **OpenGL GUI.**
{
private:
  GLFWgamepadstate gamepad;                                                                         ///< @brief **Gamepad state.**
  float            mouse_x;                                                                         ///< @brief **Mouse x movement (current) for velocity computation.**
  float            mouse_y;                                                                         ///< @brief **Mouse y movement (current) for velocity computation.**
  float            mouse_z;                                                                         ///< @brief **Mouse z movement (current) for velocity computation.**
  float            mouse_x_old;                                                                     ///< @brief **Mouse x movement (old) for velocity computation.**
  float            mouse_y_old;                                                                     ///< @brief **Mouse y movement (old) for velocity computation.**
  float            mouse_z_old;                                                                     ///< @brief **Mouse z movement (old) for velocity computation.**
  bool             mouse_sample;                                                                    ///< @brief **Mouse sample flag for velocity computation.**
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
  view_mode        VR_mode;                                                                         ///< @brief **View mode.**

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// PRIVATE METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenGL shader set method.**
  /// @details It sets an OpenGL shader.
  void set_shader (
                   nu::shader* loc_shader,                                                          ///< Shader.
                   float       view_matrix[16],                                                     ///< View matrix.
                   float       projection_matrix[16],                                               ///< Projection matrix.
                   float       framebuffer_size_x,                                                  ///< Framebuffer x-size [px_float].
                   float       framebuffer_size_y,                                                  ///< Framebuffer y-size [px_float].
                   float       framebuffer_AR                                                       ///< Framebuffer aspect ratio.
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
  static bool init_done;                                                                            ///< @brief **init_done flag.**

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
  ///////////////////////////////////////////// KEYBOARD //////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // KEYS:
  bool        key_UNKNOWN;                                                                          ///< @brief **Unknown key.**
  bool        key_SPACE;                                                                            ///< @brief **Space**
  bool        key_APOSTROPHE;                                                                       ///< @brief ** ' **
  bool        key_COMMA;                                                                            ///< @brief ** , **
  bool        key_MINUS;                                                                            ///< @brief ** - **
  bool        key_PERIOD;                                                                           ///< @brief ** . **
  bool        key_SLASH;                                                                            ///< @brief ** / **
  bool        key_0;                                                                                ///< @brief ** 0 **
  bool        key_1;                                                                                ///< @brief ** 1 **
  bool        key_2;                                                                                ///< @brief ** 2 **
  bool        key_3;                                                                                ///< @brief ** 3 **
  bool        key_4;                                                                                ///< @brief ** 4 **
  bool        key_5;                                                                                ///< @brief ** 5 **
  bool        key_6;                                                                                ///< @brief ** 6 **
  bool        key_7;                                                                                ///< @brief ** 7 **
  bool        key_8;                                                                                ///< @brief ** 8 **
  bool        key_9;                                                                                ///< @brief ** 9 **
  bool        key_SEMICOLON;                                                                        ///< @brief ** ; **
  bool        key_EQUAL;                                                                            ///< @brief ** = **
  bool        key_A;                                                                                ///< @brief ** A **
  bool        key_B;                                                                                ///< @brief ** B **
  bool        key_C;                                                                                ///< @brief ** C **
  bool        key_D;                                                                                ///< @brief ** D **
  bool        key_E;                                                                                ///< @brief ** E **
  bool        key_F;                                                                                ///< @brief ** F **
  bool        key_G;                                                                                ///< @brief ** G **
  bool        key_H;                                                                                ///< @brief ** H **
  bool        key_I;                                                                                ///< @brief ** I **
  bool        key_J;                                                                                ///< @brief ** J **
  bool        key_K;                                                                                ///< @brief ** K **
  bool        key_L;                                                                                ///< @brief ** L **
  bool        key_M;                                                                                ///< @brief ** M **
  bool        key_N;                                                                                ///< @brief ** N **
  bool        key_O;                                                                                ///< @brief ** O **
  bool        key_P;                                                                                ///< @brief ** P **
  bool        key_Q;                                                                                ///< @brief ** Q **
  bool        key_R;                                                                                ///< @brief ** R **
  bool        key_S;                                                                                ///< @brief ** S **
  bool        key_T;                                                                                ///< @brief ** T **
  bool        key_U;                                                                                ///< @brief ** U **
  bool        key_V;                                                                                ///< @brief ** V **
  bool        key_W;                                                                                ///< @brief ** W **
  bool        key_X;                                                                                ///< @brief ** X **
  bool        key_Y;                                                                                ///< @brief ** Y **
  bool        key_Z;                                                                                ///< @brief ** Z **
  bool        key_LEFT_BRACKET;                                                                     ///< @brief ** [ **
  bool        key_BACKSLASH;                                                                        ///< @brief ** \ **
  bool        key_RIGHT_BRACKET;                                                                    ///< @brief ** ] **
  bool        key_GRAVE_ACCENT;                                                                     ///< @brief ** ` **
  bool        key_WORLD_1;                                                                          ///< @brief **Non-US #1.**
  bool        key_WORLD_2;                                                                          ///< @brief **Non-US #2.**
  bool        key_ESCAPE;                                                                           ///< @brief **Escape.**
  bool        key_ENTER;                                                                            ///< @brief **Enter.**
  bool        key_TAB;                                                                              ///< @brief **Tab.**
  bool        key_BACKSPACE;                                                                        ///< @brief **Backspace.**
  bool        key_INSERT;                                                                           ///< @brief **Insert.**
  bool        key_DELETE;                                                                           ///< @brief **Delete.**
  bool        key_RIGHT;                                                                            ///< @brief **Right.**
  bool        key_LEFT;                                                                             ///< @brief **Left.**
  bool        key_DOWN;                                                                             ///< @brief **Up.**
  bool        key_UP;                                                                               ///< @brief **Down.**
  bool        key_PAGE_UP;                                                                          ///< @brief **Page up.**
  bool        key_PAGE_DOWN;                                                                        ///< @brief **Page down.**
  bool        key_HOME;                                                                             ///< @brief **Home.**
  bool        key_END;                                                                              ///< @brief **End.**
  bool        key_CAPS_LOCK;                                                                        ///< @brief **Caps lock.**
  bool        key_SCROLL_LOCK;                                                                      ///< @brief **Scroll lock.**
  bool        key_NUM_LOCK;                                                                         ///< @brief **Num lock.**
  bool        key_PRINT_SCREEN;                                                                     ///< @brief **Print screen.**
  bool        key_PAUSE;                                                                            ///< @brief **Pause.**
  bool        key_F1;                                                                               ///< @brief ** F1 **
  bool        key_F2;                                                                               ///< @brief ** F2 **
  bool        key_F3;                                                                               ///< @brief ** F3 **
  bool        key_F4;                                                                               ///< @brief ** F4 **
  bool        key_F5;                                                                               ///< @brief ** F5 **
  bool        key_F6;                                                                               ///< @brief ** F6 **
  bool        key_F7;                                                                               ///< @brief ** F7 **
  bool        key_F8;                                                                               ///< @brief ** F8 **
  bool        key_F9;                                                                               ///< @brief ** F9 **
  bool        key_F10;                                                                              ///< @brief ** F10 **
  bool        key_F11;                                                                              ///< @brief ** F11 **
  bool        key_F12;                                                                              ///< @brief ** F12 **
  bool        key_F13;                                                                              ///< @brief ** F13 **
  bool        key_F14;                                                                              ///< @brief ** F14 **
  bool        key_F15;                                                                              ///< @brief ** F15 **
  bool        key_F16;                                                                              ///< @brief ** F16 **
  bool        key_F17;                                                                              ///< @brief ** F17 **
  bool        key_F18;                                                                              ///< @brief ** F18 **
  bool        key_F19;                                                                              ///< @brief ** F19 **
  bool        key_F20;                                                                              ///< @brief ** F20 **
  bool        key_F21;                                                                              ///< @brief ** F21 **
  bool        key_F22;                                                                              ///< @brief ** F22 **
  bool        key_F23;                                                                              ///< @brief ** F23 **
  bool        key_F24;                                                                              ///< @brief ** F24 **
  bool        key_F25;                                                                              ///< @brief ** F25 **
  bool        key_KP_0;                                                                             ///< @brief ** 0 (keypad).**
  bool        key_KP_1;                                                                             ///< @brief ** 1 (keypad).**
  bool        key_KP_2;                                                                             ///< @brief ** 2 (keypad).**
  bool        key_KP_3;                                                                             ///< @brief ** 3 (keypad).**
  bool        key_KP_4;                                                                             ///< @brief ** 4 (keypad).**
  bool        key_KP_5;                                                                             ///< @brief ** 5 (keypad).**
  bool        key_KP_6;                                                                             ///< @brief ** 6 (keypad).**
  bool        key_KP_7;                                                                             ///< @brief ** 7 (keypad).**
  bool        key_KP_8;                                                                             ///< @brief ** 8 (keypad).**
  bool        key_KP_9;                                                                             ///< @brief ** 9 (keypad).**
  bool        key_KP_DECIMAL;                                                                       ///< @brief ** . (keypad).**
  bool        key_KP_DIVIDE;                                                                        ///< @brief ** / (keypad).**
  bool        key_KP_MULTIPLY;                                                                      ///< @brief ** * (keypad).**
  bool        key_KP_SUBTRACT;                                                                      ///< @brief ** - (keypad).**
  bool        key_KP_ADD;                                                                           ///< @brief ** + (keypad).**
  bool        key_KP_ENTER;                                                                         ///< @brief **Enter (keypad).**
  bool        key_KP_EQUAL;                                                                         ///< @brief ** = (keypad).**
  bool        key_LEFT_SHIFT;                                                                       ///< @brief **Left shift.**
  bool        key_LEFT_CONTROL;                                                                     ///< @brief **Left control.**
  bool        key_LEFT_ALT;                                                                         ///< @brief **Left alt.**
  bool        key_LEFT_SUPER;                                                                       ///< @brief **Left super.**
  bool        key_RIGHT_SHIFT;                                                                      ///< @brief **Right shift.**
  bool        key_RIGHT_CONTROL;                                                                    ///< @brief **Right control.**
  bool        key_RIGHT_ALT;                                                                        ///< @brief **Right alt.**
  bool        key_RIGHT_SUPER;                                                                      ///< @brief **Right super.**
  bool        key_MENU;                                                                             ///< @brief **Menu.**
  bool        key_LAST;                                                                             ///< @brief **Last.**

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

  float       mouse_X;                                                                              ///< @brief **Mouse x-coordinate [px].**
  float       mouse_Y;                                                                              ///< @brief **Mouse y-coordinate [px].**

  float       scroll_X;                                                                             ///< @brief **Mouse scroll x-coordinate [px].**
  float       scroll_Y;                                                                             ///< @brief **Mouse scroll y-coordinate [px].**

  /// @brief **Class constructor.**
  /// @details It does nothing.
  opengl(
         std::string loc_title,                                                                     ///< Window title.
         int         loc_window_size_x,                                                             ///< Window x-size [px].
         int         loc_window_size_y,                                                             ///< Window y-size [px].
         float       loc_orbit_x_initial,                                                           ///< Initial "near clipping-plane" x-coordinate.
         float       loc_orbit_y_initial,                                                           ///< Initial "near clipping-plane" y-coordinate.
         float       loc_pan_x_initial,                                                             ///< Initial pan-x coordinate.
         float       loc_pan_y_initial,                                                             ///< Initial pan-y coordinate.
         float       loc_pan_z_initial                                                              ///< Initial pan-z coordinate.
        );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// PUBLIC METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **GUI initialization.**
  /// @details Initializes GLFW, GLAD and OpenGL contexts.
  void init (
             std::string loc_title,                                                                 ///< Windows title.
             int         loc_window_size_x,                                                         ///< Window x-size [px].
             int         loc_window_size_y,                                                         ///< Window y-size [px].
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

  /// @brief **GUI mouse control.**
  /// @details Controls the GUI navigation by the mouse or trakpad.
  void mouse_navigation (
                         float loc_orbit_rate,                                                      ///< Orbit angular rate coefficient [rev/s].
                         float loc_pan_rate,                                                        ///< Pan translation rate [m/s].
                         float loc_decaytime                                                        ///< Low pass filter decay time [s].
                        );

  /// @brief **GUI gamepad control.**
  /// @details Controls the GUI navigation by the gamepad.
  void gamepad_navigation (
                           float loc_orbit_rate,                                                    ///< Orbit angular rate coefficient [rev/s].
                           float loc_pan_rate,                                                      ///< Pan translation rate [m/s].
                           float loc_decaytime,                                                     ///< Low pass filter decay time [s].
                           float loc_deadzone                                                       ///< Gamepad joystick deadzone [0...1].
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

  /// @brief **Begin method.**
  /// @details To be invoked by the user in order to start using OpenGL inside the application loop.
  void begin ();

  /// @brief **End method.**
  /// @details To be invoked by the user in order to stop using OpenGL inside the application loop.
  void end ();

  /// @brief **GUI "plot" function.**
  /// Plots graphics in the GUI. TO be invoked by the user.
  void plot (
             nu::shader*         loc_shader,                                                        ///< OpenGL shader.
             nu::projection_mode loc_pmode,                                                         ///< OpenGL projection mode.
             nu::view_mode       loc_vmode                                                          ///< OpenGL view mode.
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
}
#endif
