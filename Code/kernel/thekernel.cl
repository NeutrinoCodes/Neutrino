/// @file

__kernel void thekernel (
                          __global float4*    color_PC,
                          __global float4*    point_PC,
                          __global float4*    point_PR,
                          __global float4*    point_PU,
                          __global float4*    point_PL,
                          __global float4*    point_PD,
                          __global long*      index_PR,
                          __global long*      index_PU,
                          __global long*      index_PL,
                          __global long*      index_PD
                        )
{
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// INDEXES ///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    unsigned int gid = get_global_id(0);                                        // Setting global index "gid"...

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// NODES ////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      col_PC  = color_PC[gid];                                        // Nodes colors.
    float4      pos_PC  = point_PC[gid];                                        // Nodes positions.

    pos_PC.z = 0.1f*sin(10.0f*pos_PC.x) + 0.1*cos(10.0f*pos_PC.y);
    //C = (float4)(1.0f, 0.0f, 0.0f, 1.0f);

    color_PC[gid] = col_PC;
    point_PC[gid] = pos_PC;
}
