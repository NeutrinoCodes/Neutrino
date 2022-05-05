/// @file     linear_algebra.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declarations of various linear algebra functions.
///
/// @details  Various functions regarding 3D vectors and quaternions.

#ifndef linear_algebra_hpp
#define linear_algebra_hpp

#include "neutrino.hpp"

/// @brief **Dot product of two 3D vectors.**
/// @details Returns the dot product between the two 3D input vectors:
/// @f$ a \cdot b = \sqrt{a_x b_x + a_y b_y + a_z b_z} @f$
float dot (
           float a[3],                                                                              ///< 3D vector.
           float b[3]                                                                               ///< 3D vector.
          );

/// @brief **Magnitude of a 3D vector.**
/// @details Returns the magnitude of the 3D input vector:
/// @f$ |a| = a \cdot a @f$
float magnitude (
                 float a[3]                                                                         ///< 3D vector.
                );

/// @brief **Normalization of a 3D vector.**
/// @details Normalises the 3D input vector:
/// @f$ a \rightarrow \frac{a}{|a|} @f$. In case @f$ |a| = 0 @f$ the function makes
/// @f$ a \rightarrow (0, 0, 0) @f$. This avoids a **nan** and still makes this particular case
/// recognizable by the user.
void  normalize (
                 float a[3]                                                                         ///< 3D vector.
                );

/// @brief **Angle between two 3D vectors.**
/// @details Returns the angle [rad] between the two 3D input vectors:
/// @f$ \theta = \arccos{(a \cdot b)} @f$
float angle (
             float a[3],                                                                            ///< 3D vector.
             float b[3]                                                                             ///< 3D vector.
            );

/// @brief **Cross product between two 3D vectors.**
/// @details Returns the cross product between the two 3D input vectors:
/// @f$ v = \begin{vmatrix} i & j & k \\ a_x & a_y & a_z \\ b_x & b_y & b_z \end{vmatrix} @f$
void  cross (
             float v[3],                                                                            ///< 3D cross product vector.
             float a[3],                                                                            ///< 3D vector.
             float b[3]                                                                             ///< 3D vector.
            );

/// @brief **Conversion from 3D axis and rotation angle to rotation quaternion.**
/// @details Builds up the quaternion representing a rotation axis and a rotation angle around
/// that axis: @f$ q = \begin{pmatrix} \sin{(\frac{\theta}{2})}a_x \\
///                                    \sin{(\frac{\theta}{2})}a_y \\
///                                    \sin{(\frac{\theta}{2})}a_z \\
///                                    \cos{(\frac{\theta}{2})} \end{pmatrix} @f$
void quaternion (
                 float q[4],                                                                        ///< Rotation quaternion.
                 float axis[3],                                                                     ///< 3D rotation axis vector.
                 float theta                                                                        ///< Rotation angle [rad].
                );

/// @brief **Associated 3x3 matrix representing the quaternion rotation.**
/// @details Computes the [quaternion-derived rotation matrix]
/// (https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation), which is the
/// [Euler-Rodrigues rotation matrix]
/// (https://en.wikipedia.org/wiki/Euler%E2%80%93Rodrigues_formula), from the rotation quaternion:
/// @f$ q = \begin{pmatrix} q_0 \\ q_1 \\ q_2 \\ q_3 \end{pmatrix} \rightarrow
///     M = \begin{pmatrix} 1 - 2s(q_0^2 + q_2^2) & 2s(q_0 q_1 - q_2 q_3) & 2s(q_0 q_2 + q_1 q_3) \\
///                         2s(q_0 q_1 + q_2 q_3) & 1 - 2s(q_0^2 + q_2^2) & 2s(q_1 q_2 - q_0 q_3) \\
///                         2s(q_0 q_2 - q_1 q_3) & 2s(q_1 q_2 + q_0 q_3) & 1 - 2s(q_0^2 + q_1^2)
///         \end{pmatrix} @f$ where @f$ q_0, q_1, q_2 @f$ are the components of the vector part of
/// the quaternion, @f$ q_3 @f$ is its angular scalar part and @f$ s = |q|^{-2} @f$ .
void rotation_matrix (
                      float M[9],                                                                   ///< 3x3 rotation matrix.
                      float q[4]                                                                    ///< Rotation quaternion.
                     );

