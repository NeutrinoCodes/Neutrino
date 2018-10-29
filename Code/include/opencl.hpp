/// @file

#ifndef opencl_hpp
#define opencl_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
  #define KERNEL_NAME             "thekernel"
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include "utilities.hpp"

  #include <GL/glew.h>

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
  #endif

  #include <GLFW/glfw3.h>
  #include <GLFW/glfw3native.h>

  #ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
  #else
    #include <GL/gl.h>
  #endif

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
  } compute_device_type;

  class opencl
  {
    private:
      cl_uint         get_num_platforms();
      cl_uint         get_platforms();
      cl_uint         get_num_devices(cl_uint plat_index);
      cl_uint         get_devices(cl_uint plat_index);

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
