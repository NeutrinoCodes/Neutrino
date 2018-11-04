/// @file

#ifndef opencl_hpp
#define opencl_hpp

  typedef enum
  {
    CPU,
    GPU,
    ACCELERATOR,
    DEFAULT,
    ALL
  } compute_device_type;

  #include "neutrino.hpp"
  #include "platform.hpp"
  #include "device.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "OPENCL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class opencl
  {
    private:
      cl_device_type          device_type;

      const char*             get_error(cl_int loc_error);
      cl_uint                 get_num_platforms();
      cl_uint                 get_platforms();
      cl_uint                 get_num_devices(cl_uint loc_platform_index);
      cl_uint                 get_devices(cl_uint loc_platform_index);

    public:
      platform**              existing_platform;                                // Existing OpenCL platform array.
      cl_uint                 platforms_number;                                 // Existing OpenCL platforms number.
      cl_uint                 choosen_platform;                                 // Choosen platform index.

      device**                existing_device;                                  // Existing OpenCL device array.
      cl_uint                 devices_number;                                   // Existing OpenCL device number.
      cl_uint                 choosen_device;                                   // Choosen device index.

      cl_context_properties*  properties;
      cl_context              context_id;

            opencl();
      void  init(GLFWwindow* loc_glfw_window, compute_device_type loc_device_type);
            ~opencl();

  };

#endif
