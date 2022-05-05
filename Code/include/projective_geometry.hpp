/// @file     projective_geometry.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of various projective geometry functions.
/// @details  Various functions related to projective geometry.

#ifndef projective_geometry_hpp
#define projective_geometry_hpp

  #include "neutrino.hpp"
  #include "linear_algebra.hpp"

/// @brief **Backup of a 4x4 matrix.**
/// @details Copies an old matrix into a new matrix.
void backup (
             float M[16],                                                                           ///< New matrix: takes values from old matrix.
             float M_old[16]                                                                        ///< Old matrix.
            );

/// @brief **4x4 matrix mutiplication.**
/// @details Multiplies two matrices:
/// @f$ C = A \cdot B @f$
void multiplicate (
                   float C[16],                                                                     ///< 4x4 matrix result.
                   float A[16],                                                                     ///< 4x4 matrix.
                   float B[16]                                                                      ///< 4x4 matrix.
                  );

/// @brief **Translation matrix.***
/// @details Translates an old matrix into a new matrix by a given translation vector:
/// @f$ T = T_{old} \cdot \begin{pmatrix} 1 & 0 & 0 & t_x \\
///                                       0 & 1 & 0 & t_y \\
///                                       0 & 0 & 1 & t_z \\
///                                       0 & 0 & 0 & 1 \end{pmatrix} @f$
///
/// See [translation](https://en.wikipedia.org/wiki/Translation_(geometry)).
void translate (
                float T[16],                                                                        ///< 4x4 translation matrix.
                float T_old[16],                                                                    ///< 4x4 translation matrix backup.
                float t[3]                                                                          ///< 3D translation vector.
               );

/// @brief **Rotation matrix.**
/// @details Rotates an old matrix into a new one by a given rotation quaternion:
/// @f$ R = R_{old} \cdot
/// \begin{pmatrix}
/// 1 - 2s(q_0^2 + q_2^2) & 2s(q_0 q_1 - q_2 q_3) & 2s(q_0 q_2 + q_1 q_3) & 0 \\
/// 2s(q_0 q_1 + q_2 q_3) & 1 - 2s(q_0^2 + q_2^2) & 2s(q_1 q_2 - q_0 q_3) & 0 \\
/// 2s(q_0 q_2 - q_1 q_3) & 2s(q_1 q_2 + q_0 q_3) & 1 - 2s(q_0^2 + q_1^2) & 0 \\
/// 0                     & 0                     & 0                     & 1
/// \end{pmatrix} @f$ where @f$ q_0, q_1, q_2 @f$ are the components of the vector part of
/// the quaternion, @f$ q_3 @f$ is its angular scalar part and @f$ s = |q|^{-2} @f$ .
/// See [quaternion-derived rotation matrix]
/// (https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation), which is the
/// [Euler-Rodrigues rotation matrix]
/// (https://en.wikipedia.org/wiki/Euler%E2%80%93Rodrigues_formula).
void rotate (
             float R[16],                                                                           ///< 4x4 rotation matrix.
             float R_old[16],                                                                       ///< 4x4 rotation matrix backup.
             float q[4]                                                                             ///< Rotation quaternion.
            );

/// @brief **Frustum matrix.**
/// @details Computes the [projective frustum matrix]
/// (https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix)
/// from a given projective frustum described by the left (@f$ l @f$), right (@f$ r @f$),
/// bottom (@f$ b @f$) and top (@f$ t @f$) projective screen coordinates,
/// by its depth location (@f$ z_{near} @f$) and by the location
/// of its corresponding far frustum plane (@f$ z_{far} @f$):
/// @f$ F = \begin{pmatrix}
/// 2 \frac{z_{near}}{r - l}  & 0                         & \frac{r + l}{r - l} & 0 \\
/// 0                         & 2 \frac{z_{near}}{t - b}  & \frac{t + b}{t - b} & 0 \\
/// 0                         & 0                         & -\frac{z_{far} + z_{near}}{z_{far} - z_{near}} & -2 \frac {z_{far} z_{near}}{z_{far} - z_{near}} \\
/// 0 & 0 & -1 & 0
/// \end{pmatrix} @f$
void frustum (
              float F[16],                                                                          ///< 4x4 frustum matrix.
              float left,                                                                           ///< Projective screen left side...
              float right,                                                                          ///< Projective screen right side...
              float bottom,                                                                         ///< Projective screen bottom side...
              float top,                                                                            ///< Projective screen top side...
              float z_near,                                                                         ///< Projective screen near depth...
              float z_far                                                                           ///< Projective screen far depth...
             );

/// @brief **Monographic perspective matrix.**
/// @details Computes the projection matrix for a monographic display from a a given
/// [field of view](https://en.wikipedia.org/wiki/Field_of_view_in_video_games),
/// [aspect ratio](https://en.wikipedia.org/wiki/Aspect_ratio_(image)), projective screen location
/// (@f$ z_{near} @f$) and far frustum plane (@f$ z_{far} @f$).
void perspective_mono (
                       float P[16],                                                                 ///< 4x4 perspective matrix.
                       float fov,                                                                   ///< Field of view [rad].
                       float aspect_ratio,                                                          ///< Projective screen aspect ratio.
                       float z_near,                                                                ///< Projective screen near depth...
                       float z_far                                                                  ///< Projective screen far depth...
                      );

/// @brief **Stereographic perspective and translation matrices.**
/// @details Computes the left-eye and right-eye projection matrices and the corresponding
/// left-eye and right-eye translation matrices for a stereographic display from a given
/// [intraocular distace](https://en.wikipedia.org/wiki/Pupillary_distance),
/// [field of view](https://en.wikipedia.org/wiki/Field_of_view_in_video_games),
/// [aspect ratio](https://en.wikipedia.org/wiki/Aspect_ratio_(image)), projective screen location
/// (@f$ z_{near} @f$) and far frustum plane (@f$ z_{far} @f$).
/// The two translation matrices are used by Neutrino in order to split the screen into two parts
/// (left and right) for the rendition of the corresponding left-eye and right-eye perspective views.
void perspective_stereo (
                         float PL[16],                                                              ///< 4x4 right eye perspective matrix.
                         float PR[16],                                                              ///< 4x4 left eye perspective matrix.
                         float TL[16],                                                              ///< 4x4 right eye translation matrix.
                         float TR[16],                                                              ///< 4x4 left eye translation matrix.
                         float iod,                                                                 ///< Intraocular distance.
                         float fov,                                                                 ///< Field of view [rad].
                         float aspect_ratio,                                                        ///< Projective screen aspect ratio.
                         float z_near,                                                              ///< Projective screen near depth...
                         float z_far                                                                ///< Projective screen far depth...
                        );

#endif
