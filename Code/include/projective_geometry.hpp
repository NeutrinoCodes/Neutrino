/// @file

#ifndef projective_geometry_hpp
#define projective_geometry_hpp

  #include "neutrino.hpp"
  #include "linear_algebra.hpp"

  // Perspective frustum computation:
  void frustum          (
                          float F[16],                                          // 4x4 frustum matrix.
                          float left,                                           // Projective screen left side...
                          float right,                                          // Projective screen right side...
                          float bottom,                                         // Projective screen bottom side...
                          float top,                                            // Projective screen top side...
                          float z_near,                                         // Projective screen near depth...
                          float z_far                                           // Projective screen far depth...
                        );

  // Perspective matrix computation:
  void perspective      (
                          float P[16],                                          // 4x4 perspective matrix.
                          float fov,                                            // Field of view [rad].
                          float aspect_ratio,                                   // Projective screen aspect ratio.
                          float z_near,                                         // Projective screen near depth...
                          float z_far                                           // Projective screen far depth...
                        );

  // Rotation matrix computation:
  void rotate           (
                          float R[16],                                          // 4x4 rotation matrix.
                          float R_old[16],                                      // 4x4 rotation matrix backup.
                          float q[4]                                            // Rotation quaternion.
                        );

  // Translation matrix computation:
  void translate        (
                          float T[16],                                          // 4x4 translation matrix.
                          float translation[3]                                  // 3D translation vector.
                        );

  // Multiplication matrix computation:
  void multiplicate     (
                          float C[16],                                          // 4x4 matrix result.
                          float A[16],                                          // 4x4 matrix.
                          float B[16]                                           // 4x4 matrix.
                        );

#endif
