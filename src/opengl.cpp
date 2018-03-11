#include "opengl.hpp"

GLFWwindow*				window;

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
}

void init_glfw()
{
  if (glfwInit() != GLFW_TRUE)
	{
  	fprintf(stderr, "Error: unable to initialize GLFW!\n");
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
  window = glfwCreateWindow(800, 600, "Test interop CPP", NULL, NULL);
  if (!window)
	{
		fprintf(stderr, "Error: unable to create window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
  glfwSetKeyCallback(window, key_callback);
}

void init_glew()
{
  glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
    fprintf(stderr, "Error: unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }
}
