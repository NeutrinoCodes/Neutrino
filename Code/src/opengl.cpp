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
                      float* p,                                                 // Point on unitary ball.
                      double x,                                                 // "Near clipping-plane" x-coordinate.
                      double y                                                  // "Near clipping-plane" y-coordinate.
                     )
{
  p[0] = +(float)(2.0*x/(double)framebuffer_size_x - 1.0);                      // Computing x-point on arcball...
  p[1] = -(float)(2.0*y/(double)framebuffer_size_y - 1.0);                      // Computing y-point on arcball...
  p[2] = sqrt (3.0 - p[0]*p[0] + p[1]*p[1]);                                    // Computing z-point on arcball...
  normalize (p);                                                                // Normalizing vector...
}

/// # Window orbit function
/// ### Description:
/// Rotates the view matrix according to an orbit movement.
void opengl::orbit ()
{
  float a[3];                                                                   // Mouse vector, world coordinates.
  float b[3];                                                                   // Mouse vector, world coordinates.
  float axis[3];                                                                // Arcball axis of rotation.
  float theta;                                                                  // Arcball angle of rotation.

  arcball (a, orbit_x_old, orbit_y_old);                                        // Building mouse world vector (old)...
  arcball (b, orbit_x, orbit_y);                                                // Building mouse world vector...
  theta = ROTATION_FACTOR*angle (a, b);                                         // Computing orbit angle...

  if(orbit_on && (theta > 0.0))                                                 // If mouse has been dragged (= left click + move):
  {
    cross (axis, a, b);                                                         // Computing orbit axis of rotation...
    normalize (axis);                                                           // Normalizing rotation 3D axis...
    quaternion (q, axis, theta);                                                // Computing rotation quaternion...
    rotate (R_mat, R_mat_old, q);                                               // Computing rotation matrix...
    euler (&roll, &pitch, &yaw, q);                                             // Computing Euler (Tait-Bryan) angles...
  }
}

void opengl::grasp (
                    float  position[3],
                    double x,
                    double y
                   )
{
  position[0] = +x;                                                             // Building translation vector...
  position[1] = -y;                                                             // Building translation vector (OpenGL sign convention)...
  position[2] = +0.0;                                                           // Building translation vector...                                          // Building translation matrix...
}

void opengl::pan ()
{
  float initial_position[3];
  float final_position[3];
  float translation[3];

  grasp (initial_position, pan_x_old, pan_y_old);
  grasp (final_position, pan_x, pan_y);

  translation[0] = PAN_FACTOR*(final_position[0] - initial_position[0]);
  translation[1] = PAN_FACTOR*(final_position[1] - initial_position[1]);
  translation[2] = PAN_FACTOR*(final_position[2] - initial_position[2]);

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
                         shader* loc_shader,                                    // Shader.
                         float   view_matrix[16],                               // View matrix.
                         float   projection_matrix[16]                          // Projection matrix.
                        )
{

  glUseProgram (loc_shader->program);                                           // Using shader...

  // Setting View_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            loc_shader->program,                // Program.
                                            "View_matrix"                       // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &view_matrix[0]                                           // View matrix.
                     );

  // Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            loc_shader->program,                // Program.
                                            "Projection_matrix"                 // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &projection_matrix[0]                                     // Projection matrix.
                     );
}

