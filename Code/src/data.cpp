#include "data.hpp"

#define ASCII_33 33
#define ASCII_126 126
#define ASCII_SCALE 0.01
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

  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    x[i] = 0.0f;                                                                // Setting "x" data...
    y[i] = 0.0f;                                                                // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...
  }
}

point4::~point4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
  delete[] x;                                                                   // Releasing "x" data...
  delete[] y;                                                                   // Releasing "y" data...
  delete[] z;                                                                   // Releasing "z" data...
  delete[] w;                                                                   // Releasing "w" data...
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


  for (i = 0; i < num_data; i++)                                                // Filling arrays with default data...
  {
    r[i] = 0.0f;                                                                // Setting "r" data...
    g[i] = 0.0f;                                                                // Setting "g" data...
    b[i] = 0.0f;                                                                // Setting "b" data...
    a[i] = 1.0f;                                                                // Setting "a" data...
  }
}

color4::~color4()
{
  release_mem_object(buffer);                                                   // Releasing OpenCL data buffer...
  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...
  delete[] r;                                                                   // Releasing "r" data...
  delete[] g;                                                                   // Releasing "g" data...
  delete[] b;                                                                   // Releasing "b" data...
  delete[] a;                                                                   // Releasing "a" data...
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
  kern = new GLfloat[num_points];                                               // Kern character spacing for each font point in input string.
  offset = new GLfloat[num_points];                                             // Character offset for each font point in input string.

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

  k = 0;

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numdata[i]; j++)                                       // Looping on all font data for each single character...
    {
      data_index[k + j] = font_index[char_item[i]] + j;         // Computing index of font data for character in input string...
    }

    k += char_numdata[i];
  }

  k = 0;

  for (i = 0; i < num_char; i++)                                              // Looping on all characters in input string...
  {
    for (j = 0; j < char_numpoints[i]; j++)                                     // Looping on all font strokes for each single character...
    {
      kern[k + j] = char_kern[i];
    }

    k += char_numpoints[i];
  }

  for (j = 0; j < char_numpoints[0]; j++)
  {
    offset[j] = 0.0f;
  }

  k = 0;

  for (i = 1; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numpoints[i]; j++)                                     // Looping on all font strokes for each single character...
    {
      offset[k + j] += font_width[char_item[i - 1]];
    }

    k += char_numpoints[i];
  }

  for (i = 0; i < num_points; i++)                                              // Unwrapping text data...
  {
    even = 2*i;                                                                 // Computing "even" index...
    odd  = 2*i + 1;                                                             // Computing "odd" index...

    x[i] = ASCII_SCALE*(font_vertex[data_index[even]]);   // Setting "x" data...
    //x[i] = font_vertex[data_index[even]]*ASCII_SCALE;
    y[i] = font_vertex[data_index[odd]]*ASCII_SCALE;                            // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...

    r[i] = R;                                                                   // Setting "r" data...
    g[i] = G;                                                                   // Setting "g" data...
    b[i] = B;                                                                   // Setting "b" data...
    a[i] = A;                                                                   // Setting "a" data...
  }
}

text4::~text4()
{
  glDeleteBuffers(1, &glyph_vbo);                                               // Releasing OpenGL glyph VBO...
  glDeleteBuffers(1, &glyph_vao);                                               // Releasing OpenGL glyph VAO...
  glDeleteBuffers(1, &color_vbo);                                               // Releasing OpenGL color VBO...
  glDeleteBuffers(1, &color_vao);                                               // Releasing OpenGL color VAO...
}
