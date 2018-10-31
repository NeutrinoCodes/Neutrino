/// @file

#ifndef queue_hpp
#define queue_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
  #define KERNEL_NAME             "thekernel"
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

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

  #include "opencl.hpp"

  #include "utilities.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "QUEUE" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class queue
  {
    private:

    public:
      cl_command_queue  queue_id;                                               // OpenCL queue.
      cl_context        context_id;                                             // OpenCL context.
      cl_device_id      device_id;                                              // OpenCL device id.

            queue();
      void  init(opencl* loc_opencl_context);
            ~queue();
  };

#endif
