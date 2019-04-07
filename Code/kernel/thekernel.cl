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

    //////////////////////////////////////////////////////////////////////////////
    ////////////////////// SYNERGIC MOLECULE: LINK INDEXES ///////////////////////
    //////////////////////////////////////////////////////////////////////////////
    // NOTE: 1. the index of a non-existing particle friend must be set to the index of the particle.
    long        i_PR = index_PR[gid];                                           // Setting indexes of 1st linked particle...
    long        i_PU = index_PU[gid];                                           // Setting indexes of 2nd linked particle...
    long        i_PL = index_PL[gid];                                           // Setting indexes of 3rd linked particle...
    long        i_PD = index_PD[gid];                                           // Setting indexes of 4th linked particle...

    ////////////////////////////////////////////////////////////////////////////////
    ///////////////// SYNERGIC MOLECULE: LINKED PARTICLE POSITIONS /////////////////
    ////////////////////////////////////////////////////////////////////////////////
    float4      pos_PR = point_PC[i_PR];                                        // 1st linked particle position.
    float4      pos_PU = point_PC[i_PU];                                        // 2nd linked particle position.
    float4      pos_PL = point_PC[i_PL];                                        // 3rd linked particle position.
    float4      pos_PD = point_PC[i_PD];                                        // 4th linked particle position.

    pos_PC.z = 0.1f*sin(10.0f*pos_PC.x) + 0.1f*cos(10.0f*pos_PC.y);
    //C = (float4)(1.0f, 0.0f, 0.0f, 1.0f);

    color_PC[gid] = col_PC;
    point_PC[gid] = pos_PC;
    point_PR[gid] = pos_PR;
    point_PU[gid] = pos_PU;
    point_PL[gid] = pos_PL;
    point_PD[gid] = pos_PD;
}
