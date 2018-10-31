/// @file

#ifndef float4_hpp
#define float4_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "FLOAT4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class float4
  {
    private:
      const char*     get_error(cl_int loc_error);
      int               err;                                                    // Declaring "error" code...
      unsigned int      i;                                                      // Declaring "i" index...
      GLfloat*          data;                                                   // Declaring unfolded data array...
      cl_context        context;                                                // OpenCL context.

    public:
      float4(cl_context thecontext, int num_data);
      ~float4();

      cl_float*    x;                                                           // Declaring "x" data...
      cl_float*    y;                                                           // Declaring "y" data...
      cl_float*    z;                                                           // Declaring "z" data...
      cl_float*    w;                                                           // Declaring "w" data...

      int       size;                                                           // Declaring "size" [#]...
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;                                                         // Declaring OpenCL memory buffer...

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
  };

#endif
