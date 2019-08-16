#include "opengl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "WINDOW" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opengl::opengl()
{

}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PRIVATE METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window arcball function
/// ### Description:
/// Builds a 3D world vector from the 2D screen projection of the input device
/// coordinates during an orbit movement on the screen space.
void opengl::arcball (
                      float* p,                                                                     // Point on unitary ball.
                      double x,                                                                     // "Near clipping-plane" x-coordinate.
                      double y                                                                      // "Near clipping-plane" y-coordinate.
                     )
{
  float OP_squared;

  p[0]       = (float)x;                                                                            // Setting x-point on arcball...
  p[1]       = (float)y;                                                                            // Setting y-point on arcball...

  OP_squared = p[0]*p[0] + p[1]*p[1];                                                               // Computing OP segment...

  if(OP_squared <= 1)
  {
    p[2] = sqrt (1 - OP_squared);                                                                   // Computing z-point on arcball...
  }

  else
  {
    normalize (p);                                                                                  // Normalizing vector...
  }
}

/// # Window orbit function
/// ### Description:
/// Rotates the view matrix according to an orbit movement.
void opengl::orbit (
                    double loc_orbit_x,                                                             // "Near clipping-plane" x-coordinate.
                    double loc_orbit_y,                                                             // "Near clipping-plane" y-coordinate.
                    double loc_orbit_rate,                                                          // Orbit angular rate coefficient [rev/s].
                    double loc_orbit_deadzone,                                                      // Orbit deadzone threshold coefficient.
                    double loc_orbit_decaytime                                                      // Orbit low pass decay time [s].
                   )
{
  float  a[3];                                                                                      // Mouse vector, world coordinates.
  float  b[3];                                                                                      // Mouse vector, world coordinates.
  float  axis[3];                                                                                   // Arcball axis of rotation.
  float  theta;                                                                                     // Arcball angle of rotation.
  double alpha;

  // Preparing for orbit movement:
  orbit_rate = loc_orbit_rate;

  if((-1.0 <= loc_orbit_deadzone) &&
     (loc_orbit_deadzone <= +1.0))
  {
    orbit_deadzone = loc_orbit_deadzone;
  }

  if(loc_orbit_deadzone < -1.0)
  {
    orbit_deadzone = -1.0;
  }

  if(loc_orbit_deadzone > +1.0)
  {
    orbit_deadzone = +1.0;
  }

  if((abs (loc_orbit_x) <= orbit_deadzone) &&
     (abs (loc_orbit_y) <= orbit_deadzone))
  {
    loc_orbit_x = 0;
    loc_orbit_y = 0;
  }

  if(loc_orbit_decaytime >= NU_LP_MIN_DECAYTIME)
  {
    orbit_decaytime = loc_orbit_decaytime;
  }
  else
  {
    orbit_decaytime = NU_LP_MIN_DECAYTIME;
  }

  alpha       = exp (-2*M_PI*(baseline->loop_time/1000000.0)/orbit_decaytime);                      // Computing filter parameter "alpha"...
  orbit_x     = loc_orbit_x + alpha*(orbit_x_old - loc_orbit_x);                                    // Computing x movement...
  orbit_y     = loc_orbit_y + alpha*(orbit_y_old - loc_orbit_y);                                    // Computing y movement...
  orbit_x_old = orbit_x;                                                                            // Backing up x movement...
  orbit_y_old = orbit_y;                                                                            // Backing up y movement...

  arcball (a, 0, 0);                                                                                // Building initial mouse world vector...
  arcball (b, orbit_x, orbit_y);                                                                    // Building current mouse world vector...
  theta       = orbit_rate*2*M_PI*(baseline->loop_time/1000000.0)*angle (a, b);                     // Computing orbit angle for a rate of 2*pi rad/s...

  if(theta > 0)                                                                                     // Checking for valid rotation angle...
  {
    cross (axis, a, b);                                                                             // Computing orbit axis of rotation...
    normalize (axis);                                                                               // Normalizing rotation 3D axis...
    quaternion (q, axis, theta);                                                                    // Computing rotation quaternion...
    rotate (R_mat, R_mat_old, q);                                                                   // Computing rotation matrix...
    euler (&roll, &pitch, &yaw, q);                                                                 // Computing Euler (Tait-Bryan) angles...
    backup (R_mat_old, R_mat);                                                                      // Backing up rotation matrix...
  }
}

