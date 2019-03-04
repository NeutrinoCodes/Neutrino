/// @file

#ifndef projective_geometry_hpp
#define projective_geometry_hpp

  #include "neutrino.hpp"
  #include "linear_algebra.hpp"
// Multiplication matrix computation:
void multiplicate (
                   float C[16],                                                 // 4x4 matrix result.
                   float A[16],                                                 // 4x4 matrix.
                   float B[16]                                                  // 4x4 matrix.
                  );
// Translation matrix computation:
void translate (
                float T[16],                                                    // 4x4 translation matrix.
                float T_old[16],                                                // 4x4 translation matrix backup.
                float t[3]                                                      // 3D translation vector.
               );
// Rotation matrix computation:
void rotate (
             float R[16],                                                       // 4x4 rotation matrix.
             float R_old[16],                                                   // 4x4 rotation matrix backup.
             float q[4]                                                         // Rotation quaternion.
            );
// Perspective frustum computation:
void frustum (
              float F[16],                                                      // 4x4 frustum matrix.
              float left,                                                       // Projective screen left side...
              float right,                                                      // Projective screen right side...
              float bottom,                                                     // Projective screen bottom side...
              float top,                                                        // Projective screen top side...
              float z_near,                                                     // Projective screen near depth...
              float z_far                                                       // Projective screen far depth...
             );
// Perspective matrix computation:
void perspective (
                  float P[16],                                                  // 4x4 perspective matrix.
                  float fov,                                                    // Field of view [rad].
                  float aspect_ratio,                                           // Projective screen aspect ratio.
                  float z_near,                                                 // Projective screen near depth...
                  float z_far                                                   // Projective screen far depth...
                 );
/// # Perspective matrix function
/// ### Description:
/// Computes the perspective matrix given the projective screen boundaries.
void vr_perspective (
                     float PL[16],                                              // 4x4 right eye perspective matrix.
                     float PR[16],                                              // 4x4 left eye perspective matrix.
                     float TL[16],                                              // 4x4 right eye translation matrix.
                     float TR[16],                                              // 4x4 left eye translation matrix.
                     float iod,                                                 // Intraocular distance.
                     float fov,                                                 // Field of view [rad].
                     float aspect_ratio,                                        // Projective screen aspect ratio.
                     float z_near,                                              // Projective screen near depth...
                     float z_far                                                // Projective screen far depth...
                    );

#endif
