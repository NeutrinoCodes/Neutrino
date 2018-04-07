#include "program.hpp"
#include "context.hpp"

int main()
{
  load();
  init_opengl_context();
	init_opencl_context();
  init_opencl_kernel();
  setup();

  while (!glfwWindowShouldClose(window))
  {
    arcball();
    loop();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

	destroy_opengl_context();
	destroy_opencl_context();
  terminate();

  return 0;
}
