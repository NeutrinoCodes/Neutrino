/// @file

#ifndef float1_hpp
#define float1_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "FLOAT1" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class float1
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

      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            x;                                                    // "x" data.

      size_t              size;                                                 // Data size.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          float1();

      // Initialization:
      void                init          (
                                          neutrino*   loc_neutrino,             // Neutrino baseline.
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

                          ~float1();
  };

#endif