void opengl::grasp (
                    float  position[3],
                    double x,
                    double y
                   )
{
  position[0] = +x;                                                                                 // Building translation vector...
  position[1] = -y;                                                                                 // Building translation vector (OpenGL sign convention)...
  position[2] = +0.0;                                                                               // Building translation vector...                                          // Building translation matrix...
}

void opengl::pan ()
{
  float initial_position[3];
  float final_position[3];
  float translation[3];

  grasp (initial_position, pan_x_old, pan_y_old);
  grasp (final_position, pan_x, pan_y);

  translation[0] = NU_PAN_FACTOR*(final_position[0] - initial_position[0]);
  translation[1] = NU_PAN_FACTOR*(final_position[1] - initial_position[1]);
  translation[2] = NU_PAN_FACTOR*(final_position[2] - initial_position[2]);

  translate (T_mat, T_mat_old, translation);
}

void opengl::zoom ()
{
  float initial_translation;
  float final_translation;
  float translation[3];

  translation[0] = 0.0;
  translation[1] = 0.0;
  translation[2] = zoom_z;

  translate (T_mat, T_mat_old, translation);
  backup (T_mat_old, T_mat);
}

void opengl::set_shader (
                         shader* loc_shader,                                                        // Shader.
                         float   view_matrix[16],                                                   // View matrix.
                         float   projection_matrix[16]                                              // Projection matrix.
                        )
{

  glUseProgram (loc_shader->program);                                                               // Using shader...

  // Setting View_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                                    // Getting variable's uniform location:
                      glGetUniformLocation (
                                            loc_shader->program,                                    // Program.
                                            "V_mat"                                                 // Variable.
                                           ),
                      1,                                                                            // # of matrices to be modified.
                      GL_FALSE,                                                                     // FALSE = column major.
                      &view_matrix[0]                                                               // View matrix.
                     );

  // Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                                    // Getting variable's uniform location:
                      glGetUniformLocation (
                                            loc_shader->program,                                    // Program.
                                            "P_mat"                                                 // Variable.
                                           ),
                      1,                                                                            // # of matrices to be modified.
                      GL_FALSE,                                                                     // FALSE = column major.
                      &projection_matrix[0]                                                         // Projection matrix.
                     );
}

