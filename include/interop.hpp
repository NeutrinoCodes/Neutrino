#ifndef interop_hpp
#define interop_hpp

#include <stdio.h>
#include <stdlib.h>

#include "opengl.hpp"
#include "opencl.hpp"
#include "data.hpp"

  void set_interop();
  void set_kernel_argument(data_float4& data);

#endif
