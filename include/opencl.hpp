#ifndef opencl_hpp
#define opencl_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #include <OpenGL/OpenGL.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
    #include <GL/gl.h>
  #endif

  extern  char*                   value;
  extern  cl_platform_id*         platforms;
  extern  cl_device_id*           devices;
  extern  cl_context_properties*  properties;
  extern  cl_context              context;

  cl_uint get_platforms();
  void get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint get_devices(cl_uint index_platform);
  void get_device_info(cl_uint index_device, cl_device_info name_param);
  void get_context_properties();
  void create_context();

#endif
