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
      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int      loc_error                 // Error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int      loc_error                 // Error code.
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

                          point4();

      void                init          (
                                          neutrino*   loc_baseline,             // Neutrino baseline.
                                          size_t      loc_data_number           // Data size.
                                        );

      void                set           (
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      void                push          (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      void                pop           (
                                          queue*      loc_queue,                // OpenCL queue.
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          size_t      loc_kernel_arg            // OpenCL kernel argument index.
                                        );

                          ~point4();
  };

#endif
