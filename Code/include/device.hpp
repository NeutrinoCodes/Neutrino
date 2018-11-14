/// @file

#ifndef device_hpp
#define device_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "DEVICE" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class device
  {
    private:
      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int            loc_error           // Local error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int            loc_error           // Error code.
                                        );

      // Gets size information:
      size_t              get_info_size (
                                          cl_device_id      loc_platform_id,    // Platform ID.
                                          cl_device_info    loc_parameter_name  // Paramenter name.
                                        );

      // Gets size information:
      char*               get_info_value(
                                          cl_device_id      loc_platform_id,    // Platform ID.
                                          cl_device_info    loc_parameter_name, // Paramenter name.
                                          size_t            loc_parameter_size  // Parameter size.
                                        );

    public:
      cl_device_id        device_id;                                            // OpenCL device id.
      info*               device_name;                                          // Device name.
      info*               device_platform;                                      // Device platform.

                          device        (
                                          cl_device_id      loc_device_id       // Device ID.
                                        );

                          ~device();
  };

#endif
