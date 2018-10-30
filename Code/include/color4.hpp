/// @file

#ifndef color4_hpp
#define color4_hpp

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
  ///////////////////////////////// "COLOR4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class color4
  {
    private:
      const char*     get_error(cl_int loc_error);
      int             err;
      unsigned int    i;
      GLfloat*        data;
      cl_context      context;                                                // OpenCL context.

    public:
      GLfloat*        r;
      GLfloat*        g;
      GLfloat*        b;
      GLfloat*        a;

      int             size;
      GLuint          vao;
      GLuint          vbo;
      cl_mem          buffer;

                      color4();
      void            init(int num_data);
      void            set(kernel* k, int kernel_arg);
      void            push(queue* q, kernel* k, int kernel_arg);
      void            pop(queue* q, kernel* k, int kernel_arg);
                      ~color4();
  };

#endif
