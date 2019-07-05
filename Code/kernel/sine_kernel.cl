/// @file
#include "client_datatypes.cl"

__kernel void thekernel (
                          __global point*    voxel_point,
                          __global color*    voxel_color
                        )
{
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// INDEXES ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  unsigned int gid = get_global_id(0);                                          // Setting global index "gid"...

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// NODES ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  float4      P;                                                                // Voxel point coordinates.
  float4      C;                                                                // Voxel color coordinates.

  P.x = voxel_point[gid].x;
  P.y = voxel_point[gid].y;
  P.z = voxel_point[gid].z;
  P.w = voxel_point[gid].w;

  C.x = voxel_color[gid].r;
  C.y = voxel_color[gid].g;
  C.z = voxel_color[gid].b;
  C.w = voxel_color[gid].a;

  //float4      P  = voxel_point[gid];                                            // Voxel point coordinates.
  //float4      C  = voxel_color[gid];                                            // Voxel color coordinates.

  //P.z = 0.1f*sin(10.0f*P.x) + 0.1f*cos(10.0f*P.y);
  P.z = 2*P.x;

  voxel_point[gid].x = P.x;
  voxel_point[gid].y = P.y;
  voxel_point[gid].z = P.z;
  voxel_point[gid].w = P.w;

  voxel_color[gid].r = C.x;
  voxel_color[gid].g = C.y;
  voxel_color[gid].b = C.z;
  voxel_color[gid].a = C.w;
}
