/// @file

__kernel void thekernel (
                          __global float4*    Positions,
                          __global float4*    Colors,
                          __global long*      Index_1,
                          __global long*      Index_2,
                          __global long*      Index_3,
                          __global long*      Index_4
                        )
{
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// INDEXES ///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    unsigned int gid = get_global_id(0);                                        // Setting global index "gid"...

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// NODES ////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      P   = Positions[gid];                                           // Nodes positions.
    float4      C   = Colors[gid];                                              // Nodes colors.

    P.z = 0.1f*sin(10.0f*P.x) + 0.1*cos(10.0f*P.y);
    //C = (float4)(1.0f, 0.0f, 0.0f, 1.0f);

    Positions[gid] = P;
    Colors[gid] = C;
}
