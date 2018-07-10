#include "interop.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "INIT" FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void init_point4(text_point4* points)
{
  int err;
  int i;
  GLfloat* unfolded_data;
  GLuint    LAYOUT_0 = 0;                                                       // "layout = 0" attribute in vertex shader.

  printf("Action: initializing OpenGL points... ");

  unfolded_data = new GLfloat[4*points->size];

  for (i = 0; i < points->size; i++)
  {
    unfolded_data[4*i + 0] = points->x[i];
    unfolded_data[4*i + 1] = points->y[i];
    unfolded_data[4*i + 2] = points->z[i];
    unfolded_data[4*i + 3] = points->w[i];
  }

  glGenVertexArrays(1, &points->vao);                                           // Generating VAO...
  glBindVertexArray(points->vao);                                               // Binding VAO...
  glGenBuffers(1, &points->vbo);                                                // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(points->size),
               unfolded_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  /*points->buffer = clCreateFromGLBuffer(context,                                // Creating OpenCL buffer from OpenGL buffer...
                                        CL_MEM_READ_WRITE,
                                        points->vbo,
                                        &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
  */
  printf("DONE!\n");
}

void init_color4(text_color4* colors)
{
  int err;
  int i;
  GLfloat* unfolded_data;
  GLuint    LAYOUT_1 = 1;                                                       // "layout = 1" attribute in vertex shader.

  printf("Action: initializing OpenGL colors... ");

  unfolded_data = new GLfloat[4*colors->size];

  for (i = 0; i < colors->size; i++)
  {
    unfolded_data[4*i + 0] = colors->r[i];
    unfolded_data[4*i + 1] = colors->g[i];
    unfolded_data[4*i + 2] = colors->b[i];
    unfolded_data[4*i + 3] = colors->a[i];
  }

  glGenVertexArrays(1, &colors->vao);                                           // Generating VAO...
  glBindVertexArray(colors->vao);                                               // Binding VAO...
  glGenBuffers(1, &colors->vbo);                                                // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(colors->size),
               unfolded_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  /*colors->buffer = clCreateFromGLBuffer(context,                                // Creating OpenCL buffer from OpenGL buffer...
                                        CL_MEM_READ_WRITE,
                                        colors->vbo,
                                        &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
  */
  printf("DONE!\n");
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "SET" FUNCTIONS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void set_float(float* data, int kernel_arg)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(float), data);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

void set_int(int* data, int kernel_arg)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(int), data);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

void set_point4(point4* points, int kernel_arg)
{
  int err;
  int i;
  GLfloat* unfolded_data;
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*points->size];

  for (i = 0; i < points->size; i++)
  {
    unfolded_data[4*i + 0] = points->x[i];
    unfolded_data[4*i + 1] = points->y[i];
    unfolded_data[4*i + 2] = points->z[i];
    unfolded_data[4*i + 3] = points->w[i];
  }

  glGenVertexArrays(1, &points->vao);                                           // Generating VAO...
  glBindVertexArray(points->vao);                                               // Binding VAO...
  glGenBuffers(1, &points->vbo);                                                // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(points->size),
               unfolded_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  points->buffer = clCreateFromGLBuffer(context,                                // Creating OpenCL buffer from OpenGL buffer...
                                        CL_MEM_READ_WRITE,
                                        points->vbo,
                                        &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &points->buffer);    // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

void set_color4(color4* colors, int kernel_arg)
{
  int err;
  int i;
  GLfloat* unfolded_data;
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*colors->size];

  for (i = 0; i < colors->size; i++)
  {
    unfolded_data[4*i + 0] = colors->r[i];
    unfolded_data[4*i + 1] = colors->g[i];
    unfolded_data[4*i + 2] = colors->b[i];
    unfolded_data[4*i + 3] = colors->a[i];
  }

  glGenVertexArrays(1, &colors->vao);                                           // Generating VAO...
  glBindVertexArray(colors->vao);                                               // Binding VAO...
  glGenBuffers(1, &colors->vbo);                                                // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(colors->size),
               unfolded_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  colors->buffer = clCreateFromGLBuffer(context,                                // Creating OpenCL buffer from OpenGL buffer...
                                        CL_MEM_READ_WRITE,
                                        colors->vbo,
                                        &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &colors->buffer);    // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "PUSH" FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void push_float4(float4* data, int kernel_arg)
{
  int err;
  int i;
  GLfloat* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*data->size];

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[4*i]     = data->x[i];
    unfolded_data[4*i + 1] = data->y[i];
    unfolded_data[4*i + 2] = data->z[i];
    unfolded_data[4*i + 3] = data->w[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);

  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(data->size), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

void push_int4(int4* data, int kernel_arg)
{
  int err;
  int i;
  GLint* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLint[4*data->size];

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[4*i]     = data->x[i];
    unfolded_data[4*i + 1] = data->y[i];
    unfolded_data[4*i + 2] = data->z[i];
    unfolded_data[4*i + 3] = data->w[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);
  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*data->size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_INT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);
  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  printf("DONE!\n");
}

void push_float(float* data, int kernel_arg)
{
  int err;

  err = clSetKernelArg(kernel, kernel_arg, sizeof(float), data);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void push_int(int* data, int kernel_arg)
{
  int err;

  err = clSetKernelArg(kernel, kernel_arg, sizeof(int), data);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "POP" FUNCTIONS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void pop_float4(float4* data, int kernel_arg)
{
  // Pleonastic function...
}

void pop_int4(int4* data, int kernel_arg)
{
  // Pleonastic function...
}

void pop_float(float* data, int kernel_arg)
{
  // Pleonastic function...
}

void pop_int(int* data, int kernel_arg)
{
  // Pleonastic function...
}

void plot(point4* points, color4* colors)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  // Preparing for plotting...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing screen...
  View_matrix = Translation_matrix*Rotation_matrix;                             // Setting View_matrix matrix...
  glUseProgram(point_shader);                                                   // Using shader...
  glUniformMatrix4fv(glGetUniformLocation(point_shader, "View_matrix"),         // Setting View_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &View_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(point_shader, "Projection_matrix"),   // Setting Projection_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &Projection_matrix[0][0]);

  // Binding "points" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "colors" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_POINTS, 0, points->size);                                     // Drawing "points"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "points" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "colors" array...
}

void overlay(text_point4* points, text_color4* colors)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  // Preparing for plotting...
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing screen...
  View_matrix = Translation_matrix*Rotation_matrix;                             // Setting View_matrix matrix...
  glUseProgram(text_shader);                                                    // Using shader...
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "View_matrix"),          // Setting View_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &View_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "Projection_matrix"),    // Setting Projection_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &Projection_matrix[0][0]);

  // Binding "points" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "colors" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_LINES, 0, points->size);                                     // Drawing "points"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "points" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "colors" array...
}
