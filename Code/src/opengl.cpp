/// @file     opengl.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of the "nu::opengl" class.

#include "opengl.hpp"

bool nu::opengl::init_done = false;                                                                 // init_done flag.

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu::opengl" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::opengl::opengl (
                    std::string loc_title,                                                          // Window title.
                    int         loc_window_size_x,                                                  // Window x-size [px].
                    int         loc_window_size_y,                                                  // Window y-size [px].
                    float       loc_orbit_x_initial,                                                // Initial "near clipping-plane" x-coordinate.
                    float       loc_orbit_y_initial,                                                // Initial "near clipping-plane" y-coordinate.
                    float       loc_pan_x_initial,                                                  // Initial pan-x coordinate.
                    float       loc_pan_y_initial,                                                  // Initial pan-y coordinate.
                    float       loc_pan_z_initial                                                   // Initial pan-z coordinate.
                   )
{
  if(neutrino::init_done != true)
  {
    neutrino::init ();                                                                              // Initializing Neutrino...
  }

  if(nu::opengl::init_done != true)
  {
    nu::opengl::init (
                      loc_title,                                                                    // Window title.
                      loc_window_size_x,                                                            // Window x-size [px].
                      loc_window_size_y,                                                            // Window y-size [px].
                      loc_orbit_x_initial,                                                          // Initial "near clipping-plane" x-coordinate.
                      loc_orbit_y_initial,                                                          // Initial "near clipping-plane" y-coordinate.
                      loc_pan_x_initial,                                                            // Initial pan-x coordinate.
                      loc_pan_y_initial,                                                            // Initial pan-y coordinate.
                      loc_pan_z_initial                                                             // Initial pan-z coordinate.
                     );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// PRIVATE METHODS ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::set_shader
(
 nu::shader* loc_shader,                                                                            // Shader.
 float       view_matrix[16],                                                                       // View matrix.
 float       projection_matrix[16],                                                                 // Projection matrix.
 float       framebuffer_size_x,                                                                    // Framebuffer x-size [px_float].
 float       framebuffer_size_y,                                                                    // Framebuffer y-size [px_float].
 float       framebuffer_AR                                                                         // Framebuffer aspect ratio.
)
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  glUseProgram (loc_shader->program);                                                               // Using shader...

  // Setting View_matrix matrix on shader:
  glUniformMatrix4fv
  (
   // Getting variable's uniform location:
   glGetUniformLocation
   (
    loc_shader->program,                                                                            // Program.
    "V_mat"                                                                                         // Variable.
   ),
   1,                                                                                               // Number of matrices to be modified.
   GL_FALSE,                                                                                        // FALSE = column major.
   &view_matrix[0]                                                                                  // View matrix.
  );

  // Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv
  (
   glGetUniformLocation                                                                             // Getting variable's uniform location:
   (
    loc_shader->program,                                                                            // Program.
    "P_mat"                                                                                         // Variable.
   ),
   1,                                                                                               // Number of matrices to be modified.
   GL_FALSE,                                                                                        // FALSE = column major.
   &projection_matrix[0]                                                                            // Projection matrix.
  );

  // Setting framebuffer size_x on shader:
  glUniform1f
  (
   glGetUniformLocation                                                                             // Getting variable's uniform location:
   (
    loc_shader->program,                                                                            // Program.
    "size_x"                                                                                        // Variable.
   ),
   framebuffer_size_x                                                                               // Window x-size [px_float].
  );

  // Setting framebuffer size_y on shader:
  glUniform1f
  (
   glGetUniformLocation                                                                             // Getting variable's uniform location:
   (
    loc_shader->program,                                                                            // Program.
    "size_y"                                                                                        // Variable.
   ),
   framebuffer_size_y                                                                               // Window y-size [px_float].
  );

  // Setting framebuffer aspect ratio on shader:
  glUniform1f
  (
   glGetUniformLocation                                                                             // Getting variable's uniform location:
   (
    loc_shader->program,                                                                            // Program.
    "AR"                                                                                            // Variable.
   ),
   framebuffer_AR                                                                                   // Framebuffer aspect ratio [].
  );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// CALLBACKS /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::refresh_callback
(
 GLFWwindow* loc_window                                                                             // Window.
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->refresh ();                                                                                  // Calling refresh retpoline...
}

void nu::opengl::window_resize_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 int         loc_x_size,                                                                            // Window x-size [screen coordinates].
 int         loc_y_size                                                                             // Window y-size [screen coordinates].
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->window_resize (loc_x_size, loc_y_size);                                                      // Calling window resize retpoline...
}

void nu::opengl::framebuffer_resize_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 int         loc_x_size,                                                                            // Framebuffer x-size [px].
 int         loc_y_size                                                                             // Framebuffer y-size [px].
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->framebuffer_resize (loc_x_size, loc_y_size);                                                 // Calling framebuffer resize retpoline...
}

void nu::opengl::key_pressed_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 int         loc_key,                                                                               // Key.
 int         loc_scancode,                                                                          // Scancode.
 int         loc_action,                                                                            // Action.
 int         loc_mods                                                                               // Mods.
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->key_pressed (loc_key, loc_scancode, loc_action, loc_mods);                                   // Calling key pressed retpoline...
}

void nu::opengl::mouse_button_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 int         loc_button,                                                                            // Button.
 int         loc_action,                                                                            // Action.
 int         loc_mods                                                                               // Mods.
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->mouse_button (loc_button, loc_action, loc_mods);                                             // Calling mouse pressed retpoline...
}

void nu::opengl::mouse_moved_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 double      loc_xpos,                                                                              // Mouse x-position [px].
 double      loc_ypos                                                                               // Mouse y-position [px].
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->mouse_moved (loc_xpos, loc_ypos);                                                            // Calling mouse moved retpoline...
}

void nu::opengl::mouse_scrolled_callback
(
 GLFWwindow* loc_window,                                                                            // Window.
 double      loc_xoffset,                                                                           // Mouse scroll x-offset [px].
 double      loc_yoffset                                                                            // Mouse scroll y-offset [px].
)
{
  nu::opengl* win = (nu::opengl*) glfwGetWindowUserPointer (loc_window);                            // Getting window pointer...
  win->mouse_scrolled (loc_xoffset, loc_yoffset);                                                   // Calling mouse scrolled retpoline...
}

