/// @file

#include "opengl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENGL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opengl::opengl()
{

}

// PRIVATE METHODS:
GLuint opengl::compile_shader(const char* loc_shader_filename, shader_type loc_shader_type)
{
  GLuint    shader;                                                             // Shader.
  char*     shader_source;                                                      // Shader source.
  size_t    shader_size;                                                        // Shader size [characters].
  GLint 		success;                                                            // "GL_COMPILE_STATUS" flag.
  GLchar*		log;                                                                // Buffer for OpenGL error log.
  GLsizei 	log_size;                                                           // Size of OpenGL error log.

  // Loading shader from file:
  load_file (
              neutrino_path->value,
              shader_filename,
              &shader_source,
              &shader_size
            );

  switch(loc_shader_type)
  {
    case VERTEX:
      shader = glCreateShader(GL_VERTEX_SHADER);                                // Creating shader...
    break;

    case FRAGMENT:
      shader = glCreateShader(GL_FRAGMENT_SHADER);                              // Creating shader...
    break;
  }

  glShaderSource(shader,                                                        // Attaching source code to shader...
                 1,
                 (const char**)&shader_source,
                 (GLint*)&shader_size);
	glCompileShader(shader);                                                      // Compiling shader...
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);                           // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled shader code:
  if (!success)
  {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);                       // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(shader, log_size + 1, NULL, log);                        // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

  free_file(shader_source);                                                     // Freeing shader source file...

  return (shader);
}

GLuint opengl::build_shader(const char* filename_vertex, const char* filename_fragment)
{
  GLuint vertex;                                                                // Vertex shader.
  GLuint fragment;                                                              // Fragment shader.
  GLuint program;                                                               // Shader program.

  vertex = compile_shader(POINT_VERTEX_FILE, VERTEX);                           // Compiling vertex shader...
  fragment = compile_shader(POINT_FRAGMENT_FILE, FRAGMENT);                     // Compiling fragment shader...
  program = glCreateProgram();                                                  // Creating program...
  glBindAttribLocation(program, 0, "point");                                    // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(program, 1, "color");                                    // Binding "color" to "layout = 1" shader attribute...
  glAttachShader(program, vertex);                                              // Attaching vertex shader to program...
  glAttachShader(program, fragment);                                            // Attaching fragment shader to program...
  glLinkProgram(program);                                                       // Linking program...

  return (program);                                                             // Returning shader program...
}

