#include "program.hpp"
#include "context.hpp"
#include "utils.hpp"

// These files are relative to the build/mac or build/linux directory:
#define POINT_VERTEX_FILE       "../../shader/vertex.vert"
#define POINT_FRAGMENT_FILE     "../../shader/fragment.frag"
#define TEXT_VERTEX_FILE        "../../shader/text_vertex.vert"
#define TEXT_FRAGMENT_FILE      "../../shader/text_fragment.frag"
#define KERNEL_FILE             "../../kernel/thekernel.cl"

int main()
{
  double tic;
  double toc;

  load_point_vertex(POINT_VERTEX_FILE);
  load_point_fragment(POINT_FRAGMENT_FILE);
  load_text_vertex(TEXT_VERTEX_FILE);
  load_text_fragment(TEXT_FRAGMENT_FILE);
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
