float1::float1(int num_data)
{
  x = new cl_float[num_data];                                                   // "x" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.
  LAYOUT_0 = 0;                                                                 // Setting layout = 0;

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data:
  {
    x[i] = 0.0f;                                                                // Setting "x" data...
  }
}

void float1::init()
{
  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(size), x, GL_DYNAMIC_DRAW);    // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 1, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void float1::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void float1::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void float1::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

float1::~float1()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
  delete[] x;                                                                   // Releasing data memory...

  printf("DONE!\n");
}

int1::int1(int num_data)
{
  x = new cl_int[num_data];                                                     // "x" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.
  LAYOUT_0 = 0;                                                                 // Setting layout = 0;

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data:
  {
    x[i] = 0;                                                                   // Setting "x" data...
  }
}

void int1::init()
{
  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLint)*(size), x, GL_DYNAMIC_DRAW);      // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 1, GL_INT, GL_FALSE, 0, 0);                   // Specifying the format for "layout = 0" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void int1::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void int1::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void int1::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

int1::~int1()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
  delete[] x;                                                                   // Releasing data memory...

  printf("DONE!\n");
}

float4::float4(int num_data)
{
  x = new cl_float[num_data];                                                   // "x" data array.
  y = new cl_float[num_data];                                                   // "y" data array.
  z = new cl_float[num_data];                                                   // "z" data array.
  w = new cl_float[num_data];                                                   // "w" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.
  LAYOUT_0 = 0;                                                                 // Setting layout = 0;

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    x[i] = 0.0f;                                                                // Setting "x" data...
    y[i] = 0.0f;                                                                // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...
  }
}

void float4::init()
{
  data = new GLfloat[4*size];                                                   // Creating array for unfolded data...

  for (i = 0; i < size; i++)                                                    // Filling unfolded data array...
  {
    data[4*i + 0] = x[i];                                                       // Filling "x"...
    data[4*i + 1] = y[i];                                                       // Filling "y"...
    data[4*i + 2] = z[i];                                                       // Filling "z"...
    data[4*i + 3] = w[i];                                                       // Filling "w"...
  }

  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(size), data, GL_DYNAMIC_DRAW); // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  delete[] data;                                                                // Deleting array for unfolded data...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void float4::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void float4::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void float4::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

float4::~float4()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...

  delete[] x;
  delete[] y;
  delete[] z;
  delete[] w;

  printf("DONE!\n");
}

int4::int4(int num_data)
{
  LAYOUT_0 = 0;                                                                 // Setting layout = 0;

  x = new cl_int[num_data];                                                     // "x" data array.
  y = new cl_int[num_data];                                                     // "y" data array.
  z = new cl_int[num_data];                                                     // "z" data array.
  w = new cl_int[num_data];                                                     // "w" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    x[i] = 0;                                                                   // Setting "x" data...
    y[i] = 0;                                                                   // Setting "y" data...
    z[i] = 0;                                                                   // Setting "z" data...
    w[i] = 1;                                                                   // Setting "w" data...
  }
}

void int4::init()
{
  data = new GLint[4*size];                                                   // Creating array for unfolded data...

  for (i = 0; i < size; i++)                                                    // Filling unfolded data array...
  {
    data[4*i + 0] = x[i];                                                       // Filling "x"...
    data[4*i + 1] = y[i];                                                       // Filling "y"...
    data[4*i + 2] = z[i];                                                       // Filling "z"...
    data[4*i + 3] = w[i];                                                       // Filling "w"...
  }

  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLint)*(size), data, GL_DYNAMIC_DRAW); // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_INT, GL_FALSE, 0, 0);                   // Specifying the format for "layout = 0" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  delete[] data;                                                                // Deleting array for unfolded data...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void int4::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void int4::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void int4::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

int4::~int4()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...

  delete[] x;
  delete[] y;
  delete[] z;
  delete[] w;

  printf("DONE!\n");
}

