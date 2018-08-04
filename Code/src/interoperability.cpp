/// @file

#include "interoperability.hpp"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// "INIT" FUNCTIONS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void set_text4(text4* text)
{
  int      err;
  int      i;
  GLfloat* unfolded_glyph_data;                                                 // Text "glyph" data.
  GLfloat* unfolded_color_data;                                                 // Text "color" data.
  GLuint   LAYOUT_0;                                                            // "layout = 0" attribute in vertex shader.
  GLuint   LAYOUT_1;                                                            // "layout = 1" attribute in vertex shader.

  printf("Action: initializing OpenGL text... ");

  LAYOUT_0 = 0;
  LAYOUT_1 = 1;

  unfolded_glyph_data = new GLfloat[4*text->size];
  unfolded_color_data = new GLfloat[4*text->size];

  for (i = 0; i < text->size; i++)
  {
    unfolded_glyph_data[4*i + 0] = text->x[i];
    unfolded_glyph_data[4*i + 1] = text->y[i];
    unfolded_glyph_data[4*i + 2] = text->z[i];
    unfolded_glyph_data[4*i + 3] = text->w[i];

    unfolded_color_data[4*i + 0] = text->r[i];
    unfolded_color_data[4*i + 1] = text->g[i];
    unfolded_color_data[4*i + 2] = text->b[i];
    unfolded_color_data[4*i + 3] = text->a[i];
  }

  // TEXT GLYPHS:
  glGenVertexArrays(1, &text->glyph_vao);                                       // Generating glyph VAO...
  glBindVertexArray(text->glyph_vao);                                           // Binding glyph VAO...
  glGenBuffers(1, &text->glyph_vbo);                                            // Generating glyph VBO...

  glBindBuffer(GL_ARRAY_BUFFER, text->glyph_vbo);                               // Binding glyph VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(text->size),
               unfolded_glyph_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->glyph_vbo);                               // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // TEXT COLORS:
  glGenVertexArrays(1, &text->color_vao);                                       // Generating color VAO...
  glBindVertexArray(text->color_vao);                                           // Binding color VAO...
  glGenBuffers(1, &text->color_vbo);                                            // Generating color VBO...
  glBindBuffer(GL_ARRAY_BUFFER, text->color_vbo);                               // Binding color VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(text->size),
               unfolded_color_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->color_vbo);                               // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  delete[] unfolded_glyph_data;
  delete[] unfolded_color_data;
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

  delete[] unfolded_data;

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

  delete[] unfolded_data;

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

  delete[] unfolded_data;

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

  delete[] unfolded_data;

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
