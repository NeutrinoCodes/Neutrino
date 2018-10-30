/// @file

#ifndef platform_hpp
#define platform_hpp

  #include <stdio.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "PLATFORM" CLASS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class platform
  {
    private:
      size_t  get_info_size(cl_platform_info loc_parameter_name);
      char*   get_info_value(cl_platform_info loc_parameter_name, size_t loc_parameter_size);

    public:
      cl_platform_id          platform_id;                                      // OpenCL platform id.
      info*                   profile;                                          // Platform parameter.
      info*                   version;                                          // Platform parameter.
      info*                   name;                                             // Platform parameter.
      info*                   vendor;                                           // Platform parameter.
      info*                   extensions;                                       // Platform parameter.

            platform();
      void  init(cl_platform_id loc_platform_id);
            ~platform();
  };

#endif
