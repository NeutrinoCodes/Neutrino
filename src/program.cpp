#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/kernel.txt"

data_float4 points(100);

void setup()
{
  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);
  set_kernel_argument(points);
}

void loop()
{
  acquire_GL_object(&points.buffer);
  enqueue_task();
  wait_for_event();
  execute_kernel();
  release_GL_object(&points.buffer);
  finish_queue();
  release_event();

  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(points.vao);
  glDrawArrays(GL_POINTS, 0, points.size);
  glBindVertexArray(0);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  delete &points;

  printf("All done!\n");
}
