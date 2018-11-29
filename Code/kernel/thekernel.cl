/// @file

__kernel void thekernel (
                          __global float4*    P,
                          __global float4*    C
                        )
{
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// INDEXES ///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    unsigned int gid = get_global_id(0);                                        // Setting global index "gid"...

    //c[gid] = a[gid] + b[gid];
    //barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// NODES ////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    //float4      P   = Positions[gid];                                           // Nodes positions.
    //float4      C   = Colors[gid];                                              // Nodes colors.

    //barrier(CLK_GLOBAL_MEM_FENCE);
    //P = float4(1.0f, 0.0f, 0.0f, 1.0f);
    //C = float4(1.0f, 0.0f, 0.0f, 1.0f);
    //barrier(CLK_GLOBAL_MEM_FENCE);

    //Positions[gid] = P;
    //Colors[gid] = C;

    //barrier(CLK_GLOBAL_MEM_FENCE);
}
