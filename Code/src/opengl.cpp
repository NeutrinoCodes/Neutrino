#include "opengl.hpp"

GLFWwindow*				window;                                                       // Window handle.
int								window_size_x = SIZE_WINDOW_X;                                // Window x-size [px].
int								window_size_y = SIZE_WINDOW_Y;                                // Window y-size [px].
float							aspect_ratio = (float)window_size_x/(float)window_size_y;     // Window aspcet-ratio [].
char*             vertex_source;                                                // Vertex shader source.
size_t            vertex_size;                                                  // Vertex shader size [characters].
char*             fragment_source;                                              // Fragment shader source.
size_t            fragment_size;                                                // Fragment shader size [characters].
GLuint 						shader;                                                       // Shader program.
GLuint            text_texture;                                                 // Text texture.

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
void load_vertex(const char* filename_vertex)
{
  printf("Action: loading OpenGL vertex source from file... ");

  load_file(filename_vertex, &vertex_source, &vertex_size);

	printf("DONE!\n");
}

void load_fragment(const char* filename_fragment)
{
	printf("Action: loading OpenGL fragment source from file... ");

  load_file(filename_fragment, &fragment_source, &fragment_size);

	printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// INITIALIZATIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void init_window()
{
  // Inititalizing GLFW context...
  if (glfwInit() != GLFW_TRUE)
	{
  	printf("Error:  unable to initialize GLFW!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

  // Initializing GLFW hints...
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

  // Creating window...
  window = glfwCreateWindow(window_size_x,
                            window_size_y,
                            "Neutrino",
                            NULL,
                            NULL);
  if (!window)
	{
		printf("Error:  unable to create window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  // Setting window callbacks...
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
  glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);

  // Initializing GLEW context...
  glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
    printf("Error:  unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }
}

void init_shaders()
{
  GLuint		vs;
	GLuint 		fs;
	GLint 		success;
  GLsizei 	log_size;
  GLchar*		log;

  printf("Action: initialising OpenGL shaders... ");

  // Compiling vertex shader...
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, (const char**)&vertex_source, (GLint*)&vertex_size);
	glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &log_size);
    log = (char*) malloc(log_size+1);
    log[log_size] = '\0';
    glGetShaderInfoLog(vs, log_size+1, NULL, log);
    printf("%s\n", log);
    free(log);
    exit(1);
  }

	// Compiling fragment shader...
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, (const char**)&fragment_source, (GLint*)&fragment_size);
	glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &log_size);
    log = (char*) malloc(log_size+1);
    log[log_size] = '\0';
    glGetShaderInfoLog(fs, log_size+1, NULL, log);
    printf("%s\n", log);
    free(log);
    exit(1);
  }

	// Creating OpenGL shader program...
  shader = glCreateProgram();
  glBindAttribLocation(shader, 0, "point");
  glBindAttribLocation(shader, 1, "vertex_color");
  glAttachShader(shader, vs);
  glAttachShader(shader, fs);
  glLinkProgram(shader);
  free_file(vertex_source);
  free_file(fragment_source);

  printf("DONE!\n");
}

void init_screen()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &text_texture);
  glBindTexture(GL_TEXTURE_2D, text_texture);
  glUniform1i(uniform_tex, 0);

  Translation_matrix = glm::translate(glm::mat4(),                              // Setting initial Translation_matrix matrix...
                                      glm::vec3(0.0f, 0.0f, -3.0f));
  Projection_matrix = glm::perspective(glm::radians(FOV),                       // Setting Projection_matrix matrix...
                                aspect_ratio,
                                NEAR_Z_CLIP,
                                FAR_Z_CLIP);
}
