/// @file

#ifndef int4_hpp
#define int4_hpp

  #include "neutrino.hpp"
  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "INT4" CLASS /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class int4
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
      cl_long*            data;                                                 // Wrapped data.

      size_t              size;                                                 // Data size.
      cl_mem              buffer;                                               // OpenGL data memory buffer.

                          int4();

      // Initialization:
      void                init          (
                                          neutrino* loc_baseline,               // Neutrino baseline.
                                          kernel*   loc_kernel,                 // OpenCL kernel.
                                          cl_uint   loc_kernel_arg,             // OpenCL kernel argument #.
                                          size_t    loc_data_size               // Data number.
                                        );

      // "x" set function:
      void                set_x         (
                                          size_t    loc_index,                  // Data index.
                                          cl_long   loc_value                   // Data value.
                                        );

      // "y" set function:
      void                set_y         (
                                          size_t    loc_index,                  // Data index.
                                          cl_long   loc_value                   // Data value.
                                        );

      // "z" set function:
      void                set_z         (
                                          size_t    loc_index,                  // Data index.
                                          cl_long   loc_value                   // Data value.
                                        );

      // "w" set function:
      void                set_w         (
                                          size_t    loc_index,                  // Data index.
                                          cl_long   loc_value                   // Data value.
                                        );

      // "x" get function:
      cl_long             get_x         (
                                          size_t    loc_index                   // Data index.
                                        );

      // "y" get function:
      cl_long             get_y         (
                                          size_t    loc_index                   // Data index.
                                        );

      // "z" get function:
      cl_long             get_z         (
                                          size_t    loc_index                   // Data index.
                                        );

      // "w" get function:
      cl_long             get_w         (
                                          size_t    loc_index                   // Data index.
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

                          ~int4();
  };

#endif
