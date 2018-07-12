#ifndef data_hpp
#define data_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "font.hpp"

  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  class float4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      float4(int num_data);
      ~float4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;
      GLfloat*  data;
      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

  class int4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      int4(int num_data);
      ~int4();

      GLint*    x;
      GLint*    y;
      GLint*    z;
      GLint*    w;
      GLint*    data;
      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

  class point4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      point4(int num_data);
      ~point4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;

      int size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

  class color4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      color4(int num_data);
      ~color4();

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

  class text4
  {
    private:
      int      err;
      int      i;
      int      j;
      int      k;
      int      even;
      int      odd;

      int      num_char;
      int      num_data;
      int      num_points;
      int      num_strokes;

      int*     char_code;
      int*     char_item;
      int*     char_numdata;
      int*     char_numpoints;
      int*     char_numstrokes;
      int*     char_kern;

      int*     data_index;
      GLfloat* kern;
      GLfloat* offset;

    public:
      text4(const char* text, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
      ~text4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;

      int       size;

      GLuint    glyph_vao;
      GLuint    color_vao;
      GLuint    glyph_vbo;
      GLuint    color_vbo;
  };

#endif
