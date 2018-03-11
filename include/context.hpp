#ifndef context_hpp
#define context_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #include "opengl.hpp"
  #include "opencl.hpp"

  void create_opengl_context();
  void create_opencl_context();
  void destroy_opengl_context();
	void destroy_opencl_context();

#endif