/// # Initialisation function
/// ### Description:
/// Initialises GLFW context, initialises GLAD context, initialises OpenGL
/// shaders.
void opengl::init (
                   neutrino*   loc_baseline,                                                        // Neutrino baseline.
                   int         loc_window_size_x,                                                   // Window x-size [px].
                   int         loc_window_size_y,                                                   // Window y-size [px].
                   std::string loc_title                                                            // Window title.
                  )
{
  char*  loc_title_buffer;
  size_t loc_title_size;

  baseline      = loc_baseline;                                                                     // Initializing Neutrino baseline...
  window_size_x = loc_window_size_x;                                                                // Initializing window x-size [px]...
  window_size_y = loc_window_size_y;                                                                // Initializing window y-size [px]...
  title         = loc_title;                                                                        // Initializing window title...
  aspect_ratio  = (double)window_size_x/(double)window_size_y;                                      // Initializing window aspect ration []...

  mouse_x       = 0;                                                                                // Initializing mouse x-coordinate [px]...
  mouse_y       = 0;                                                                                // Initializing mouse y-coordinate [px]...

  scroll_x      = 0;                                                                                // Initializing scroll x-coordinate [px]...
  scroll_y      = 0;                                                                                // Initializing scroll y-coordinate [px]...

  orbit_x       = 0.0;
  orbit_y       = 0.0;
  orbit_x_old   = 0.0;
  orbit_y_old   = 0.0;
  orbit_on      = false;                                                                            // Initializing orbit activation flag...

  pan_x         = 0.0;
  pan_y         = 0.0;
  pan_x_old     = 0.0;
  pan_y_old     = 0.0;
  pan_on        = false;

  zoom_z_old    = NU_INITIAL_ZOOM;
  zoom_z        = 0.0;                                                                              // Initializing zoom coefficient...

  int         glfw_ver_major;
  int         glfw_ver_minor;
  int         glfw_rev;
  std::string glfw_ver_string;

  int         opengl_ver_major;                                                                     // OpenGL version major number.
  int         opengl_ver_minor;                                                                     // OpenGL version minor number.
  int         opengl_msaa;                                                                          // OpenGL multisampling antialiasing factor.

  opengl_ver_major                 = 4;                                                             // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_ver_minor                 = 1;                                                             // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_msaa                      = 4;                                                             // EZOR: 3 or 4 sample is good due to the general oversampling-decimation method.

  loc_title_size                   = loc_title.size ();                                             // Getting source size...
  loc_title_buffer                 = new char[loc_title_size + 1];
  loc_title.copy (loc_title_buffer, loc_title_size + 1);
  loc_title_buffer[loc_title_size] = '\0';

  if(baseline->interop)
  {
    glfwGetVersion (&glfw_ver_major, &glfw_ver_minor, &glfw_rev);                                   // Getting GLFW version...

    // Building up glfw version string:
    glfw_ver_string = "initializing GLFW... found version " +
                      std::to_string (glfw_ver_major) +                                             // GLFW major version.
                      std::to_string (glfw_ver_minor) +                                             // GLFW minor version.
                      std::to_string (glfw_rev);                                                    // GLFW revision.

    baseline->action (glfw_ver_string);                                                             // Printing message...

    // Initializing GLFW context:
    if(glfwInit () == GLFW_TRUE)                                                                    // Inititalizing GLFW context...
    {
      glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, opengl_ver_major);                                // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
      glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, opengl_ver_minor);                                // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
      glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                                         // Initializing GLFW hints...
      glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                               // Initializing GLFW hints...
      glfwWindowHint (GLFW_SAMPLES, opengl_msaa);                                                   // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
    }

    else
    {
      baseline->error ("unable to initialize GLFW!\n");                                             // Printing message...
      glfwTerminate ();                                                                             // Terminating GLFW context...
      exit (EXIT_FAILURE);                                                                          // Exiting...
    }

    glfw_window = glfwCreateWindow (
                                    window_size_x,                                                  // Window x-size [px].
                                    window_size_y,                                                  // Window y-size [px].
                                    loc_title_buffer,                                               // Window title.
                                    NULL,                                                           // Monitor.
                                    NULL                                                            // Share.
                                   );
    delete loc_title_buffer;

    if(!glfw_window)
    {
      baseline->error ("unable to create window!\n");                                               // Printing message...
      glfwTerminate ();                                                                             // Terminating GLFW context...
      exit (EXIT_FAILURE);                                                                          // Exiting...
    }

    glfwSetWindowUserPointer (glfw_window, this);                                                   // Getting window pointer...
    glfwMakeContextCurrent (glfw_window);                                                           // Making the context of this window current for the calling thread...

    glfwSetWindowRefreshCallback (glfw_window, refresh_callback);                                   // Setting refresh callback...
    glfwSetWindowSizeCallback (glfw_window, window_resize_callback);                                // Setting window resize callback...
    glfwSetFramebufferSizeCallback (glfw_window, framebuffer_resize_callback);                      // Setting framebuffer resize callback...
    glfwSetKeyCallback (glfw_window, key_pressed_callback);                                         // Setting key pressed callback...
    glfwSetMouseButtonCallback (glfw_window, mouse_button_callback);                                // Setting mouse pressed callback...
    glfwSetCursorPosCallback (glfw_window, mouse_moved_callback);                                   // Setting mouse moved callback...
    glfwSetScrollCallback (glfw_window, mouse_scrolled_callback);                                   // Setting mouse scrolled callback...

    baseline->done ();                                                                              // Printing message...

    // Initializing GLAD OpenGL extension loader:
    baseline->action ("initializing GLAD...");                                                      // Printing message...

    if(gladLoadGL ())
    {
      baseline->done ();                                                                            // Printing message...
    }

    else
    {
      baseline->error ("unable to initialize GLAD!\n");                                             // Printing message...
      exit (EXIT_FAILURE);                                                                          // Exiting...
    }

    // Initializing OpenGL:
    baseline->action ("initializing OpenGL...");                                                    // Printing message...

    glfwGetWindowSize (glfw_window, &window_size_x, &window_size_y);                                // Getting window size...
    glfwGetFramebufferSize (
                                                                                                    // Getting framebuffer size...
                            glfw_window,
                            &framebuffer_size_x,
                            &framebuffer_size_y
                           );                                                                       // Getting window size...
    aspect_ratio = (double)framebuffer_size_x/(double)framebuffer_size_y;                           // Setting window aspect ration []...
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);                                                          // Setting color for clearing window...
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                            // Clearing window...
    glEnable (GL_DEPTH_TEST);                                                                       // Enabling depth test...
    glEnable (GL_PROGRAM_POINT_SIZE);                                                               // Enabling "gl_PointSize" in vertex shader...
    glLineWidth (NU_LINE_WIDTH);                                                                    // Setting line width...

    PR_mode      = NU_MODE_MONO;                                                                    // Setting monoscopic projection mode...

    // Setting monoscopic perspective:
    perspective_mono (
                      P_mat,                                                                        // 4x4 perspective matrix.
                      NU_FOV*M_PI/180.0,                                                            // Field of view [rad].
                      aspect_ratio,                                                                 // Projective screen aspect ratio (full screen).
                      NU_NEAR_Z_CLIP,                                                               // Projective screen near depth...
                      NU_FAR_Z_CLIP                                                                 // Projective screen near depth...
                     );

    // Setting stereoscopic perspective:
    perspective_stereo (
                        PL_mat,                                                                     // 4x4 right eye perspective matrix.
                        PR_mat,                                                                     // 4x4 left eye perspective matrix.
                        TL_mat,                                                                     // 4x4 right eye translation matrix.
                        TR_mat,                                                                     // 4x4 left eye translation matrix.
                        NU_IOD,                                                                     // Intraocular distance.
                        NU_FOV*M_PI/180.0,                                                          // Field of view [rad].
                        aspect_ratio/2.0,                                                           // Projective screen aspect ratio (half screen).
                        NU_NEAR_Z_CLIP,                                                             // Projective screen near depth...
                        NU_FAR_Z_CLIP                                                               // Projective screen near depth...
                       );

    translate (T_mat, T_mat_old, initial_scene_position);                                           // Setting initial scene position...
    backup (T_mat_old, T_mat);                                                                      // Backing up translation matrix...

    zoom_z = zoom_z_old;                                                                            // Setting initial zoom...

    glfwSwapInterval (1);                                                                           // Enabling screen vertical retrace synchronization (vsync)...
    glfwSwapBuffers (glfw_window);                                                                  // Swapping front and back buffers...
    glfwPollEvents ();                                                                              // Polling GLFW events...

    baseline->done ();                                                                              // Printing message...
  }
  else
  {
    baseline->action ("OpenCL/GL interoperability disabled by user...");                            // Printing message...
  }
}

