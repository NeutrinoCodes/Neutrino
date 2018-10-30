/// @file

#ifndef point4_hpp
#define point4_hpp

  #include <stdio.h>

  class point4
  {
    private:
      int               err;
      unsigned int      i;
      GLfloat*          data;
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.
      cl_context        context;                                                // OpenCL context.

    public:
      point4(cl_context thecontext, int num_data);
      ~point4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;

      int size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
  };

#endif
