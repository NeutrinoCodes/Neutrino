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

      GLsizeiptr          size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.
      GLuint              vbo;                                                  // OpenGL data VBO.

                          point4();

      // Initialization:
      void                init          (
                                          neutrino*   loc_baseline,             // Neutrino baseline.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          cl_uint     loc_kernel_arg,           // OpenCL kernel argument #.
                                          GLsizeiptr  loc_data_size             // Data number.
                                        );

      // "x" set function:
      void                set_x         (
                                          GLsizeiptr  loc_index,                // Data index.
                                          GLfloat     loc_value                 // Data value.
                                        );

      // "y" set function:
      void                set_y         (
                                          GLsizeiptr  loc_index,                // Data index.
                                          GLfloat     loc_value                 // Data value.
                                        );

      // "z" set function:
      void                set_z         (
                                          GLsizeiptr  loc_index,                // Data index.
                                          GLfloat     loc_value                 // Data value.
                                        );

      // "w" set function:
      void                set_w         (
                                          GLsizeiptr  loc_index,                // Data index.
                                          GLfloat     loc_value                 // Data value.
                                        );

      // "x" get function:
      GLfloat             get_x         (
                                          GLsizeiptr  loc_index                 // Data index.
                                        );

      // "y" get function:
      GLfloat             get_y         (
                                          GLsizeiptr  loc_index                 // Data index.
                                        );

      // "z" get function:
      GLfloat             get_z         (
                                          GLsizeiptr  loc_index                 // Data index.
                                        );

      // "w" get function:
      GLfloat             get_w         (
                                          GLsizeiptr  loc_index                 // Data index.
                                        );

      // OpenCL write buffer function:
      void                write         (
                                          queue*    loc_queue,                  // OpenCL queue.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          cl_uint   loc_kernel_arg              // OpenCL kernel argument index.
                                        );

      // OpenCL read buffer function:
      void                read          (
                                          queue*    loc_queue,                  // OpenCL queue.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          cl_uint   loc_kernel_arg              // OpenCL kernel argument index.
                                        );

      // OpenCL acquire buffer function:
      void                acquire_gl    (
                                          queue*  loc_queue,                    // Queue.
                                          kernel* loc_kernel,                   // Kernel.
                                          cl_uint loc_kernel_arg                // Kernel argument index.
                                        );

      // OpenCL release buffer function:
      void                release_gl    (
                                          queue*  loc_queue,                    // Queue.
                                          kernel* loc_kernel,                   // Kernel.
                                          cl_uint loc_kernel_arg                // Kernel argument index.
                                        );

                          ~point4();
  };

#endif
