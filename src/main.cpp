#include "program.hpp"
#include "context.hpp"

int main()
{
  create_opengl_context();
	create_opencl_context();

	setup();

  while (!glfwWindowShouldClose(window))
  {
    loop();
  }

	terminate();

	destroy_opengl_context();
	destroy_opencl_context();

  return 0;
}
