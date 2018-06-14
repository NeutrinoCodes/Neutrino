__kernel void thekernel(__global  float4*       points,
                        __global  float4*       colors,
                                  int           points_size,
                                  float         tick)
{
  int i = get_global_id(0);
  float4 P = points[i];
  float4 C = colors[i];
  barrier(CLK_GLOBAL_MEM_FENCE);

  //P.z = 0.1*sin(10.0f*P.x - 1.0f*tick) + 0.1*cos(10.0f*P.y - 1.0f*tick);        // Sine 3D...
  P += (float4)(0.0f, 0.0f, 0.001f, 0.0f);
  barrier(CLK_GLOBAL_MEM_FENCE);                                                // Translation: read/write loop test...

  points[i] = P;
  colors[i] = C;
  barrier(CLK_GLOBAL_MEM_FENCE);
}
