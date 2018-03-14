#ifndef data_hpp
#define data_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include "opengl.hpp"
  #include "opencl.hpp"

  class data_float4
  {
    private:
      int               err;
      unsigned int      i;

    public:
      data_float4(unsigned int num_data);
      ~data_float4();

      float*  x;
      float*  y;
      float*  z;
      float*  w;
      float*  data;
      unsigned int size;
      GLuint  vao;
      GLuint  vbo;
      cl_mem  buffer;
  };

#endif
