/// @file

#ifndef float1_hpp
#define float1_hpp

  #define LAYOUT_0 0
  #define LAYOUT_1 1

  #include <stdio.h>

  #include "neutrino.hpp"

  /// **Declaration of "float1" data class:**
  /// "float1" is an array of "num_data" elements.
  class float1
  {
    private:

      cl_context        context;                                                // OpenCL context.

    public:
      float1(cl_context thecontext, int num_data);
      ~float1();

      cl_float*    x;                                                           // Declaring "x" data...

      int       size;                                                           // Declaring "size" [#]...
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;                                                         // Declaring OpenCL memory buffer...

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
  };

#endif
