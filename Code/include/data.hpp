#ifndef data_hpp
#define data_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include "opengl.hpp"
  #include "opencl.hpp"

  // data_float4:
  class data_float4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      data_float4(unsigned int num_data);
      ~data_float4();

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

  // data_float:
  class data_float
  {
    private:
      int               err;
      unsigned int      i;

    public:
      data_float(unsigned int num_data);
      ~data_float();

      float*  x;
      float*  data;
      unsigned int size;
      GLuint  vao;
      GLuint  vbo;
      cl_mem  buffer;
  };

  // data_int4:
  class data_int4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      data_int4(unsigned int num_data);
      ~data_int4();

      int*  x;
      int*  y;
      int*  z;
      int*  w;
      int*  data;
      unsigned int size;
      GLuint  vao;
      GLuint  vbo;
      cl_mem  buffer;
  };

  // data_int:
  class data_int
  {
    private:
      int               err;
      unsigned int      i;

    public:
      data_int(unsigned int num_data);
      ~data_int();

      int*  x;
      int*  data;
      unsigned int size;
      GLuint  vao;
      GLuint  vbo;
      cl_mem  buffer;
  };

#endif
