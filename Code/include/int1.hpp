/// @file

#ifndef int1_hpp
#define int1_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "INT1" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class int1
  {
    private:
      const char*     get_error(cl_int loc_error);
      int               err;
      unsigned int      i;
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
