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
      // OpenCL error function:
      const char*         get_error     (
                                          cl_int loc_error                      // Local error code.
                                        );

      void                check_error   (
                                          cl_int loc_error                      // Local error code.
                                        );

      GLfloat*            data;
      cl_context          opencl_context;                                       // OpenCL context.

    public:
      GLfloat*            r;
      GLfloat*            g;
      GLfloat*            b;
      GLfloat*            a;

      cl_ulong            size;
      GLuint              vao;
      GLuint              vbo;
      cl_mem              buffer;

                          color4();

      void                init          (
                                          neutrino* loc_neutrino,
                                          cl_ulong loc_data_number
                                        );

      void                set           (
                                          kernel* loc_kernel,
                                          cl_ulong loc_kernel_arg
                                        );

      void                push          (
                                          queue* loc_queue,
                                          kernel* loc_kernel,
                                          cl_ulong loc_kernel_arg
                                        );

      void                pop           (
                                          queue* loc_queue,
                                          kernel* loc_kernel,
                                          cl_ulong loc_kernel_arg
                                        );

                          ~color4();
  };

#endif
