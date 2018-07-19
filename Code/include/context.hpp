#ifndef context_hpp
#define context_hpp

  #define GLM_ENABLE_EXPERIMENTAL

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "interop.hpp"

  void init_opengl_context();
  void init_opencl_context();
  void destroy_opengl_context();
	void destroy_opencl_context();

#endif
