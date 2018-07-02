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
glm::quat					arcball_quaternion = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);				// Arcball quaternion.
glm::mat4					Rotation_matrix = glm::mat4(1.0f);										 				// Rotation matrix.
glm::mat4					Rotation_matrix_old = glm::mat4(1.0f);												// Rotation matrix backup.
glm::mat4 				Translation_matrix = glm::mat4(1.0f);													// Translation matrix.
glm::mat4 				Model_matrix = glm::mat4(1.0f);																// Model matrix.
glm::mat4 				View_matrix = glm::mat4(1.0f);							   								// View matrix.
glm::mat4 				Projection_matrix = glm::mat4(1.0f);				  								// Projection matrix.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// REFRESH //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void screen_refresh()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// ARCBALL //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
glm::vec3 get_arcball_vector(int x, int y)
{
  glm::vec3 P;																																	// Point "P" on unitary ball.
	float OP_sq;																																	// Center "O" to "P" squared distance.

	glfwGetWindowSize(window, &window_size_x, &window_size_y);										// Getting window size...
	P = glm::vec3(2.0*x/window_size_x - 1.0, 2.0*y/window_size_y - 1.0, 0);				// Computing point on unitary ball...
  P.y = -P.y;																																		// Inverting y-axis according to OpenGL...
	OP_sq = P.x*P.x + P.y*P.y;                                                    // Computing "OP" squared...

  if (OP_sq <= 1.0)																															// Checking P to ball-center distance...
	{
    P.z = sqrt(1.0 - OP_sq);  																									// Pythagoras' theorem...
	}

  else
	{
    P = glm::normalize(P);  																										// Normalizing if too far...
	}

  return P;
}

void arcball()
{
	glm::vec3 va;																																	// Mouse vector, world coordinates.
	glm::vec3 vb;																																  // Mouse vector, world coordinates.
	glm::vec3 arcball_axis;																												// Arcball axis of rotation.
	double theta;																																	// Arcball angle of rotation.

	if (arcball_on &&(mouse_x != mouse_x_old || mouse_y != mouse_y_old))
	{
		va = get_arcball_vector(mouse_x_old, mouse_y_old);													// Building mouse world vector (old)...
		vb = get_arcball_vector(mouse_x, mouse_y);																	// Building mouse world vector...
		theta = ROTATION_FACTOR*acos(glm::clamp(glm::dot(glm::normalize(va),
                                            glm::normalize(vb)), -1.0f, 1.0f));	// Calculating arcball angle...
    arcball_axis = glm::cross(va, vb);																					// Calculating arcball axis of rotation...
		arcball_quaternion = glm::normalize(glm::quat(cos(theta/2.0f),							// Building rotation quaternion...
																	 arcball_axis.x * sin(theta/2.0f),
									 					 			 arcball_axis.y * sin(theta/2.0f),
								 	 			 		 			 arcball_axis.z * sin(theta/2.0f)));

		Rotation_matrix = glm::toMat4(arcball_quaternion)*Rotation_matrix_old;			// Building rotation matrix...
	}
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CALLBACKS ////////////////////////////////////
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
    Rotation_matrix_old = Rotation_matrix;																			// Backing up Rotation_matrix matrix...
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
	scroll_x = xoffset;																														// Getting scroll position...
	scroll_y = yoffset;																														// Getting scroll position...
	zoom = Translation_matrix[3][2];																							// Getting z-axis translation...

	if (scroll_y > 0)
	{
		zoom *= ZOOM_FACTOR;																												// Zooming-in...
	}

	if (scroll_y < 0)
	{
		zoom /= ZOOM_FACTOR;																												// Zooming-out...
	}

	Translation_matrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, zoom));// Building translation matrix...
}

void window_refresh_callback(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
	glfwSwapBuffers(window);                                                      // Swapping front and back buffers...
}

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

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// SHADERS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// SCREEN ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void init_screen()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  Translation_matrix = glm::translate(glm::mat4(),                              // Setting initial Translation_matrix matrix...
                                      glm::vec3(0.0f, 0.0f, -3.0f));
  Projection_matrix = glm::perspective(glm::radians(FOV),                       // Setting Projection_matrix matrix...
                                aspect_ratio,
                                NEAR_Z_CLIP,
                                FAR_Z_CLIP);
}