/// # Initialisation function
/// ### Description:
/// Initialises GLFW context, initialises GLAD context, initialises OpenGL
/// shaders.
void opengl::init (
                   neutrino*   loc_baseline,                                    // Neutrino baseline.
                   int         loc_window_size_x,                               // Window x-size [px].
                   int         loc_window_size_y,                               // Window y-size [px].
                   const char* loc_title                                        // Window title.
                  )
{
  baseline         = loc_baseline;                                              // Initializing Neutrino baseline...
  window_size_x    = loc_window_size_x;                                         // Initializing window x-size [px]...
  window_size_y    = loc_window_size_y;                                         // Initializing window y-size [px]...
  title            = loc_title;                                                 // Initializing window title...
  aspect_ratio     = (double)window_size_x/(double)window_size_y;               // Initializing window aspect ration []...

  mouse_x          = 0;                                                         // Initializing mouse x-coordinate [px]...
  mouse_y          = 0;                                                         // Initializing mouse y-coordinate [px]...

  scroll_x         = 0;                                                         // Initializing scroll x-coordinate [px]...
  scroll_y         = 0;                                                         // Initializing scroll y-coordinate [px]...

  orbit_x          = 0.0;
  orbit_y          = 0.0;
  orbit_x_old      = 0.0;
  orbit_y_old      = 0.0;
  orbit_on         = false;                                                     // Initializing orbit activation flag...

  pan_x            = 0.0;
  pan_y            = 0.0;
  pan_x_old        = 0.0;
  pan_y_old        = 0.0;
  pan_on           = false;

  zoom_z_old       = INITIAL_ZOOM;
  zoom_z           = 0.0;                                                       // Initializing zoom coefficient...

  int opengl_ver_major;                                                         // OpenGL version major number.
  int opengl_ver_minor;                                                         // OpenGL version minor number.
  int opengl_msaa;                                                              // OpenGL multisampling antialiasing factor.

  opengl_ver_major = 4;                                                         // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_ver_minor = 1;                                                         // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_msaa      = 4;                                                         // EZOR: 3 or 4 sample is good due to the general oversampling-decimation method.

  #ifdef USE_GRAPHICS
    // Initializing GLFW context:
    baseline->action ("initializing GLFW...");                                  // Printing message...

    if(glfwInit () == GLFW_TRUE)                                                // Inititalizing GLFW context...
    {
      glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, opengl_ver_major);            // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
      glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, opengl_ver_minor);            // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
      glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                     // Initializing GLFW hints...
      glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);           // Initializing GLFW hints...
      glfwWindowHint (GLFW_SAMPLES, opengl_msaa);                               // Initializing GLFW hints... EZOR 05OCT2018: (was 4)

      baseline->done ();                                                        // Printing message...
    }

    else
    {
      printf ("Error:  unable to initialize GLFW!\n");                          // Printing message...
      glfwTerminate ();                                                         // Terminating GLFW context...
      exit (EXIT_FAILURE);                                                      // Exiting...
    }

    glfw_window = glfwCreateWindow (
                                    window_size_x,                              // Window x-size [px].
                                    window_size_y,                              // Window y-size [px].
                                    title,                                      // Window title.
                                    NULL,                                       // Monitor.
                                    NULL                                        // Share.
                                   );
    if(!glfw_window)
    {
      printf ("Error:  unable to create window!\n");                            // Printing message...
      glfwTerminate ();                                                         // Terminating GLFW context...
      exit (EXIT_FAILURE);                                                      // Exiting...
    }

    glfwSetWindowUserPointer (glfw_window, this);                               // Getting window pointer...
    glfwMakeContextCurrent (glfw_window);                                       // Making the context of this window current for the calling thread...

    glfwSetWindowRefreshCallback (glfw_window, refresh_callback);               // Setting refresh callback...
    glfwSetWindowSizeCallback (glfw_window, window_resize_callback);            // Setting window resize callback...
    glfwSetFramebufferSizeCallback (glfw_window, framebuffer_resize_callback);  // Setting framebuffer resize callback...
    glfwSetKeyCallback (glfw_window, key_pressed_callback);                     // Setting key pressed callback...
    glfwSetMouseButtonCallback (glfw_window, mouse_button_callback);            // Setting mouse pressed callback...
    glfwSetCursorPosCallback (glfw_window, mouse_moved_callback);               // Setting mouse moved callback...
    glfwSetScrollCallback (glfw_window, mouse_scrolled_callback);               // Setting mouse scrolled callback...

    // Initializing GLAD OpenGL extension loader:
    baseline->action ("initializing GLAD...");                                  // Printing message...

    if(gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
    {
      baseline->done ();                                                        // Printing message...
    }

    else
    {
      printf ("Error:  unable to initialize GLAD!\n");                          // Printing message...
      exit (EXIT_FAILURE);                                                      // Exiting...
    }

    // Initializing shaders:
    baseline->action ("initializing GLSL shaders...");                          // Printing message...

    point_shader     = build_shader (
                                     POINT_VERTEX_FILE,                         // Vertex shader file name.
                                     POINT_GEOMETRY_FILE,                       // Geometry shader file name.
                                     POINT_FRAGMENT_FILE                        // Fragment shader file name.
                                    );

    voxel_shader     = build_shader (
                                     VOXEL_VERTEX_FILE,                         // Vertex shader file name.
                                     VOXEL_GEOMETRY_FILE,                       // Geometry shader file name.
                                     VOXEL_FRAGMENT_FILE                        // Fragment shader file name.
                                    );

    wireframe_shader = build_shader (
                                     WIREFRAME_VERTEX_FILE,                     // Vertex shader file name.
                                     WIREFRAME_GEOMETRY_FILE,                   // Geometry shader file name.
                                     WIREFRAME_FRAGMENT_FILE                    // Fragment shader file name.
                                    );

    shaded_shader    = build_shader (
                                     SHADED_VERTEX_FILE,                        // Vertex shader file name.
                                     SHADED_GEOMETRY_FILE,                      // Geometry shader file name.
                                     SHADED_FRAGMENT_FILE                       // Fragment shader file name.
                                    );

    text_shader      = build_shader (
                                     TEXT_VERTEX_FILE,                          // Vertex shader file name.
                                     TEXT_GEOMETRY_FILE,                        // Geometry shader file name.
                                     TEXT_FRAGMENT_FILE                         // Fragment shader file name.
                                    );
    baseline->done ();                                                          // Printing message...

    glfwGetWindowSize (glfw_window, &window_size_x, &window_size_y);            // Getting window size...
    glfwGetFramebufferSize (
                                                                                // Getting framebuffer size...
                            glfw_window,
                            &framebuffer_size_x,
                            &framebuffer_size_y
                           );                                                   // Getting window size...
    aspect_ratio = (double)framebuffer_size_x/(double)framebuffer_size_y;       // Setting window aspect ration []...
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);                                      // Setting color for clearing window...
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                        // Clearing window...
    glEnable (GL_DEPTH_TEST);                                                   // Enabling depth test...
    glEnable (GL_PROGRAM_POINT_SIZE);                                           // Enabling "gl_PointSize" in vertex shader...
    glLineWidth (LINE_WIDTH);                                                   // Setting line width...

    PR_mode      = MODE_2D;                                                     // Setting 2D projection mode...

    // Setting monoscopic perspective:
    perspective_mono (
                      P_mat,                                                    // 4x4 perspective matrix.
                      FOV*M_PI/180.0,                                           // Field of view [rad].
                      aspect_ratio,                                             // Projective screen aspect ratio (full screen).
                      NEAR_Z_CLIP,                                              // Projective screen near depth...
                      FAR_Z_CLIP                                                // Projective screen near depth...
                     );

    // Setting stereoscopic perspective:
    perspective_stereo (
                        PL_mat,                                                 // 4x4 right eye perspective matrix.
                        PR_mat,                                                 // 4x4 left eye perspective matrix.
                        TL_mat,                                                 // 4x4 right eye translation matrix.
                        TR_mat,                                                 // 4x4 left eye translation matrix.
                        IOD,                                                    // Intraocular distance.
                        FOV*M_PI/180.0,                                         // Field of view [rad].
                        aspect_ratio/2.0,                                       // Projective screen aspect ratio (half screen).
                        NEAR_Z_CLIP,                                            // Projective screen near depth...
                        FAR_Z_CLIP                                              // Projective screen near depth...
                       );

    translate (T_mat, T_mat_old, initial_scene_position);                       // Setting initial scene position...
    backup (T_mat_old, T_mat);                                                  // Backing up translation matrix...

    zoom_z = zoom_z_old;                                                        // Setting initial zoom...

    glfwSwapInterval (1);                                                       // Enabling screen vertical retrace synchronization (vsync)...
    glfwSwapBuffers (glfw_window);                                              // Swapping front and back buffers...
    glfwPollEvents ();                                                          // Polling GLFW events...
  #else
    baseline->action ("graphics disabled by user: switching to text mode...");  // Printing message...
  #endif
}

