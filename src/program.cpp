#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/kernel.txt"

void setup()
{
  GLuint points_vao;
  GLuint points_vbo;
  GLuint colors_vbo;

  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);

  create_VAO(&points_vao);
  // Settings points VBO...
  create_VBO(&points_vbo);
  glBufferData(GL_ARRAY_BUFFER, num_points*NUM_COMPONENTS*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glVertexAttribPointer(COORDS_ATTRIBUTE, NUM_COMPONENTS, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(COORDS_ATTRIBUTE);
  create_buffer_from_VBO(context, points_vbo, CL_MEM_WRITE_ONLY, &points[0]);
  OpenCLsetKernelArgument(kernel, &points[0], sizeof(cl_mem), COORDS_ATTRIBUTE);

  // Settings colors VBO...
  create_VBO(&colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, num_points*NUM_COMPONENTS*sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glVertexAttribPointer(COLORS_ATTRIBUTE, NUM_COMPONENTS, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(COLORS_ATTRIBUTE);
  create_buffer_from_VBO(p_CL_context, p_colors_vbo, CL_MEM_WRITE_ONLY, &p_CL_colors[0]);
  OpenCLsetKernelArgument(p_CL_kernel, &p_CL_colors[0], sizeof(cl_mem), COLORS_ATTRIBUTE);
}

void loop()
{
  OpenCLenqueueAcquireGLObjects(p_CL_queue, 1, p_CL_coords);
  OpenCLenqueueAcquireGLObjects(p_CL_queue, 1, p_CL_colors);
  OpenCLsetKernelArgument(p_CL_kernel, &p_num_points, sizeof(p_num_points), NUM_POINTS_ATTRIBUTE);
  OpenCLsetKernelArgument(p_CL_kernel, &p_frame, sizeof(p_frame), FRAME_ATTRIBUTE);

  p_workitem_dimensions = 1;

  OpenCLexecuteKernel(p_CL_queue, p_CL_kernel, p_workitem_dimensions, &p_workgroup_size, NULL);
  OpenCLenqueueReleaseGLObjects(p_CL_queue, 1, p_CL_coords);
  OpenCLenqueueReleaseGLObjects(p_CL_queue, 1, p_CL_colors);
  OpenCLFinish(p_CL_queue);
  glBindVertexArray(p_points_vao);
  glDrawArrays(GL_LINE_STRIP, 0, p_num_points);
  glBindVertexArray(0);

// vecchie robe...da sistemare
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  OpenCLReleaseMemObject(p_CL_coords[0]);
  OpenCLReleaseMemObject(p_CL_colors[0]);
  glDeleteBuffers(1, &p_coords_vbo);
  glDeleteBuffers(1, &p_colors_vbo);

  printf("All done!\n");
}
