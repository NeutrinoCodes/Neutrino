#include "program.hpp"
#include "context.hpp"
#include "utils.hpp"

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
    screen_refresh();
    ascii_spin("Action: running OpenCL program... ");
  }

  ascii_spin_stop();
	destroy_opengl_context();
	destroy_opencl_context();
  terminate();

  return 0;
}