/// # Window closed function
/// ### Description:
/// Closes the graphics window.
bool opengl::closed ()
{
  #ifdef USE_GRAPHICS
    if(glfwWindowShouldClose (glfw_window))
    {
      baseline->erase ();                                                       // Printing message...
      baseline->action ("terminating graphics context...");                     // Printing message...
      baseline->done ();                                                        // Printing message...
    }

    return(glfwWindowShouldClose (glfw_window));                                // Returning window closure status...
  #else
    baseline->action ("terminating text context...");                           // Printing message...
  #endif
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CALLBACKS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window refresh callback function
/// ### Description:
/// Invokes the refresh retpoline function.
void opengl::refresh_callback (
                               GLFWwindow* loc_window                           // Window.
                              )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->refresh ();                                                              // Calling refresh retpoline...
}

/// # Window resize callback function
/// ### Description:
/// Invokes the window resize retpoline function.
void opengl::window_resize_callback (
                                     GLFWwindow* loc_window,                    // Window.
                                     int         loc_x_size,                    // Window x-size [screen coordinates].
                                     int         loc_y_size                     // Window y-size [screen coordinates].
                                    )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->window_resize (loc_x_size, loc_y_size);                                  // Calling window resize retpoline...
}

/// # Framebuffer resize callback function
/// ### Description:
/// Invokes the framebuffer resize retpoline function.
void opengl::framebuffer_resize_callback (
                                          GLFWwindow* loc_window,               // Window.
                                          int         loc_x_size,               // Framebuffer x-size [px].
                                          int         loc_y_size                // Framebuffer y-size [px].
                                         )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->framebuffer_resize (loc_x_size, loc_y_size);                             // Calling framebuffer resize retpoline...
}

