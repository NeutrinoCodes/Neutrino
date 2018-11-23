/// @file

#ifndef int4_hpp
#define int4_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "INT4" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class int4
  {
    private:
      neutrino*           baseline;                                             // Neutrino baseline.

      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int      loc_error                 // Local error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int      loc_error                 // Local error code.
                                        );

      cl_long*            data;                                                 // Wrapped data.
      cl_context          opencl_context;                                       // OpenCL context.

    public:
      cl_long*            x;                                                    // "x" data.
      cl_long*            y;                                                    // "y" data.
      cl_long*            z;                                                    // "z" data.
      cl_long*            w;                                                    // "w" data.

      size_t              size;                                                 // Data size.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          int4();

      // Initialization:
      void                init          (
                                          neutrino*   loc_baseline,             // Neutrino baseline.
                                          size_t      loc_data_number           // Data size.
                                        );

      // Set kernel argument:
      void                set           (
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      // Push kernel argument:
      void                push          (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      // Pop kernel argument:
      void                pop           (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

                          ~int4();
  };

#endif
