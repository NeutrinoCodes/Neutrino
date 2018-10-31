/// @file

#ifndef point4_hpp
#define point4_hpp

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
  ///////////////////////////////// "POINT4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class point4
  {
    private:
      const char*       get_error(cl_int loc_error);
      GLfloat*          data;
      cl_context        context;                                                // OpenCL context.

    public:



      GLfloat*          x;
      GLfloat*          y;
      GLfloat*          z;
      GLfloat*          w;

      int               size;
      GLuint            vao;
      GLuint            vbo;
      cl_mem            buffer;

                        point4();

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

                        ~point4();
  };

#endif
