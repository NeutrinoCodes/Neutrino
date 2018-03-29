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
double            mouse_x = 0;
double            mouse_y = 0;
double            mouse_x_old = 0;
double            mouse_y_old = 0;
int								mouse_button = -1;
int								mouse_action = -1;
bool							mouse_1st_left_click = false;
double						scroll_x = 0;
double						scroll_y = 0;
bool							mouse_right_button = false;
bool							key_ctrl_L = false;

glm::vec3					I3 = glm::vec3(1.0f, 1.0f, 1.0f);															// 3x1 ones vector.
glm::vec4					I4 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);												// 4x1 ones vector.
glm::mat4					I4x4 = glm::mat4(1.0f);																				// 4x4 identity matrix.

glm::vec3					S3 = I3;																											// 3x1 scale vector.
glm::vec3					R3 = I3;																											// 3x1 rotation vector.
glm::vec3					T3 = I3;																											// 3x1 translation vector.

glm::quat					R4 = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);												// 4x1 rotation quaternion.
glm::vec4					viewport = I4;																								// 4x1 viewport vector.

glm::mat4 				S4x4 = I4x4;																									// 4x4 scale matrix.
glm::mat4					R4x4 = I4x4;																									// 4x4 rotation matrix.
glm::mat4 				T4x4 = I4x4;																									// 4x4 translation matrix.
glm::mat4 				M4x4 = I4x4;																									// 4x4 model matrix.
glm::mat4 				V4x4 = I4x4;																									// 4x4 view matrix.
glm::mat4 				P4x4 = I4x4;																									// 4x4 projection matrix.

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
void detect_mouse_1st_left_click()
{
	if (mouse_button == GLFW_MOUSE_BUTTON_LEFT && mouse_action == GLFW_PRESS)
  {
		if (mouse_1st_left_click == false)
		{
			mouse_x_old = mouse_x;
			mouse_y_old = mouse_y;
			mouse_1st_left_click = true;
		}
	}

	if (mouse_button == GLFW_MOUSE_BUTTON_LEFT && mouse_action == GLFW_RELEASE)
  {
		if (mouse_1st_left_click == true)
		{
			mouse_1st_left_click = false;
		}
	}
}

void arcball()
{
	glm::vec3 mouse_screen;																												// Mouse vector, screen coordinates at z = 0.
	glm::vec3 mouse_screen_old;																										// Mouse vector, screen coordinates at z = 0.
	glm::vec3 mouse_world;																												// Mouse vector, world coordinates.
	glm::vec3 mouse_world_old;																									  // Mouse vector, world coordinates.
	glm::vec3 mouse_delta;																												// Mouse delta world vector.
	glm::vec3 momentum;																														// Arcball mmomentum (axis of rotation).
	double theta;																																	// Arcball angle of rotation.

  glfwGetWindowSize(window, &size_window_x, &size_window_y);										// Getting window size...
  glfwGetWindowPos(window, &window_x, &window_y);																// Getting window position offset...
  viewport = glm::vec4(window_x, window_y, size_window_x, size_window_y);				// Getting current viewport...
	mouse_screen_old = glm::vec3(mouse_x_old, mouse_y_old, 0.0f);									// Building mouse screen vector...
	mouse_world_old = glm::unProject(mouse_screen_old, V4x4, P4x4, viewport);			// Building mouse world vector...
	mouse_screen = glm::vec3(mouse_x, mouse_y, 0.0f);															// Building mouse screen vector...
	mouse_world = glm::unProject(mouse_screen, V4x4, P4x4, viewport);							// Building mouse world vector...
	mouse_delta = mouse_world - mouse_world_old;																	// Calculating mouse delta..
	momentum = glm::cross(mouse_delta, mouse_world_old);													// Calculating arcball momentum...
 	theta = glm::angle(mouse_world, mouse_world_old);															// Calculating arcball angle...
	R4 = glm::quat(momentum.x * sin(theta/2.0f),																	// Calculating rotation quaternion...
								 momentum.y * sin(theta/2.0f),
							 	 momentum.z * sin(theta/2.0f),
							   cos(theta/2.0f));
	R4x4 = glm::toMat4(R4);																												// Transforming quaterion into rotation matrix...
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	mouse_button = button;
	mouse_action = action;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	detect_mouse_1st_left_click();
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mouse_1st_left_click)
	{
		mouse_x = xpos;
		mouse_y = ypos;
		arcball();
		mouse_x = mouse_x_old;
		mouse_y = mouse_y_old;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll_x = xoffset;
	scroll_y = yoffset;

	if (scroll_y > 0)
	{
		S3 = S3*1.1f;
	}

	if (scroll_y < 0)
	{
		S3 = S3/1.1f;
	}

	S4x4 = glm::scale(I4x4, S3);
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
  glUseProgram(shader);
  printf("DONE!\n");
}
