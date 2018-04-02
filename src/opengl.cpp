#include "opengl.hpp"

GLFWwindow*				window;
int								window_x;
int								window_y;
int								size_window_x = SIZE_WINDOW_X;
int								size_window_y = SIZE_WINDOW_Y;
float							aspect_ratio = (float)size_window_x/(float)size_window_y;
char*             vertex_source;
size_t            size_vertex;
char*             fragment_source;
size_t            size_fragment;
GLuint 						shader;
GLint 						scale_shader;
GLint 						view_shader;
GLint 						projection_shader;
double            mouse_x = 0;
double            mouse_y = 0;
double            mouse_x_old = 0;
double            mouse_y_old = 0;
bool 							arcball_on = false;
double						scroll_x = 0;
double						scroll_y = 0;
bool							mouse_right_button = false;
bool							key_ctrl_L = false;
double						zoom = 0;

glm::quat					arcball_quaternion = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);				// 4x1 arcball rotation quaternion.
glm::vec4					viewport = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);									// 4x1 viewport vector.

glm::mat4 				Scale = glm::mat4(1.0f);																			// 4x4 scale matrix.
glm::mat4					Rotation = glm::mat4(1.0f);																		// 4x4 rotation matrix.
glm::mat4					Rotation_old = glm::mat4(1.0f);																// 4x4 rotation matrix.
glm::mat4 				Translation = glm::mat4(1.0f);																// 4x4 translation matrix.
glm::mat4 				Model = glm::mat4(1.0f);																			// 4x4 model matrix.
glm::mat4 				View = glm::mat4(1.0f);																				// 4x4 view matrix.
glm::mat4 				Projection = glm::mat4(1.0f);																	// 4x4 projection matrix.

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// KEYBOARD /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
		key_ctrl_L = true;
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
	{
		key_ctrl_L = false;
	}
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MOUSE ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
glm::vec3 get_arcball_vector(int x, int y)
{
  glm::vec3 P;																																	// Point "P" on unitary ball.
	float OP_sq;																																	// Center "O" to "P" squared distance...

	glfwGetWindowSize(window, &size_window_x, &size_window_y);										// Getting window size...

	P = glm::vec3(2.0*x/size_window_x - 1.0, 2.0*y/size_window_y - 1.0, 0);				// Computing point on unitary ball...
  P.y = -P.y;																																		// Inverting y-axis (mouse coordinates are opposite to OpenGL)...

	OP_sq = P.x*P.x + P.y*P.y;

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

	if (mouse_x != mouse_x_old || mouse_y != mouse_y_old)
	{
		va = get_arcball_vector(mouse_x_old, mouse_y_old);													// Building mouse world vector (old)...
		vb = get_arcball_vector(mouse_x, mouse_y);																	// Building mouse world vector...
		theta = ROTATION_FACTOR*acos(glm::min(1.0f, glm::dot(va, vb)));							// Calculating arcball angle...
		arcball_axis = glm::cross(va, vb);																					// Calculating arcball axis of rotation...
		arcball_quaternion = glm::quat(cos(theta/2.0f),															// Building rotation quaternion...
																	 arcball_axis.x * sin(theta/2.0f),
									 					 			 arcball_axis.y * sin(theta/2.0f),
								 	 			 		 			 arcball_axis.z * sin(theta/2.0f));

		Rotation = glm::toMat4(arcball_quaternion)*Rotation_old;										// Building rotation matrix...
		mouse_x_old = mouse_x;																											// Updating mouse position...
		mouse_y_old = mouse_y;																											// Updating mouse position...
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && arcball_on == false)
	{
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
		mouse_x_old = mouse_x;																											// Updating mouse position...
		mouse_y_old = mouse_y;																											// Updating mouse position...
		arcball_on = true;																													// Turning on arcball...
  }

	else
	{
    arcball_on = false;																													// Turning off arcball...
  }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (arcball_on)
	{
    mouse_x = xpos;																															// Getting current mouse position...
    mouse_y = ypos;																															// Getting current mouse position...
		Rotation_old = Rotation;																										// Updating Rotation matrix...
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll_x = xoffset;																														// Getting scroll position...
	scroll_y = yoffset;																														// Getting scroll position...
	zoom = Translation[3][2];																											// Getting z-axis translation...

	if (scroll_y > 0)
	{
		zoom *= ZOOM_FACTOR;																												// Zooming-in...
	}

	else
	{
		zoom /= ZOOM_FACTOR;																												// Zooming-out...
	}

	Translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, zoom));				// Building translation matrix...
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// WINDOW //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void window_refresh_callback(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void init_glfw()
{
  if (glfwInit() != GLFW_TRUE)
	{
  	printf("Error:  unable to initialize GLFW!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void init_hints()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void create_window()
{
  window = glfwCreateWindow(size_window_x, size_window_y, "Test interop CPP", NULL, NULL);
  if (!window)
	{
		printf("Error:  unable to create window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
  glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void init_glew()
{
  glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
    printf("Error:  unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// SHADERS /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void load_vertex(const char* filename_vertex)
{
	FILE* handle;

	printf("Action: loading OpenGL vertex source from file... ");

  handle = fopen(filename_vertex, "rb");
  if(handle == NULL)
  {
    printf("\nError:  could not find the file!\n");
    exit(1);
  }
  fseek(handle, 0, SEEK_END);
  size_vertex = (size_t)ftell(handle);
  rewind(handle);
  vertex_source = (char*)malloc(size_vertex + 1);
  if (!vertex_source)
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(vertex_source, sizeof(char), size_vertex, handle);
  fclose(handle);
  vertex_source[size_vertex] = '\0';

	printf("DONE!\n");
}

void load_fragment(const char* filename_fragment)
{
	FILE* handle;

	printf("Action: loading OpenGL fragment source from file... ");

  handle = fopen(filename_fragment, "rb");
  if(handle == NULL)
  {
    printf("\nError:  could not find the file!\n");
    exit(1);
  }
  fseek(handle, 0, SEEK_END);
  size_fragment = (size_t)ftell(handle);
  rewind(handle);
  fragment_source = (char*)malloc(size_fragment + 1);
  if (!fragment_source)
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(fragment_source, sizeof(char), size_fragment, handle);
  fclose(handle);
  fragment_source[size_fragment] = '\0';

	printf("DONE!\n");
}

void init_shaders()
{
  GLuint		vs;
	GLuint 		fs;
	GLint 		success;
  GLsizei 	log_size;
  GLchar*		log;

  printf("Action: initialising OpenGL shaders... ");
  vs = glCreateShader(GL_VERTEX_SHADER);
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vs, 1, (const char**)&vertex_source, (GLint*)&size_vertex);
  glShaderSource(fs, 1, (const char**)&fragment_source, (GLint*)&size_fragment);

	// Compiling vertex shader...
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
  glBindAttribLocation(shader, 0, "in_point");
  glBindAttribLocation(shader, 1, "in_color");
  glAttachShader(shader, vs);
  glAttachShader(shader, fs);
  glLinkProgram(shader);
  printf("DONE!\n");
}
