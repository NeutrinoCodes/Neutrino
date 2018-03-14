#include "data.hpp"

data_float4::data_float4(unsigned int num_data)
{
  x = new float[num_data];
  y = new float[num_data];
  z = new float[num_data];
  w = new float[num_data];
  size = num_data;

  data = new float[4*num_data];

  for (i = 0; i < num_data; i++)
  {
    data[4*i]     = x[i] = 0;
    data[4*i + 1] = y[i] = 0;
    data[4*i + 2] = z[i] = 0;
    data[4*i + 3] = w[i] = 1.0;
  }

}

data_float4::~data_float4()
{
  release_mem_object(buffer);
  glDeleteBuffers(1, &vbo);
}
