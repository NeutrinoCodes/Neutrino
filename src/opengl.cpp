#include "opengl.hpp"

GLFWwindow*				window;
int								window_x;
int								window_y;
int								size_window_x = SIZE_WINDOW_X;
int								size_window_y = SIZE_WINDOW_Y;
float							aspect_ratio = size_window_x/size_window_y;
char*             vertex_source;
size_t            size_vertex;
char*             fragment_source;
size_t            size_fragment;
double            mouse_x = 0;
double            mouse_y = 0;
double            mouse_x_old = 0;
double            mouse_y_old = 0;
bool							mouse_1st_left_click = false;
double						scroll_x = 0;
double						scroll_y = 0;
bool							mouse_right_button = false;
bool							key_ctrl_L = false;

glm::vec3					I3 = glm::vec3(1.0f, 1.0f, 1.0f);															// 3x1 ones vector.
glm::vec4					I4 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);												// 4x1 ones vector.
glm::mat4					I4x4 = glm::mat4(1.0f);																				// 4x4 identity matrix.

glm::vec3					S3 = I3;																											// 3x1 scale vector.
glm::vec3					T3 = I3;																											// 3x1 translation vector.
glm::vec4					viewport = I4;																								// 4x1 viewport vector.

glm::mat4 				S4x4 = I4x4;																									// 4x4 scale matrix.
glm::mat4					R4x4 = I4x4;																									// 4x4 rotation matrix.
glm::mat4 				T4x4 = I4x4;																									// 4x4 translation matrix.
glm::mat4 				M4x4 = I4x4;																									// 4x4 model matrix.
glm::mat4 				V4x4 = I4x4;																									// 4x4 view matrix.
glm::mat4 				P4x4 = I4x4;																									// 4x4 projection matrix.


void window_refresh_callback(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
		if (mouse_1st_left_click == false)
		{
			glfwGetCursorPos(window, &mouse_x_old, &mouse_y_old);
			mouse_1st_left_click = true;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
  {
		if (mouse_1st_left_click == true)
		{
			mouse_1st_left_click = false;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
  {
		mouse_right_button = true;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
  {
		mouse_right_button = false;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec3 mouse_screen_near;																									// Mouse vector, screen coordinates at "near plane" (z = 0).
	glm::vec3 mouse_world;																												// Mouse vector, world coordinates.

	int mouse_left_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if ((mouse_left_button == GLFW_PRESS) && mouse_1st_left_click)
	{
		mouse_x = xpos;
		mouse_y = ypos;
		mouse_screen_near = glm::vec3(mouse_x_old, mouse_y_old, 0.0f);							// Building mouse screen vector...
		glfwGetWindowSize(window, &size_window_x, &size_window_y);									// Getting window size...
		glfwGetWindowPos(window, &window_x, &window_y);															// Getting window position offset...
		//aspect_ratio = size_window_x/size_window_y;																	// Calculating window aspect ratio...
		viewport = glm::vec4(window_x, window_y, size_window_x, size_window_y);			// Getting current viewport...
		mouse_world = glm::unProject(mouse_screen_near, V4x4, P4x4, viewport);			// Building mouse world vector...

		...EZOR 27MAR2018: arcball to be completed.
		1. differential mouse world position to be computed
		2. cross product for the calculation of the momentum to be computed
		3. quaternion rotation to be computed.

	}

	if (mouse_left_button && key_ctrl_L)
	{
		glfwGetWindowSize(window, &size_window_x, &size_window_y);
		glfwGetWindowPos(window, &window_x, &window_y);
		aspect_ratio = size_window_x/size_window_y;
		viewport = glm::vec4(window_x, window_y, size_window_x, size_window_y);			// Getting current viewport...
		mouse_screen_near = glm::vec3(xpos, ypos, 0.0f);														// Building mouse screen vector...
		mouse_world = glm::unProject(mouse_screen_near, V4x4, P4x4, viewport);			// Building mouse world vector...


		T4x4 = glm::scale(I4x4, I3);
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
	GLuint 		prog;
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
  prog = glCreateProgram();
  glBindAttribLocation(prog, 0, "in_point");
  glBindAttribLocation(prog, 1, "in_color");
  glAttachShader(prog, vs);
  glAttachShader(prog, fs);
  glLinkProgram(prog);
  glUseProgram(prog);
  printf("DONE!\n");
}
