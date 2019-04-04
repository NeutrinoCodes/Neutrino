/// @file

__kernel void thekernel (
                          __global float4*    Positions,
                          __global float4*    Colors,
                          __global float4*    Nodes,
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
    float4      N   = Nodes[gid];                                               // Nodes positions.
    float4      P   = Positions[gid];                                           // Nodes positions.
    float4      C   = Colors[gid];                                              // Nodes colors.

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////// SYNERGIC MOLECULE: LINK INDEXES /////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    // NOTE: 1. the index of a non-existing particle friend must be set to the index of the particle.
    long         il_1 = Index_1[gid];                                       // Setting indexes of 1st linked particle...
    long         il_2 = Index_2[gid];                                       // Setting indexes of 2nd linked particle...
    long         il_3 = Index_3[gid];                                       // Setting indexes of 3rd linked particle...
    long         il_4 = Index_4[gid];                                       // Setting indexes of 4th linked particle...

    ////////////////////////////////////////////////////////////////////////////////
    ///////////////// SYNERGIC MOLECULE: LINKED PARTICLE POSITIONS /////////////////
    ////////////////////////////////////////////////////////////////////////////////
    float4      Pl_1 = Positions[il_1];                                           // 1st linked particle position.
    float4      Pl_2 = Positions[il_2];                                           // 2nd linked particle position.
    float4      Pl_3 = Positions[il_3];                                           // 3rd linked particle position.
    float4      Pl_4 = Positions[il_4];                                           // 4th linked particle position.

    N.z = 0.1f*sin(10.0f*N.x) + 0.1*cos(10.0f*N.y);
    //C = (float4)(1.0f, 0.0f, 0.0f, 1.0f);
    P = N;


    Nodes[gid] = N;
    Positions[gid] = P;
    Positions[il_1] = Pl_2;
    Positions[il_2] = Pl_1;
    Positions[il_3] = Pl_3;
    Positions[il_4] = Pl_4;

    Colors[gid] = C;
}