/// # Window closed function
/// ### Description:
/// Returns "true" if graphics window has been closed.
bool opengl::closed ()
{
  if(baseline->interop)
  {
    if(glfwWindowShouldClose (glfw_window))
    {
      baseline->erase ();                                                                           // Printing message...
      baseline->action ("terminating graphics context...");                                         // Printing message...
      baseline->done ();                                                                            // Printing message...
    }

    return(glfwWindowShouldClose (glfw_window));                                                    // Returning window closure status...
  }
  else
  {
    baseline->action ("terminating text context...");                                               // Printing message...
    return (true);
  }
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CALLBACKS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window refresh callback function
/// ### Description:
/// Invokes the refresh retpoline function.
void opengl::refresh_callback (
                               GLFWwindow* loc_window                                               // Window.
                              )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->refresh ();                                                                                  // Calling refresh retpoline...
}

/// # Window resize callback function
/// ### Description:
/// Invokes the window resize retpoline function.
void opengl::window_resize_callback (
                                     GLFWwindow* loc_window,                                        // Window.
                                     int         loc_x_size,                                        // Window x-size [screen coordinates].
                                     int         loc_y_size                                         // Window y-size [screen coordinates].
                                    )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->window_resize (loc_x_size, loc_y_size);                                                      // Calling window resize retpoline...
}

/// # Framebuffer resize callback function
/// ### Description:
/// Invokes the framebuffer resize retpoline function.
void opengl::framebuffer_resize_callback (
                                          GLFWwindow* loc_window,                                   // Window.
                                          int         loc_x_size,                                   // Framebuffer x-size [px].
                                          int         loc_y_size                                    // Framebuffer y-size [px].
                                         )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->framebuffer_resize (loc_x_size, loc_y_size);                                                 // Calling framebuffer resize retpoline...
}

