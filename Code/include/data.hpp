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
      GLfloat*  data;
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
      GLfloat*  data;
      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

  class text_point4
  {
    private:
      int               err;
      unsigned int      i;
      unsigned int      j;
      int               text_size;
      int               num_traits;
      int*              ascii_code;
      int*              ascii_index;
      int*              ascii_trait;
      int*              trait_index;
      int*              ascii_kern;

    public:
      text_point4(const char* text);
      ~text_point4();

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

  class text_color4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      text_color4(int num_data);
      ~text_color4();

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;
      GLfloat*  data;
      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
  };

#endif
