#include "window.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "WINDOW" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
window::window()
{

}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PRIVATE METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window arcball function
/// ### Description:
/// Builds a 3D world vector from the 2D screen projection of the input device
/// coordinates during an orbit movement on the screen space.
void window::arcball (
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
void window::orbit ()
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
    rotate (R, R_old, q);                                                       // Computing rotation matrix...
    euler (&roll, &pitch, &yaw, q);                                             // Computing Euler (Tait-Bryan) angles...
  }
}

void window::grasp (
                    float  position[3],
                    double x,
                    double y
                   )
{
  position[0] = +x;                                                             // Building translation vector...
  position[1] = -y;                                                             // Building translation vector (OpenGL sign convention)...
  position[2] = +0.0;                                                           // Building translation vector...                                          // Building translation matrix...
}

void window::pan ()
{
  float initial_position[3];
  float final_position[3];
  float translation[3];

  grasp (initial_position, pan_x_old, pan_y_old);
  grasp (final_position, pan_x, pan_y);

  translation[0] = PAN_FACTOR*(final_position[0] - initial_position[0]);
  translation[1] = PAN_FACTOR*(final_position[1] - initial_position[1]);
  translation[2] = PAN_FACTOR*(final_position[2] - initial_position[2]);

  translate (T, T_old, translation);
}

void window::zoom ()
{
  float initial_translation;
  float final_translation;
  float translation[3];

  translation[0] = 0.0;
  translation[1] = 0.0;
  translation[2] = zoom_z;

  translate (T, T_old, translation);
  backup (T_old, T);
}

/// # OpenGL shader compile function
/// ### Description:
/// Compiles an OpenGL shader.
GLuint window::compile_shader (
                               const char* loc_shader_filename,                 // GLSL shader file name.
                               shader_type loc_shader_type                      // GLSL shader type.
                              )
{
  GLuint  shader;                                                               // Shader.
  char*   shader_source;                                                        // Shader source.
  size_t  shader_size;                                                          // Shader size [characters].
  GLint   success;                                                              // "GL_COMPILE_STATUS" flag.
  GLchar* log;                                                                  // Buffer for OpenGL error log.
  GLsizei log_size;                                                             // Size of OpenGL error log.
  char    shader_fullname[MAX_PATH_SIZE];                                       // Shader full file name.

  // Adding NEUTRINO_PATH to relative path file name:
  snprintf (
            shader_fullname,                                                    // Destination string.
            sizeof shader_fullname,                                             // Size of destination string.
            "%s%s",                                                             // Merging two strings.
            baseline -> neutrino_path -> value,                                 // Source string 1 (NEUTRINO_PATH).
            loc_shader_filename                                                 // Source string 2 (relative path).
           );

  // Loading shader from file:
  baseline -> load_file (
                         shader_fullname,                                       // Shader file.
                         &shader_source,                                        // Shader buffer.
                         &shader_size                                           // Shader buffer size.
                        );


  // Selecting shader type:
  switch(loc_shader_type)
  {
    case VERTEX:
      shader = glCreateShader (GL_VERTEX_SHADER);                               // Creating shader...
      break;

    case FRAGMENT:
      shader = glCreateShader (GL_FRAGMENT_SHADER);                             // Creating shader...
      break;
  }

  // Attaching source code to shader:
  glShaderSource (
                  shader,                                                       // GLSL shader.
                  1,                                                            // # of shaders.
                  (const char**)&shader_source,                                 // Shader source.
                  (GLint*)&shader_size                                          // Shader size.
                 );

  glCompileShader (shader);                                                     // Compiling shader...

  // Reading "GL_COMPILE_STATUS" flag:
  glGetShaderiv (
                 shader,                                                        // GLSL shader.
                 GL_COMPILE_STATUS,                                             // Requested shader parameter.
                 &success                                                       // Success status flag.
                );

  // Checking compiled shader code:
  if(!success)
  {
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_size);                      // Getting log length...
    log           = (char*) malloc (log_size + 1);                              // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog (shader, log_size + 1, NULL, log);                       // Getting log...
    printf ("%s\n", log);                                                       // Printing log...
    free (log);                                                                 // Freeing log...
    exit (1);                                                                   // Exiting...
  }

  baseline -> free_file (shader_source);                                        // Freeing shader source file...

  return (shader);                                                              // Returning shader...
}

