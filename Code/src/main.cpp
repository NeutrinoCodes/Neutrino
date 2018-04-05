#include "program.hpp"
#include "context.hpp"

int main()
{
  load();
  create_opengl_context();
	create_opencl_context();
  create_program();
  build_program();
  create_queue();
  create_kernel();
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
