/// @file

#ifndef float4_hpp
#define float4_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "FLOAT4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class float4
  {
    private:
      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int      loc_error                 // Local error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int      loc_error                 // Local error code.
                                        );

      GLfloat*            data;                                                 // Wrapped data.
      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            x;                                                    // "x" data.
      GLfloat*            y;                                                    // "y" data.
      GLfloat*            z;                                                    // "z" data.
      GLfloat*            w;                                                    // "w" data.

      size_t              size;                                                 // Data size.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          float4();

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

                          ~float4();
  };

#endif
