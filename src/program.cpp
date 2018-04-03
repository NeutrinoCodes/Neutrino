#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      900
#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define SIZE_X          30
#define SIZE_Y          30
#define DX              0.066f
#define DY              0.066f

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);

void load()
{
  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);
}

float tick;

void setup()
{
  size_global = points.size;
  dim_kernel = 1;
  unsigned int i;
  unsigned int j;
  float x;
  float y;

  tick = 0.0f;

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// Preparing point array... ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  y = Y_MIN;

  for (j = 0; j < SIZE_Y; j++)
  {
    x = X_MIN;

    for (i = 0; i < SIZE_X; i++)
    {
      points.x[i + SIZE_X*j]= x;                                                // Setting np "x" positions...
      points.y[i + SIZE_X*j]= y;                                                // Setting np "y" positions...
      points.z[i + SIZE_X*j] = 0.0f;                                            // Setting np "z" positions...
      points.w[i + SIZE_X*j] = 1.0f;                                            // Setting np "w" positions...
      x += DX;
    }
    y += DY;
  }

  for (i = 0; i < colors.size; i++)
  {
    colors.x[i] = glm::linearRand(0.0f, 1.0f);
    colors.y[i] = glm::linearRand(0.0f, 1.0f);
    colors.z[i] = glm::linearRand(0.0f, 1.0f);
    colors.w[i] = 1.0f;
  }

  push_float4_points(&points);
  push_float4_colors(&colors);
  push_float4_size(&points);
  clSetKernelArg(kernel, 3, sizeof(unsigned int), &tick);                       // "3" is kernel_arg = 3.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// Setting up OpenGL environment... //////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...
  Translation_matrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));      // Setting initial Translation_matrix matrix...
  Projection_matrix = glm::perspective(glm::radians(FOV),                              // Setting Projection_matrix matrix...
                                aspect_ratio,
                                NEAR_Z_CLIP,
                                FAR_Z_CLIP);
}

void loop()
{
  acquire_GL_object(&points.buffer);
  acquire_GL_object(&colors.buffer);
  clSetKernelArg(kernel, 3, sizeof(unsigned int), &tick);                       // "3" is kernel_arg = 3.
  enqueue_task();
  wait_for_event();
  execute_kernel();
  release_GL_object(&points.buffer);
  release_GL_object(&colors.buffer);
  finish_queue();
  release_event();

  tick += 0.1f;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing screen...
  View_matrix = Translation_matrix*Rotation_matrix;                             // Setting View_matrix matrix...
  glUseProgram(shader);                                                         // Using shader...
  view_shader = glGetUniformLocation(shader, "View_matrix" );                   // Getting View_matrix matrix handle from shader...
  projection_shader = glGetUniformLocation(shader, "Projection_matrix" );       // Getting Projection_matrix matrix handle from shader...
  glUniformMatrix4fv(view_shader, 1, GL_FALSE, &View_matrix[0][0]);             // Setting View_matrix matrix on shader...
  glUniformMatrix4fv(projection_shader, 1, GL_FALSE, &Projection_matrix[0][0]); // Setting Projection_matrix matrix on shader...

  // Binding "points" array...
  glEnableVertexAttribArray(0);                                                 // Matches "layout = 0" variable in vertex shader.
  glBindBuffer(GL_ARRAY_BUFFER, points.vbo);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);                        // Matches "layout = 0" variable in vertex shader.

  // Binding "colors" array...
  glEnableVertexAttribArray(1);                                                 // Matches "layout = 1" variable in vertex shader.
  glBindBuffer(GL_ARRAY_BUFFER, colors.vbo);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);                        // Matches "layout = 1" variable in vertex shader.

  // Drawing "points"...
  glDrawArrays(GL_POINTS, 0, points.size);

  // Unbinding "points" array...
  glDisableVertexAttribArray(0);                                                // Matches "layout = 0" variable in vertex shader.

  // Unbinding "colors" array...
  glDisableVertexAttribArray(1);                                                // Matches "layout = 1" variable in vertex shader.

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  printf("All done!\n");
}
