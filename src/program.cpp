#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      10

data_float4 points(NUM_POINTS);
//data_float4 colors(NUM_POINTS);

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] =
{
   -1.2f, -1.2f, 0.0f,
   1.2f, -1.2f, 0.0f,
   1.2f,  1.2f, 0.0f,
   -1.2f, 1.2f ,0.0f
};

// This will identify our vertex buffer
GLuint vertexbuffer;

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

  // Setting buffer for square...
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(LINE_WIDTH);
  Translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));
  Projection = glm::perspective(glm::radians(FOV), aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing screen...
  View = Translation*Rotation;                                                  // Setting View matrix...
  glUseProgram(shader);                                                         // Using shader...
  view_shader = glGetUniformLocation(shader, "View" );                          // Getting View matrix handle from shader...
  projection_shader = glGetUniformLocation(shader, "Projection" );              // Getting Projection matrix handle from shader...
  glUniformMatrix4fv(view_shader, 1, GL_FALSE, &View[0][0]);                    // Setting View matrix on shader...
  glUniformMatrix4fv(projection_shader, 1, GL_FALSE, &Projection[0][0]);        // Setting Projection matrix on shader...


  // Drawing arrays...
  glVertexAttrib3f((GLuint)1, 1.0, 1.0, 1.0); // set constant color attribute
  glBindVertexArray(points.vao);
  glDrawArrays(GL_POINTS, 0, points.size);
  glBindVertexArray(0);



  // Drawing the square...
  /*glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  glVertexAttrib3f((GLuint)1, 1.0, 1.0, 1.0); // set constant color attribute
  glDrawArrays(GL_LINE_LOOP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);
  */

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  printf("All done!\n");
}
