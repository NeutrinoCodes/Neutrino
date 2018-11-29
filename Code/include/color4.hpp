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

      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            data;                                                 // Wrapped data.

      int                 size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.

                          color4();

      // Initialization:
      void                init          (
                                          neutrino* loc_baseline,               // Neutrino baseline.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          int       loc_kernel_arg,             // OpenCL kernel argument #.
                                          int       loc_data_size               // Data number.
                                        );

      void                set_r         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_g         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_b         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_a         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      cl_float            get_r         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_g         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_b         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_a         (
                                          int       loc_index                   // Data index.
                                        );

      // Push kernel argument:
      void                write         (
                                          queue*    loc_queue,                  // OpenCL queue.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          int       loc_kernel_arg              // OpenCL kernel argument index.
                                        );

      // Pop kernel argument:
      void                read          (
                                          queue*    loc_queue,                  // OpenCL queue.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          int       loc_kernel_arg              // OpenCL kernel argument index.
                                        );

      void                acquire_gl    (
                                          queue*  loc_queue,                    // Queue.
                                          kernel* loc_kernel,                   // Kernel.
                                          int     loc_kernel_arg                // Kernel argument index.
                                        );

      void                release_gl    (
                                          queue*  loc_queue,                    // Queue.
                                          kernel* loc_kernel,                   // Kernel.
                                          int     loc_kernel_arg                // Kernel argument index.
                                        );

                          ~color4();
  };

#endif