/// # Window key-pressed callback function
/// ### Description:
/// Invokes the key-pressed retpoline function.
void opengl::key_pressed_callback (
                                   GLFWwindow* loc_window,                                          // Window.
                                   int         loc_key,                                             // Key.
                                   int         loc_scancode,                                        // Scancode.
                                   int         loc_action,                                          // Action.
                                   int         loc_mods                                             // Mods.
                                  )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->key_pressed (loc_key, loc_scancode, loc_action, loc_mods);                                   // Calling key pressed retpoline...
}

/// # Window mouse-pressed callback function
/// ### Description:
/// Invokes the mouse-pressed retpoline function.
void opengl::mouse_button_callback (
                                    GLFWwindow* loc_window,                                         // Window.
                                    int         loc_button,                                         // Button.
                                    int         loc_action,                                         // Action.
                                    int         loc_mods                                            // Mods.
                                   )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->mouse_button (loc_button, loc_action, loc_mods);                                             // Calling mouse pressed retpoline...
}

/// # Window mouse-moved callback function
/// ### Description:
/// Invokes the mouse-moved retpoline function.
void opengl::mouse_moved_callback (
                                   GLFWwindow* loc_window,                                          // Window.
                                   double      loc_xpos,                                            // Mouse x-position [px].
                                   double      loc_ypos                                             // Mouse y-position [px].
                                  )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->mouse_moved (loc_xpos, loc_ypos);                                                            // Calling mouse moved retpoline...
}

/// # Window mouse-scrolled callback function
/// ### Description:
/// Invokes the mouse-scrolled retpoline function.
void opengl::mouse_scrolled_callback (
                                      GLFWwindow* loc_window,                                       // Window.
                                      double      loc_xoffset,                                      // Mouse scroll x-offset [px].
                                      double      loc_yoffset                                       // Mouse scroll y-offset [px].
                                     )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                                    // Getting window pointer...
  win->mouse_scrolled (loc_xoffset, loc_yoffset);                                                   // Calling mouse scrolled retpoline...
}

void opengl::joystick_connected_callback (
                                          int loc_joystick,                                         // Joystick.
                                          int loc_event                                             // Joystick-connected event.
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

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window key-pressed retpoline function
/// ### Description:
/// On ESC, closes the graphics window.
void opengl::key_pressed (
                          int loc_key,                                                              // Key.
                          int loc_scancode,                                                         // Scancode.
                          int loc_action,                                                           // Action.
                          int loc_mods                                                              // Mods.
                         )
{
  // Checking key pressed:
  switch(loc_key)
  {
    case GLFW_KEY_ESCAPE:
      if(loc_action == GLFW_PRESS)
      {
        glfwSetWindowShouldClose (glfw_window, GL_TRUE);                                            // Setting window "closed" flag...
      }
      break;

    case GLFW_KEY_2:
      if(loc_action == GLFW_PRESS)
      {
        PR_mode = NU_MODE_MONO;                                                                     // Switching to monoscopic mode...
      }
      break;

    case GLFW_KEY_3:
      if(loc_action == GLFW_PRESS)
      {
        PR_mode = NU_MODE_STEREO;                                                                   // Switching to stereoscopic mode...
      }
      break;
  }

}

/// # Window mouse-button retpoline function
/// ### Description:
/// Gets the mouse coordinates, checks the orbit status.
void opengl::mouse_button (
                           int loc_button,                                                          // Button.
                           int loc_action,                                                          // Action.
                           int loc_mods                                                             // Mods.
                          )
{
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// READING MOUSE BUTTONS: ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  switch(loc_button)
  {
    case GLFW_MOUSE_BUTTON_LEFT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          if(orbit_on == false)
          {
            /*
               orbit_x_old =
               (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
               0.5f;                                                                                 // Backing up orbit_x position...
               orbit_y_old =
               (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
               0.5f;                                                                                 // Backing up orbit_y position...
             */
            orbit_on = true;                                                                        // Turning on orbit...
          }
          break;

        case GLFW_RELEASE:
          if(orbit_on == true)
          {
            //backup (R_mat_old, R_mat);                                                              // Backing up rotation matrix...
            orbit_on = false;                                                                       // Turning off orbit...
          }
          break;
      }

      break;

    case GLFW_MOUSE_BUTTON_RIGHT:

      switch(loc_action)
      {
        case GLFW_PRESS:
          if(pan_on == false)
          {
            /*
               pan_x_old =
               (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
               0.5f;                                                                                 // Backing up orbit_x position...
               pan_y_old =
               (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
               0.5f;                                                                                 // Backing up orbit_y position...
             */
            pan_on = true;                                                                          // Turning on orbit...
          }
          break;

        case GLFW_RELEASE:
          if(pan_on == true)
          {
            //backup (T_mat_old, T_mat);                                                              // Backing up translation matrix...
            pan_on = false;
          }
          break;
      }

      break;
  }
}

