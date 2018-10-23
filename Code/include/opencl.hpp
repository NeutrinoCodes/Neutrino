/// @file

#ifndef opencl_hpp
#define opencl_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
  #define KERNEL_NAME             "thekernel"
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
  #endif

  const char* get_error(cl_int error);

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "INFO" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class info
  {
    private:

    public:
      char*   value;                                                            // Value array.
      size_t  size;                                                             // Value array size.

      info(size_t value_size);
      ~info();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "PLATFORM" CLASS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class platform
  {
    private:
      cl_uint platform_index;
      size_t  get_info_size(cl_platform_info parameter_name);
      char*   get_info_value(cl_platform_info parameter_name, size_t value_size);

    public:
      cl_platform_id*         theplatform;                                      // OpenCL platform.
      char*                   profile;                                          // Platform parameter.
      char*                   version;                                          // Platform parameter.
      char*                   name;                                             // Platform parameter.
      char*                   vendor;                                           // Platform parameter.
      char*                   extensions;                                       // Platform parameter.

      platform(cl_uint pl_index);
      ~platform();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "DEVICE" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class device
  {
    private:
      cl_uint device_index;
      size_t  get_info_size(cl_device_info parameter_name);
      char*   get_info_value(cl_device_info parameter_name, size_t parameter_size);

    public:
      cl_device_id*           thedevice;                                        // OpenCL device.
      cl_device_type          thedevice_type;                                   // Device type.
      char*                   device_name;                                      // Device name.
      char*                   device_platform;                                  // Device platform.

      device(cl_uint dev_index);
      ~device();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "OPENCL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  typedef enum
  {
    CPU,
    GPU,
    ACCELERATOR,
    DEFAULT,
    ALL
  } device_type;

  class opencl
  {
    private:
      cl_int  err;

      cl_uint get_num_platforms();
      cl_uint get_platforms();
      cl_uint get_num_devices(cl_uint pl_index, device_type dev_type);
      cl_uint get_devices(cl_uint pl_index);

    public:
      platform*               existing_platform;
      device*                 existing_device;
      cl_uint                 num_platforms;
      cl_uint                 num_devices;
      cl_context_properties*  properties;
      cl_context              thecontext;

            opencl();
      void  init();
            ~opencl();

  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "QUEUE" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class queue
  {
    private:
      cl_uint           device_index;                                           // OpenCL device index.
      cl_context        context;                                                // OpenCL context.

    public:
      cl_command_queue  thequeue;                                               // OpenCL queue.

            queue(cl_context thecontext, cl_uint dev_index);
      void  init();
            ~queue();
  };


  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "KERNEL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  typedef enum
  {
    WAIT,
    DONT_WAIT
  } kernel_event;

  class kernel
  {
    private:
      cl_int            err;
      size_t            log_size;
      char*             log;
      cl_context        context;                                                // OpenCL context.

    public:
      cl_kernel         thekernel;
      char*             file_name;
      char*             source;
      size_t            source_size;                                            // Kernel source size [characters].
      cl_program        program;
      size_t            size;
      cl_uint           dimension;
      cl_event          event;

            kernel(cl_context thecontext);
      void  init(char* neutrino_path, char* kernel_filename, size_t kernel_size, cl_uint kernel_dimension);
      void  execute(queue* q, kernel_event k_ev);
            ~kernel();
  };

#endif