point4::point4(int num_data)
{
  LAYOUT_0 = 0;                                                                 // Setting layout = 0;

  x = new GLfloat[num_data];                                                    // "x" data array.
  y = new GLfloat[num_data];                                                    // "y" data array.
  z = new GLfloat[num_data];                                                    // "z" data array.
  w = new GLfloat[num_data];                                                    // "w" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    x[i] = 0.0f;                                                                // Setting "x" data...
    y[i] = 0.0f;                                                                // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...
  }
}

void point4::init()
{
  data = new GLfloat[4*size];                                                   // Creating array for unfolded data...

  for (i = 0; i < size; i++)                                                    // Filling unfolded data array...
  {
    data[4*i + 0] = x[i];                                                       // Filling "x"...
    data[4*i + 1] = y[i];                                                       // Filling "y"...
    data[4*i + 2] = z[i];                                                       // Filling "z"...
    data[4*i + 3] = w[i];                                                       // Filling "w"...
  }

  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(size), data, GL_DYNAMIC_DRAW); // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  delete[] data;                                                                // Deleting array for unfolded data...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void point4::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void point4::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void point4::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

point4::~point4()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...

  delete[] x;                                                                   // Releasing "x" data...
  delete[] y;                                                                   // Releasing "y" data...
  delete[] z;                                                                   // Releasing "z" data...
  delete[] w;                                                                   // Releasing "w" data...

  printf("DONE!\n");
}

color4::color4(int num_data)
{
  LAYOUT_1 = 1;                                                                 // Setting layout = 1;

  r = new GLfloat[num_data];                                                    // "r" data array.
  g = new GLfloat[num_data];                                                    // "g" data array.
  b = new GLfloat[num_data];                                                    // "b" data array.
  a = new GLfloat[num_data];                                                    // "a" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    r[i] = 0.0f;                                                                // Setting "r" data...
    g[i] = 0.0f;                                                                // Setting "g" data...
    b[i] = 0.0f;                                                                // Setting "b" data...
    a[i] = 1.0f;                                                                // Setting "a" data...
  }
}

void color4::init()
{
  data = new GLfloat[4*size];                                                   // Creating array for unfolded data...

  for (i = 0; i < size; i++)                                                    // Filling unfolded data array...
  {
    data[4*i + 0] = r[i];                                                       // Filling "x"...
    data[4*i + 1] = g[i];                                                       // Filling "y"...
    data[4*i + 2] = b[i];                                                       // Filling "z"...
    data[4*i + 3] = a[i];                                                       // Filling "w"...
  }

  glGenVertexArrays(1, &vao);                                                   // Generating VAO...
  glBindVertexArray(vao);                                                       // Binding VAO...
  glGenBuffers(1, &vbo);                                                        // Generating VBO...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(size), data, GL_DYNAMIC_DRAW); // Creating and initializing a buffer object's data store...
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                           // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...
  buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo, &err);         // Creating OpenCL buffer from OpenGL buffer...

  delete[] data;                                                                // Deleting array for unfolded data...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void color4::set(kernel* k, int kernel_arg)
{
  err = clSetKernelArg(k->thekernel, kernel_arg, sizeof(cl_mem), &buffer);      // Setting buffer as OpenCL kernel argument...

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }
}

