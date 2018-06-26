#ifndef data_hpp
#define data_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include "opengl.hpp"
  #include "opencl.hpp"

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

#endif