/// # OpenGL shader build function
/// ### Description:
/// Builds an OpenGL shader.
GLuint window::build_shader (
                             const char* loc_vertex_filename,                   // Vertex shader file name.
                             const char* loc_fragment_filename                  // Fragment shader file name.
                            )
{
  GLuint vertex;                                                                // Vertex shader.
  GLuint fragment;                                                              // Fragment shader.
  GLuint program;                                                               // Shader program.

  vertex   = compile_shader (loc_vertex_filename, VERTEX);                      // Compiling vertex shader...
  fragment = compile_shader (loc_fragment_filename, FRAGMENT);                  // Compiling fragment shader...
  program  = glCreateProgram ();                                                // Creating program...
  glBindAttribLocation (program, 0, "point");                                   // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation (program, 1, "color");                                   // Binding "color" to "layout = 1" shader attribute...
  glAttachShader (program, vertex);                                             // Attaching vertex shader to program...
  glAttachShader (program, fragment);                                           // Attaching fragment shader to program...
  glLinkProgram (program);                                                      // Linking program...

  return (program);                                                             // Returning shader program...
}


void window::set_plot_style (
                             plot_style ps,                                     // Plot style.
                             float      view_matrix[16],                        // View matrix.
                             float      projection_matrix[16]                   // Projection matrix.
                            )
{
  switch(ps)
  {
    case STYLE_POINT:
      glUseProgram (point_shader);                                              // Using shader...

      // Setting View_matrix matrix on shader:
      glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                          glGetUniformLocation (
                                                point_shader,                   // Program.
                                                "View_matrix"                   // Variable.
                                               ),
                          1,                                                    // # of matrices to be modified.
                          GL_FALSE,                                             // FALSE = column major.
                          &view_matrix[0]                                       // View matrix.
                         );

      // Setting Projection_matrix matrix on shader:
      glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                          glGetUniformLocation (
                                                point_shader,                   // Program.
                                                "Projection_matrix"             // Variable.
                                               ),
                          1,                                                    // # of matrices to be modified.
                          GL_FALSE,                                             // FALSE = column major.
                          &projection_matrix[0]                                 // Projection matrix.
                         );
      break;

    default:
      glUseProgram (point_shader);                                              // Using shader...

      // Setting View_matrix matrix on shader:
      glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                          glGetUniformLocation (
                                                point_shader,                   // Program.
                                                "View_matrix"                   // Variable.
                                               ),
                          1,                                                    // # of matrices to be modified.
                          GL_FALSE,                                             // FALSE = column major.
                          &view_matrix[0]                                       // View matrix.
                         );

      // Setting Projection_matrix matrix on shader:
      glUniformMatrix4fv (
                                                                                // Getting variable's uniform location:
                          glGetUniformLocation (
                                                point_shader,                   // Program.
                                                "Projection_matrix"             // Variable.
                                               ),
                          1,                                                    // # of matrices to be modified.
                          GL_FALSE,                                             // FALSE = column major.
                          &projection_matrix[0]                                 // Projection matrix.
                         );
      break;
  }
}

