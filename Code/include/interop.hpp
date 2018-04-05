#ifndef interop_hpp
#define interop_hpp

#include <stdio.h>
#include <stdlib.h>

#include "opengl.hpp"
#include "opencl.hpp"
#include "data.hpp"

  void push_float4_data(data_float4* data, int kernel_arg);
  void set_int(int* data, int kernel_arg);
  void set_float(float* data, int kernel_arg);
  void set_points(data_float4* points, int kernel_arg);
  void set_colors(data_float4* colors, int kernel_arg);
  void push_float(float* data, int kernel_arg);
  void push_int(int* data, int kernel_arg);
  void push_float_data(data_float* data, int kernel_arg);
  void push_float_size(data_float* data, int kernel_arg);
  void push_int4_data(data_int4* data, int kernel_arg);
  void push_int4_size(data_int4* data, int kernel_arg);
  void push_int_data(data_int* data, int kernel_arg);
  void push_int_size(data_int* data, int kernel_arg);
  void plot_points(data_float4* points, data_float4* colors);

#endif
