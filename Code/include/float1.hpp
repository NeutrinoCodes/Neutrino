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
      neutrino*           baseline;                                             // Neutrino baseline.
      size_t*             position;                                             // Position of kernel argument in each kernel.

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

      size_t              size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          float1();

      // Initialization:
      void                init          (
                                          neutrino*   loc_baseline,             // Neutrino baseline.
                                          GLsizeiptr  loc_data_size             // Data number.
                                        );

      ////////////////////////////////////////////////////////////////////////////
      /////////////////////////// HOST "SET" FUNCTIONS:  /////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Kernel set function:
      void                set_arg       (
                                          kernel*     loc_kernel,               // OpenCL kernel.
                                          cl_uint     loc_kernel_arg            // OpenCL kernel argument #.
                                        );

      // "x" set function:
      void                set_x         (
                                          size_t      loc_index,                // Data index.
                                          cl_float    loc_value                 // Data value.
                                        );

      ////////////////////////////////////////////////////////////////////////////
      /////////////////////////// HOST "GET" FUNCTIONS:  /////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // Kernel get function:
      size_t              get_arg       (
                                          kernel*     loc_kernel                // OpenCL kernel.
                                        );

      // "x" get function:
      cl_float            get_x         (
                                          size_t      loc_index                 // Data index.
                                        );

      ////////////////////////////////////////////////////////////////////////////
      ///////////////////////////// CLIENT FUNCTIONS:  ///////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      // OpenCL write buffer function:
      void                push          (
                                          queue*      loc_queue,                // OpenCL queue.
                                          cl_uint     loc_kernel_arg            // OpenCL kernel argument index.
                                        );

      // OpenCL read buffer function:
      void                pull          (
                                          queue*      loc_queue,                // OpenCL queue.
                                          cl_uint     loc_kernel_arg            // OpenCL kernel argument index.
                                        );

                          ~float1();
  };

#endif
