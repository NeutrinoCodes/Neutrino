#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      121
#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define SIZE_X          11
#define SIZE_Y          11
#define DX              0.2f
#define DY              0.2f

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);

// Vertices of a square:
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
  unsigned int i;
  unsigned int j;
  float x;
  float y;

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
    colors.x[i] = 1.0f;
    colors.y[i] = 0.0f;
    colors.z[i] = 0.0f;
    colors.w[i] = 1.0f;
  }

  push_float4_points(&points);
  push_float4_colors(&colors);
  push_float4_size(&points);

  // Setting buffer for square...
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
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


  // Drawing the square...
  glEnableVertexAttribArray(0);
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


  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
  printf("All done!\n");
}
