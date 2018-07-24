#include "opengl.hpp"

GLFWwindow*				window;                                                       // Window handle.
int								window_size_x = SIZE_WINDOW_X;                                // Window x-size [px].
int								window_size_y = SIZE_WINDOW_Y;                                // Window y-size [px].
float							aspect_ratio = (float)window_size_x/(float)window_size_y;     // Window aspcet-ratio [].

char*             point_vertex_source;                                          // Point vertex shader source.
size_t            point_vertex_size;                                            // Point vertex shader size [characters].
char*             point_fragment_source;                                        // Point fragment shader source.
size_t            point_fragment_size;                                          // Point fragment shader size [characters].
GLuint 						point_shader;                                                 // Point shader program.

char*             text_vertex_source;                                           // Point vertex shader source.
size_t            text_vertex_size;                                             // Point vertex shader size [characters].
char*             text_fragment_source;                                         // Point fragment shader source.
size_t            text_fragment_size;                                           // Point fragment shader size [characters].
GLuint 						text_shader;                                                  // Point shader program.

double            mouse_x = 0;                                                  // Mouse x-coordinate [px].
double            mouse_y = 0;                                                  // Mouse y-coordinate [px].
double            mouse_x_old = 0;                                              // Mouse x-coordinate backup [px].
double            mouse_y_old = 0;                                              // Mouse y-coordinate backup [px].
double						scroll_x = 0;                                                 // Scroll x-coordinate [px].
double						scroll_y = 0;                                                 // Scroll y-coordinate [px].

bool 							arcball_on = false;                                           // Arcball activation flag.
double						zoom = 0;                                                     // Zoom coefficient.

quaternion        arcball_quaternion;                   // Arcball quaternion.

