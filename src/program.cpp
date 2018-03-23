#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      5

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);
data_float  tick(1);

void load()
{
  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);
}

void setup()
{
  size_global = points.size;
  dim_kernel = 1;

  push_float4_data(&points);
  //push_float4_size(points);
  //push_float_data(tick);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(3);

}

void loop()
{
  //tick.x[0] += 0.01f;
  acquire_GL_object(&points.buffer);
  enqueue_task();
  wait_for_event();
  execute_kernel();
  release_GL_object(&points.buffer);
  finish_queue();
  release_event();


  // Scale to window size
  GLint windowWidth, windowHeight;
  glfwGetWindowSize(window, &windowWidth, &windowHeight);
  glViewport(0, 0, windowWidth, windowHeight);

  // Draw stuff
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION_MATRIX);
  glLoadIdentity();
  glPerspective(60, (double)windowWidth/(double)windowHeight, 0.1, 100);
  glMatrixMode(GL_MODELVIEW_MATRIX);
  glTranslatef(0,0,-5);

  glBindVertexArray(points.vao);
  glDrawArrays(GL_POINTS, 0, points.size);
  glBindVertexArray(0);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  printf("All done!\n");
}