void nu::opengl::joystick_connected_callback
(
 int loc_joystick,                                                                                  // Joystick.
 int loc_event                                                                                      // Joystick-connected event.
)
{
  /*
     if(event == GLFW_CONNECTED)
     {
     // The joystick was connected:
     std::cout << "Joystick connected!" << std::endl;
     }
     else if(event == GLFW_DISCONNECTED)
     {
     // The joystick was disconnected:
      std::cout << "Joystick disconnected!" << std::endl;
     }*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// PRIVATE RETPOLINES ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::key_pressed
(
 int loc_key,                                                                                       // Key.
 int loc_scancode,                                                                                  // Scancode.
 int loc_action,                                                                                    // Action.
 int loc_mods                                                                                       // Mods.
)
{
  // Checking key pressed:
  switch(loc_key)
  {
    case GLFW_KEY_UNKNOWN:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_UNKNOWN = true;
          break;
        case GLFW_RELEASE:
          key_UNKNOWN = false;
          break;
      }

      break;

    case GLFW_KEY_SPACE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_SPACE = true;
          break;
        case GLFW_RELEASE:
          key_SPACE = false;
          break;
      }

      break;

    case GLFW_KEY_APOSTROPHE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_APOSTROPHE = true;
          break;
        case GLFW_RELEASE:
          key_APOSTROPHE = false;
          break;
      }

      break;

    case GLFW_KEY_COMMA:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_COMMA = true;
          break;
        case GLFW_RELEASE:
          key_COMMA = false;
          break;
      }

      break;

    case GLFW_KEY_MINUS:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_MINUS = true;
          break;
        case GLFW_RELEASE:
          key_MINUS = false;
          break;
      }

      break;

    case GLFW_KEY_PERIOD:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_PERIOD = true;
          break;
        case GLFW_RELEASE:
          key_PERIOD = false;
          break;
      }

      break;

    case GLFW_KEY_SLASH:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_SLASH = true;
          break;
        case GLFW_RELEASE:
          key_SLASH = false;
          break;
      }

      break;

    case GLFW_KEY_0:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_0 = true;
          break;
        case GLFW_RELEASE:
          key_0 = false;
          break;
      }

      break;

    case GLFW_KEY_1:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_1 = true;
          break;
        case GLFW_RELEASE:
          key_1 = false;
          break;
      }

      break;

    case GLFW_KEY_2:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_2 = true;
          break;
        case GLFW_RELEASE:
          key_2 = false;
          break;
      }

      break;

    case GLFW_KEY_3:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_3 = true;
          break;
        case GLFW_RELEASE:
          key_3 = false;
          break;
      }

      break;

    case GLFW_KEY_4:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_4 = true;
          break;
        case GLFW_RELEASE:
          key_4 = false;
          break;
      }

      break;

    case GLFW_KEY_5:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_5 = true;
          break;
        case GLFW_RELEASE:
          key_5 = false;
          break;
      }

      break;

    case GLFW_KEY_6:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_6 = true;
          break;
        case GLFW_RELEASE:
          key_6 = false;
          break;
      }

      break;

    case GLFW_KEY_7:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_7 = true;
          break;
        case GLFW_RELEASE:
          key_7 = false;
          break;
      }

      break;

    case GLFW_KEY_8:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_8 = true;
          break;
        case GLFW_RELEASE:
          key_8 = false;
          break;
      }

      break;

    case GLFW_KEY_9:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_9 = true;
          break;
        case GLFW_RELEASE:
          key_9 = false;
          break;
      }

      break;

    case GLFW_KEY_SEMICOLON:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_SEMICOLON = true;
          break;
        case GLFW_RELEASE:
          key_SEMICOLON = false;
          break;
      }

      break;

    case GLFW_KEY_EQUAL:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_EQUAL = true;
          break;
        case GLFW_RELEASE:
          key_EQUAL = false;
          break;
      }

      break;

    case GLFW_KEY_A:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_A = true;
          break;
        case GLFW_RELEASE:
          key_A = false;
          break;
      }

      break;

    case GLFW_KEY_B:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_B = true;
          break;
        case GLFW_RELEASE:
          key_B = false;
          break;
      }

      break;

    case GLFW_KEY_C:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_C = true;
          break;
        case GLFW_RELEASE:
          key_C = false;
          break;
      }

      break;

    case GLFW_KEY_D:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_D = true;
          break;
        case GLFW_RELEASE:
          key_D = false;
          break;
      }

      break;

    case GLFW_KEY_E:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_E = true;
          break;
        case GLFW_RELEASE:
          key_E = false;
          break;
      }

      break;

    case GLFW_KEY_F:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F = true;
          break;
        case GLFW_RELEASE:
          key_F = false;
          break;
      }

      break;

    case GLFW_KEY_G:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_G = true;
          break;
        case GLFW_RELEASE:
          key_G = false;
          break;
      }

      break;

    case GLFW_KEY_H:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_H = true;
          break;
        case GLFW_RELEASE:
          key_H = false;
          break;
      }

      break;

    case GLFW_KEY_I:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_I = true;
          break;
        case GLFW_RELEASE:
          key_I = false;
          break;
      }

      break;

    case GLFW_KEY_J:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_J = true;
          break;
        case GLFW_RELEASE:
          key_J = false;
          break;
      }

      break;

    case GLFW_KEY_K:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_K = true;
          break;
        case GLFW_RELEASE:
          key_K = false;
          break;
      }

      break;

    case GLFW_KEY_L:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_L = true;
          break;
        case GLFW_RELEASE:
          key_L = false;
          break;
      }

      break;

    case GLFW_KEY_M:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_M = true;
          break;
        case GLFW_RELEASE:
          key_M = false;
          break;
      }

      break;

    case GLFW_KEY_N:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_N = true;
          break;
        case GLFW_RELEASE:
          key_N = false;
          break;
      }

      break;

    case GLFW_KEY_O:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_O = true;
          break;
        case GLFW_RELEASE:
          key_O = false;
          break;
      }

      break;

    case GLFW_KEY_P:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_P = true;
          break;
        case GLFW_RELEASE:
          key_P = false;
          break;
      }

      break;

    case GLFW_KEY_Q:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_Q = true;
          break;
        case GLFW_RELEASE:
          key_Q = false;
          break;
      }

      break;

    case GLFW_KEY_R:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_R = true;
          break;
        case GLFW_RELEASE:
          key_R = false;
          break;
      }

      break;

    case GLFW_KEY_S:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_S = true;
          break;
        case GLFW_RELEASE:
          key_S = false;
          break;
      }

      break;

    case GLFW_KEY_T:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_T = true;
          break;
        case GLFW_RELEASE:
          key_T = false;
          break;
      }

      break;

    case GLFW_KEY_U:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_U = true;
          break;
        case GLFW_RELEASE:
          key_U = false;
          break;
      }

      break;

    case GLFW_KEY_V:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_V = true;
          break;
        case GLFW_RELEASE:
          key_V = false;
          break;
      }

      break;

    case GLFW_KEY_W:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_W = true;
          break;
        case GLFW_RELEASE:
          key_W = false;
          break;
      }

      break;

    case GLFW_KEY_X:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_X = true;
          break;
        case GLFW_RELEASE:
          key_X = false;
          break;
      }

      break;

    case GLFW_KEY_Y:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_Y = true;
          break;
        case GLFW_RELEASE:
          key_Y = false;
          break;
      }

      break;

    case GLFW_KEY_Z:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_Z = true;
          break;
        case GLFW_RELEASE:
          key_Z = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT_BRACKET:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT_BRACKET = true;
          break;
        case GLFW_RELEASE:
          key_LEFT_BRACKET = false;
          break;
      }

      break;

    case GLFW_KEY_BACKSLASH:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_BACKSLASH = true;
          break;
        case GLFW_RELEASE:
          key_BACKSLASH = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT_BRACKET:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT_BRACKET = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT_BRACKET = false;
          break;
      }

      break;

    case GLFW_KEY_GRAVE_ACCENT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_GRAVE_ACCENT = true;
          break;
        case GLFW_RELEASE:
          key_GRAVE_ACCENT = false;
          break;
      }

      break;

    case GLFW_KEY_WORLD_1:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_WORLD_1 = true;
          break;
        case GLFW_RELEASE:
          key_WORLD_1 = false;
          break;
      }

      break;

    case GLFW_KEY_WORLD_2:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_WORLD_2 = true;
          break;
        case GLFW_RELEASE:
          key_WORLD_2 = false;
          break;
      }

      break;

    case GLFW_KEY_ESCAPE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_ESCAPE = true;
          break;
        case GLFW_RELEASE:
          key_ESCAPE = false;
          break;
      }

      break;

    case GLFW_KEY_ENTER:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_ENTER = true;
          break;
        case GLFW_RELEASE:
          key_ENTER = false;
          break;
      }

      break;

    case GLFW_KEY_TAB:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_TAB = true;
          break;
        case GLFW_RELEASE:
          key_TAB = false;
          break;
      }

      break;

    case GLFW_KEY_BACKSPACE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_BACKSPACE = true;
          break;
        case GLFW_RELEASE:
          key_BACKSPACE = false;
          break;
      }

      break;

    case GLFW_KEY_INSERT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_INSERT = true;
          break;
        case GLFW_RELEASE:
          key_INSERT = false;
          break;
      }

      break;

    case GLFW_KEY_DELETE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_DELETE = true;
          break;
        case GLFW_RELEASE:
          key_DELETE = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT = true;
          break;
        case GLFW_RELEASE:
          key_LEFT = false;
          break;
      }

      break;

    case GLFW_KEY_DOWN:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_DOWN = true;
          break;
        case GLFW_RELEASE:
          key_DOWN = false;
          break;
      }

      break;

    case GLFW_KEY_UP:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_UP = true;
          break;
        case GLFW_RELEASE:
          key_UP = false;
          break;
      }

      break;

    case GLFW_KEY_PAGE_UP:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_PAGE_UP = true;
          break;
        case GLFW_RELEASE:
          key_PAGE_UP = false;
          break;
      }

      break;

    case GLFW_KEY_PAGE_DOWN:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_PAGE_DOWN = true;
          break;
        case GLFW_RELEASE:
          key_PAGE_DOWN = false;
          break;
      }

      break;

    case GLFW_KEY_HOME:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_HOME = true;
          break;
        case GLFW_RELEASE:
          key_HOME = false;
          break;
      }

      break;

    case GLFW_KEY_END:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_END = true;
          break;
        case GLFW_RELEASE:
          key_END = false;
          break;
      }

      break;

    case GLFW_KEY_CAPS_LOCK:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_CAPS_LOCK = true;
          break;
        case GLFW_RELEASE:
          key_CAPS_LOCK = false;
          break;
      }

      break;

    case GLFW_KEY_SCROLL_LOCK:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_SCROLL_LOCK = true;
          break;
        case GLFW_RELEASE:
          key_SCROLL_LOCK = false;
          break;
      }

      break;

    case GLFW_KEY_NUM_LOCK:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_NUM_LOCK = true;
          break;
        case GLFW_RELEASE:
          key_NUM_LOCK = false;
          break;
      }

      break;

    case GLFW_KEY_PRINT_SCREEN:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_PRINT_SCREEN = true;
          break;
        case GLFW_RELEASE:
          key_PRINT_SCREEN = false;
          break;
      }

      break;

    case GLFW_KEY_PAUSE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_PAUSE = true;
          break;
        case GLFW_RELEASE:
          key_PAUSE = false;
          break;
      }

      break;

    case GLFW_KEY_F1:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F1 = true;
          break;
        case GLFW_RELEASE:
          key_F1 = false;
          break;
      }

      break;

    case GLFW_KEY_F2:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F2 = true;
          break;
        case GLFW_RELEASE:
          key_F2 = false;
          break;
      }

      break;

    case GLFW_KEY_F3:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F3 = true;
          break;
        case GLFW_RELEASE:
          key_F3 = false;
          break;
      }

      break;

    case GLFW_KEY_F4:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F4 = true;
          break;
        case GLFW_RELEASE:
          key_F4 = false;
          break;
      }

      break;

    case GLFW_KEY_F5:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F5 = true;
          break;
        case GLFW_RELEASE:
          key_F5 = false;
          break;
      }

      break;

    case GLFW_KEY_F6:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F6 = true;
          break;
        case GLFW_RELEASE:
          key_F6 = false;
          break;
      }

      break;

    case GLFW_KEY_F7:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F7 = true;
          break;
        case GLFW_RELEASE:
          key_F7 = false;
          break;
      }

      break;

    case GLFW_KEY_F8:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F8 = true;
          break;
        case GLFW_RELEASE:
          key_F8 = false;
          break;
      }

      break;

    case GLFW_KEY_F9:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F9 = true;
          break;
        case GLFW_RELEASE:
          key_F9 = false;
          break;
      }

      break;

    case GLFW_KEY_F10:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F10 = true;
          break;
        case GLFW_RELEASE:
          key_F10 = false;
          break;
      }

      break;

    case GLFW_KEY_F11:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F11 = true;
          break;
        case GLFW_RELEASE:
          key_F11 = false;
          break;
      }

      break;

    case GLFW_KEY_F12:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F12 = true;
          break;
        case GLFW_RELEASE:
          key_F12 = false;
          break;
      }

      break;

    case GLFW_KEY_F13:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F13 = true;
          break;
        case GLFW_RELEASE:
          key_F13 = false;
          break;
      }

      break;

    case GLFW_KEY_F14:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F14 = true;
          break;
        case GLFW_RELEASE:
          key_F14 = false;
          break;
      }

      break;

    case GLFW_KEY_F15:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F15 = true;
          break;
        case GLFW_RELEASE:
          key_F15 = false;
          break;
      }

      break;

    case GLFW_KEY_F16:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F16 = true;
          break;
        case GLFW_RELEASE:
          key_F16 = false;
          break;
      }

      break;

    case GLFW_KEY_F17:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F17 = true;
          break;
        case GLFW_RELEASE:
          key_F17 = false;
          break;
      }

      break;

    case GLFW_KEY_F18:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F18 = true;
          break;
        case GLFW_RELEASE:
          key_F18 = false;
          break;
      }

      break;

    case GLFW_KEY_F19:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F19 = true;
          break;
        case GLFW_RELEASE:
          key_F19 = false;
          break;
      }

      break;

    case GLFW_KEY_F20:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F20 = true;
          break;
        case GLFW_RELEASE:
          key_F20 = false;
          break;
      }

      break;

    case GLFW_KEY_F21:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F21 = true;
          break;
        case GLFW_RELEASE:
          key_F21 = false;
          break;
      }

      break;

    case GLFW_KEY_F22:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F22 = true;
          break;
        case GLFW_RELEASE:
          key_F22 = false;
          break;
      }

      break;

    case GLFW_KEY_F23:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F23 = true;
          break;
        case GLFW_RELEASE:
          key_F23 = false;
          break;
      }

      break;

    case GLFW_KEY_F24:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F24 = true;
          break;
        case GLFW_RELEASE:
          key_F24 = false;
          break;
      }

      break;

    case GLFW_KEY_F25:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_F25 = true;
          break;
        case GLFW_RELEASE:
          key_F25 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_0:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_0 = true;
          break;
        case GLFW_RELEASE:
          key_KP_0 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_1:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_1 = true;
          break;
        case GLFW_RELEASE:
          key_KP_1 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_2:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_2 = true;
          break;
        case GLFW_RELEASE:
          key_KP_2 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_3:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_3 = true;
          break;
        case GLFW_RELEASE:
          key_KP_3 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_4:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_4 = true;
          break;
        case GLFW_RELEASE:
          key_KP_4 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_5:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_5 = true;
          break;
        case GLFW_RELEASE:
          key_KP_5 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_6:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_6 = true;
          break;
        case GLFW_RELEASE:
          key_KP_6 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_7:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_7 = true;
          break;
        case GLFW_RELEASE:
          key_KP_7 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_8:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_8 = true;
          break;
        case GLFW_RELEASE:
          key_KP_8 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_9:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_9 = true;
          break;
        case GLFW_RELEASE:
          key_KP_9 = false;
          break;
      }

      break;

    case GLFW_KEY_KP_DECIMAL:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_DECIMAL = true;
          break;
        case GLFW_RELEASE:
          key_KP_DECIMAL = false;
          break;
      }

      break;

    case GLFW_KEY_KP_DIVIDE:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_DIVIDE = true;
          break;
        case GLFW_RELEASE:
          key_KP_DIVIDE = false;
          break;
      }

      break;

    case GLFW_KEY_KP_MULTIPLY:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_MULTIPLY = true;
          break;
        case GLFW_RELEASE:
          key_KP_MULTIPLY = false;
          break;
      }

      break;

    case GLFW_KEY_KP_SUBTRACT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_SUBTRACT = true;
          break;
        case GLFW_RELEASE:
          key_KP_SUBTRACT = false;
          break;
      }

      break;

    case GLFW_KEY_KP_ADD:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_ADD = true;
          break;
        case GLFW_RELEASE:
          key_KP_ADD = false;
          break;
      }

      break;

    case GLFW_KEY_KP_ENTER:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_ENTER = true;
          break;
        case GLFW_RELEASE:
          key_KP_ENTER = false;
          break;
      }

      break;

    case GLFW_KEY_KP_EQUAL:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_KP_EQUAL = true;
          break;
        case GLFW_RELEASE:
          key_KP_EQUAL = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT_SHIFT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT_SHIFT = true;
          break;
        case GLFW_RELEASE:
          key_LEFT_SHIFT = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT_CONTROL:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT_CONTROL = true;
          break;
        case GLFW_RELEASE:
          key_LEFT_CONTROL = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT_ALT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT_ALT = true;
          break;
        case GLFW_RELEASE:
          key_LEFT_ALT = false;
          break;
      }

      break;

    case GLFW_KEY_LEFT_SUPER:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_LEFT_SUPER = true;
          break;
        case GLFW_RELEASE:
          key_LEFT_SUPER = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT_SHIFT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT_SHIFT = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT_SHIFT = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT_CONTROL:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT_CONTROL = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT_CONTROL = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT_ALT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT_ALT = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT_ALT = false;
          break;
      }

      break;

    case GLFW_KEY_RIGHT_SUPER:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_RIGHT_SUPER = true;
          break;
        case GLFW_RELEASE:
          key_RIGHT_SUPER = false;
          break;
      }

      break;

    case GLFW_KEY_MENU:

      switch(loc_action)
      {
        case GLFW_PRESS:
          key_MENU = true;
          break;
        case GLFW_RELEASE:
          key_MENU = false;
          break;
      }

      break;

      /*
         case GLFW_KEY_ESCAPE:
         if(loc_action == GLFW_PRESS)
         {
          glfwSetWindowShouldClose (glfw_window, GL_TRUE);                                            // Setting window "closed" flag...
         }
         break;

         case GLFW_KEY_2:
         if(loc_action == GLFW_PRESS)
         {
          PR_mode = MONOCULAR;                                                                     // Switching to monoscopic mode...
         }
         break;

         case GLFW_KEY_3:
         if(loc_action == GLFW_PRESS)
         {
          PR_mode = BINOCULAR;                                                                   // Switching to stereoscopic mode...
         }
         break;
       */
  }

}

