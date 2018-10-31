/// @file

#ifndef kernel_hpp
#define kernel_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "KERNEL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class kernel
  {
    private:

    public:
      cl_kernel         kernel_id;                                              // Kernel id.
      char*             file_name;                                              // Kernel file name.
      char*             source;                                                 // Kernel source.
      size_t            source_size;                                            // Kernel source size [characters].
      cl_program        program;                                                // Kernel program.
      size_t*           size;                                                   // Kernel size(s) [size_t x dimension array].
      cl_uint           dimension;                                              // Kernel dimension.
      cl_event          event;                                                  // Kernel event.
      char*             log_value;                                              // OpenCL compiler log value array.
      size_t            log_size;                                               // OpenCL compiler log size array.

            kernel();

      void  init      (
                        neutrino*     loc_neutrino,
                        char*         loc_kernel_filename,
                        size_t*       loc_kernel_size,
                        cl_uint       loc_kernel_dimension
                      );

      void  execute   (
                        queue*        loc_queue,
                        blocking_mode loc_blocking_mode
                      );

            ~kernel();
  };

#endif
