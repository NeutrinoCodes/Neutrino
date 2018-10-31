/// @file

#ifndef float1_hpp
#define float1_hpp

  #define LAYOUT_0 0
  #define LAYOUT_1 1

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

  #include "kernel.hpp"
  #include "queue.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "FLOAT1" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class float1
  {
    private:
      const char*       get_error(cl_int loc_error);
      cl_context        context;                                                // OpenCL context.

    public:
      cl_float*         x;                                                      // "x" data.

      int               size;                                                   // Data size [#].
      GLuint            vao;                                                    // OpenGL Vertex Array Object.
      GLuint            vbo;                                                    // OpenGL Vertex Buffer Object.
      cl_mem            buffer;                                                 // OpenCL memory buffer.

                        float1();

      void              init  (
                                cl_context loc_opencl_context,
                                int loc_data_number
                              );

      void              set   (
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              push  (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              pop   (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

                        ~float1();
  };

#endif
