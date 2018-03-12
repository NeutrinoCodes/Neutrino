#include "program.hpp"
#include "context.hpp"

int main()
{
  setup();
  create_opengl_context();
	create_opencl_context();

  while (!glfwWindowShouldClose(window))
  {
    loop();
  }

	destroy_opengl_context();
	destroy_opencl_context();
  terminate();

  return 0;
}