/// # Initialisation function
/// ### Description:
/// Initialises GLFW context, initialises GLEW context, initialises OpenGL
/// shaders.
void window::init (
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

  // Initializing GLFW context:
  baseline -> action ("initializing GLFW...");                                  // Printing message...

  if(glfwInit () == GLFW_TRUE)                                                  // Inititalizing GLFW context...
  {
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, opengl_ver_major);              // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, opengl_ver_minor);              // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                       // Initializing GLFW hints...
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);             // Initializing GLFW hints...
    glfwWindowHint (GLFW_SAMPLES, opengl_msaa);                                 // Initializing GLFW hints... EZOR 05OCT2018: (was 4)

    baseline -> done ();                                                        // Printing message...
  }

  else
  {
    printf ("Error:  unable to initialize GLFW!\n");                            // Printing message...
    glfwTerminate ();                                                           // Terminating GLFW context...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }

  glfw_window = glfwCreateWindow (
                                  window_size_x,                                // Window x-size [px].
                                  window_size_y,                                // Window y-size [px].
                                  title,                                        // Window title.
                                  NULL,                                         // Monitor.
                                  NULL                                          // Share.
                                 );
  if(!glfw_window)
  {
    printf ("Error:  unable to create window!\n");                              // Printing message...
    glfwTerminate ();                                                           // Terminating GLFW context...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }

  glfwSetWindowUserPointer (glfw_window, this);                                 // Getting window pointer...
  glfwMakeContextCurrent (glfw_window);                                         // Making the context of this window current for the calling thread...

  glfwSetWindowRefreshCallback (glfw_window, refresh_callback);                 // Setting refresh callback...
  glfwSetWindowSizeCallback (glfw_window, window_resize_callback);              // Setting window resize callback...
  glfwSetFramebufferSizeCallback (glfw_window, framebuffer_resize_callback);    // Setting framebuffer resize callback...
  glfwSetKeyCallback (glfw_window, key_pressed_callback);                       // Setting key pressed callback...
  glfwSetMouseButtonCallback (glfw_window, mouse_button_callback);              // Setting mouse pressed callback...
  glfwSetCursorPosCallback (glfw_window, mouse_moved_callback);                 // Setting mouse moved callback...
  glfwSetScrollCallback (glfw_window, mouse_scrolled_callback);                 // Setting mouse scrolled callback...

  // Initializing GLEW context:
  baseline -> action ("initializing GLEW...");                                  // Printing message...

  glewExperimental = GL_TRUE;                                                   // Ensuring that all extensions with valid entry points will be exposed...

  if(glewInit () == GLEW_OK)                                                    // Checking GLEW initialization...
  {

    baseline -> done ();                                                        // Printing message...
  }

  else
  {
    printf ("Error:  unable to initialize GLEW!\n");                            // Printing message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }

  // Initializing shaders:
  baseline -> action ("initializing GLSL shaders...");                          // Printing message...

  point_shader = build_shader (
                               POINT_VERTEX_FILE,                               // Vertex shader file name.
                               POINT_FRAGMENT_FILE                              // Fragment shader file name.
                              );

  text_shader  = build_shader (
                               TEXT_VERTEX_FILE,                                // Vertex shader file name.
                               TEXT_FRAGMENT_FILE                               // Fragment shader file name.
                              );
  baseline -> done ();                                                          // Printing message...

  glfwGetWindowSize (glfw_window, &window_size_x, &window_size_y);              // Getting window size...
  glfwGetFramebufferSize (
                                                                                // Getting framebuffer size...
                          glfw_window,
                          &framebuffer_size_x,
                          &framebuffer_size_y
                         );                                                     // Getting window size...
  aspect_ratio = (double)framebuffer_size_x/(double)framebuffer_size_y;         // Setting window aspect ration []...
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);                                        // Setting color for clearing window...
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                          // Clearing window...
  glEnable (GL_DEPTH_TEST);                                                     // Enabling depth test...
  glEnable (GL_PROGRAM_POINT_SIZE);                                             // Enabling "gl_PointSize" in vertex shader...
  glLineWidth (LINE_WIDTH);                                                     // Setting line width...

  PR_mode      = MODE_2D;                                                       // Setting 2D projection mode...

  // Setting monoscopic perspective:
  perspective_mono (
                    P,                                                          // 4x4 perspective matrix.
                    FOV*M_PI/180.0,                                             // Field of view [rad].
                    aspect_ratio,                                               // Projective screen aspect ratio (full screen).
                    NEAR_Z_CLIP,                                                // Projective screen near depth...
                    FAR_Z_CLIP                                                  // Projective screen near depth...
                   );

  // Setting stereoscopic perspective:
  perspective_stereo (
                      PL,                                                       // 4x4 right eye perspective matrix.
                      PR,                                                       // 4x4 left eye perspective matrix.
                      TL,                                                       // 4x4 right eye translation matrix.
                      TR,                                                       // 4x4 left eye translation matrix.
                      IOD,                                                      // Intraocular distance.
                      FOV*M_PI/180.0,                                           // Field of view [rad].
                      aspect_ratio/2.0,                                         // Projective screen aspect ratio (half screen).
                      NEAR_Z_CLIP,                                              // Projective screen near depth...
                      FAR_Z_CLIP                                                // Projective screen near depth...
                     );

  translate (T, T_old, initial_scene_position);                                 // Setting initial scene position...
  backup (T_old, T);                                                            // Backing up translation matrix...

  zoom_z = zoom_z_old;                                                          // Setting initial zoom...

  glfwSwapBuffers (glfw_window);                                                // Swapping front and back buffers...
  glfwPollEvents ();                                                            // Polling GLFW events...
}

/// # Window closed function
/// ### Description:
/// Closes the graphics window.
bool window::closed ()
{
  if(glfwWindowShouldClose (glfw_window))
  {
    baseline -> erase ();                                                       // Printing message...
    baseline -> action ("finishing OpenCL program...");                         // Printing message...
    baseline -> done ();                                                        // Printing message...
  }

  return(glfwWindowShouldClose (glfw_window));                                  // Returning window closure status...
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CALLBACKS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window refresh callback function
/// ### Description:
/// Invokes the refresh retpoline function.
void window::refresh_callback (
                               GLFWwindow* loc_window                           // Window.
                              )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> refresh ();                                                            // Calling refresh retpoline...
}

/// # Window resize callback function
/// ### Description:
/// Invokes the window resize retpoline function.
void window::window_resize_callback (
                                     GLFWwindow* loc_window,                    // Window.
                                     int         loc_x_size,                    // Window x-size [screen coordinates].
                                     int         loc_y_size                     // Window y-size [screen coordinates].
                                    )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> window_resize (loc_x_size, loc_y_size);                                // Calling window resize retpoline...
}

