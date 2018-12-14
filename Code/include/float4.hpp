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
      cl_float*           data;                                                 // Wrapped data.

      size_t              size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          float4();

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
                                          size_t    loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      // "y" set function:
      void                set_y         (
                                          size_t    loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      // "z" set function:
      void                set_z         (
                                          size_t    loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
                                        );

      // "w" set function:
      void                set_w         (
                                          size_t    loc_index,                  // Data index.
                                          cl_float  loc_value                   // Data value.
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
                                          size_t    loc_index                   // Data index.
                                        );

      // "y" get function:
      cl_float            get_y         (
                                          size_t    loc_index                   // Data index.
                                        );

      // "z" get function:
      cl_float            get_z         (
                                          size_t    loc_index                   // Data index.
                                        );

      // "w" get function:
      cl_float            get_w         (
                                          size_t    loc_index                   // Data index.
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

                          ~float4();
  };

#endif
