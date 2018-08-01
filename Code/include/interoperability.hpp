/// @file

#ifndef interoperability_hpp
#define interoperability_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "data.hpp"

  void init_text4(text4* text);

  void set_float(float* data, int kernel_arg);
  void set_int(int* data, int kernel_arg);
  void set_point4(point4* points, int kernel_arg);
  void set_color4(color4* colors, int kernel_arg);

  void push_float4(float4* data, int kernel_arg);
  void push_int4(int4* data, int kernel_arg);
  void push_float(float* data, int kernel_arg);
  void push_int(int* data, int kernel_arg);

  void pop_float4(float4* data, int kernel_arg);
  void pop_int4(int4* data, int kernel_arg);
  void pop_float(float* data, int kernel_arg);
  void pop_int(int* data, int kernel_arg);

#endif
