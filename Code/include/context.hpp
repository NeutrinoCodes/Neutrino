/// @file

#ifndef context_hpp
#define context_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "interoperability.hpp"

  /// **Initialization of OpenGL graphic context:**
  void init_opengl_context();

  /// **Initialization of OpenCL computational context:**
  void init_opencl_context();

  /// **Destruction of OpenGL graphic context:**
  void destroy_opengl_context();

  /// **Destruction of OpenCL computational context:**
  void destroy_opencl_context();

#endif
