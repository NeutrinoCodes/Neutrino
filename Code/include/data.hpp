#ifndef data_hpp
#define data_hpp

  #define GLM_ENABLE_EXPERIMENTAL

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "font.hpp"

  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  class ket3
  {
    private:

    public:
      ket3();
      ~ket3();

      float x;
      float y;
      float z;
  };

  class ket4
  {
    private:

    public:
      ket4();
      ~ket4();

      float x;
      float y;
      float z;
  };

  class euclidean_metric
  {
    private:

    public:
      euclidean_metric();
      ~euclidean_metric();

      float g_11;
      float g_12;
      float g_13;
      float g_14;
      float g_21;
      float g_22;
      float g_23;
      float g_24;
      float g_31;
      float g_32;
      float g_33;
      float g_34;
      float g_41;
      float g_42;
      float g_43;
      float g_44;
  };

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
      int      shift;
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
      int*     kern;
      int*     offset;

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