// PUBLIC METHODS:
void opengl::init(path* loc_neutrino_path)                                      // OpenGL initialization.
{
  int opengl_ver_major;                                                         // OpenGL version major number.
  int opengl_ver_minor;                                                         // OpenGL version minor number.
  int opengl_msaa;                                                              // OpenGL multisampling antialiasing factor.
  path* neutrino_path = new path();

  neutrino_path->value = loc_neutrino_path->value;
  neutrino_path->size = loc_neutrino_path->size;

  // Initializing GLFW context:
  printf("Action: initializing GLFW... ");

  if (glfwInit() == GLFW_TRUE)                                                  // Inititalizing GLFW context...
	{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver_major);                      // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver_minor);                      // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
  	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                        // Initializing GLFW hints...
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);              // Initializing GLFW hints...
  	glfwWindowHint(GLFW_SAMPLES, msaa);                                         // Initializing GLFW hints... EZOR 05OCT2018: (was 4)

    printf("DONE!\n");
  }

  else
  {
    printf("Error:  unable to initialize GLFW!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
  }

  // Initializing GLEW context:
  printf("Action: initializing GLEW... ");
  glewExperimental = GL_TRUE;                                                   // Ensuring that all extensions with valid entry points will be exposed...

	if (glewInit() == GLEW_OK)
	{

    printf("DONE!\n");
  }

  else
  {
    printf("Error:  unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }

  // Initializing shaders:
  printf("Action: initializing GLSL shaders... ");
  point_shader = build_shader(POINT_VERTEX_FILE, POINT_FRAGMENT_FILE);
  text_shader = build_shader(TEXT_VERTEX_FILE, TEXT_FRAGMENT_FILE);
  printf("DONE!\n");
}

opengl::~opengl()
{
  glfwDestroyWindow(window);                                                    // Destroying window...
  glfwTerminate();                                                              // Terminating GLFW...
  free(theneutrino_path);                                                       // Freeing theneutrino_path...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "WINDOW" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
window::window(int window_size_x, int window_size_y, const char* title)
{
  window_sx = window_size_x;                                                    // Initializing window x-size [px]...
  window_sy = window_size_y;                                                    // Initializing window y-size [px]...
  aspect_ratio = = (double)window_size_x/(double)window_size_y;                 // Initializing window aspect ration []...
  mouse_x = 0;                                                                  // Initializing mouse x-coordinate [px]...
  mouse_y = 0;                                                                  // Initializing mouse y-coordinate [px]...
  mouse_x_old = 0;                                                              // Initializing mouse x-coordinate backup [px]...
  mouse_y_old = 0;                                                              // Initializing mouse y-coordinate backup [px]...
  scroll_x = 0;                                                                 // Initializing scroll x-coordinate [px]...
  scroll_y = 0;                                                                 // Initializing scroll y-coordinate [px]...
  zoom = 0;                                                                     // Initializing zoom coefficient...
  arcball_on = false;                                                           // Initializing arcball activation flag...

  initial_translation[0] =  0.0;                                                // Building initial translation vector...
  initial_translation[1] =  0.0;                                                // Building initial translation vector...
  initial_translation[2] = -3.0;                                                // Building initial translation vector...

  q[4]      = {1.0, 0.0, 0.0, 0.0};                                             // Initializing arcball quaternion...

  R[16]     = {1.0, 0.0, 0.0, 0.0,                                              // Initializing rotation matrix...
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0};

  R_old[16] = {1.0, 0.0, 0.0, 0.0,                                              // Initializing rotation matrix backup...
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0};

  T[16]     = {1.0, 0.0, 0.0, 0.0,                                              // Initializing translation matrix...
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0};

  V[16]     = {1.0, 0.0, 0.0, 0.0,                                              // Initializing view matrix...
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0};

  P[16]     = {1.0, 0.0, 0.0, 0.0,                                              // Initializing projection matrix...
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0};
}

// PRIVATE METHODS:
void window::grasp(float* p, int x, int y)                                      // Grasp arcball action.
{
	float  op_sq;																																	// Center "o" to "p" squared distance.

	glfwGetWindowSize(glfw_window, &window_size_x, &window_size_y);							  // Getting window size...
  p[0] =   2.0*x/window_size_x - 1.0;                                           // Computing point on unitary ball [x]...
  p[1] = -(2.0*y/window_size_y - 1.0);                                          // Computing point on unitary ball [y] (axis inverted according to OpenGL)...
  p[2] =   0.0;                                                                 // Computing point on unitary ball [z]...
	op_sq = p[0]*p[0] + p[1]*p[1];                                                // Computing "op" squared...

  if (op_sq <= 1.0)																															// Checking p to ball-center distance...
	{
    p[2] = sqrt(1.0 - op_sq);  																									// Pythagoras' theorem...
	}

  else
	{
    normalize(p);  																										          // Normalizing if too far...
	}
}

void window::arcball()                                                          // Arcball computation.
{
	float a[3]; 																															    // Mouse vector, world coordinates.
	float b[3]; 																															    // Mouse vector, world coordinates.
	float axis[3];																										   		      // Arcball axis of rotation.
	float theta;																																	// Arcball angle of rotation.

	if (arcball_on &&((mouse_x != mouse_x_old) || (mouse_y != mouse_y_old)))      // If mouse has been dragged (= left click + move):
	{
		grasp(a, mouse_x_old, mouse_y_old);							  			                    // Building mouse world vector (old)...
		grasp(b, mouse_x, mouse_y);												   					              // Building mouse world vector...
		theta = ROTATION_FACTOR*angle(a, b);                                        // Calculating arcball angle...
    normalize(a);
    normalize(b);
    cross(axis, a, b);									            				                    // Calculating arcball axis of rotation...
    normalize(axis);
    rotate(R, R_old, axis, theta);                                              // Calculating rotation matrix...
	}
}

// PUBLIC METHODS:
auto window::init()                                                             // Window initialization.
{
  glfw_window = glfwCreateWindow(width,                                         // Width.
                                 height,                                        // Height.
                                 title,                                         // Title.
                                 NULL,                                          // Monitor.
                                 NULL);                                         // Share.
  if (!glfw_window)
	{
		printf("Error:  unable to create window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetWindowUserPointer(glfw_window, this);
  glfwMakeContextCurrent(glfw_window);                                          // Making the context of this window current for the calling thread...

  glfwSetWindowRefreshCallback(glfw_window, refresh_callback);                  // Setting window callbacks...
  glfwSetKeyCallback(glfw_window, key_callback);                                // Setting window callbacks...
	glfwSetMouseButtonCallback(glfw_window, mouse_pressed_callback);              // Setting window callbacks...
	glfwSetCursorPosCallback(glfw_window, mouse_moved_callback);                  // Setting window callbacks...
	glfwSetScrollCallback(glfw_window, mouse_scrolled_callback);                  // Setting window callbacks...

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...

  translate(T, initial_translation);                                            // Setting initial Translation_matrix matrix...
  perspective(P, FOV*M_PI/180.0, aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);        // Setting Projection_matrix matrix...
}

bool window::closed()
{
  return(glfwWindowShouldClose(glfw_window));
}

auto window::clear()                                                            // Window clearance.
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
}

auto window::refresh()->void                                                    // Window refresh.
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glfwSwapBuffers(glfw_window);                                                 // Swapping front and back buffers...
  glfwPollEvents();                                                             // Polling GLFW events...
}

auto window::key_pressed(int key, int scancode, int action, int mods)->void     // Key-pressed retpoline.
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(glfw_window, GL_TRUE);
  }
}

auto window::mouse_pressed(int key, int scancode, int action, int mods)->void   // Mouse-pressed retpoline.
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && arcball_on == false)
  {
    glfwGetCursorPos(glfw_window, &mouse_x, &mouse_y);                          // Getting mouse position...
    mouse_x_old = mouse_x;																											// Backing up mouse position...
    mouse_y_old = mouse_y;																											// Backing up mouse position...
    arcball_on = true;																													// Turning on arcball...
  }

  else
  {
    arcball_on = false;																													// Turning off arcball...
  }

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
  {
    R_old[0] = R[0]; R_old[4] = R[4]; R_old[8]  = R[8];  R_old[12] = R[12];		  // Backing up Rotation_matrix matrix...
    R_old[1] = R[1]; R_old[5] = R[5]; R_old[9]  = R[9];  R_old[13] = R[13];			// Backing up Rotation_matrix matrix...
    R_old[2] = R[2]; R_old[6] = R[6]; R_old[10] = R[10]; R_old[14] = R[14];		  // Backing up Rotation_matrix matrix...
    R_old[3] = R[3]; R_old[7] = R[7]; R_old[11] = R[11]; R_old[15] = R[15];		  // Backing up Rotation_matrix matrix...
  }
}

