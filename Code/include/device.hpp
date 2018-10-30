/// @file

#ifndef device_hpp
#define device_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "DEVICE" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class device
  {
    private:
      size_t  get_info_size(cl_device_info loc_parameter_name);
      char*   get_info_value(cl_device_info loc_parameter_name, size_t loc_parameter_size);

    public:
      cl_device_id            device_id;                                        // OpenCL device id.
      info*                   device_name;                                      // Device name.
      info*                   device_platform;                                  // Device platform.

            device();
      void  init(cl_device_id loc_device_id);
            ~device();
  };

#endif
