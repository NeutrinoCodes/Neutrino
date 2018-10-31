/// @file

#ifndef kernel_hpp
#define kernel_hpp

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

  //#include "neutrino.hpp"
  #include "queue.hpp"

  #include "utilities.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "KERNEL" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  typedef enum
  {
    WAIT,
    DONT_WAIT
  } blocking_mode;

  class kernel
  {
    private:

    public:
      cl_kernel         kernel_id;                                              // Kernel id.
      char*             file_name;                                              // Kernel file name.
      char*             source;                                                 // Kernel source.
      size_t            source_size;                                            // Kernel source size [characters].
      cl_program        program;                                                // Kernel program.
      size_t*           size;                                                   // Kernel size(s) [size_t x dimension array].
      cl_uint           dimension;                                              // Kernel dimension.
      cl_event          event;                                                  // Kernel event.
      char*             log_value;                                              // OpenCL compiler log value array.
      size_t            log_size;                                               // OpenCL compiler log size array.

            kernel();

      void  init      (
                        neutrino*     loc_neutrino,
                        char*         loc_kernel_filename,
                        size_t*       loc_kernel_size,
                        cl_uint       loc_kernel_dimension
                      );

      void  execute   (
                        queue*        loc_queue,
                        blocking_mode loc_blocking_mode
                      );

            ~kernel();
  };

#endif
