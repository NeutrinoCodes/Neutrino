/// @file

#ifndef color4_hpp
#define color4_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "COLOR4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class color4
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

      GLfloat*            data;                                                 // Wrapped data.
      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            r;                                                    // Red color channel.
      GLfloat*            g;                                                    // Green color channel.
      GLfloat*            b;                                                    // Blue color channel.
      GLfloat*            a;                                                    // Alpha transparency channel.

      int                 size;                                                 // Data size.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          color4();

      // Initialization:
      void                init          (
                                          neutrino*   loc_baseline,             // Neutrino baseline.
                                          int         loc_data_number           // Data size.
                                        );

      // Set kernel argument:
      void                set           (
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          int         loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      // Push kernel argument:
      void                push          (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          int         loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      // Pop kernel argument:
      void                pop           (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          int         loc_kernel_arg            // OpenCL kernel argument index.
                                        );

                          ~color4();
  };

#endif
