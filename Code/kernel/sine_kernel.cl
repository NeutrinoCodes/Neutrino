/// @file

__kernel void thekernel (
                          __global float4*    voxel_point,                      // Voxel point coordinates.
                          __global float4*    voxel_color,                      // Voxel color coordinates.
                          __global float*     time                              // Time [s].
                        )
{
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// INDEXES ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  unsigned int gid = get_global_id(0);                                          // Global index "0".

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// NODES ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  float4      P;                                                                // Voxel point coordinates.
  float4      C;                                                                // Voxel color coordinates.
  float       t;                                                                // Time [s].

  P = voxel_point[gid];                                                         // Getting voxel point...
  C = voxel_color[gid];                                                         // Getting voxel color...

  t = time[gid];

  P.z = 0.1f*sin(10.0f*P.x - 0.1f*t) + 0.1f*cos(10.0f*P.y - 0.1f*t);            // Computing "z" point coordinate...
  t += 0.1;

  voxel_point[gid] = P;                                                         // Setting voxel point...
  voxel_color[gid] = C;                                                         // Setting voxel color...

  time[gid] = t;
}
