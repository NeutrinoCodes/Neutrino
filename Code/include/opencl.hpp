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

  typedef enum
  {
    WAIT,
    DONT_WAIT
  } kernel_event;

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

    public:
      cl_platform_id*         theplatform;                                      // OpenCL platform.
      char*                   profile;                                          // Platform parameter.
      char*                   version;                                          // Platform parameter.
      char*                   name;                                             // Platform parameter.
      char*                   vendor;                                           // Platform parameter.
      char*                   extensions;                                       // Platform parameter.

      platform(cl_uint index_platform);
      ~platform();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "DEVICE" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class device
  {
    private:
      cl_int err;
    public:
      device(cl_uint index_device);
      ~device();
  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "QUEUE" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class queue
  {
    private:
      cl_int  err;

    public:
      cl_command_queue        thequeue;

      queue();
      ~queue();
      void init();
  };


  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "KERNEL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class kernel
  {
    private:
      cl_int  err;
      size_t  log_size;
      char*   log;

    public:
      cl_kernel               thekernel;

      char*                   source_file;
      size_t                  source_size;
      char*                   source;

      cl_program              program;
      size_t                  size;
      cl_uint                 dimension;
      cl_event                event;

      kernel();
      ~kernel();
      void init(char* kernel_source, size_t kernel_size, cl_uint kernel_dimension);
      void execute(queue* q, kernel_event k_ev);
  };

  class opencl
  {
    private:
      cl_int  err;

      cl_uint get_platforms();
      void get_platform_info(cl_uint index_platform, cl_platform_info name_param);
      cl_uint get_devices(cl_uint index_platform);
      void get_device_info(cl_uint index_device, cl_device_info name_param);

    public:
      platform*               existing_platform;
      cl_uint                 num_platforms;
      cl_uint                 num_devices;
      cl_context_properties*  properties;
      cl_context              context;

      opencl();
      void init();
      ~opencl();

  };

#endif
