/// @file

#ifndef int1_hpp
#define int1_hpp

  #include <stdio.h>

  class int1
  {
    private:
      int               err;
      unsigned int      i;
      // NOTE: There is no need for "unfolded-data" because these data are 1xN.
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.
      cl_context        context;                                                // OpenCL context.

    public:
      int1(cl_context thecontext, int num_data);
      ~int1();

      cl_int*      x;

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
