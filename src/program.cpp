#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      100

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);

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
  push_float4_data(&colors);
  push_float4_size(&points);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(3);
  P4x4 = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);
}

void loop()
{
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  acquire_GL_object(&points.buffer);
  acquire_GL_object(&colors.buffer);
  //enqueue_task();
  //wait_for_event();
  execute_kernel();
  release_GL_object(&points.buffer);
  release_GL_object(&colors.buffer);
  finish_queue();
  //release_event();


  // Scale to window size
  GLint windowWidth, windowHeight;
  glfwGetWindowSize(window, &windowWidth, &windowHeight);
  glViewport(0, 0, windowWidth, windowHeight);

  // Draw stuff
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Transfer the transformation matrices to the shader program
  GLint model = glGetUniformLocation(shader, "S4x4" );
  glUniformMatrix4fv(model, 1, GL_FALSE, &S4x4[0][0]);

  GLint view = glGetUniformLocation(shader, "R4x4" );
  glUniformMatrix4fv(view, 1, GL_FALSE, &R4x4[0][0]);

  GLint projection = glGetUniformLocation(shader, "P4x4" );
  glUniformMatrix4fv(projection, 1, GL_FALSE, &P4x4[0][0]);


  //glMatrixMode(GL_PROJECTION_MATRIX);
  //glLoadIdentity();


  //glMatrixMode(GL_MODELVIEW_MATRIX);
  //glTranslatef(0,0,-5);

  glBindVertexArray(points.vao);
  glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute
  glDrawArrays(GL_POINTS, 0, points.size);
  glBindVertexArray(0);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  printf("All done!\n");
}
