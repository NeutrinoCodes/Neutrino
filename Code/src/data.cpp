#include "data.hpp"

float4::float4(int num_data)
{
  x = new GLfloat[num_data];                                                    // "x" data array.
  y = new GLfloat[num_data];                                                    // "y" data array.
  z = new GLfloat[num_data];                                                    // "z" data array.
  w = new GLfloat[num_data];                                                    // "w" data array.
  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  data = new GLfloat[4*num_data];                                               // Allocating data array...

  // Filling arrays with default data:
  for (i = 0; i < num_data; i++)
  {
    data[4*i + 0] = x[i] = 0.0f;                                                // Setting "x" data...
    data[4*i + 1] = y[i] = 0.0f;                                                // Setting "y" data...
    data[4*i + 2] = z[i] = 0.0f;                                                // Setting "z" data...
    data[4*i + 3] = w[i] = 1.0f;                                                // Setting "w" data...
  }
}

float4::~float4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}

int4::int4(int num_data)
{
  x = new GLint[num_data];                                                      // "x" data array.
  y = new GLint[num_data];                                                      // "y" data array.
  z = new GLint[num_data];                                                      // "z" data array.
  w = new GLint[num_data];                                                      // "w" data array.
  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  data = new GLint[4*num_data];                                                 // Allocating data array...

  // Filling arrays with default data:
  for (i = 0; i < num_data; i++)
  {
    data[4*i + 0] = x[i] = 0.0f;                                                // Setting "x" data...
    data[4*i + 1] = y[i] = 0.0f;                                                // Setting "y" data...
    data[4*i + 2] = z[i] = 0.0f;                                                // Setting "z" data...
    data[4*i + 3] = w[i] = 1.0f;                                                // Setting "w" data...
  }
}

int4::~int4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}

point4::point4(int num_data)
{
  x = new GLfloat[num_data];                                                    // "x" data array.
  y = new GLfloat[num_data];                                                    // "y" data array.
  z = new GLfloat[num_data];                                                    // "z" data array.
  w = new GLfloat[num_data];                                                    // "w" data array.
  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  data = new GLfloat[4*num_data];                                               // Allocating data array...

  // Filling arrays with default data:
  for (i = 0; i < num_data; i++)
  {
    data[4*i + 0] = x[i] = 0.0f;                                                // Setting "x" data...
    data[4*i + 1] = y[i] = 0.0f;                                                // Setting "y" data...
    data[4*i + 2] = z[i] = 0.0f;                                                // Setting "z" data...
    data[4*i + 3] = w[i] = 1.0f;                                                // Setting "w" data...
  }
}

point4::~point4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}

color4::color4(int num_data)
{
  r = new GLfloat[num_data];                                                    // "r" data array.
  g = new GLfloat[num_data];                                                    // "g" data array.
  b = new GLfloat[num_data];                                                    // "b" data array.
  a = new GLfloat[num_data];                                                    // "a" data array.
  size = num_data;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  data = new GLfloat[4*num_data];                                               // Allocating data array...

  // Filling arrays with default data:
  for (i = 0; i < num_data; i++)
  {
    data[4*i + 0] = r[i] = 0.0f;                                                // Setting "r" data...
    data[4*i + 1] = g[i] = 0.0f;                                                // Setting "g" data...
    data[4*i + 2] = b[i] = 0.0f;                                                // Setting "b" data...
    data[4*i + 3] = a[i] = 1.0f;                                                // Setting "a" data...
  }
}

color4::~color4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}
