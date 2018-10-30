/// @file

#ifndef color4_hpp
#define color4_hpp

  #include <stdio.h>

  class color4
  {
    private:
      int               err;
      unsigned int      i;
      GLfloat*          data;
      GLuint            LAYOUT_1;                                               // "layout = 1" attribute in vertex shader.
      cl_context        context;                                                // OpenCL context.

    public:
      color4(cl_context thecontext, int num_data);
      ~color4();

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
  };

#endif
