#ifndef context_hpp
#define context_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #include "opengl.hpp"
  #include "opencl.hpp"

  // These files are relative to the build/mac or build/linux directory:
  #define VERTEX_FILE     "../../shader/vertex.txt"
  #define FRAGMENT_FILE   "../../shader/fragment.txt"

  void create_opengl_context();
  void create_opencl_context();
  void destroy_opengl_context();
	void destroy_opencl_context();

#endif
