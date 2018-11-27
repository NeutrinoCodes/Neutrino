/// @file

__kernel void thekernel (
                          __global float4*    Positions,
                          __global float4*    Colors
                        )
{
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// INDEXES ///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    unsigned int gid = get_global_id(0);                                        // Setting global index "gid"...

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// NODES ////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      P   = Positions[gid];                                           // Nodes positions.
    float4      C   = Colors[gid];                                              // Nodes colors.

    barrier(CLK_GLOBAL_MEM_FENCE);
    P = float4(0.1f, 0.0f, 0.0f, 1.0f);
    C = float4(1.0f, 0.0f, 0.0f, 1.0f);

    Positions[gid] = P;
    Colors[gid] = C;

    barrier(CLK_GLOBAL_MEM_FENCE);
}