void color4::push(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueAcquireGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Passing "points" to OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

void color4::pop(queue* q, kernel* k, int kernel_arg)
{
  err = clEnqueueReleaseGLObjects(q->thequeue, 1, &buffer, 0, NULL, NULL);      // Releasing "points" from OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

color4::~color4()
{
  printf("Action: releasing \"float1\" object... ");

  if(buffer != NULL)
  {
    err = clReleaseMemObject(buffer);                                           // Releasing OpenCL buffer object...

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...

  delete[] r;                                                                   // Releasing "r" data...
  delete[] g;                                                                   // Releasing "g" data...
  delete[] b;                                                                   // Releasing "b" data...
  delete[] a;                                                                   // Releasing "a" data...

  printf("DONE!\n");
}

text4::text4(const char* text, GLfloat R, GLfloat G, GLfloat B, GLfloat A)
{
  num_char = strlen(text);                                                      // Total # of characters in input string.
  num_data = 0;                                                                 // Total # of font data in input string.
  num_points = 0;                                                               // Total # of font points in input string.
  num_strokes = 0;                                                              // Total # of font strokes in input string.

  char_code         = new int[num_char];                                        // Ascii code for each character in input string.
  char_item         = new int[num_char];                                        // Font character position for each character in input string.
  char_numdata      = new int[num_char];                                        // # of font data for each character in input string.
  char_numpoints    = new int[num_char];                                        // # of font points for each character in input string.
  char_numstrokes   = new int[num_char];                                        // # of font strokes for each character in input string.
  char_kern         = new int[num_char];                                        // Kern spacing for each character in input string.

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    char_code[i] = (int)text[i];                                                // Getting single character ascii code...

    if ( (ASCII_33 <= char_code[i]) && (char_code[i] <= ASCII_126) )            // Selecting character range...
    {
      char_item[i] = char_code[i] - ASCII_33;                                   // Computing font character position for character in input string...
      char_numdata[i] = font_numdata[char_item[i]];                             // Computing # of data for character in input string...
      char_kern[i]  = ASCII_SPACE_LITTLE;                                       // Setting kern spacing for character in input string...
    }

    if (char_code[i] == 32)                                                     // Handling "SPACE" special case...
    {
      char_item[i] = 0;                                                         // Computing font character position for character in input string...
      char_numdata[i] = 0;                                                      // Setting # of data for character in input string... ("SPACE" has no data)
      char_kern[i] = ASCII_SPACE_LITTLE + ASCII_SPACE_BIG;                      // Setting kern spacing for character in input string...
    }

    char_numpoints[i] = char_numdata[i]/2;                                      // Computing # of font points for each character in input string...
    char_numstrokes[i] = char_numpoints[i]/2;                                   // Computing # of font strokes for each character in input string...
    num_data += char_numdata[i];                                                // Accumulating total # of font data in input string...
    num_points += char_numpoints[i];                                            // Accumulating total # of font points in input string...
    num_strokes += char_numstrokes[i];                                          // Accumulating total # of font strokes in input string...
  }

  data_index = new int[num_data];                                               // Index of font data for each character in input string.
  kern = new int[num_points];                                                   // Kern character spacing for each font point in input string.
  offset = new int[num_points];                                                 // Character offset for each font point in input string.

  x = new GLfloat[num_points];                                                  // "x" data array.
  y = new GLfloat[num_points];                                                  // "y" data array.
  z = new GLfloat[num_points];                                                  // "z" data array.
  w = new GLfloat[num_points];                                                  // "w" data array.

  r = new GLfloat[num_points];                                                  // "r" data array.
  g = new GLfloat[num_points];                                                  // "g" data array.
  b = new GLfloat[num_points];                                                  // "b" data array.
  a = new GLfloat[num_points];                                                  // "a" data array.

  size = num_points;                                                            // Text array size.

  glyph_vao = 0;                                                                // OpenGL glyph data VAO.
  color_vao = 0;                                                                // OpenGL color data VAO.
  glyph_vbo = 0;                                                                // OpenGL glyph data VBO.
  color_vbo = 0;                                                                // OpenGL color data VBO.

  k = 0;                                                                        // Resetting "k" index...

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numdata[i]; j++)                                       // Looping on all font data for each single character...
    {
      data_index[k + j] = font_index[char_item[i]] + j;                         // Computing index of font data for character in input string...
    }

    k += char_numdata[i];                                                       // Accumulating # of data...
  }

  k = 0;                                                                        // Resetting "k" index...
  shift = 0;                                                                    // Resetting character shift...

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numpoints[i]; j++)                                     // Looping on all font strokes for each single character...
    {
      kern[k + j] = char_kern[i];                                               // Computing kern for characters in input string...
      offset[k + j] = shift;                                                    // Computing offset for characters in input string...
    }

    k += char_numpoints[i];                                                     // Accumulating # of points...
    shift += font_width[char_item[i]];                                          // Accumulating character shift...
  }

  for (i = 0; i < num_points; i++)                                              // Unwrapping text data...
  {
    even = 2*i;                                                                 // Computing "even" index...
    odd  = 2*i + 1;                                                             // Computing "odd" index...

    // Setting "x" data:
    x[i] = ASCII_SCALE*                                                         // Applying scaling...
           (font_vertex[data_index[even]] -                                     // Setting vertex data...
            font_vertex[data_index[0]] +                                        // Subtracting base point...
            offset[i] +                                                         // Adding offset...
            kern[i]);                                                           // Adding kern...

    y[i] = font_vertex[data_index[odd]]*ASCII_SCALE;                            // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...

    r[i] = R;                                                                   // Setting "r" data...
    g[i] = G;                                                                   // Setting "g" data...
    b[i] = B;                                                                   // Setting "b" data...
    a[i] = A;                                                                   // Setting "a" data...
  }

  printf("DONE!\n");
}