/// # Window key-pressed callback function
/// ### Description:
/// Invokes the key-pressed retpoline function.
void opengl::key_pressed_callback (
                                   GLFWwindow* loc_window,                      // Window.
                                   int         loc_key,                         // Key.
                                   int         loc_scancode,                    // Scancode.
                                   int         loc_action,                      // Action.
                                   int         loc_mods                         // Mods.
                                  )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->key_pressed (loc_key, loc_scancode, loc_action, loc_mods);               // Calling key pressed retpoline...
}

/// # Window mouse-pressed callback function
/// ### Description:
/// Invokes the mouse-pressed retpoline function.
void opengl::mouse_button_callback (
                                    GLFWwindow* loc_window,                     // Window.
                                    int         loc_button,                     // Button.
                                    int         loc_action,                     // Action.
                                    int         loc_mods                        // Mods.
                                   )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->mouse_button (loc_button, loc_action, loc_mods);                         // Calling mouse pressed retpoline...
}

/// # Window mouse-moved callback function
/// ### Description:
/// Invokes the mouse-moved retpoline function.
void opengl::mouse_moved_callback (
                                   GLFWwindow* loc_window,                      // Window.
                                   double      loc_xpos,                        // Mouse x-position [px].
                                   double      loc_ypos                         // Mouse y-position [px].
                                  )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->mouse_moved (loc_xpos, loc_ypos);                                        // Calling mouse moved retpoline...
}