/// # Window mouse-moved retpoline function
/// ### Description:
/// Gets the mouse coordinates.
void opengl::mouse_moved (
                          double loc_xpos,                                                          // Mouse position [px].
                          double loc_ypos                                                           // Mouse position [px].
                         )
{
  mouse_x = loc_xpos;                                                                               // Getting mouse position...
  mouse_y = loc_ypos;                                                                               // Getting mouse position...

  /*
     if(orbit_on)
     {
     orbit_x = (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
              0.5f;                                                                                 // Computing OpenGL pixel x-coordinates...
     orbit_y = (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
              0.5f;                                                                                 // Computing OpenGL pixel y-coordinates...
     //EZOR: orbit ();                                                                                       // Computing orbit...
     }

     if(pan_on)
     {
     pan_x = (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
            0.5f;                                                                                   // Computing OpenGL pixel x-coordinates...
     pan_y = (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
            0.5f;                                                                                   // Computing OpenGL pixel y-coordinates...
     pan ();
     }
   */

}

/// # Window mouse-scrolled retpoline function
/// ### Description:
/// Gets the mouse scroll. Sets the zoom factor.
void opengl::mouse_scrolled (
                             double loc_xoffset,                                                    // Mouse scrolled x-position [px].
                             double loc_yoffset                                                     // Mouse scrolled y-position [px].
                            )
{
  scroll_x = loc_xoffset;                                                                           // Getting scroll position...
  scroll_y = loc_yoffset;                                                                           // Getting scroll position...

  // Checking y-position:
  if(scroll_y > 0)
  {
    zoom_z = +NU_ZOOM_INCREMENT;                                                                    // Setting zoom-in...
  }

  // Checking y-position:
  if(scroll_y < 0)
  {
    zoom_z = -NU_ZOOM_INCREMENT;                                                                    // Setting zoom-out...
  }

  zoom ();                                                                                          // Zooming...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PUBLIC RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window clear retpoline function
/// ### Description:
/// Clears the window.
void opengl::clear ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                              // Clearing window...
}

/// # Window refresh retpoline function
/// ### Description:
/// Refresh the window.
void opengl::refresh ()
{
  glfwSwapBuffers (glfw_window);                                                                    // Swapping front and back buffers...
}

/// # Window resize retpoline function
/// ### Description:
/// Resizes the window, according to the perspective and aspect ratio.
void opengl::window_resize (
                            int loc_x_size,                                                         // Window x-size [screen coordinates].
                            int loc_y_size                                                          // Window y-size [screen coordinates].
                           )
{
  window_size_x = loc_x_size;                                                                       // Setting window_size_x...
  window_size_y = loc_y_size;                                                                       // Setting window_size_y...
}

