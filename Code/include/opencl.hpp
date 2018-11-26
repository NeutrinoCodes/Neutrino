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
      neutrino*               baseline;                                         // Neutrino baseline.
      cl_device_type          device_type;
      char*                   device_type_text;
      cl_uint                 get_platforms_number();
      cl_platform_id          get_platform_id(cl_uint loc_platform_index);
      cl_uint                 get_devices_number();
      cl_device_id            get_device_id(cl_uint loc_platform_index);

      // OpenCL error get function:
      const char*             get_error     (
                                              cl_int      loc_error             // Local error code.
                                        )   ;

      // OpenCL error check function:
      void                    check_error   (
                                              cl_int      loc_error             // Local error code.
                                            );

    public:
      cl_uint                 platforms_number;                                 // Existing OpenCL platforms number.
      cl_uint                 selected_platform;                                // Selected platform index.
      platform*               ppp;                                  // OpenCL platform.

      cl_uint                 devices_number;                                   // Existing OpenCL device number.
      cl_uint                 selected_device;                                  // Selected device index.
      device*                 opencl_device;                                    // Existing OpenCL device array.

      cl_context_properties*  properties;
      cl_context              context_id;

            opencl();
      void  init(neutrino* loc_baseline, GLFWwindow* loc_glfw_window, compute_device_type loc_device_type);
            ~opencl();

  };

#endif
