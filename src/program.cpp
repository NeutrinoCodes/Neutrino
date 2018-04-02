#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      100

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] =
{
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   -1.0f, 1.0f ,0.0f
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

  for (i = 0; i < points.size; i++)
  {
    points.x[i] = i/points.size;
    points.y[i] = i/points.size;
    points.z[i] = i/points.size;
    colors.x[i] = 1.0;
    colors.y[i] = 1.0;
    colors.z[i] = 1.0;
  }

  push_float4_data(&points);
  push_float4_data(&colors);
  push_float4_size(&points);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(LINE_WIDTH);
  Translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));
  Projection = glm::perspective(glm::radians(FOV), aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);

  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void loop()
{
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  acquire_GL_object(&points.buffer);
  acquire_GL_object(&colors.buffer);
  enqueue_task();
  wait_for_event();
  execute_kernel();
  release_GL_object(&points.buffer);
  release_GL_object(&colors.buffer);
  finish_queue();
  release_event();

  // Draw stuff
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  View = Translation*Rotation;
  glUseProgram(shader);

  // Transfer the transformation matrices to the shader program
  view_shader = glGetUniformLocation(shader, "View" );
  projection_shader = glGetUniformLocation(shader, "Projection" );
  glUniformMatrix4fv(view_shader, 1, GL_FALSE, &View[0][0]);
  glUniformMatrix4fv(projection_shader, 1, GL_FALSE, &Projection[0][0]);


  //glMatrixMode(GL_PROJECTION_MATRIX);
  //glLoadIdentity();


  //glMatrixMode(GL_MODELVIEW_MATRIX);
  //glTranslatef(0,0,-5);

  //glBindVertexArray(points.vao);
  //glVertexAttrib3f((GLuint)1, 1.0, 1.0, 1.0); // set constant color attribute
  //glDrawArrays(GL_POINTS, 0, points.size);
  //glBindVertexArray(0);



  // 1rst attribute buffer : vertices
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

  // Drawing the square...
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