/// # Framebuffer resize retpoline function
/// ### Description:
/// Resizes the framebuffer, according to the perspective and aspect ratio.
void opengl::framebuffer_resize (
                                 int loc_x_size,                                                    // Window x-size [screen coordinates].
                                 int loc_y_size                                                     // Window y-size [screen coordinates].
                                )
{
  framebuffer_size_x = loc_x_size;                                                                  // Setting framebuffer_size_x...
  framebuffer_size_y = loc_y_size;                                                                  // Setting framebuffer_size_y...
  aspect_ratio       = (double)framebuffer_size_x/(double)framebuffer_size_y;                       // Setting window aspect ration []...
  perspective_mono (
                    P_mat,
                    NU_FOV*M_PI/180.0,
                    aspect_ratio,
                    NU_NEAR_Z_CLIP,
                    NU_FAR_Z_CLIP
                   );                                                                               // Setting Projection_matrix matrix...

  // Setting stereoscopic perspective and translation matrices:
  perspective_stereo (
                      PL_mat,                                                                       // 4x4 right eye perspective matrix.
                      PR_mat,                                                                       // 4x4 left eye perspective matrix.
                      TL_mat,                                                                       // 4x4 right eye translation matrix.
                      TR_mat,                                                                       // 4x4 left eye translation matrix.
                      NU_IOD,                                                                       // Intraocular distance.
                      NU_FOV*M_PI/180.0,                                                            // Field of view [rad].
                      aspect_ratio/2.0,                                                             // Projective screen aspect ratio.
                      NU_NEAR_Z_CLIP,                                                               // Projective screen near depth...
                      NU_FAR_Z_CLIP                                                                 // Projective screen far depth...
                     );

  glViewport (0, 0, framebuffer_size_x, framebuffer_size_y);                                        // Resizing OpenGL viewport...
}

