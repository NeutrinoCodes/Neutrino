/// @file

#ifndef int4_hpp
#define int4_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "INT4" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class int4
  {
    private:
      const char*     get_error(cl_int loc_error);
      int               err;
      unsigned int      i;
      GLint*            data;                                                   // Declaring unfolded data array...
      cl_context        context;                                                // OpenCL context.

    public:
      int4(cl_context thecontext, int num_data);
      ~int4();

      cl_int*      x;
      cl_int*      y;
      cl_int*      z;
      cl_int*      w;

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