void nu::opengl::mouse_button
(
 int loc_button,                                                                                    // Button.
 int loc_action,                                                                                    // Action.
 int loc_mods                                                                                       // Mods.
)
{
  ImGuiIO &io = ImGui::GetIO ();                                                                    // Getting ImGuiIO handle...

  // Reading mouse buttons:
  switch(loc_button)
  {
    case GLFW_MOUSE_BUTTON_LEFT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          io.MouseDown[loc_button] = true;

          if(!io.WantCaptureMouse)
          {
            mouse_LEFT = true;
          }
          break;

        case GLFW_RELEASE:
          io.MouseDown[loc_button] = false;
          mouse_LEFT               = false;
          break;
      }

      break;

    case GLFW_MOUSE_BUTTON_RIGHT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          io.MouseDown[loc_button] = true;

          if(!io.WantCaptureMouse)
          {
            mouse_RIGHT = true;
          }
          break;

        case GLFW_RELEASE:
          io.MouseDown[loc_button] = false;
          mouse_RIGHT              = false;
          break;
      }

      break;
  }
}

void nu::opengl::mouse_moved
(
 double loc_xpos,                                                                                   // Mouse position [px].
 double loc_ypos                                                                                    // Mouse position [px].
)
{
  mouse_X = loc_xpos;                                                                               // Getting mouse position...
  mouse_Y = loc_ypos;                                                                               // Getting mouse position...
}

