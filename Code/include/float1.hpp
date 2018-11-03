/// @file

#ifndef float1_hpp
#define float1_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "FLOAT1" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class float1
  {
    private:
      const char*       get_error(cl_int loc_error);
      cl_context        context;                                                // OpenCL context.

    public:
      cl_float*         x;                                                      // "x" data.

      int               size;                                                   // Data size [#].
      GLuint            vao;                                                    // OpenGL Vertex Array Object.
      GLuint            vbo;                                                    // OpenGL Vertex Buffer Object.
      cl_mem            buffer;                                                 // OpenCL memory buffer.

                        float1();

      void              init  (
                                cl_context loc_opencl_context,
                                int loc_data_number
                              );

      void              set   (
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              push  (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              pop   (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

                        ~float1();
  };

#endif
