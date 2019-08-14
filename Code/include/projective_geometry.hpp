/// @file

#ifndef projective_geometry_hpp
#define projective_geometry_hpp

  #include "neutrino.hpp"
  #include "linear_algebra.hpp"
// Copies "old" matrix into "new" matrix.
void backup (
             float M_mat[16],                                                                       // New matrix: takes values from old matrix.
             float M_mat_old[16]                                                                    // Old matrix.
            );
// Multiplication matrix computation:
void multiplicate (
                   float C_mat[16],                                                                 // 4x4 matrix result.
                   float A_mat[16],                                                                 // 4x4 matrix.
                   float B_mat[16]                                                                  // 4x4 matrix.
                  );
// Translation matrix computation:
void translate (
                float T_mat[16],                                                                    // 4x4 translation matrix.
                float T_mat_old[16],                                                                // 4x4 translation matrix backup.
                float t[3]                                                                          // 3D translation vector.
               );
// Rotation matrix computation:
void rotate (
             float R_mat[16],                                                                       // 4x4 rotation matrix.
             float R_mat_old[16],                                                                   // 4x4 rotation matrix backup.
             float q[4]                                                                             // Rotation quaternion.
            );
// Perspective frustum computation:
void frustum (
              float F_mat[16],                                                                      // 4x4 frustum matrix.
              float left,                                                                           // Projective screen left side...
              float right,                                                                          // Projective screen right side...
              float bottom,                                                                         // Projective screen bottom side...
              float top,                                                                            // Projective screen top side...
              float z_near,                                                                         // Projective screen near depth...
              float z_far                                                                           // Projective screen far depth...
             );
// Perspective matrix computation:
void perspective_mono (
                       float P_mat[16],                                                             // 4x4 perspective matrix.
                       float fov,                                                                   // Field of view [rad].
                       float aspect_ratio,                                                          // Projective screen aspect ratio.
                       float z_near,                                                                // Projective screen near depth...
                       float z_far                                                                  // Projective screen far depth...
                      );
/// # Perspective matrix function
/// ### Description:
/// Computes the perspective matrix given the projective screen boundaries.
void perspective_stereo (
                         float PL_mat[16],                                                          // 4x4 right eye perspective matrix.
                         float PR_mat[16],                                                          // 4x4 left eye perspective matrix.
                         float TL_mat[16],                                                          // 4x4 right eye translation matrix.
                         float TR_mat[16],                                                          // 4x4 left eye translation matrix.
                         float iod,                                                                 // Intraocular distance.
                         float fov,                                                                 // Field of view [rad].
                         float aspect_ratio,                                                        // Projective screen aspect ratio.
                         float z_near,                                                              // Projective screen near depth...
                         float z_far                                                                // Projective screen far depth...
                        );

#endif