auto window::mouse_moved(int key, int scancode, int action, int mods)->void     // Mouse-moved retpoline.
{
  if (arcball_on)
  {
    mouse_x = xpos;																															// Getting mouse position...
    mouse_y = ypos;																															// Getting mouse position...
  }
}

auto window::mouse_scrolled(int key, int scancode, int action, int mods)->void  // Mmouse-scrolled retpoline.
{
  float translation[3];                                                         // Translation vector.

  scroll_x = xoffset;																														// Getting scroll position...
  scroll_y = yoffset;																														// Getting scroll position...
  zoom = T[14];																							                    // Getting z-axis translation...

  if (scroll_y > 0)
  {
    zoom *= ZOOM_FACTOR;																												// Zooming-in...
  }

  if (scroll_y < 0)
  {
    zoom /= ZOOM_FACTOR;																												// Zooming-out...
  }

  translation[0] = 0.0;                                                         // Building translation vector...
  translation[1] = 0.0;                                                         // Building translation vector...
  translation[2] = zoom;                                                        // Building translation vector...
  translate(T, translation);                                                    // Building translation matrix...
}

void window::plot(point4* points, color4* colors, plot_style ps)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...

  switch(ps)
  {
    case STYLE_POINT:
      glUseProgram(point_shader);                                               // Using shader...
      glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                              "View_matrix"),                   // Setting View_matrix matrix on shader...
                         1,                                                     // # of matrices to be modified.
                         GL_FALSE,                                              // FALSE = column major.
                         &V[0]);                                                // View matrix.

      glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                              "Projection_matrix"),             // Setting Projection_matrix matrix on shader...
                         1,                                                     // # of matrices to be modified.
                         GL_FALSE,                                              // FALSE = column major.
                         &P[0]);                                                // Projection matrix.
      break;

    default:
    glUseProgram(point_shader);                                               // Using shader...
    glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                            "View_matrix"),                   // Setting View_matrix matrix on shader...
                       1,                                                     // # of matrices to be modified.
                       GL_FALSE,                                              // FALSE = column major.
                       &V[0]);                                                // View matrix.

    glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                            "Projection_matrix"),             // Setting Projection_matrix matrix on shader...
                       1,                                                     // # of matrices to be modified.
                       GL_FALSE,                                              // FALSE = column major.
                       &P[0]);                                                // Projection matrix.
    break;
  }

  // Binding "points" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "colors" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_POINTS, 0, points->size);                                     // Drawing "points"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "points" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "colors" array...
}

void window::print(text4* text)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...
  glUseProgram(text_shader);                                                    // Using shader...
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "View_matrix"),          // Setting View_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &V[0]);
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "Projection_matrix"),    // Setting Projection_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &P[0]);

  // Binding "glyph" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->glyph_vbo);                               // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->color_vbo);                                // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_LINES, 0, text->size);                                        // Drawing "glyphs"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "glyph" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "color" array...
}

window::~window()
{

}
