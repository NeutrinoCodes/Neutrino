/// @file

#ifndef linear_algebra_hpp
#define linear_algebra_hpp

#include "neutrino.hpp"

  // Dot product of two 3D vectors:
  float   dot             (
                            float a[3],                                         // 3D vector.
                            float b[3]                                          // 3D vector.
                          );

  // Magnitude of a 3D vector:
  float   magnitude       (
                            float a[3]                                          // 3D vector.
                          );

  // Normalization of a 3D vector:
  void    normalize       (
                            float a[3]                                          // 3D vector.
                          );

  // Angle between two 3D vectors:
  float   angle           (
                            float a[3],                                         // 3D vector.
                            float b[3]                                          // 3D vector.
                          );

  // Cross product between two 3D vectors:
  void    cross           (
                            float v[3],                                         // 3D cross product vector.
                            float a[3],                                         // 3D vector.
                            float b[3]                                          // 3D vector.
                          );

  // Associated 3x3 matrix representing the quaternion rotation:
  void    rotation_matrix (
                            float M[9],                                         // 3x3 rotation matrix.
                            float q[4]                                          // Rotation quaternion.
                          );

#endif
