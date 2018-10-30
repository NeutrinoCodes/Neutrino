#include "color4.hpp"

color4::color4(cl_context thecontext, int num_data)
{
  r = new GLfloat[num_data];                                                    // "r" data array.
  g = new GLfloat[num_data];                                                    // "g" data array.
  b = new GLfloat[num_data];                                                    // "b" data array.
  a = new GLfloat[num_data];                                                    // "a" data array.

  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.
  LAYOUT_1 = 1;                                                                 // Setting layout = 1;
  context = thecontext;                                                         // Getting OpenCL context...

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