/// # Framebuffer resize callback function
/// ### Description:
/// Invokes the framebuffer resize retpoline function.
void window::framebuffer_resize_callback (
                                          GLFWwindow* loc_window,               // Window.
                                          int         loc_x_size,               // Framebuffer x-size [px].
                                          int         loc_y_size                // Framebuffer y-size [px].
                                         )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> framebuffer_resize (loc_x_size, loc_y_size);                           // Calling framebuffer resize retpoline...
}

/// # Window key-pressed callback function
/// ### Description:
/// Invokes the key-pressed retpoline function.
void window::key_pressed_callback (
                                   GLFWwindow* loc_window,                      // Window.
                                   int         loc_key,                         // Key.
                                   int         loc_scancode,                    // Scancode.
                                   int         loc_action,                      // Action.
                                   int         loc_mods                         // Mods.
                                  )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> key_pressed (loc_key, loc_scancode, loc_action, loc_mods);             // Calling key pressed retpoline...
}

/// # Window mouse-pressed callback function
/// ### Description:
/// Invokes the mouse-pressed retpoline function.
void window::mouse_button_callback (
                                    GLFWwindow* loc_window,                     // Window.
                                    int         loc_button,                     // Button.
                                    int         loc_action,                     // Action.
                                    int         loc_mods                        // Mods.
                                   )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> mouse_button (loc_button, loc_action, loc_mods);                       // Calling mouse pressed retpoline...
}