float         R[16]     = {1.0, 0.0, 0.0, 0.0,                                  // Rotation matrix.
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

float         R_old[16] = {1.0, 0.0, 0.0, 0.0,                                  // Rotation matrix backup.
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

float         T[16]     = {1.0, 0.0, 0.0, 0.0,                                  // Translation matrix.
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

float         V[16]     = {1.0, 0.0, 0.0, 0.0,                                  // View matrix.
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

float         P[16]     = {1.0, 0.0, 0.0, 0.0,                                  // Projection matrix.
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FILES //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void load_point_vertex(const char* filename_vertex)
{
 printf("Action: loading OpenGL point vertex source from file... ");

 load_file(filename_vertex, &point_vertex_source, &point_vertex_size);

	printf("DONE!\n");
}

void load_point_fragment(const char* filename_fragment)
{
	printf("Action: loading OpenGL point fragment source from file... ");

 load_file(filename_fragment, &point_fragment_source, &point_fragment_size);

	printf("DONE!\n");
}

void load_text_vertex(const char* filename_vertex)
{
 printf("Action: loading OpenGL point vertex source from file... ");

 load_file(filename_vertex, &text_vertex_source, &text_vertex_size);

	printf("DONE!\n");
}

void load_text_fragment(const char* filename_fragment)
{
	printf("Action: loading OpenGL point fragment source from file... ");

 load_file(filename_fragment, &text_fragment_source, &text_fragment_size);

	printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// WINDOW ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void init_window()
{
  if (glfwInit() != GLFW_TRUE)                                                  // Inititalizing GLFW context...
	{
  	printf("Error:  unable to initialize GLFW!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                                // Initializing GLFW hints...
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);                                // Initializing GLFW hints...
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                          // Initializing GLFW hints...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                // Initializing GLFW hints...
	glfwWindowHint(GLFW_SAMPLES, 4);                                              // Initializing GLFW hints...

  // Creating window:
  window = glfwCreateWindow(window_size_x,                                      // Width.
                            window_size_y,                                      // Height.
                            "Neutrino",                                         // Title.
                            NULL,                                               // Monitor.
                            NULL);                                              // Share.
  if (!window)
	{
		printf("Error:  unable to create window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);                                               // Making the context of this window current for the calling thread...
	glfwSetWindowRefreshCallback(window, window_refresh_callback);                // Setting window callbacks...
  glfwSetKeyCallback(window, key_callback);                                     // Setting window callbacks...
	glfwSetMouseButtonCallback(window, mouse_button_callback);                    // Setting window callbacks...
	glfwSetCursorPosCallback(window, cursor_position_callback);                   // Setting window callbacks...
	glfwSetScrollCallback(window, scroll_callback);                               // Setting window callbacks...

  // Initializing GLEW context:
  glewExperimental = GL_TRUE;                                                   // Ensuring that all extensions with valid entry points will be exposed...

	if (glewInit() != GLEW_OK)
	{
    printf("Error:  unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }
}

void init_shaders()
{
  GLuint		point_vertex_shader;                                                // "Point" vertex shader.
	GLuint 		point_fragment_shader;                                              // "Point" fragment shader.
  GLuint    LAYOUT_0 = 0;                                                       // "layout = 0" attribute in vertex shader.
  GLuint    LAYOUT_1 = 1;                                                       // "layout = 1" attribute in vertex shader.

  GLuint		text_vertex_shader;                                                 // "Text" vertex shader.
	GLuint 		text_fragment_shader;                                               // "Text" fragment shader.

	GLint 		success;
  GLsizei 	log_size;
  GLchar*		log;

  printf("Action: initialising OpenGL shaders... ");

  // POINT SHADER:

  // Compiling point vertex shader...
  point_vertex_shader = glCreateShader(GL_VERTEX_SHADER);                       // Creating shader...
  glShaderSource(point_vertex_shader,                                           // Attaching source code to shader...
                 1,
                 (const char**)&point_vertex_source,
                 (GLint*)&point_vertex_size);
	glCompileShader(point_vertex_shader);                                         // Compiling shader...
  glGetShaderiv(point_vertex_shader, GL_COMPILE_STATUS, &success);              // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled point vertex shader code:
  if (!success)
  {
    glGetShaderiv(point_vertex_shader, GL_INFO_LOG_LENGTH, &log_size);          // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(point_vertex_shader, log_size + 1, NULL, log);           // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Compiling point fragment shader...
  point_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);                   // Creating shader...
  glShaderSource(point_fragment_shader,                                         // Attaching source code to shader...
                 1,
                 (const char**)&point_fragment_source,
                 (GLint*)&point_fragment_size);
	glCompileShader(point_fragment_shader);
  glGetShaderiv(point_fragment_shader, GL_COMPILE_STATUS, &success);

  // Checking compiled point fragment shader code:
  if (!success)
  {
    glGetShaderiv(point_fragment_shader, GL_INFO_LOG_LENGTH, &log_size);        // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(point_fragment_shader, log_size + 1, NULL, log);         // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Creating OpenGL shader program:
  point_shader = glCreateProgram();                                             // Creating program...
  glBindAttribLocation(point_shader, LAYOUT_0, "point");                        // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(point_shader, LAYOUT_1, "color");                        // Binding "vertex_color" to "layout = 1" shader attribute...
  glAttachShader(point_shader, point_vertex_shader);                            // Attaching point vertex shader to program...
  glAttachShader(point_shader, point_fragment_shader);                          // Attaching point fragment shader to program...
  glLinkProgram(point_shader);                                                  // Linking program...
  free_file(point_vertex_source);                                               // Freeing point vertex source file...
  free_file(point_fragment_source);                                             // Freeing fragment vertex source file...

  // TEXT SHADER:

  // Compiling text vertex shader...
  text_vertex_shader = glCreateShader(GL_VERTEX_SHADER);                        // Creating shader...
  glShaderSource(text_vertex_shader,                                            // Attaching source code to shader...
                 1,
                 (const char**)&text_vertex_source,
                 (GLint*)&text_vertex_size);
	glCompileShader(text_vertex_shader);                                          // Compiling shader...
  glGetShaderiv(text_vertex_shader, GL_COMPILE_STATUS, &success);               // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled text vertex shader code:
  if (!success)
  {
    glGetShaderiv(text_vertex_shader, GL_INFO_LOG_LENGTH, &log_size);           // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(text_vertex_shader, log_size + 1, NULL, log);            // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Compiling text fragment shader...
  text_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);                    // Creating shader...
  glShaderSource(text_fragment_shader,                                          // Attaching source code to shader...
                 1,
                 (const char**)&text_fragment_source,
                 (GLint*)&text_fragment_size);
	glCompileShader(text_fragment_shader);
  glGetShaderiv(text_fragment_shader, GL_COMPILE_STATUS, &success);

  // Checking compiled text fragment shader code:
  if (!success)
  {
    glGetShaderiv(text_fragment_shader, GL_INFO_LOG_LENGTH, &log_size);         // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(text_fragment_shader, log_size + 1, NULL, log);          // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Creating OpenGL shader program:
  text_shader = glCreateProgram();                                              // Creating program...
  glBindAttribLocation(text_shader, LAYOUT_0, "point");                         // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(text_shader, LAYOUT_1, "color");                         // Binding "vertex_color" to "layout = 1" shader attribute...
  glAttachShader(text_shader, text_vertex_shader);                              // Attaching point vertex shader to program...
  glAttachShader(text_shader, text_fragment_shader);                            // Attaching point fragment shader to program...
  glLinkProgram(text_shader);                                                   // Linking program...
  free_file(text_vertex_source);                                                // Freeing point vertex source file...
  free_file(text_fragment_source);                                              // Freeing fragment vertex source file...

  printf("DONE!\n");
}

void init_screen()
{
  vector initial_translation;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  initial_translation.x =  0.0;                                                 // Building initial translation vector...
  initial_translation.y =  0.0;                                                 // Building initial translation vector...
  initial_translation.z = -3.0;                                                 // Building initial translation vector...

  translate(T, initial_translation);                                            // Setting initial Translation_matrix matrix...
  perspective(P, FOV*M_PI/180.0, aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);        // Setting Projection_matrix matrix...

  printf("V11 = %f, V12 = %f, V13 = %f, V14 = %f\n", V[0], V[4], V[8], V[12]);
  printf("V21 = %f, V22 = %f, V23 = %f, V24 = %f\n", V[1], V[5], V[9], V[13]);
  printf("V31 = %f, V32 = %f, V33 = %f, V34 = %f\n", V[2], V[6], V[10], V[14]);
  printf("V41 = %f, V42 = %f, V43 = %f, V44 = %f\n", V[3], V[7], V[11], V[15]);

  printf("T11 = %f, T12 = %f, T13 = %f, T14 = %f\n", T[0], T[4], T[8], T[12]);
  printf("T21 = %f, T22 = %f, T23 = %f, T24 = %f\n", T[1], T[5], T[9], T[13]);
  printf("T31 = %f, T32 = %f, T33 = %f, T34 = %f\n", T[2], T[6], T[10], T[14]);
  printf("T41 = %f, T42 = %f, T43 = %f, T44 = %f\n", T[3], T[7], T[11], T[15]);

}

void refresh_screen()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void clear_screen()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing screen...
}

void plot(point4* points, color4* colors)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...

  printf("V11 = %f, V12 = %f, V13 = %f, V14 = %f\n", V[0], V[4], V[8], V[12]);
  printf("V21 = %f, V22 = %f, V23 = %f, V24 = %f\n", V[1], V[5], V[9], V[13]);
  printf("V31 = %f, V32 = %f, V33 = %f, V34 = %f\n", V[2], V[6], V[10], V[14]);
  printf("V41 = %f, V42 = %f, V43 = %f, V44 = %f\n", V[3], V[7], V[11], V[15]);

  glUseProgram(point_shader);                                                   // Using shader...
  glUniformMatrix4fv(glGetUniformLocation(point_shader, "View_matrix"),         // Setting View_matrix matrix on shader...
                     1,                                                         // # of matrices to be modified.
                     GL_FALSE,                                                  // FALSE = column major.
                     &V[0]);                                       // Matrix.
  glUniformMatrix4fv(glGetUniformLocation(point_shader, "Projection_matrix"),   // Setting Projection_matrix matrix on shader...
                     1,                                                         // # of matrices to be modified.
                     GL_FALSE,                                                  // FALSE = column major.
                     &P[0]);                                 // Matrix.

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

vector get_arcball_vector(int x, int y)
{
  vector p;																																	    // Point "p" on unitary ball.
	float  op_sq;																																	// Center "o" to "p" squared distance.

	glfwGetWindowSize(window, &window_size_x, &window_size_y);										// Getting window size...
  p.x = 2.0*x/window_size_x - 1.0;                                              // Computing point on unitary ball [x]...
  p.y = 2.0*y/window_size_y - 1.0;                                              // Computing point on unitary ball [y]...
  p.z = 0.0;                                                                    // Computing point on unitary ball [z]...
  p.y = -p.y;																																		// Inverting y-axis according to OpenGL...
	op_sq = p.x*p.x + p.y*p.y;                                                    // Computing "op" squared...

  if (op_sq <= 1.0)																															// Checking p to ball-center distance...
	{
    p.z = sqrt(1.0 - op_sq);  																									// Pythagoras' theorem...
	}

  else
	{
    p = normalize(p);  																										      // Normalizing if too far...
	}

  return p;
}

void arcball()
{
	vector a; 																															  		// Mouse vector, world coordinates.
	vector b; 																															  	  // Mouse vector, world coordinates.
	vector axis;																										   		        // Arcball axis of rotation.
	float  theta;																																	// Arcball angle of rotation.

	if (arcball_on &&(mouse_x != mouse_x_old || mouse_y != mouse_y_old))          // If mouse has been dragged (= left click + move):
	{
		a = get_arcball_vector(mouse_x_old, mouse_y_old);							  						// Building mouse world vector (old)...
		b = get_arcball_vector(mouse_x, mouse_y);												   					// Building mouse world vector...
		theta = ROTATION_FACTOR*angle(a, b);                                        // Calculating arcball angle...
    axis = normalize(cross(a, b));									            				        // Calculating arcball axis of rotation...
    rotate(R, R_old, axis, theta);                                              // Calculating rotation matrix...
	}
}

void print(text4* text)
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

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// WINDOW's CALLBACKS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && arcball_on == false)
	{
		glfwGetCursorPos(window, &mouse_x, &mouse_y);                               // Getting mouse position...
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

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (arcball_on)
	{
    mouse_x = xpos;																															// Getting mouse position...
    mouse_y = ypos;																															// Getting mouse position...
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  vector translation;                                                           // Translation vector.

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

  translation.x = 0.0;                                                          // Building translation vector...
  translation.y = 0.0;                                                          // Building translation vector...
  translation.z = zoom;                                                         // Building translation vector...
  translate(T, translation);                                                    // Building translation matrix...
}

void window_refresh_callback(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
	glfwSwapBuffers(window);                                                      // Swapping front and back buffers...
}
