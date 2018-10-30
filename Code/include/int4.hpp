/// @file

#ifndef int4_hpp
#define int4_hpp

  #define LAYOUT_0 0
  #define LAYOUT_1 1

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
  ////////////////////////////////// "INT4" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class int4
  {
    private:
      const char*     get_error(cl_int loc_error);
      int               err;
      unsigned int      i;
      GLint*            data;                                                   // Declaring unfolded data array...
      cl_context        context;                                                // OpenCL context.

    public:
      int4(cl_context thecontext, int num_data);
      ~int4();

      cl_int*      x;
      cl_int*      y;
      cl_int*      z;
      cl_int*      w;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
  };

#endif
