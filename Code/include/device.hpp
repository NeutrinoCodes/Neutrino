/// @file

#ifndef device_hpp
#define device_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "DEVICE" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class device
  {
    private:
      const char*     get_error(cl_int loc_error);
      size_t          get_info_size(cl_device_info loc_parameter_name);
      char*           get_info_value(cl_device_info loc_parameter_name, size_t loc_parameter_size);

    public:
      cl_device_id            device_id;                                        // OpenCL device id.
      info*                   device_name;                                      // Device name.
      info*                   device_platform;                                  // Device platform.

            device();
      void  init(cl_device_id loc_device_id);
            ~device();
  };

#endif