/// # Window mouse-moved callback function
/// ### Description:
/// Invokes the mouse-moved retpoline function.
void window::mouse_moved_callback (
                                   GLFWwindow* loc_window,                      // Window.
                                   double      loc_xpos,                        // Mouse x-position [px].
                                   double      loc_ypos                         // Mouse y-position [px].
                                  )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> mouse_moved (loc_xpos, loc_ypos);                                      // Calling mouse moved retpoline...
}

/// # Window mouse-scrolled callback function
/// ### Description:
/// Invokes the mouse-scrolled retpoline function.
void window::mouse_scrolled_callback (
                                      GLFWwindow* loc_window,                   // Window.
                                      double      loc_xoffset,                  // Mouse scroll x-offset [px].
                                      double      loc_yoffset                   // Mouse scroll y-offset [px].
                                     )
{
  window* win = (window*) glfwGetWindowUserPointer (loc_window);                // Getting window pointer...
  win -> mouse_scrolled (loc_xoffset, loc_yoffset);                             // Calling mouse scrolled retpoline...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window key-pressed retpoline function
/// ### Description:
/// On ESC, closes the graphics window.
void window::key_pressed (
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
void window::mouse_button (
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
            backup (R_old, R);                                                  // Backing up rotation matrix...
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
            backup (T_old, T);                                                  // Backing up translation matrix...
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
void window::mouse_moved (
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
void window::mouse_scrolled (
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
void window::clear ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                          // Clearing window...
}

/// # Window refresh retpoline function
/// ### Description:
/// Refresh the window.
void window::refresh ()
{
  glfwSwapBuffers (glfw_window);                                                // Swapping front and back buffers...
}

/// # Window resize retpoline function
/// ### Description:
/// Resizes the window, according to the perspective and aspect ratio.
void window::window_resize (
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
void window::framebuffer_resize (
                                 int loc_x_size,                                // Window x-size [screen coordinates].
                                 int loc_y_size                                 // Window y-size [screen coordinates].
                                )
{
  framebuffer_size_x = loc_x_size;                                              // Setting framebuffer_size_x...
  framebuffer_size_y = loc_y_size;                                              // Setting framebuffer_size_y...
  aspect_ratio       = (double)framebuffer_size_x/(double)framebuffer_size_y;   // Setting window aspect ration []...
  perspective_mono (P, FOV*M_PI/180.0, aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);  // Setting Projection_matrix matrix...

  // Setting stereoscopic perspective and translation matrices:
  perspective_stereo (
                      PL,                                                       // 4x4 right eye perspective matrix.
                      PR,                                                       // 4x4 left eye perspective matrix.
                      TL,                                                       // 4x4 right eye translation matrix.
                      TR,                                                       // 4x4 left eye translation matrix.
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
void window::poll_events ()
{
  glfwPollEvents ();                                                            // Polling GLFW events...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PUBLIC METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Window plot function
/// ### Description:
/// Selects a plot style and plots data.
void window::plot (
                   point4*    points,
                   color4*    colors,
                   plot_style ps
                  )
{
  switch(PR_mode)
  {
    case MODE_2D:
      // Computing view matrix:
      multiplicate (V, T, R);                                                   // Setting view matrix...
      set_plot_style (ps, V, P);                                                // Setting plot style...

      // Binding "points" array:
      glEnableVertexAttribArray (LAYOUT_0);                                     // Enabling "layout = 0" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, points -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 0" attribute in vertex shader...

      // Binding "colors" array:
      glEnableVertexAttribArray (LAYOUT_1);                                     // Enabling "layout = 1" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, colors -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 1" attribute in vertex shader...

      // Drawing:
      glViewport (0, 0, window_size_x, window_size_y);
      glDrawArrays (GL_POINTS, 0, points -> size);                              // Drawing "points"...

      // Finishing:
      glDisableVertexAttribArray (LAYOUT_0);                                    // Unbinding "points" array...
      glDisableVertexAttribArray (LAYOUT_1);                                    // Unbinding "colors" array...

      break;

    case MODE_3D:
      multiplicate (V, T, R);                                                   // Setting view matrix...
      multiplicate (VL, TL, V);                                                 // Setting left eye stereoscopic view matrix...
      multiplicate (VR, TR, V);                                                 // Setting right eye stereoscopic view matrix...

      ////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////// LEFT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_plot_style (ps, VL, PL);                                              // Setting plot style...

      // Binding "points" array:
      glEnableVertexAttribArray (LAYOUT_0);                                     // Enabling "layout = 0" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, points -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 0" attribute in vertex shader...

      // Binding "colors" array:
      glEnableVertexAttribArray (LAYOUT_1);                                     // Enabling "layout = 1" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, colors -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 1" attribute in vertex shader...

      // Drawing:
      glViewport (0, 0, window_size_x/2, window_size_y);
      glDrawArrays (GL_POINTS, 0, points -> size);                              // Drawing "points"...

      // Finishing:
      glDisableVertexAttribArray (LAYOUT_0);                                    // Unbinding "points" array...
      glDisableVertexAttribArray (LAYOUT_1);                                    // Unbinding "colors" array...

      ////////////////////////////////////////////////////////////////////////////
      //////////////////////////////// RIGHT EYE /////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      set_plot_style (ps, VR, PR);                                              // Setting plot style...

      // Binding "points" array:
      glEnableVertexAttribArray (LAYOUT_0);                                     // Enabling "layout = 0" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, points -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 0" attribute in vertex shader...

      // Binding "colors" array:
      glEnableVertexAttribArray (LAYOUT_1);                                     // Enabling "layout = 1" attribute in vertex shader...
      glBindBuffer (GL_ARRAY_BUFFER, colors -> vbo);                            // Binding VBO...
      glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);            // Specifying the format for "layout = 1" attribute in vertex shader...

      // Drawing:
      glViewport (
                  window_size_x/2,
                  0,
                  window_size_x/2,
                  window_size_y
                 );
      glDrawArrays (GL_POINTS, 0, points -> size);                              // Drawing "points"...

      // Finishing:
      glDisableVertexAttribArray (LAYOUT_0);                                    // Unbinding "points" array...
      glDisableVertexAttribArray (LAYOUT_1);                                    // Unbinding "colors" array...
      break;
  }
}

/// # Window print function
/// ### Description:
/// Prints 3D text on the graphics window.
void window::print (
                    text4* text
                   )
{
  multiplicate (V, T, R);                                                       // Setting View_matrix matrix...
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
                      &V[0]                                                     // View matrix.
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
                      &P[0]                                                     // Projection matrix.
                     );

  // Binding "glyph" array:
  glEnableVertexAttribArray (LAYOUT_0);                                         // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, text -> glyph_vbo);                            // Binding glyph VBO...
  glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray (LAYOUT_1);                                         // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, text -> color_vbo);                            // Binding color VBO...
  glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays (GL_LINES, 0, text -> size);                                     // Drawing "glyphs"...

  // Finishing:
  glDisableVertexAttribArray (LAYOUT_0);                                        // Unbinding "glyph" array...
  glDisableVertexAttribArray (LAYOUT_1);                                        // Unbinding "color" array...
}

// Cockpit_AI function:
void window::cockpit_AI (
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
  glBindBuffer (GL_ARRAY_BUFFER, controller -> wings_data_vbo);                 // Binding glyph VBO...
  glVertexAttribPointer (LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray (LAYOUT_1);                                         // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer (GL_ARRAY_BUFFER, controller -> wings_colors_vbo);               // Binding color VBO...
  glVertexAttribPointer (LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays (GL_LINES, 0, controller -> wings_points);                       // Drawing "glyphs"...

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

window::~window()
{
  glfwTerminate ();                                                             // Terminating GLFW...
}
