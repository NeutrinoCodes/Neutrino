/// @file   linear_algebra.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declarations of an various linear algebra functions.

#ifndef linear_algebra_hpp
#define linear_algebra_hpp

#include "neutrino.hpp"

/// @brief **Dot product of two 3D vectors.**
/// @details Returns the dot product between the two 3D input vectors:
/// \f$ \sqrt{(x_2-x_1)^2+(y_2-y_1)^2} \f$
float dot (
           float a[3],                                                                              // 3D vector.
           float b[3]                                                                               // 3D vector.
          );

// Magnitude of a 3D vector:
float magnitude (
                 float a[3]                                                                         // 3D vector.
                );

// Normalization of a 3D vector:
void  normalize (
                 float a[3]                                                                         // 3D vector.
                );

// Angle between two 3D vectors:
float angle (
             float a[3],                                                                            // 3D vector.
             float b[3]                                                                             // 3D vector.
            );

// Cross product between two 3D vectors:
void  cross (
             float v[3],                                                                            // 3D cross product vector.
             float a[3],                                                                            // 3D vector.
             float b[3]                                                                             // 3D vector.
            );

// Conversion from 3D axis and rotation angle to rotation quaternion:
void  quaternion (
                  float q[4],                                                                       // Rotation quaternion.
                  float axis[3],                                                                    // 3D rotation axis vector.
                  float theta                                                                       // Rotation angle [rad].
                 );

// Associated 3x3 matrix representing the quaternion rotation:
void  rotation_matrix (
                       float M[9],                                                                  // 3x3 rotation matrix.
                       float q[4]                                                                   // Rotation quaternion.
                      );

// Conversion from rotation quaternion to Euler (Tait-Bryan) angles:
void  euler (
             float* roll,                                                                           // Roll angle [rad].
             float* pitch,                                                                          // Pitch angle [rad].
             float* yaw,                                                                            // Yaw angle [rad].
             float  q[4]                                                                            // Rotation quaternion.
            );

#endif
