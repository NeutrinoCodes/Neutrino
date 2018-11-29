/// @file

#ifndef point4_hpp
#define point4_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "POINT4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class point4
  {
    private:
      neutrino*           baseline;                                             // Neutrino baseline.

      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int      loc_error                 // Error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int      loc_error                 // Error code.
                                        );

      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            data;                                                 // Wrapped data.

      int                 size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.
      GLuint              vao;                                                  // OpenGL data VAO.
      GLuint              vbo;                                                  // OpenGL data VBO.

                          point4();

      // Initialization:
      void                init          (
                                          neutrino* loc_baseline,               // Neutrino baseline.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          int       loc_kernel_arg,             // OpenCL kernel argument #.
                                          int       loc_data_size               // Data number.
                                        );

      void                set_x         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_y         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_z         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      void                set_w         (
                                          int       loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      cl_float            get_x         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_y         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_z         (
                                          int       loc_index                   // Data index.
                                        );

      cl_float            get_w         (
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

                          ~point4();
  };

#endif
