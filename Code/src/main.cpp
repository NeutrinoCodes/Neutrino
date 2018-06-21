#include "program.hpp"
#include "context.hpp"
#include "utils.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.vert"
#define FRAGMENT_FILE   "../../shader/fragment.frag"
#define KERNEL_FILE     "../../kernel/thekernel.cl"

int main()
{
  double tic;
  double toc;

  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);

  init_opengl_context();
	init_opencl_context();
  init_opencl_kernel();
  init_freetype();

  setup();

  while (!glfwWindowShouldClose(window))
  {
    tic = getCPUTime();
    arcball();
    loop();
    screen_refresh();
    toc = getCPUTime();
    ascii_spin("Action: running OpenCL program...", tic, toc);
  }

  ascii_spin_stop();
	destroy_opengl_context();
	destroy_opencl_context();
  terminate();

  return 0;
}