/// # Window mouse-scrolled callback function
/// ### Description:
/// Invokes the mouse-scrolled retpoline function.
void opengl::mouse_scrolled_callback (
                                      GLFWwindow* loc_window,                   // Window.
                                      double      loc_xoffset,                  // Mouse scroll x-offset [px].
                                      double      loc_yoffset                   // Mouse scroll y-offset [px].
                                     )
{
  opengl* win = (opengl*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win->mouse_scrolled (loc_xoffset, loc_yoffset);                               // Calling mouse scrolled retpoline...
}

void opengl::joystick_connected_callback (
                                          int loc_joystick,                     // Joystick.
                                          int loc_event                         // Joystick-connected event.
                                         )
{
  /*
     if(event == GLFW_CONNECTED)
     {
     // The joystick was connected:
     printf ("Joystick connected!\n");
     }
     else if(event == GLFW_DISCONNECTED)
     {
     // The joystick was disconnected:
     printf ("Joystick disconnected!\n");
     }*/
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window key-pressed retpoline function
/// ### Description:
/// On ESC, closes the graphics window.
void opengl::key_pressed (
                          int loc_key,                                          // Key.
                          int loc_scancode,                                     // Scancode.
                          int loc_action,                                       // Action.
                          int loc_mods                                          // Mods.
                         )
{
  // Checking key pressed:
  switch(loc_key)
  {
    case GLFW_KEY_ESCAPE:
      if(loc_action == GLFW_PRESS)
      {
        glfwSetWindowShouldClose (glfw_window, GL_TRUE);                        // Setting window "closed" flag...
      }
      break;

    case GLFW_KEY_2:
      if(loc_action == GLFW_PRESS)
      {
        PR_mode = MODE_2D;                                                      // Switching to 2D mode...
      }
      break;

    case GLFW_KEY_3:
      if(loc_action == GLFW_PRESS)
      {
        PR_mode = MODE_3D;                                                      // Switching to 3D mode...
      }
      break;
  }

}

/// # Window mouse-button retpoline function
/// ### Description:
/// Gets the mouse coordinates, checks the orbit status.
void opengl::mouse_button (
                           int loc_button,                                      // Button.
                           int loc_action,                                      // Action.
                           int loc_mods                                         // Mods.
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
            orbit_x_old =
              (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
              0.5f;                                                             // Backing up orbit_x position...
            orbit_y_old =
              (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
              0.5f;                                                             // Backing up orbit_y position...

            orbit_on    = true;                                                 // Turning on orbit...
          }
          break;

        case GLFW_RELEASE:
          if(orbit_on == true)
          {
            backup (R_mat_old, R_mat);                                          // Backing up rotation matrix...
            orbit_on = false;                                                   // Turning off orbit...
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
            pan_x_old =
              (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
              0.5f;                                                             // Backing up orbit_x position...
            pan_y_old =
              (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
              0.5f;                                                             // Backing up orbit_y position...

            pan_on    = true;                                                   // Turning on orbit...
          }
          break;

        case GLFW_RELEASE:
          if(pan_on == true)
          {
            backup (T_mat_old, T_mat);                                          // Backing up translation matrix...
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
                          double loc_xpos,                                      // Mouse position [px].
                          double loc_ypos                                       // Mouse position [px].
                         )
{
  mouse_x = loc_xpos;                                                           // Getting mouse position...
  mouse_y = loc_ypos;                                                           // Getting mouse position...

  if(orbit_on)
  {
    orbit_x = (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
              0.5f;                                                             // Computing OpenGL pixel x-coordinates...
    orbit_y = (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
              0.5f;                                                             // Computing OpenGL pixel y-coordinates...
    orbit ();                                                                   // Computing orbit...
  }

  if(pan_on)
  {
    pan_x = (mouse_x*(double)framebuffer_size_x/(double)window_size_x) +
            0.5f;                                                               // Computing OpenGL pixel x-coordinates...
    pan_y = (mouse_y*(double)framebuffer_size_y/(double)window_size_y) +
            0.5f;                                                               // Computing OpenGL pixel y-coordinates...
    pan ();
  }

}

/// # Window mouse-scrolled retpoline function
/// ### Description:
/// Gets the mouse scroll. Sets the zoom factor.
void opengl::mouse_scrolled (
                             double loc_xoffset,                                // Mouse scrolled x-position [px].
                             double loc_yoffset                                 // Mouse scrolled y-position [px].
                            )
{
  scroll_x = loc_xoffset;                                                       // Getting scroll position...
  scroll_y = loc_yoffset;                                                       // Getting scroll position...

  // Checking y-position:
  if(scroll_y > 0)
  {
    zoom_z = +ZOOM_INCREMENT;                                                   // Setting zoom-in...
  }

  // Checking y-position:
  if(scroll_y < 0)
  {
    zoom_z = -ZOOM_INCREMENT;                                                   // Setting zoom-out...
  }

  zoom ();                                                                      // Zooming...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PUBLIC RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window clear retpoline function
/// ### Description:
/// Clears the window.
void opengl::clear ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                          // Clearing window...
}

/// # Window refresh retpoline function
/// ### Description:
/// Refresh the window.
void opengl::refresh ()
{
  glfwSwapBuffers (glfw_window);                                                // Swapping front and back buffers...
}

/// # Window resize retpoline function
/// ### Description:
/// Resizes the window, according to the perspective and aspect ratio.
void opengl::window_resize (
                            int loc_x_size,                                     // Window x-size [screen coordinates].
                            int loc_y_size                                      // Window y-size [screen coordinates].
                           )
{
  window_size_x = loc_x_size;                                                   // Setting window_size_x...
  window_size_y = loc_y_size;                                                   // Setting window_size_y...
}

/// # Framebuffer resize retpoline function
/// ### Description:
/// Resizes the framebuffer, according to the perspective and aspect ratio.
void opengl::framebuffer_resize (
                                 int loc_x_size,                                // Window x-size [screen coordinates].
                                 int loc_y_size                                 // Window y-size [screen coordinates].
                                )
{
  framebuffer_size_x = loc_x_size;                                              // Setting framebuffer_size_x...
  framebuffer_size_y = loc_y_size;                                              // Setting framebuffer_size_y...
  aspect_ratio       = (double)framebuffer_size_x/(double)framebuffer_size_y;   // Setting window aspect ration []...
  perspective_mono (
                    P_mat,
                    FOV*M_PI/180.0,
                    aspect_ratio,
                    NEAR_Z_CLIP,
                    FAR_Z_CLIP
                   );                                                           // Setting Projection_matrix matrix...

  // Setting stereoscopic perspective and translation matrices:
  perspective_stereo (
                      PL_mat,                                                   // 4x4 right eye perspective matrix.
                      PR_mat,                                                   // 4x4 left eye perspective matrix.
                      TL_mat,                                                   // 4x4 right eye translation matrix.
                      TR_mat,                                                   // 4x4 left eye translation matrix.
                      IOD,                                                      // Intraocular distance.
                      FOV*M_PI/180.0,                                           // Field of view [rad].
                      aspect_ratio/2.0,                                         // Projective screen aspect ratio.
                      NEAR_Z_CLIP,                                              // Projective screen near depth...
                      FAR_Z_CLIP                                                // Projective screen far depth...
                     );

  glViewport (0, 0, framebuffer_size_x, framebuffer_size_y);                    // Resizing OpenGL viewport...
}

/// # Window poll events function
/// ### Description:
/// Polls GLFW events.
void opengl::poll_events ()
{

  glfwPollEvents ();                                                            // Polling GLFW events...

  if(glfwJoystickPresent ( GLFW_JOYSTICK_1 ))                                   // Checking joystick...
  {
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
    if(axes[R2_ANALOG] > ZOOM_THRESHOLD_PS4)
    {
      zoom_z = (axes[R2_ANALOG] + 1.0)/2.0*ZOOM_INCREMENT_PS4;
      zoom ();                                                                  // Zooming...
    }

    // Setting zoom-:
    if(axes[L2_ANALOG] > ZOOM_THRESHOLD_PS4)
    {
      zoom_z = -(axes[L2_ANALOG] + 1.0)/2.0*ZOOM_INCREMENT_PS4;
      zoom ();                                                                  // Zooming...
    }

    // Preparing for orbit movement:
    if((abs (axes[L_ANALOG_H]) <= ROTATION_THRESHOLD_PS4) &&
       (abs (axes[L_ANALOG_V]) <= ROTATION_THRESHOLD_PS4))
    {
      orbit_on    = false;                                                      // Turning off orbit...
      orbit_x_old = ROTATION_FACTOR_PS4*axes[L_ANALOG_H];
      orbit_y_old = ROTATION_FACTOR_PS4*axes[L_ANALOG_V];
      backup (R_mat_old, R_mat);                                                // Backing up rotation matrix...
    }

    // Setting orbit movement:
    if((abs (axes[L_ANALOG_H]) > ROTATION_THRESHOLD_PS4) ||
       (abs (axes[L_ANALOG_V]) > ROTATION_THRESHOLD_PS4))
    {
      orbit_on = true;
      orbit_x  = ROTATION_FACTOR_PS4*axes[L_ANALOG_H];
      orbit_y  = ROTATION_FACTOR_PS4*axes[L_ANALOG_V];
      orbit ();                                                                 // Computing orbit...
      backup (R_mat_old, R_mat);                                                // Backing up rotation matrix...
    }

    // Preparing for pan movement:
    if((abs (axes[R_ANALOG_H]) <= ROTATION_THRESHOLD_PS4) &&
       (abs (axes[R_ANALOG_V]) <= ROTATION_THRESHOLD_PS4))
    {
      pan_on    = false;                                                        // Turning off orbit...
      pan_x_old = ROTATION_FACTOR_PS4*axes[R_ANALOG_H];
      pan_y_old = ROTATION_FACTOR_PS4*axes[R_ANALOG_V];
      backup (T_mat_old, T_mat);                                                // Backing up rotation matrix...
    }

    // Setting orbit movement:
    if((abs (axes[R_ANALOG_H]) > ROTATION_THRESHOLD_PS4) ||
       (abs (axes[R_ANALOG_V]) > ROTATION_THRESHOLD_PS4))
    {
      pan_on = true;
      pan_x  = ROTATION_FACTOR_PS4*axes[R_ANALOG_H];
      pan_y  = ROTATION_FACTOR_PS4*axes[R_ANALOG_V];
      pan ();                                                                   // Computing orbit...
      backup (T_mat_old, T_mat);                                                // Backing up rotation matrix...
    }

    if( GLFW_PRESS == button[SQUARE] )
    {
      printf ("Button SQUARE pressed\n");
    }

    if( GLFW_PRESS == button[CROSS] )
    {
      glfwSetWindowShouldClose (glfw_window, GL_TRUE);                          // Setting window "closed" flag...
    }

    if( GLFW_PRESS == button[CIRCLE] )
    {
      printf ("Button CIRCLE pressed\n");
    }

    if( GLFW_PRESS == button[TRIANGLE] )
    {
      printf ("Button TRIANGLE pressed\n");
    }

    if( GLFW_PRESS == button[L1] )
    {
      printf ("Button L1 pressed\n");
    }

    if( GLFW_PRESS == button[R1] )
    {
      printf ("Button R1 pressed\n");
    }

    if( GLFW_PRESS == button[L2] )
    {
      printf ("Button L2 pressed\n");
    }

    if( GLFW_PRESS == button[R2] )
    {
      printf ("Button R2 pressed\n");
    }

    if( GLFW_PRESS == button[SHARE] )
    {
      printf ("Button SHARE pressed\n");
    }

    if( GLFW_PRESS == button[OPTIONS] )
    {
      printf ("Button OPTIONS pressed\n");
    }

    if( GLFW_PRESS == button[PS] )
    {
      printf ("Button PS pressed\n");
    }

    if( GLFW_PRESS == button[TOUCH] )
    {
      printf ("Button TOUCH pressed\n");
    }

    if( GLFW_PRESS == button[L_ANALOG] )
    {
      printf ("Button L_ANALOG pressed\n");
    }

    if( GLFW_PRESS == button[R_ANALOG] )
    {
      printf ("Button R_ANALOG pressed\n");
    }

    if( GLFW_PRESS == button[DPAD_LEFT] )
    {
      printf ("Button DPAD_LEFT pressed\n");
    }

    if( GLFW_PRESS == button[DPAD_DOWN] )
    {
      printf ("Button DPAD_DOWN pressed\n");
    }

    if( GLFW_PRESS == button[DPAD_RIGHT] )
    {
      printf ("Button DPAD_RIGHT pressed\n");
    }

    if( GLFW_PRESS == button[DPAD_UP] )
    {
      printf ("Button DPAD_UP pressed\n");
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
                   shader* loc_shader                                           // OpenGL shader.
                  )
{
  switch(PR_mode)
  {
    case MODE_MONO:
      // Computing view matrix:
      multiplicate (V_mat, T_mat, R_mat);                                       // Setting view matrix...
      set_plot_style (ps, V_mat, P_mat);                                        // Setting plot style...

      // Drawing:
      glViewport (0, 0, window_size_x, window_size_y);
      glDrawArrays (GL_POINTS, 0, NODES);                                       // Drawing "points"...

      break;

    case MODE_STEREO:
      multiplicate (V_mat, T_mat, R_mat);                                       // Setting view matrix...
      multiplicate (VL_mat, TL_mat, V_mat);                                     // Setting left eye stereoscopic view matrix...
      multiplicate (VR_mat, TR_mat, V_mat);                                     // Setting right eye stereoscopic view matrix...

      ////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////// LEFT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_plot_style (ps, VL_mat, PL_mat);                                      // Setting plot style...

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
                    NODES
                   );                                                           // Drawing "points"...

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// RIGHT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_plot_style (ps, VR_mat, PR_mat);                                      // Setting plot style...

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
                    NODES
                   );                                                           // Drawing "points"...

      break;
  }
}

/// # Window print function
/// ### Description:
/// Prints 3D text on the graphics window.
void opengl::print (
                    text4* text
                   )
{
  multiplicate (V_mat, T_mat, R_mat);                                           // Setting View_matrix matrix...
  glUseProgram (text_shader);                                                   // Using shader...

  // Setting View_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            text_shader,                        // Program.
                                            "View_matrix"                       // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &V_mat[0]                                                 // View matrix.
                     );

  // Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            text_shader,                        // Program.
                                            "Projection_matrix"                 // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &P_mat[0]                                                 // Projection matrix.
                     );

  // Binding "glyph" array:
  glEnableVertexAttribArray (LAYOUT_0);                                         // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, text->glyph_vbo);                              // Binding glyph VBO...
  glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray (LAYOUT_1);                                         // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, text->color_vbo);                              // Binding color VBO...
  glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays (GL_LINES, 0, text->size);                                       // Drawing "glyphs"...

  // Finishing:
  glDisableVertexAttribArray (LAYOUT_0);                                        // Unbinding "glyph" array...
  glDisableVertexAttribArray (LAYOUT_1);                                        // Unbinding "color" array...
}

// Cockpit_AI function:
void opengl::cockpit_AI (
                         memory_orb* controller
                        )
{
  // Rotation matrix:
  float R_AI[16] = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

  // Translation matrix:
  float T_AI[16] = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

  // View matrix:
  float V_AI[16] = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

  // Projection matrix:
  float P_AI[16] = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

  multiplicate (V_AI, T_AI, R_AI);                                              // Setting View_matrix matrix...
  glUseProgram (text_shader);                                                   // Using shader...

  // Setting View_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            text_shader,                        // Program.
                                            "View_matrix"                       // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &V_AI[0]                                                  // View matrix.
                     );

  // Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                      glGetUniformLocation (
                                            text_shader,                        // Program.
                                            "Projection_matrix"                 // Variable.
                                           ),
                      1,                                                        // # of matrices to be modified.
                      GL_FALSE,                                                 // FALSE = column major.
                      &P_AI[0]                                                  // Projection matrix.
                     );


  // Binding "glyph" array:
  glEnableVertexAttribArray (LAYOUT_0);                                         // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, controller->wings_data_vbo);                   // Binding glyph VBO...
  glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray (LAYOUT_1);                                         // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, controller->wings_colors_vbo);                 // Binding color VBO...
  glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays (GL_LINES, 0, controller->wings_points);                         // Drawing "glyphs"...

  /*

     // Binding "glyph" array:
     glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
     glBindBuffer(GL_ARRAY_BUFFER, controller->pitch_level_data_vbo);                // Binding glyph VBO...
     glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

     // Binding "color" array:
     glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
     glBindBuffer(GL_ARRAY_BUFFER, controller->pitch_level_colors_vbo);              // Binding color VBO...
     glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

     // Drawing:
     glDrawArrays(GL_LINES, 0, controller->pitch_level_points);                 // Drawing "glyphs"...

   */

  // Finishing:
  glDisableVertexAttribArray (LAYOUT_0);                                        // Unbinding "glyph" array...
  glDisableVertexAttribArray (LAYOUT_1);                                        // Unbinding "color" array...
}

opengl::~opengl()
{
  glfwTerminate ();                                                             // Terminating GLFW...
}