/// @brief **Conversion from rotation quaternion to Euler (Tait-Bryan) angles.**
/// @details Computes the [Euler angles from the rotation quaternion]
/// (https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles):
/// @f$ roll = \arctan{\left(\frac{2(q_4 q_1 + q_2 q_3)}{1 - 2(q_1^2 + q_2^2)}\right)} @f$,
/// @f$ pitch = \arcsin{\left(2(q_4 q_2 - q_3 q_1)\right)} @f$,
/// @f$ yaw = \arctan{\left(\frac{2(q_4 q_3 + q_1 q_2)}{1 - 2(q_2^2 + q_3^2)}\right)} @f$
void  euler (
             float* roll,                                                                           ///< Roll angle [rad].
             float* pitch,                                                                          ///< Pitch angle [rad].
             float* yaw,                                                                            ///< Yaw angle [rad].
             float  q[4]                                                                            ///< Rotation quaternion.
            );

/// @brief **Determinant of a 2x2 matrix.**
/// @details Computes the determinant of a 4x4 matrix
float det (
           float M[4]                                                                               ///< Input matrix.
          );

/// @brief **Determinant of a 3x3 matrix.**
/// @details Computes the determinant of a 4x4 matrix
float det (
           float M[9]                                                                               ///< Input matrix.
          );

/// @brief **Determinant of a 4x4 matrix.**
/// @details Computes the determinant of a 4x4 matrix
float det (
           float M[16]                                                                              ///< Input matrix.
          );

/// @brief **Transpose of a 4x4 matrix.**
/// @details Computes the transpose of a 4x4 matrix
void  transpose (
                 float M[16]                                                                        ///< Input matrix.
                );

/// @brief **Transpose of a 3x3 matrix.**
/// @details Computes the transpose of a 3x3 matrix
void  transpose (
                 float M[9]                                                                         ///< Input matrix.
                );

/// @brief **Transpose of a 2x2 matrix.**
/// @details Computes the transpose of a 2x2 matrix
void  transpose (
                 float M[4]                                                                         ///< Input matrix.
                );

/// @brief **Complementary minor of a 4x4 matrix.**
/// @details Computes the complementary minor matrix of a 4x4 matrix
void  minor (
             float m[9],                                                                            ///< Complementary minor matrix.
             float M[16],                                                                           ///< Input matrix.
             int   i,                                                                               ///< Row index.
             int   j                                                                                ///< Column index.
            );

/// @brief **Complementary minor of a 3x3 matrix.**
/// @details Computes the complementary minor matrix of a 3x3 matrix
void  minor (
             float m[4],                                                                            ///< Complementary minor matrix.
             float M[9],                                                                            ///< Input matrix.
             int   i,                                                                               ///< Row index.
             int   j                                                                                ///< Column index.
            );

/// @brief **Cofactor of a 4x4 matrix.**
/// @details Computes the cofactor of a 4x4 matrix
float cof (
           float M[16],                                                                             ///< Input matrix.
           int   i,                                                                                 ///< Row index.
           int   j                                                                                  ///< Column index.
          );

/// @brief **Cofactor of a 3x3 matrix.**
/// @details Computes the cofactor of a 3x3 matrix
float cof (
           float M[9],                                                                              ///< Input matrix.
           int   i,                                                                                 ///< Row index.
           int   j                                                                                  ///< Column index.
          );

/// @brief **Adjugate of a 4x4 matrix.**
/// @details Computes the adjugate of a 4x4 matrix
void  adj (
           float A[16],                                                                             ///< Adjugate of input matrix.
           float M[16]                                                                              ///< Input matrix.
          );

// @brief **Adjugate of a 3x3 matrix.**
/// @details Computes the adjugate of a 3x3 matrix
void  adj (
           float A[9],                                                                              ///< Adjugate of input matrix.
           float M[9]                                                                               ///< Input matrix.
          );

// @brief **Adjugate of a 2x2 matrix.**
/// @details Computes the adjugate of a 2x2 matrix
void  adj (
           float A[4],                                                                              ///< Adjugate of input matrix.
           float M[4]                                                                               ///< Input matrix.
          );

/// @brief **Inverse of a 4x4 matrix.**
/// @details Computes the inverse of a 4x4 matrix
void  inv (
           float I[16],                                                                             ///< Inverse of input matrix.
           float M[16]                                                                              ///< Input matrix.
          );

/// @brief **Inverse of a 3x3 matrix.**
/// @details Computes the inverse of a 3x3 matrix
void  inv (
           float I[9],                                                                              ///< Inverse of input matrix.
           float M[9]                                                                               ///< Input matrix.
          );

/// @brief **Inverse of a 2x2 matrix.**
/// @details Computes the inverse of a 2x2 matrix
void  inv (
           float I[4],                                                                              ///< Inverse of input matrix.
           float M[4]                                                                               ///< Input matrix.
          );

#endif
