#include "data.hpp"

#define ASCII_33 33
#define ASCII_126 126
#define ASCII_SCALE 0.02
#define ASCII_SPACE_LITTLE 4
#define ASCII_SPACE_BIG 16

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

text_point4::text_point4(const char* text)
{
  text_size = strlen(text);                                                     // Text array size.
  num_traits = 0;

  ascii_code    = new int[text_size];
  ascii_index   = new int[text_size];
  ascii_trait   = new int[text_size];
  ascii_kern    = new int[text_size];


  for (i = 0; i < text_size; i++)                                               // Looping on all characters in input string...
  {
    ascii_code[i] = (int)text[i];                                               // Getting single character ascii code...
    ascii_index[i] = ascii_code[i] - ASCII_33;                                  // Computing single character ascii index...

    if ( (ASCII_33 <= ascii_code[i]) && (ascii_code[i] <= ASCII_126) )          // Selecting character range...
    {
      ascii_trait[i] = font_trait_size[ascii_index[i]];                         // Getting ascii character # of traits...
      ascii_kern[i]  = ASCII_SPACE_LITTLE;                                      // Setting ascii character kern...
    }

    if (ascii_code[i] == 32)                                                    // Handling "SPACE" special case...
    {
      ascii_trait[i] = 0;                                                       // Setting ascii character # of traits ("SPACE" has no traits)...
      ascii_kern[i] = ASCII_SPACE_LITTLE + ASCII_SPACE_BIG;                     // Setting ascii character kern...
    }

    num_traits += ascii_trait[i];                                               // Accumulating total # of traits in input string...
  }

  trait_index = new int[num_traits];
  x = new GLfloat[num_traits];                                                    // "x" data array.
  y = new GLfloat[num_traits];                                                    // "y" data array.
  z = new GLfloat[num_traits];                                                    // "z" data array.
  w = new GLfloat[num_traits];                                                    // "w" data array.
  size = num_traits;                                                              // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.

  data = new GLfloat[4*num_traits];                                             // Allocating data array...

  for (i = 0; i < text_size; i++)                                               // Looping on all characters in input string...
  {
    for (j = 0; j < ascii_trait[i]; j++)                                        // Looping on all traits in single character...
    {
      trait_index[i*ascii_trait[i] + j] = font_index[ascii_index[i] + j];       // Computing trait index...
    }
  }
  // Filling arrays with default data:
  for (i = 0; i < int(num_traits/2) - 1; i++)                                   // Unwrapping text data...
  {
    data[4*i + 0] = x[i] = (font_vertex[trait_index[2*i]] +
                            ascii_kern[2*i])*ASCII_SCALE;                       // Setting "x" data...
    data[4*i + 1] = y[i] = (font_vertex[trait_index[2*i + 1]] +
                            ascii_kern[2*i + 1])*ASCII_SCALE;                   // Setting "y" data...
    data[4*i + 2] = z[i] = 0.0f;                                                // Setting "z" data...
    data[4*i + 3] = w[i] = 1.0f;                                                // Setting "w" data...
  }
}

text_point4::~text_point4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}

text_color4::text_color4(int num_data)
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

text_color4::~text_color4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
}
