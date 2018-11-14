/// @file

#ifndef opencl_hpp
#define opencl_hpp

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
      cl_uint                 get_num_platforms();
      cl_platform_id          get_platform_id(cl_uint loc_platforms_number, cl_uint loc_platform_index);
      cl_uint                 get_num_devices(cl_uint loc_platform_index);
      cl_uint                 get_devices(cl_uint loc_platform_index);

      // OpenCL error get function:
      const char*             get_error     (
                                              cl_int      loc_error             // Local error code.
                                        )   ;

      // OpenCL error check function:
      void                    check_error   (
                                              cl_int      loc_error             // Local error code.
                                            );

    public:
      platform*               opencl_platform;                                  // OpenCL platform.
      cl_uint                 platforms_number;                                 // Existing OpenCL platforms number.
      cl_uint                 choosen_platform;                                 // Choosen platform index.

      device**                existing_device;                                  // Existing OpenCL device array.
      cl_uint                 devices_number;                                   // Existing OpenCL device number.
      cl_uint                 choosen_device;                                   // Choosen device index.

      cl_context_properties*  properties;
      cl_context              context_id;

            opencl();
      void  init(neutrino* loc_neutrino, GLFWwindow* loc_glfw_window, compute_device_type loc_device_type);
            ~opencl();

  };

#endif
