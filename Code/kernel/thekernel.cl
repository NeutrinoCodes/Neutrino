/// @file

#define l(A)            length(A)                                               // Length function.

__kernel void thekernel(__global float4*    Positions,
                        __global float4*    Colors,
                        __global float4*    Positions_old,
                        __global float4*    Velocities,
                        __global float4*    Accelerations,
                        __global float4*    Gravity,
                        __global float4*    Stiffnesses,
                        __global float4*    Resting,
                        __global float4*    Frictions,
                        __global float4*    Masses,
                        __global int*       indexes_PC,
                        __global int*       indexes_PR,
                        __global int*       indexes_PU,
                        __global int*       indexes_PL,
                        __global int*       indexes_PD)
{
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// INDEXES ///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    unsigned int gid = get_global_id(0);                                        // Setting global index "gid"...
    int iPC = indexes_PC[gid];                                                  // Setting centre particle index "iPC"...
    int iPR = indexes_PR[gid];                                                  // Setting neighbour index "iPR"...
    int iPU = indexes_PU[gid];                                                  // Setting neighbour index "iPU"...
    int iPL = indexes_PL[gid];                                                  // Setting neighbour index "iPL"...
    int iPD = indexes_PD[gid];                                                  // Setting neighbour index "iPD"...

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// CENTRE PARTICLES /////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      Po  = Positions_old[iPC];                                       // Old centre particle positions.
    float4      P   = Positions[iPC];                                           // Centre particle positions.
    float4      V   = Velocities[iPC];                                          // Centre particle velocities.
    float4      A   = Accelerations[iPC];                                       // Centre particle accelerations.
    float4      M   = Masses[iPC];                                              // Centre particle masses.
    float4      G   = Gravity[iPC];                                             // Centre particle gravity field.
    float4      C   = Frictions[iPC];                                           // Centre particle frictions.

    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////// NEIGHBOUR PARTICLES POSITIONS /////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      PR  = Positions[iPR];                                           // "RIGHT" neighbour particle positions.
    float4      PU  = Positions[iPU];                                           // "UP"    neighbour particle positions.
    float4      PL  = Positions[iPL];                                           // "LEFT"  neighbour particle positions.
    float4      PD  = Positions[iPD];                                           // "DOWN"  neighbour particle positions.

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////// NEIGHBOUR LINK RESTING DISTANCES /////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      rR  = Resting[iPR];                                             // "RIGHT" link resting distances.
    float4      rU  = Resting[iPU];                                             // "UP"    link resting distances.
    float4      rL  = Resting[iPL];                                             // "LEFT"  link resting distances.
    float4      rD  = Resting[iPD];                                             // "DOWN"  link resting distances.

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////// NEIGHBOUR LINK STIFFNESSES ///////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      kR = Stiffnesses[iPR];                                          // "RIGHT" link stiffnesses.
    float4      kU = Stiffnesses[iPU];                                          // "UP"    link stiffnesses.
    float4      kL = Stiffnesses[iPL];                                          // "LEFT"  link stiffnesses.
    float4      kD = Stiffnesses[iPD];                                          // "DOWN"  link stiffnesses.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////// NEIGHBOUR LINK DISPLACEMENTS //////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      DR  = PR - P;                                                   // "RIGHT" link displacements.
    float4      DU  = PU - P;                                                   // "UP"    link displacements.
    float4      DL  = PL - P;                                                   // "LEFT"  link displacements.
    float4      DD  = PD - P;                                                   // "DOWN"  link displacements.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// NEIGHBOUR LINK LENGTHS /////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      lR  = l(DR);                                                    // "RIGHT" link lengths.
    float4      lU  = l(DU);                                                    // "UP"    link lengths.
    float4      lL  = l(DL);                                                    // "LEFT"  link lengths.
    float4      lD  = l(DD);                                                    // "DOWN"  link lengths.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// NEIGHBOUR LINK STRAINS /////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      sR  = (lR - rR)/lR;                                             // "RIGHT" link strains.
    float4      sU  = (lU - rU)/lU;                                             // "UP"    link strains.
    float4      sL  = (lL - rL)/lL;                                             // "LEFT"  link strains.
    float4      sD  = (lD - rD)/lD;                                             // "DOWN"  link strains.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ////////////////////// NEIGHBOUR LINK RELATIVE DISPLACEMENTS /////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      UR  = sR*DR;                                                    // "RIGHT" link relative displacements.
    float4      UU  = sU*DU;                                                    // "UP"    link relative displacements.
    float4      UL  = sL*DL;                                                    // "LEFT"  link relative displacements.
    float4      UD  = sD*DD;                                                    // "DOWN"  link relative displacements.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////// CENTRE PARTICLE ELASTIC FORCES /////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      Fe  = kR*UR + kU*UU + kL*UL + kD*UD;                            // Elastic force applied to the centre particles.
    //float4      mag_Fe = fabs(Fe);                                              // Magnitude of Fe.
    float4      col = Colors[iPC];
    col = (float4)(1.0f, 0.0f, 0.0f, 1.0f);

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////// CENTRE PARTICLE VISCOUS FORCES /////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      Fv  = -C*V;                                                     // Viscous force applied to the centre particles.

    //////////////////////////////////////////////////////////////////////////////
    ////////////////////// CENTRE PARTICLE GRAVITATIONAL FORCES //////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      Fg  = M*G;                                                      // Gravitational force applied to the centre particles.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    ///////////////////////// CENTRE PARTICLE TOTAL FORCES ///////////////////////
    //////////////////////////////////////////////////////////////////////////////
    float4      Ft  = Fe + Fv + Fg;                                             // Total force applied to the centre particles.

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// VERLET INTEGRATION ///////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    V = (P - Po);                                                               // Calculating current velocities...
    A = Ft/M;                                                                   // Calculating current accelerations...
    Po = P;                                                                     // Updating old positions...

    barrier(CLK_GLOBAL_MEM_FENCE);

    P = P + V + A*0.005f*0.005f;                                                // Calculating and updating new positions...

    barrier(CLK_GLOBAL_MEM_FENCE);

    Positions_old[iPC] = Po;                                                    // Updating OpenCL array...
    Positions[iPC] = P;                                                         // Updating OpenCL array...
    Velocities[iPC] = V;                                                        // Updating OpenCL array...
    Accelerations[iPC] = A;                                                     // Updating OpenCL array...

    barrier(CLK_GLOBAL_MEM_FENCE);

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// 4th component set ////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    Positions[iPC].w = 1.0;                                                     // Resetting w (for 3D distance computation)...
    Positions_old[iPC].w = 1.0;                                                 // Resetting w (for 3D distance computation)...
    Velocities[iPC].w = 1.0;                                                    // Resetting w (for 3D distance computation)...
    Accelerations[iPC].w = 1.0;                                                 // Resetting w (for 3D distance computation)...

    Colors[iPC] = col;

    barrier(CLK_GLOBAL_MEM_FENCE);
}