/// # Window poll events function
/// ### Description:
/// Polls GLFW events.
void opengl::poll_events ()
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
        axis_RIGHT_X        = gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        axis_RIGHT_Y        = gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
        axis_RIGHT_TRIGGER  = gamepad.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];
        axis_LEFT_X         = gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        axis_LEFT_Y         = gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        axis_LEFT_TRIGGER   = gamepad.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
      }
    }

    int                  num_buttons;
    const unsigned char* button = glfwGetJoystickButtons (
                                                          GLFW_JOYSTICK_1,
                                                          &num_buttons
                                                         );

    int                  num_axes;
    const float*         axes   = glfwGetJoystickAxes (
                                                       GLFW_JOYSTICK_1,
                                                       &num_axes
                                                      );

    // Setting zoom+:
    if(axes[NU_R2_ANALOG] > NU_ZOOM_THRESHOLD_PS4)
    {
      zoom_z = (axes[NU_R2_ANALOG] + 1.0)/2.0*NU_ZOOM_INCREMENT_PS4;
      zoom ();                                                                                      // Zooming...
    }

    // Setting zoom-:
    if(axes[NU_L2_ANALOG] > NU_ZOOM_THRESHOLD_PS4)
    {
      zoom_z = -(axes[NU_L2_ANALOG] + 1.0)/2.0*NU_ZOOM_INCREMENT_PS4;
      zoom ();                                                                                      // Zooming...
    }

    /*
       // Preparing for orbit movement:
       if((abs (axes[NU_L_ANALOG_H]) <= NU_ROTATION_THRESHOLD_PS4) &&
       (abs (axes[NU_L_ANALOG_V]) <= NU_ROTATION_THRESHOLD_PS4))
       {
       orbit_on    = false;                                                                          // Turning off orbit...
       orbit_x_old = NU_ROTATION_FACTOR_PS4*axes[NU_L_ANALOG_H];
       orbit_y_old = NU_ROTATION_FACTOR_PS4*axes[NU_L_ANALOG_V];
       backup (R_mat_old, R_mat);                                                                    // Backing up rotation matrix...
       }

       // Setting orbit movement:
       if((abs (axes[NU_L_ANALOG_H]) > NU_ROTATION_THRESHOLD_PS4) ||
       (abs (axes[NU_L_ANALOG_V]) > NU_ROTATION_THRESHOLD_PS4))
       {
       orbit_on = true;
       orbit_x  = NU_ROTATION_FACTOR_PS4*axes[NU_L_ANALOG_H];
       orbit_y  = NU_ROTATION_FACTOR_PS4*axes[NU_L_ANALOG_V];
       //EZOR: orbit ();                                                                                     // Computing orbit...
       backup (R_mat_old, R_mat);                                                                    // Backing up rotation matrix...
       }
     */

    // Preparing for pan movement:
    if((abs (axes[NU_R_ANALOG_H]) <= NU_ROTATION_THRESHOLD_PS4) &&
       (abs (axes[NU_R_ANALOG_V]) <= NU_ROTATION_THRESHOLD_PS4))
    {
      pan_on    = false;                                                                            // Turning off orbit...
      pan_x_old = NU_ROTATION_FACTOR_PS4*axes[NU_R_ANALOG_H];
      pan_y_old = NU_ROTATION_FACTOR_PS4*axes[NU_R_ANALOG_V];
      backup (T_mat_old, T_mat);                                                                    // Backing up rotation matrix...
    }

    // Setting pan movement:
    if((abs (axes[NU_R_ANALOG_H]) > NU_ROTATION_THRESHOLD_PS4) ||
       (abs (axes[NU_R_ANALOG_V]) > NU_ROTATION_THRESHOLD_PS4))
    {
      pan_on = true;
      pan_x  = NU_ROTATION_FACTOR_PS4*axes[NU_R_ANALOG_H];
      pan_y  = NU_ROTATION_FACTOR_PS4*axes[NU_R_ANALOG_V];
      pan ();                                                                                       // Computing orbit...
      backup (T_mat_old, T_mat);                                                                    // Backing up rotation matrix...
    }

    if( GLFW_PRESS == button[NU_SQUARE] )
    {
      std::cout << "Button NU_SQUARE pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_CROSS] )
    {
      glfwSetWindowShouldClose (glfw_window, GL_TRUE);                                              // Setting window "closed" flag...
    }

    if( GLFW_PRESS == button[NU_CIRCLE] )
    {
      std::cout << "Button NU_CIRCLE pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_TRIANGLE] )
    {
      std::cout << "Button NU_TRIANGLE pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_L1] )
    {
      std::cout << "Button NU_L1 pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_R1] )
    {
      std::cout << "Button NU_R1 pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_L2] )
    {
      std::cout << "Button NU_L2 pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_R2] )
    {
      std::cout << "Button NU_R2 pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_SHARE] )
    {
      std::cout << "Button NU_SHARE pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_OPTIONS] )
    {
      std::cout << "Button NU_OPTIONS pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_PS] )
    {
      std::cout << "Button NU_PS pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_TOUCH] )
    {
      std::cout << "Button NU_TOUCH pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_L_ANALOG] )
    {
      std::cout << "Button NU_L_ANALOG pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_R_ANALOG] )
    {
      std::cout << "Button NU_R_ANALOG pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_DPAD_LEFT] )
    {
      std::cout << "Button NU_DPAD_LEFT pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_DPAD_DOWN] )
    {
      std::cout << "Button NU_DPAD_DOWN pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_DPAD_RIGHT] )
    {
      std::cout << "Button NU_DPAD_RIGHT pressed" << std::endl;
    }

    if( GLFW_PRESS == button[NU_DPAD_UP] )
    {
      std::cout << "Button NU_DPAD_UP pressed" << std::endl;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PUBLIC METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window plot function
/// ### Description:
/// Selects a plot style and plots data.
void opengl::plot (
                   shader* loc_shader                                                               // OpenGL shader.
                  )
{
  switch(PR_mode)
  {
    case NU_MODE_MONO:
      // Computing view matrix:
      multiplicate (V_mat, T_mat, R_mat);                                                           // Setting view matrix...
      set_shader (loc_shader, V_mat, P_mat);                                                        // Setting plot style...

      // Drawing:
      glViewport (0, 0, window_size_x, window_size_y);
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...

      break;

    case NU_MODE_STEREO:
      multiplicate (V_mat, T_mat, R_mat);                                                           // Setting view matrix...
      multiplicate (VL_mat, TL_mat, V_mat);                                                         // Setting left eye stereoscopic view matrix...
      multiplicate (VR_mat, TR_mat, V_mat);                                                         // Setting right eye stereoscopic view matrix...

      ////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////// LEFT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_shader (loc_shader, VL_mat, PL_mat);                                                      // Setting plot style...

      // Drawing:
      glViewport (
                  0,
                  0,
                  window_size_x/2,
                  window_size_y
                 );
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// RIGHT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_shader (loc_shader, VR_mat, PR_mat);                                                      // Setting plot style...

      // Drawing:
      glViewport (
                  window_size_x/2,
                  0,
                  window_size_x/2,
                  window_size_y
                 );
      glDrawArrays (
                    GL_POINTS,
                    0,
                    loc_shader->size
                   );                                                                               // Drawing "points"...

      break;
  }
}

opengl::~opengl()
{
  glfwTerminate ();                                                                                 // Terminating GLFW...
}
