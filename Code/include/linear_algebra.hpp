/// @file   linear_algebra.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declarations of an various linear algebra functions.

#ifndef linear_algebra_hpp
#define linear_algebra_hpp

#include "neutrino.hpp"

/// @brief **Dot product of two 3D vectors.**
/// @details Returns the dot product between the two 3D input vectors:
/// @f$ a \cdot b = \sqrt{a_x b_x + a_y b_y + a_z b_z} @f$
float dot (
           float a[3],                                                                              // 3D vector.
           float b[3]                                                                               // 3D vector.
          );

/// @brief **Magnitude of a 3D vector.**
/// @details Returns the magnitude of the 3D input vector:
/// @f$ |a| = a \cdot a @f$
float magnitude (
                 float a[3]                                                                         // 3D vector.
                );

/// @brief **Normalization of a 3D vector.**
/// @details Normalises the 3D input vector:
/// @f$ a \rightarrow \frac{a}{|a|} @f$. In case @f$ |a| = 0 @f$ the function makes
/// @f$ a \rightarrow (0, 0, 0) @f$. This avoids a **nan** and still makes this particular case
/// recognizable by the user.
void  normalize (
                 float a[3]                                                                         // 3D vector.
                );

/// @brief **Angle between two 3D vectors.**
/// @details Returns the angle [rad] between the two 3D input vectors:
/// @f$ \theta = \arccos{(a \cdot b)} @f$
float angle (
             float a[3],                                                                            // 3D vector.
             float b[3]                                                                             // 3D vector.
            );

/// @brief **Cross product between two 3D vectors.**
/// @details Returns the cross product between the two 3D input vectors:
/// @f$ v = \begin{vmatrix} i & j & k \\ a_x & a_y & a_z \\ b_x & b_y & b_z \end{vmatrix} @f$
void  cross (
             float v[3],                                                                            // 3D cross product vector.
             float a[3],                                                                            // 3D vector.
             float b[3]                                                                             // 3D vector.
            );

/// @brief **Conversion from 3D axis and rotation angle to rotation quaternion.**
/// @details Builds up the quaternion representing a rotation axis and a rotation angle around
/// that axis: @f$ q = \begin{pmatrix} \sin{(\frac{\theta}{2})}a_x \\
///                                    \sin{(\frac{\theta}{2})}a_y \\
///                                    \sin{(\frac{\theta}{2})}a_z \\
///                                    \cos{(\frac{\theta}{2})} \end{pmatrix} @f$
void quaternion (
                 float q[4],                                                                        // Rotation quaternion.
                 float axis[3],                                                                     // 3D rotation axis vector.
                 float theta                                                                        // Rotation angle [rad].
                );

/// @brief **Associated 3x3 matrix representing the quaternion rotation.**
/// @details Computes the [quaternion-derived rotation matrix]
/// (https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation), which is the
/// [Euler-Rodrigues rotation matrix]
/// (https://en.wikipedia.org/wiki/Euler%E2%80%93Rodrigues_formula), from the rotation quaternion:
/// @f$ q = \begin{pmatrix} q_x \\ q_y \\ q_z \\ q_w \end{pmatrix} \rightarrow
///     M = \begin{pmatrix} 1 - 2s(q_x^2 + q_z^2) & 2s(q_x q_y - q_z q_w) & 2s(q_x q_z + q_y q_w) \\
///                         2s(q_x q_y + q_z q_w) & 1 - 2s(q_x^2 + q_z^2) & 2s(q_y q_z - q_x q_w) \\
///                         2s(q_x q_z - q_y q_w) & 2s(q_y q_z + q_x q_w) & 1 - 2s(q_x^2 + q_y^2)
///         \end{pmatrix} @f$ where @f$ q_x, q_y, q_z @f$ are the components of the vector part of
/// the quaternion and @f$ q_w @f$ is its angular scalar part and where @f$ s = .... @f$
/// EZOR: 3OCT2019 maybe the actual formula I use can be further simplified by using the
/// Euler-Rodrigues formula. To be checked.
void rotation_matrix (
                      float M[9],                                                                   // 3x3 rotation matrix.
                      float q[4]                                                                    // Rotation quaternion.
                     );

// Conversion from rotation quaternion to Euler (Tait-Bryan) angles:
void euler (
            float* roll,                                                                            // Roll angle [rad].
            float* pitch,                                                                           // Pitch angle [rad].
            float* yaw,                                                                             // Yaw angle [rad].
            float  q[4]                                                                             // Rotation quaternion.
           );

#endif