void text4::init()
{
  printf("Action: initializing OpenGL text... ");

  LAYOUT_0 = 0;
  LAYOUT_1 = 1;

  glyph_data = new GLfloat[4*size];
  color_data = new GLfloat[4*size];

  for (i = 0; i < size; i++)
  {
    glyph_data[4*i + 0] = x[i];
    glyph_data[4*i + 1] = y[i];
    glyph_data[4*i + 2] = z[i];
    glyph_data[4*i + 3] = w[i];

    color_data[4*i + 0] = r[i];
    color_data[4*i + 1] = g[i];
    color_data[4*i + 2] = b[i];
    color_data[4*i + 3] = a[i];
  }

  // TEXT GLYPHS:
  glGenVertexArrays(1, &glyph_vao);                                             // Generating glyph VAO...
  glBindVertexArray(glyph_vao);                                                 // Binding glyph VAO...
  glGenBuffers(1, &glyph_vbo);                                                  // Generating glyph VBO...

  glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);                                     // Binding glyph VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(size),
               glyph_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);                                     // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // TEXT COLORS:
  glGenVertexArrays(1, &color_vao);                                             // Generating color VAO...
  glBindVertexArray(color_vao);                                                 // Binding color VAO...
  glGenBuffers(1, &color_vbo);                                                  // Generating color VBO...
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);                                     // Binding color VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(size),
               color_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);                                     // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  delete[] glyph_data;
  delete[] color_data;

  printf("DONE!\n");
}

text4::~text4()
{
  glDeleteBuffers(1, &glyph_vbo);                                               // Releasing OpenGL glyph VBO...
  glDeleteBuffers(1, &glyph_vao);                                               // Releasing OpenGL glyph VAO...
  glDeleteBuffers(1, &color_vbo);                                               // Releasing OpenGL color VBO...
  glDeleteBuffers(1, &color_vao);                                               // Releasing OpenGL color VAO...

  delete[] char_code;                                                           // Releasing ascii code for each character in input string...
  delete[] char_item;                                                           // Releasing font character position for each character in input string...
  delete[] char_numdata;                                                        // Releasing # of font data for each character in input string...
  delete[] char_numpoints;                                                      // Releasing # of font points for each character in input string...
  delete[] char_numstrokes;                                                     // Releasing # of font strokes for each character in input string...
  delete[] char_kern;                                                           // Releasing kern spacing for each character in input string...

  delete[] data_index;                                                          // Releasing index of font data for each character in input string...
  delete[] kern;                                                                // Releasing kern character spacing for each font point in input string...
  delete[] offset;                                                              // Releasing character offset for each font point in input string...

  delete[] x;                                                                   // Releasing "x" data array...
  delete[] y;                                                                   // Releasing "y" data array...
  delete[] z;                                                                   // Releasing "z" data array...
  delete[] w;                                                                   // Releasing "w" data array...

  delete[] r;                                                                   // Releasing "r" data array...
  delete[] g;                                                                   // Releasing "g" data array...
  delete[] b;                                                                   // Releasing "b" data array...
  delete[] a;                                                                   // Releasing "a" data array...
}
