#ifndef interop_hpp
#define interop_hpp

#include <stdio.h>
#include <stdlib.h>

#include "opengl.hpp"
#include "opencl.hpp"
#include "data.hpp"

  void set_interop();
  void push_float4_data(data_float4& data);
  void push_float4_size(data_float4 &data);
  void push_float_data(data_float& data);
  void push_float_size(data_float& data);
  void push_int4_data(data_int4& data);
  void push_int4_size(data_int4& data);
  void push_int_data(data_int& data);
  void push_int_size(data_int& data);

#endif