void nu::opengl::mouse_scrolled
(
 double loc_xoffset,                                                                                // Mouse scrolled x-position [px].
 double loc_yoffset                                                                                 // Mouse scrolled y-position [px].
)
{
  scroll_X = loc_xoffset;                                                                           // Getting scroll position...
  scroll_Y = loc_yoffset;                                                                           // Getting scroll position...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// PUBLIC METHODS ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::init
(
 std::string loc_title,                                                                             // Window title.
 int         loc_window_size_x,                                                                     // Window x-size [px].
 int         loc_window_size_y,                                                                     // Window y-size [px].
 float       loc_orbit_x_initial,                                                                   // Initial "near clipping-plane" x-coordinate.
 float       loc_orbit_y_initial,                                                                   // Initial "near clipping-plane" y-coordinate.
 float       loc_pan_x_initial,                                                                     // Initial pan-x coordinate.
 float       loc_pan_y_initial,                                                                     // Initial pan-y coordinate.
 float       loc_pan_z_initial                                                                      // Initial pan-z coordinate.
)
{
  char*  loc_title_buffer;
  size_t loc_title_size;

  title                     = loc_title;                                                            // Initializing window title...
  window_size_x             = loc_window_size_x;                                                    // Initializing window x-size [px]...
  window_size_y             = loc_window_size_y;                                                    // Initializing window y-size [px]...
  aspect_ratio              = (float)window_size_x/(float)window_size_y;                            // Initializing window aspect ration []...

  initial_scene_position[0] = loc_pan_x_initial;                                                    // Initializing x-position...
  initial_scene_position[1] = loc_pan_y_initial;                                                    // Initializing y-position...
  initial_scene_position[2] = loc_pan_z_initial;                                                    // Initializing z-position...

  mouse_sample              = false;                                                                // Resetting mouse sampling flag...
  mouse_LEFT                = false;                                                                // Resetting mouse left button pressed flag...
  mouse_RIGHT               = false;                                                                // Resetting mouse right button pressed flag...

  mouse_X                   = 0.0f;                                                                 // Initializing mouse x-coordinate [px]...
  mouse_Y                   = 0.0f;                                                                 // Initializing mouse y-coordinate [px]...

  scroll_X                  = 0.0f;                                                                 // Initializing scroll x-coordinate [px]...
  scroll_Y                  = 0.0f;                                                                 // Initializing scroll y-coordinate [px]...

  orbit_x                   = 0.0f;                                                                 // Initializing orbit x-coordinate...
  orbit_y                   = 0.0f;                                                                 // Initializing orbit y-coordinate...
  orbit_x_old               = 0.0f;                                                                 // Initializing orbit x-coordinate (old)...
  orbit_y_old               = 0.0f;                                                                 // Initializing orbit y-coordinate (old)...
  orbit_on                  = false;                                                                // Initializing orbit activation flag...

  pan_x                     = 0.0f;                                                                 // Initializing pan x-coordinate...
  pan_y                     = 0.0f;                                                                 // Initializing pan y-coordinate...
  pan_z                     = 0.0f;                                                                 // Initializing pan z-coordinate...
  pan_x_old                 = 0.0f;                                                                 // Initializing pan x-coordinate (old)...
  pan_y_old                 = 0.0f;                                                                 // Initializing pan y-coordinate (old)...
  pan_z_old                 = 0.0f;                                                                 // Initializing pan z-coordinate (old)...
  pan_on                    = false;                                                                // Initializing pan activation flag...

  // KEYS:
  key_UNKNOWN               = false;                                                                // Initializing key value...
  key_SPACE                 = false;                                                                // Initializing key value...
  key_APOSTROPHE            = false;                                                                // Initializing key value...
  key_COMMA                 = false;                                                                // Initializing key value...
  key_MINUS                 = false;                                                                // Initializing key value...
  key_PERIOD                = false;                                                                // Initializing key value...
  key_SLASH                 = false;                                                                // Initializing key value...
  key_0                     = false;                                                                // Initializing key value...
  key_1                     = false;                                                                // Initializing key value...
  key_2                     = false;                                                                // Initializing key value...
  key_3                     = false;                                                                // Initializing key value...
  key_4                     = false;                                                                // Initializing key value...
  key_5                     = false;                                                                // Initializing key value...
  key_6                     = false;                                                                // Initializing key value...
  key_7                     = false;                                                                // Initializing key value...
  key_8                     = false;                                                                // Initializing key value...
  key_9                     = false;                                                                // Initializing key value...
  key_SEMICOLON             = false;                                                                // Initializing key value...
  key_EQUAL                 = false;                                                                // Initializing key value...
  key_A                     = false;                                                                // Initializing key value...
  key_B                     = false;                                                                // Initializing key value...
  key_C                     = false;                                                                // Initializing key value...
  key_D                     = false;                                                                // Initializing key value...
  key_E                     = false;                                                                // Initializing key value...
  key_F                     = false;                                                                // Initializing key value...
  key_G                     = false;                                                                // Initializing key value...
  key_H                     = false;                                                                // Initializing key value...
  key_I                     = false;                                                                // Initializing key value...
  key_J                     = false;                                                                // Initializing key value...
  key_K                     = false;                                                                // Initializing key value...
  key_L                     = false;                                                                // Initializing key value...
  key_M                     = false;                                                                // Initializing key value...
  key_N                     = false;                                                                // Initializing key value...
  key_O                     = false;                                                                // Initializing key value...
  key_P                     = false;                                                                // Initializing key value...
  key_Q                     = false;                                                                // Initializing key value...
  key_R                     = false;                                                                // Initializing key value...
  key_S                     = false;                                                                // Initializing key value...
  key_T                     = false;                                                                // Initializing key value...
  key_U                     = false;                                                                // Initializing key value...
  key_V                     = false;                                                                // Initializing key value...
  key_W                     = false;                                                                // Initializing key value...
  key_X                     = false;                                                                // Initializing key value...
  key_Y                     = false;                                                                // Initializing key value...
  key_Z                     = false;                                                                // Initializing key value...
  key_LEFT_BRACKET          = false;                                                                // Initializing key value...
  key_BACKSLASH             = false;                                                                // Initializing key value...
  key_RIGHT_BRACKET         = false;                                                                // Initializing key value...
  key_GRAVE_ACCENT          = false;                                                                // Initializing key value...
  key_WORLD_1               = false;                                                                // Initializing key value...
  key_WORLD_2               = false;                                                                // Initializing key value...
  key_ESCAPE                = false;                                                                // Initializing key value...
  key_ENTER                 = false;                                                                // Initializing key value...
  key_TAB                   = false;                                                                // Initializing key value...
  key_BACKSPACE             = false;                                                                // Initializing key value...
  key_INSERT                = false;                                                                // Initializing key value...
  key_DELETE                = false;                                                                // Initializing key value...
  key_RIGHT                 = false;                                                                // Initializing key value...
  key_LEFT                  = false;                                                                // Initializing key value...
  key_DOWN                  = false;                                                                // Initializing key value...
  key_UP                    = false;                                                                // Initializing key value...
  key_PAGE_UP               = false;                                                                // Initializing key value...
  key_PAGE_DOWN             = false;                                                                // Initializing key value...
  key_HOME                  = false;                                                                // Initializing key value...
  key_END                   = false;                                                                // Initializing key value...
  key_CAPS_LOCK             = false;                                                                // Initializing key value...
  key_SCROLL_LOCK           = false;                                                                // Initializing key value...
  key_NUM_LOCK              = false;                                                                // Initializing key value...
  key_PRINT_SCREEN          = false;                                                                // Initializing key value...
  key_PAUSE                 = false;                                                                // Initializing key value...
  key_F1                    = false;                                                                // Initializing key value...
  key_F2                    = false;                                                                // Initializing key value...
  key_F3                    = false;                                                                // Initializing key value...
  key_F4                    = false;                                                                // Initializing key value...
  key_F5                    = false;                                                                // Initializing key value...
  key_F6                    = false;                                                                // Initializing key value...
  key_F7                    = false;                                                                // Initializing key value...
  key_F8                    = false;                                                                // Initializing key value...
  key_F9                    = false;                                                                // Initializing key value...
  key_F10                   = false;                                                                // Initializing key value...
  key_F11                   = false;                                                                // Initializing key value...
  key_F12                   = false;                                                                // Initializing key value...
  key_F13                   = false;                                                                // Initializing key value...
  key_F14                   = false;                                                                // Initializing key value...
  key_F15                   = false;                                                                // Initializing key value...
  key_F16                   = false;                                                                // Initializing key value...
  key_F17                   = false;                                                                // Initializing key value...
  key_F18                   = false;                                                                // Initializing key value...
  key_F19                   = false;                                                                // Initializing key value...
  key_F20                   = false;                                                                // Initializing key value...
  key_F21                   = false;                                                                // Initializing key value...
  key_F22                   = false;                                                                // Initializing key value...
  key_F23                   = false;                                                                // Initializing key value...
  key_F24                   = false;                                                                // Initializing key value...
  key_F25                   = false;                                                                // Initializing key value...
  key_KP_0                  = false;                                                                // Initializing key value...
  key_KP_1                  = false;                                                                // Initializing key value...
  key_KP_2                  = false;                                                                // Initializing key value...
  key_KP_3                  = false;                                                                // Initializing key value...
  key_KP_4                  = false;                                                                // Initializing key value...
  key_KP_5                  = false;                                                                // Initializing key value...
  key_KP_6                  = false;                                                                // Initializing key value...
  key_KP_7                  = false;                                                                // Initializing key value...
  key_KP_8                  = false;                                                                // Initializing key value...
  key_KP_9                  = false;                                                                // Initializing key value...
  key_KP_DECIMAL            = false;                                                                // Initializing key value...
  key_KP_DIVIDE             = false;                                                                // Initializing key value...
  key_KP_MULTIPLY           = false;                                                                // Initializing key value...
  key_KP_SUBTRACT           = false;                                                                // Initializing key value...
  key_KP_ADD                = false;                                                                // Initializing key value...
  key_KP_ENTER              = false;                                                                // Initializing key value...
  key_KP_EQUAL              = false;                                                                // Initializing key value...
  key_LEFT_SHIFT            = false;                                                                // Initializing key value...
  key_LEFT_CONTROL          = false;                                                                // Initializing key value...
  key_LEFT_ALT              = false;                                                                // Initializing key value...
  key_LEFT_SUPER            = false;                                                                // Initializing key value...
  key_RIGHT_SHIFT           = false;                                                                // Initializing key value...
  key_RIGHT_CONTROL         = false;                                                                // Initializing key value...
  key_RIGHT_ALT             = false;                                                                // Initializing key value...
  key_RIGHT_SUPER           = false;                                                                // Initializing key value...
  key_MENU                  = false;                                                                // Initializing key value...
  key_LAST                  = false;                                                                // Initializing key value...

  // BUTTONS:
  button_A                  = false;                                                                // Initializing button value...
  button_B                  = false;                                                                // Initializing button value...
  button_X                  = false;                                                                // Initializing button value...
  button_Y                  = false;                                                                // Initializing button value...
  button_CROSS              = false;                                                                // Initializing button value...
  button_CIRCLE             = false;                                                                // Initializing button value...
  button_SQUARE             = false;                                                                // Initializing button value...
  button_TRIANGLE           = false;                                                                // Initializing button value...
  button_LEFT_BUMPER        = false;                                                                // Initializing button value...
  button_RIGHT_BUMPER       = false;                                                                // Initializing button value...
  button_BACK               = false;                                                                // Initializing button value...
  button_START              = false;                                                                // Initializing button value...
  button_GUIDE              = false;                                                                // Initializing button value...
  button_LEFT_THUMB         = false;                                                                // Initializing button value...
  button_RIGHT_THUMB        = false;                                                                // Initializing button value...
  button_DPAD_UP            = false;                                                                // Initializing button value...
  button_DPAD_RIGHT         = false;                                                                // Initializing button value...
  button_DPAD_DOWN          = false;                                                                // Initializing button value...
  button_DPAD_LEFT          = false;                                                                // Initializing button value...

  // AXES:
  axis_RIGHT_X              = 0.0f;                                                                 // Initializing axis value...
  axis_RIGHT_Y              = 0.0f;                                                                 // Initializing axis value...
  axis_RIGHT_TRIGGER        = -1.0f;                                                                // Initializing axis value...
  axis_LEFT_X               = 0.0f;                                                                 // Initializing axis value...
  axis_LEFT_Y               = 0.0f;                                                                 // Initializing axis value...
  axis_LEFT_TRIGGER         = -1.0f;                                                                // Initializing axis value...

  int         glfw_ver_major;
  int         glfw_ver_minor;
  int         glfw_rev;
  std::string glfw_ver_string;

  int         opengl_ver_major;                                                                     // OpenGL version major number.
  int         opengl_ver_minor;                                                                     // OpenGL version minor number.
  int         opengl_msaa;                                                                          // OpenGL multisampling antialiasing factor.
  char        opengl_ver_string[64];                                                                // OpenGL version as string (for ImGui initializaton).

  opengl_ver_major                 = 4;                                                             // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_ver_minor                 = 6;                                                             // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_msaa                      = 4;                                                             // 3 or 4 is good due to the oversampling-decimation method.

  loc_title_size                   = loc_title.size ();                                             // Getting source size...
  loc_title_buffer                 = new char[loc_title_size + 1]();
  loc_title.copy (loc_title_buffer, loc_title.size ());                                             // Copying title into char buffer...
  loc_title_buffer[loc_title_size] = '\0';                                                          // NULL-terminating char buffer...

  glfwGetVersion (&glfw_ver_major, &glfw_ver_minor, &glfw_rev);                                     // Getting GLFW version...

  // Building up glfw version string:
  glfw_ver_string                  = "initializing GLFW... found version " +
                                     std::to_string (glfw_ver_major) +                              // GLFW major version.
                                     std::to_string (glfw_ver_minor) +                              // GLFW minor version.
                                     std::to_string (glfw_rev);                                     // GLFW revision.

  neutrino::action (glfw_ver_string);                                                               // Printing message...

  // Initializing GLFW context:
  if(glfwInit () == GLFW_TRUE)                                                                      // Inititalizing GLFW context...
  {
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, opengl_ver_major);                                  // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, opengl_ver_minor);                                  // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                                           // Initializing GLFW hints...
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                                 // Initializing GLFW hints...
    glfwWindowHint (GLFW_SAMPLES, opengl_msaa);                                                     // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
  }

  else
  {
    neutrino::error ("unable to initialize GLFW!\n");                                               // Printing message...
    glfwTerminate ();                                                                               // Terminating GLFW context...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  glfw_window = glfwCreateWindow
                (
                 window_size_x,                                                                     // Window x-size [px].
                 window_size_y,                                                                     // Window y-size [px].
                 loc_title_buffer,                                                                  // Window title.
                 NULL,                                                                              // Monitor.
                 NULL                                                                               // Share.
                );

  delete loc_title_buffer;

  if(!glfw_window)
  {
    neutrino::error ("unable to create window!\n");                                                 // Printing message...
    glfwTerminate ();                                                                               // Terminating GLFW context...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  glfwSetWindowUserPointer (glfw_window, this);                                                     // Getting window pointer...
  glfwMakeContextCurrent (glfw_window);                                                             // Making the context current for the calling thread...

  glfwSetWindowRefreshCallback (glfw_window, refresh_callback);                                     // Setting refresh callback...
  glfwSetWindowSizeCallback (glfw_window, window_resize_callback);                                  // Setting window resize callback...
  glfwSetFramebufferSizeCallback (glfw_window, framebuffer_resize_callback);                        // Setting framebuffer resize callback...
  glfwSetKeyCallback (glfw_window, key_pressed_callback);                                           // Setting key pressed callback...
  glfwSetMouseButtonCallback (glfw_window, mouse_button_callback);                                  // Setting mouse pressed callback...
  glfwSetCursorPosCallback (glfw_window, mouse_moved_callback);                                     // Setting mouse moved callback...
  glfwSetScrollCallback (glfw_window, mouse_scrolled_callback);                                     // Setting mouse scrolled callback...

  neutrino::done ();                                                                                // Printing message...

  // Initializing GLAD OpenGL extension loader:
  neutrino::action ("initializing GLAD...");                                                        // Printing message...

  if(gladLoadGL ())
  {
    neutrino::done ();                                                                              // Printing message...
  }

  else
  {
    neutrino::error ("unable to initialize GLAD!\n");                                               // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Initializing OpenGL:
  neutrino::action ("initializing OpenGL...");                                                      // Printing message...

  glfwGetWindowSize (glfw_window, &window_size_x, &window_size_y);                                  // Getting window size...
  glfwGetFramebufferSize
  (
   // Getting framebuffer size...
   glfw_window,
   &framebuffer_size_x,
   &framebuffer_size_y
  );                                                                                                // Getting window size...
  aspect_ratio = (float)framebuffer_size_x/(float)framebuffer_size_y;                               // Setting window aspect ration []...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);                                                            // Setting color for clearing window...
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                              // Clearing window...

  // SETTINGS FOR TRANSPARENCY:
  glDisable (GL_DEPTH_TEST);                                                                        // Disabling depth test...
  glEnable (GL_PROGRAM_POINT_SIZE);                                                                 // Enabling "gl_PointSize" in vertex shader...
  glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);                                                // Setting blending function...
  glEnable (GL_BLEND);                                                                              // Enabling alpha blending...

  PR_mode = MONOCULAR;                                                                              // Setting monoscopic projection mode...

  // Setting monoscopic perspective:
  perspective_mono
  (
   P_mat,                                                                                           // 4x4 perspective matrix.
   NU_FOV*M_PI/180.0f,                                                                              // Field of view [rad].
   aspect_ratio,                                                                                    // Projective screen aspect ratio (full screen).
   NU_NEAR_Z_CLIP,                                                                                  // Projective screen near depth...
   NU_FAR_Z_CLIP                                                                                    // Projective screen near depth...
  );

  // Setting stereoscopic perspective:
  perspective_stereo
  (
   PL_mat,                                                                                          // 4x4 right eye perspective matrix.
   PR_mat,                                                                                          // 4x4 left eye perspective matrix.
   TL_mat,                                                                                          // 4x4 right eye translation matrix.
   TR_mat,                                                                                          // 4x4 left eye translation matrix.
   NU_IOD,                                                                                          // Intraocular distance.
   NU_FOV*M_PI/180.0f,                                                                              // Field of view [rad].
   aspect_ratio/2.0f,                                                                               // Projective screen aspect ratio (half screen).
   NU_NEAR_Z_CLIP,                                                                                  // Projective screen near depth...
   NU_FAR_Z_CLIP                                                                                    // Projective screen near depth...
  );

  translate (T_mat, T_mat_old, initial_scene_position);                                             // Setting initial scene position...
  backup (T_mat_old, T_mat);                                                                        // Backing up translation matrix...

  glfwSwapInterval (1);                                                                             // Enabling screen vertical retrace synch (vsync)...
  glfwSwapBuffers (glfw_window);                                                                    // Swapping front and back buffers...
  glfwPollEvents ();                                                                                // Polling GLFW events...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  neutrino::glfw_window = glfw_window;                                                              // Setting glfw window...

  snprintf (opengl_ver_string, 64, "#version %d%d0", opengl_ver_major, opengl_ver_minor);           // Building OpenGL version string...
  IMGUI_CHECKVERSION ();                                                                            // Checking ImGui version...
  ImGui::CreateContext ();                                                                          // Creating ImGui context...
  ImGuiIO &io = ImGui::GetIO ();                                                                    // Getting ImGuiIO handle...
  (void)io;                                                                                         // Casting ImGuiIO handle to void...
  ImGui::StyleColorsDark ();                                                                        // Setting ImGui style...
  ImGui_ImplGlfw_InitForOpenGL (glfw_window, true);                                                 // Initializing ImGui context...
  ImGui_ImplOpenGL3_Init (opengl_ver_string);                                                       // Initializing ImGui renderer...
  ImPlot::CreateContext ();                                                                         // Initializing ImPlot context...
  nu::opengl::init_done = true;                                                                     // Setting init_done flag...

  neutrino::done ();                                                                                // Printing message...
}

void nu::opengl::poll_events ()
{

  glfwPollEvents ();                                                                                // Polling GLFW events...

  if(glfwJoystickPresent ( GLFW_JOYSTICK_1 ))                                                       // Checking whether a joystick is present...
  {
    if(glfwJoystickIsGamepad (GLFW_JOYSTICK_1))                                                     // Checking whether the joystick is a gamepad...
    {
      if(glfwGetGamepadState (GLFW_JOYSTICK_1, &gamepad))                                           // Getting gamepad state...
      {
        // BUTTONS:
        button_A            = gamepad.buttons[GLFW_GAMEPAD_BUTTON_A];
        button_B            = gamepad.buttons[GLFW_GAMEPAD_BUTTON_B];
        button_X            = gamepad.buttons[GLFW_GAMEPAD_BUTTON_X];
        button_Y            = gamepad.buttons[GLFW_GAMEPAD_BUTTON_Y];
        button_CROSS        = gamepad.buttons[GLFW_GAMEPAD_BUTTON_CROSS];                           // = A;
        button_CIRCLE       = gamepad.buttons[GLFW_GAMEPAD_BUTTON_CIRCLE];                          // = B;
        button_SQUARE       = gamepad.buttons[GLFW_GAMEPAD_BUTTON_SQUARE];                          // = X;
        button_TRIANGLE     = gamepad.buttons[GLFW_GAMEPAD_BUTTON_TRIANGLE];                        // = Y;
        button_LEFT_BUMPER  = gamepad.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
        button_RIGHT_BUMPER = gamepad.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER];
        button_BACK         = gamepad.buttons[GLFW_GAMEPAD_BUTTON_BACK];
        button_START        = gamepad.buttons[GLFW_GAMEPAD_BUTTON_START];
        button_GUIDE        = gamepad.buttons[GLFW_GAMEPAD_BUTTON_GUIDE];
        button_LEFT_THUMB   = gamepad.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB];
        button_RIGHT_THUMB  = gamepad.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB];
        button_DPAD_UP      = gamepad.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP];
        button_DPAD_RIGHT   = gamepad.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT];
        button_DPAD_DOWN    = gamepad.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN];
        button_DPAD_LEFT    = gamepad.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT];

        // AXES:
        axis_RIGHT_X        = float (gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
        axis_RIGHT_Y        = float (gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
        axis_RIGHT_TRIGGER  = float (gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
        axis_LEFT_X         = float (gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
        axis_LEFT_Y         = float (gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
        axis_LEFT_TRIGGER   = float (gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
      }
    }
  }
}

void nu::opengl::orbit
(
 float loc_orbit_x,                                                                                 // "Near clipping-plane" x-coordinates.
 float loc_orbit_y,                                                                                 // "Near clipping-plane" y-coordinates.
 float loc_orbit_rate,                                                                              // Orbit angular rate coefficient [rev/s].
 float loc_orbit_deadzone,                                                                          // Orbit deadzone threshold coefficient.
 float loc_orbit_decaytime                                                                          // Orbit low pass decay time [s].
)
{
  float loc_orbit_initial[3];                                                                       // Initial orbit vector.
  float loc_orbit_final[3];                                                                         // Final orbit vector.
  float loc_axis[3];                                                                                // Arcball axis of rotation.
  float loc_theta;                                                                                  // Arcball angle of rotation.
  float loc_OP_squared;                                                                             // Center to arcball surface vector length.
  float loc_alpha;                                                                                  // LP filter decay constant.
  float loc_dt;                                                                                     // Baseline loop time [s].

  loc_dt               = float (neutrino::loop_time);                                               // Getting loop time [s]...

  loc_orbit_initial[0] = 0.0f;                                                                      // Building initial world vector...
  loc_orbit_initial[1] = 0.0f;                                                                      // Building initial world vector...
  loc_orbit_initial[2] = 1.0f;                                                                      // Building initial world vector...

  // Constraining input values:
  loc_orbit_x          = neutrino::constrain_float
                         (
                          loc_orbit_x,                                                              // Initial x-orbit.
                          NU_GAMEPAD_MIN_AXES,                                                      // Minimum x-orbit.
                          NU_GAMEPAD_MAX_AXES                                                       // Maximum x-orbit.
                         );
  loc_orbit_y          = neutrino::constrain_float
                         (
                          loc_orbit_y,                                                              // Initial y-orbit.
                          NU_GAMEPAD_MIN_AXES,                                                      // Minimum y-orbit.
                          NU_GAMEPAD_MAX_AXES                                                       // Maximum y-orbit.
                         );

  loc_orbit_rate       = neutrino::constrain_float
                         (
                          loc_orbit_rate,                                                           // Orbit angular rate [rev/s].
                          NU_GAMEPAD_MIN_ORBIT_RATE,                                                // Minimum orbit angular rate [rev/s].
                          NU_GAMEPAD_MAX_ORBIT_RATE                                                 // Maximum orbit angular rate [rev/s].
                         );

  loc_orbit_deadzone   = neutrino::constrain_float
                         (
                          loc_orbit_deadzone,                                                       // Orbit deadzone.
                          NU_GAMEPAD_MIN_AXES,                                                      // Minimum gampad axes value.
                          NU_GAMEPAD_MAX_AXES                                                       // Maximum gampad axes value.
                         );

  loc_orbit_decaytime  = neutrino::constrain_float
                         (
                          loc_orbit_decaytime,                                                      // Orbit LP filter decay time [s].
                          NU_GAMEPAD_MIN_DECAYTIME,                                                 // Minimum orbit LP filter decay time [s].
                          NU_GAMEPAD_MAX_DECAYTIME                                                  // Maximum orbit LP filter decay time [s].
                         );

  // Applying deadzone:
  if((abs (loc_orbit_x) <= loc_orbit_deadzone) &&
     (abs (loc_orbit_y) <= loc_orbit_deadzone))
  {
    loc_orbit_x = 0.0f;                                                                             // Justifying value...
    loc_orbit_y = 0.0f;                                                                             // Justifying value...
  }

  // Computing LP filter:
  loc_alpha          = (float) exp (-2.0f*M_PI*loc_dt/loc_orbit_decaytime);                         // Computing filter parameter "alpha"...
  orbit_x            = loc_orbit_x + loc_alpha*(orbit_x_old - loc_orbit_x);                         // Filtering...
  orbit_y            = loc_orbit_y + loc_alpha*(orbit_y_old - loc_orbit_y);                         // Filtering...
  orbit_x_old        = orbit_x;                                                                     // Backing up...
  orbit_y_old        = orbit_y;                                                                     // Backing up...

  // Computing arcball:
  loc_orbit_final[0] = orbit_x;                                                                     // Setting x-point on arcball...
  loc_orbit_final[1] = orbit_y;                                                                     // Setting y-point on arcball...
  loc_orbit_final[2] = 0.0f;                                                                        // Setting z-point on arcball...
  loc_OP_squared     = loc_orbit_final[0]*loc_orbit_final[0] +
                       loc_orbit_final[1]*loc_orbit_final[1];                                       // Computing OP segment...

  if(loc_OP_squared <= 1.0f)
  {
    loc_orbit_final[2] = sqrt (1.0f - loc_OP_squared);                                              // Computing z-point on arcball...
  }
  else
  {
    normalize (loc_orbit_final);                                                                    // Computing z-point on arcball (in case too far)...
  }

  loc_theta          = loc_orbit_rate*2.0f*M_PI*loc_dt*angle
                       (
                        loc_orbit_initial,
                        loc_orbit_final
                       );                                                                           // Computing orbit angle for a rate of 2*pi rad/s...

  // Doing rotation:
  if(loc_theta > 0.0f)                                                                              // Checking for valid rotation angle...
  {
    cross (loc_axis, loc_orbit_initial, loc_orbit_final);                                           // Computing orbit axis of rotation...
    normalize (loc_axis);                                                                           // Normalizing rotation 3D axis...
    quaternion (q, loc_axis, loc_theta);                                                            // Computing rotation quaternion...
    rotate (R_mat, R_mat_old, q);                                                                   // Computing rotation matrix...
    euler (&roll, &pitch, &yaw, q);                                                                 // Computing Euler (Tait-Bryan) angles...
    backup (R_mat_old, R_mat);                                                                      // Backing up rotation matrix...
  }
}

void nu::opengl::pan
(
 float loc_pan_x,                                                                                   // World x-pan.
 float loc_pan_y,                                                                                   // World y-pan.
 float loc_pan_z,                                                                                   // World z-pan.
 float loc_pan_rate,                                                                                // Pan rate [units/s].
 float loc_pan_deadzone,                                                                            // Pan deadzone threshold coefficient.
 float loc_pan_decaytime                                                                            // Pan low pass decay time [s].
)
{
  float loc_initial_pan[3];
  float loc_final_pan[3];
  float translation[3];
  float loc_alpha;
  float loc_dt;                                                                                     // Baseline loop time [s].

  loc_dt             = float (neutrino::loop_time);                                                 // Getting loop time [s]...

  loc_initial_pan[0] = 0.0f;                                                                        // Building initial pan vector...
  loc_initial_pan[1] = 0.0f;                                                                        // Building initial pan vector...
  loc_initial_pan[2] = 0.0f;                                                                        // Building initial pan vector...

  // Constraining input values:
  loc_pan_x          = neutrino::constrain_float
                       (
                        loc_pan_x,                                                                  // Initial x-pan.
                        NU_GAMEPAD_MIN_AXES,                                                        // Minimum x-pan.
                        NU_GAMEPAD_MAX_AXES                                                         // Maximum x-pan.
                       );
  loc_pan_y          = neutrino::constrain_float
                       (
                        loc_pan_y,                                                                  // Initial y-pan.
                        NU_GAMEPAD_MIN_AXES,                                                        // Minimum y-pan.
                        NU_GAMEPAD_MAX_AXES                                                         // Maximum y-pan.
                       );
  loc_pan_z          = neutrino::constrain_float
                       (
                        loc_pan_z,                                                                  // Initial z-pan.
                        NU_GAMEPAD_MIN_AXES,                                                        // Minimum z-pan.
                        NU_GAMEPAD_MAX_AXES                                                         // Maximum z-pan.
                       );

  // Applying deadzone:
  if((abs (loc_pan_x) <= loc_pan_deadzone) &&
     (abs (loc_pan_y) <= loc_pan_deadzone) &&
     (abs (loc_pan_z) <= loc_pan_deadzone))
  {
    loc_pan_x = 0.0f;                                                                               // Justifying value...
    loc_pan_y = 0.0f;                                                                               // Justifying value...
    loc_pan_z = 0.0f;                                                                               // Justifying value...
  }

  // Computing LP filter:
  loc_alpha        = (float) exp (-2.0f*M_PI*loc_dt/loc_pan_decaytime);                             // Computing filter parameter "alpha"...

  pan_x            = loc_pan_x + loc_alpha*(pan_x_old - loc_pan_x);                                 // Filtering...
  pan_y            = loc_pan_y + loc_alpha*(pan_y_old - loc_pan_y);                                 // Filtering...
  pan_z            = loc_pan_z + loc_alpha*(pan_z_old - loc_pan_z);                                 // Filtering...

  pan_x_old        = pan_x;                                                                         // Backing up...
  pan_y_old        = pan_y;                                                                         // Backing up...
  pan_z_old        = pan_z;                                                                         // Backing up...

  loc_final_pan[0] = pan_x;                                                                         // Setting up final x-pan...
  loc_final_pan[1] = pan_y;                                                                         // Setting up final y-pan...
  loc_final_pan[2] = pan_z;                                                                         // Setting up final z-pan...

  // Doing translation:
  translation[0]   = loc_pan_rate*loc_dt*(loc_final_pan[0] - loc_initial_pan[0]);                   // Computing translation vector...
  translation[1]   = loc_pan_rate*loc_dt*(loc_final_pan[1] - loc_initial_pan[1]);                   // Computing translation vector...
  translation[2]   = loc_pan_rate*loc_dt*(loc_final_pan[2] - loc_initial_pan[2]);                   // Computing translation vector...

  translate
  (
   T_mat,
   T_mat_old,
   translation
  );                                                                                                // Computing translation matrix...

  backup
  (
   T_mat_old,
   T_mat
  );                                                                                                // Backing up translation matrix...
}

void nu::opengl::mouse_navigation (
                                   float loc_orbit_rate,                                            // Orbit angular rate coefficient [rev/s].
                                   float loc_pan_rate,                                              // Pan translation rate [m/s].
                                   float loc_decaytime                                              // Low pass filter decay time [s].
                                  )
{
  float dt          = 0.0;
  float dt_min      = 0.01;
  float dt_max      = 0.05;
  float loc_orbit_x = 0.0;
  float loc_orbit_y = 0.0;
  float loc_pan_x   = 0.0;
  float loc_pan_y   = 0.0;
  float loc_pan_z   = 0.0;
  float loc_vx      = 0.0;
  float loc_vy      = 0.0;
  float loc_vz      = 0.0;

  if(mouse_sample)                                                                                  // Sampling mouse position...
  {
    mouse_x_old  = mouse_x;                                                                         // Backing up mouse x-axis...
    mouse_y_old  = mouse_y;                                                                         // Backing up mouse y-axis...
    mouse_z_old  = mouse_z;                                                                         // Backing up mouse z-axis...
    mouse_x      = mouse_X;                                                                         // Getting mouse x-axis...
    mouse_y      = mouse_Y;                                                                         // Getting mouse y-axis...
    mouse_z      = scroll_Y;                                                                        // Getting mouse z-axis...
    mouse_sample = false;                                                                           // Resetting sample flag...
  }
  else
  {
    mouse_x      = mouse_X;                                                                         // Getting mouse x-axis...
    mouse_y      = mouse_Y;                                                                         // Getting mouse y-axis...
    mouse_z      = scroll_Y;                                                                        // Getting mouse z-axis...
    mouse_sample = true;                                                                            // Setting sample flag...
  }

  dt     = neutrino::constrain_float (neutrino::loop_time, dt_min, dt_max);                         // Getting loop time...
  loc_vx = +(mouse_x - mouse_x_old)/(window_size_x*dt);                                             // Computing mouse x-velocity [px/s]...
  loc_vy = -(mouse_y - mouse_y_old)/(window_size_y*dt);                                             // Computing mouse y-velocity [px/s]...
  loc_vz = +(mouse_z - mouse_z_old)/(window_size_y*dt);                                             // Computing mouse z-velocity [px/s]...

  // Doing mouse orbit movement...
  if(mouse_LEFT)
  {
    loc_orbit_x = loc_vx;
    loc_orbit_y = loc_vy;
  }

  // Doing mouse pan movement...
  if(mouse_RIGHT)
  {
    loc_pan_x = loc_vx;
    loc_pan_y = loc_vy;
    loc_pan_z = 0.0;
  }

  if(mouse_z != 0.0)
  {
    loc_pan_z = mouse_z;
  }

  orbit (
         loc_orbit_x,                                                                               // "Near clipping-plane" x-coordinate.
         loc_orbit_y,                                                                               // "Near clipping-plane" y-coordinate.
         loc_orbit_rate,                                                                            // Orbit angular rate coefficient [rev/s].
         0.0,                                                                                       // Orbit deadzone threshold coefficient.
         loc_decaytime                                                                              // Orbit low pass decay time [s].
        );

  pan (
       loc_pan_x,                                                                                   // World x-pan.
       loc_pan_y,                                                                                   // World y-pan.
       loc_pan_z,                                                                                   // World z-pan.
       loc_pan_rate,                                                                                // Pan rate [length/s].
       0.0,                                                                                         // Pan deadzone threshold coefficient.
       loc_decaytime                                                                                // Pan low pass decay time [s].
      );

  scroll_Y = 0;                                                                                     // Resetting scroll_Y...
}

void nu::opengl::gamepad_navigation (
                                     float loc_orbit_rate,                                          // Orbit angular rate coefficient [rev/s].
                                     float loc_pan_rate,                                            // Pan translation rate [m/s].
                                     float loc_decaytime,                                           // Low pass filter decay time [s].
                                     float loc_deadzone                                             // Gamepad joystick deadzone [0...1].
                                    )
{
  float loc_orbit_x;
  float loc_orbit_y;
  float loc_pan_x;
  float loc_pan_y;
  float loc_pan_z;

  loc_orbit_x = +axis_LEFT_X;                                                                       // Setting "Near clipping-plane" x-coordinate...
  loc_orbit_y = -axis_LEFT_Y;                                                                       // Setting "Near clipping-plane" y-coordinate...
  loc_pan_x   = +axis_RIGHT_X;                                                                      // Setting world x-pan...
  loc_pan_y   = -axis_RIGHT_Y;                                                                      // Setting world y-pan...
  loc_pan_z   = (axis_RIGHT_TRIGGER + 1.0)/2.0 - (axis_LEFT_TRIGGER + 1.0)/2.0;                     // Setting world z-pan...

  orbit (
         loc_orbit_x,                                                                               // "Near clipping-plane" x-coordinate.
         loc_orbit_y,                                                                               // "Near clipping-plane" y-coordinate.
         loc_orbit_rate,                                                                            // Orbit angular rate coefficient [rev/s].
         loc_deadzone,                                                                              // Orbit deadzone threshold coefficient.
         loc_decaytime                                                                              // Orbit low pass decay time [s].
        );

  pan (
       loc_pan_x,                                                                                   // World x-pan.
       loc_pan_y,                                                                                   // World y-pan.
       loc_pan_z,                                                                                   // World z-pan.
       loc_pan_rate,                                                                                // Pan rate [length/s].
       loc_deadzone,                                                                                // Pan deadzone threshold coefficient.
       loc_decaytime                                                                                // Pan low pass decay time [s].
      );
}

void nu::opengl::close ()
{
  glfwSetWindowShouldClose (glfw_window, GL_TRUE);                                                  // Setting window "closed" flag...
}

bool nu::opengl::closed ()
{
  if(glfwWindowShouldClose (glfw_window))
  {
    ImGui_ImplOpenGL3_Shutdown ();                                                                  // Deinitializing ImGui...
    ImGui_ImplGlfw_Shutdown ();                                                                     // Deinitializing ImGui...
    ImPlot::DestroyContext ();                                                                      // Deinitializing ImPlot...
    ImGui::DestroyContext ();                                                                       // Deinitializing ImGui...
    neutrino::erase ();                                                                             // Printing message...
    neutrino::action ("terminating graphics context...");                                           // Printing message...
    neutrino::done ();                                                                              // Printing message...
  }

  return(glfwWindowShouldClose (glfw_window));                                                      // Returning window closure status...
}

void nu::opengl::clear ()
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                              // Clearing window...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  ImGui_ImplOpenGL3_NewFrame ();                                                                    // Initializing ImGui...
  ImGui_ImplGlfw_NewFrame ();                                                                       // Initializing ImGui...
  ImGui::NewFrame ();                                                                               // Initializing ImGui...
}

void nu::opengl::plot
(
 nu::shader*         loc_shader,                                                                    // OpenGL shader.
 nu::projection_mode loc_mode                                                                       // OpenGL projection mode.
)
{
  PR_mode = loc_mode;                                                                               // Setting OpenGL projection mode...

  switch(PR_mode)
  {
    case MONOCULAR:
      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      // Computing view matrix:
      multiplicate (V_mat, T_mat, R_mat);                                                           // Setting view matrix...

      // Setting plot style:
      set_shader (
                  loc_shader,                                                                       // Shader.
                  V_mat,                                                                            // View matrix.
                  P_mat,                                                                            // Projection matrix.
                  (float)framebuffer_size_x,                                                        // Framebuffer size_x.
                  (float)framebuffer_size_y,                                                        // Framebuffer size_y.
                  aspect_ratio                                                                      // Framebuffer aspect ratio.
                 );

      // Drawing:
      glViewport (0, 0, window_size_x, window_size_y);
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...
      glFinish ();                                                                                  // Waiting for OpenGL to finish...
      break;

    case BINOCULAR:
      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      multiplicate (V_mat, T_mat, R_mat);                                                           // Setting view matrix...
      multiplicate (VL_mat, TL_mat, V_mat);                                                         // Setting left eye stereoscopic view matrix...
      multiplicate (VR_mat, TR_mat, V_mat);                                                         // Setting right eye stereoscopic view matrix...

      // Left eye:
      set_shader (
                  loc_shader,                                                                       // Shader.
                  VL_mat,                                                                           // View matrix.
                  PL_mat,                                                                           // Projection matrix.
                  (float)floor (framebuffer_size_x/2.0),                                            // Framebuffer size_x.
                  (float)framebuffer_size_y,                                                        // Framebuffer size_y.
                  aspect_ratio/2.0f                                                                 // Framebuffer aspect ratio.
                 );                                                                                 // Setting plot style...

      glViewport (
                  0,
                  0,
                  window_size_x/2,
                  window_size_y
                 );                                                                                 // Setting viewport...
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...

      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      // Right eye:
      set_shader (
                  loc_shader,                                                                       // Shader.
                  VR_mat,                                                                           // View matrix.
                  PR_mat,                                                                           // Projection matrix.
                  (float)floor (framebuffer_size_x/2.0),                                            // Framebuffer size_x.
                  (float)framebuffer_size_y,                                                        // Framebuffer size_y.
                  aspect_ratio/2.0f                                                                 // Framebuffer aspect ratio.
                 );                                                                                 // Setting plot style...

      // Setting plot style:
      glViewport (
                  window_size_x/2,
                  0,
                  window_size_x/2,
                  window_size_y
                 );                                                                                 // Setting viewport...
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...

      glFinish ();                                                                                  // Waiting for OpenGL to finish...
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// OPENGL BEGIN ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::begin ()
{
  nu::opengl::clear ();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// PUBLIC RETPOLINES /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::refresh ()
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glfwSwapBuffers (glfw_window);                                                                    // Swapping front and back buffers...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
}

void nu::opengl::window_resize
(
 int loc_x_size,                                                                                    // Window x-size [screen coordinates].
 int loc_y_size                                                                                     // Window y-size [screen coordinates].
)
{
  window_size_x = loc_x_size;                                                                       // Setting window_size_x...
  window_size_y = loc_y_size;                                                                       // Setting window_size_y...
}

void nu::opengl::framebuffer_resize
(
 int loc_x_size,                                                                                    // Window x-size [screen coordinates].
 int loc_y_size                                                                                     // Window y-size [screen coordinates].
)
{
  framebuffer_size_x = loc_x_size;                                                                  // Setting framebuffer_size_x...
  framebuffer_size_y = loc_y_size;                                                                  // Setting framebuffer_size_y...
  aspect_ratio       = (float)framebuffer_size_x/(float)framebuffer_size_y;                         // Setting window aspect ration []...
  perspective_mono
  (
   P_mat,
   NU_FOV*M_PI/180.0f,
   aspect_ratio,
   NU_NEAR_Z_CLIP,
   NU_FAR_Z_CLIP
  );                                                                                                // Setting Projection_matrix matrix...

  // Setting stereoscopic perspective and translation matrices:
  perspective_stereo
  (
   PL_mat,                                                                                          // 4x4 right eye perspective matrix.
   PR_mat,                                                                                          // 4x4 left eye perspective matrix.
   TL_mat,                                                                                          // 4x4 right eye translation matrix.
   TR_mat,                                                                                          // 4x4 left eye translation matrix.
   NU_IOD,                                                                                          // Intraocular distance.
   NU_FOV*M_PI/180.0f,                                                                              // Field of view [rad].
   aspect_ratio/2.0f,                                                                               // Projective screen aspect ratio.
   NU_NEAR_Z_CLIP,                                                                                  // Projective screen near depth...
   NU_FAR_Z_CLIP                                                                                    // Projective screen far depth...
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glViewport (0, 0, framebuffer_size_x, framebuffer_size_y);                                        // Resizing OpenGL viewport...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// OPENGL END /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::opengl::end ()
{
  ImGui::Render ();                                                                                 // Rendering windows...
  ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());                                         // Rendering windows...
  nu::opengl::refresh ();
}

nu::opengl::~opengl ()
{
  glfwTerminate ();                                                                                 // Terminating GLFW...
}
