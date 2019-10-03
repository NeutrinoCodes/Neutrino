/// @file

#include "linear_algebra.hpp"

float   dot
(
 float a[3],                                                                                        // 3D Vector.
 float b[3]                                                                                         // 3D Vector.
)
{
  return(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);                                                        // Returning dot product...
}

float   magnitude
(
 float a[3]                                                                                         // 3D Vector.
)
{
  return sqrt (dot (a, a));                                                                         // Returning magnitude...
}

void    normalize
(
 float a[3]                                                                                         // 3D Vector.
)
{
  float mag;                                                                                        // Magnitude.

  mag = magnitude (a);                                                                              // Getting magnitude...

  if(mag != 0.0f)                                                                                   // Normalizable vector:
  {
    a[0] /= mag;                                                                                    // Normalizing...
    a[1] /= mag;                                                                                    // Normalizing...
    a[2] /= mag;                                                                                    // Normalizing...
  }

  else // Non-normalizable vector:
  {
    a[0] = 0.0f;                                                                                    // Setting component to zero...
    a[1] = 0.0f;                                                                                    // Setting component to zero...
    a[2] = 0.0f;                                                                                    // Setting component to zero...
  }
}

float   angle
(
 float a[3],                                                                                        // 3D Vector.
 float b[3]                                                                                         // 3D Vector.
)
{
  float u[3];                                                                                       // Normalized vector.
  float v[3];                                                                                       // Normalized vector.
  float theta;                                                                                      // Angle between vectors.
  float cos_theta;                                                                                  // Cosine of angle between vectors.

  u[0]      = a[0];                                                                                 // Getting 1st vector "x" component...
  u[1]      = a[1];                                                                                 // Getting 1st vector "y" component...
  u[2]      = a[2];                                                                                 // Getting 1st vector "z" component...

  v[0]      = b[0];                                                                                 // Getting 2nd vector "x" component...
  v[1]      = b[1];                                                                                 // Getting 2nd vector "y" component...
  v[2]      = b[2];                                                                                 // Getting 2nd vector "z" component...

  normalize (u);                                                                                    // Normalizing vector...
  normalize (v);                                                                                    // Normalizing vector...

  cos_theta = dot (u, v);                                                                           // Computing cos_theta...

  // Fixing numerical approximation errors in cosine computation:
  if(cos_theta > 1.0f)                                                                              // Clamping cos_theta...
  {
    cos_theta = 1.0f;                                                                               // Setting cos_theta maximum value...
  }

  if(cos_theta < -1.0f)                                                                             // Clamping cos_theta...
  {
    cos_theta = -1.0f;                                                                              // Setting cos_theta minimum value...
  }

  theta = acos (cos_theta);                                                                         // Computing theta...

  return theta;                                                                                     // Returning cos_theta...
}

void  cross
(
 float v[3],                                                                                        // 3D cross product vector.
 float a[3],                                                                                        // 3D Vector.
 float b[3]                                                                                         // 3D Vector.
)
{
  v[0] = +(a[1]*b[2] - a[2]*b[1]);                                                                  // Computing cross product...
  v[1] = -(a[0]*b[2] - a[2]*b[0]);                                                                  // Computing cross product...
  v[2] = +(a[0]*b[1] - a[1]*b[0]);                                                                  // Computing cross product...
}

void  quaternion
(
 float q[4],                                                                                        // Rotation quaternion.
 float axis[3],                                                                                     // 3D rotation axis vector.
 float theta                                                                                        // Rotation angle [rad].
)
{
  float cos_theta_half;                                                                             // cos(theta/2).
  float sin_theta_half;                                                                             // sin(theta/2).

  cos_theta_half = cos (theta/2.0f);                                                                // Computing cos(theta/2)...
  sin_theta_half = sin (theta/2.0f);                                                                // Computing sin(theta/2)...

  //normalize(axis);                                                              // Normalizing rotation axis...

  q[0]           = axis[0]*sin_theta_half;                                                          // Computing rotation quaternion...
  q[1]           = axis[1]*sin_theta_half;                                                          // Computing rotation quaternion...
  q[2]           = axis[2]*sin_theta_half;                                                          // Computing rotation quaternion...
  q[3]           = cos_theta_half;                                                                  // Computing rotation quaternion...
}

void  rotation_matrix
(
 float M[9],                                                                                        // 3x3 rotation matrix.
 float q[4]                                                                                         // Rotation quaternion.
)
{
  float mag;                                                                                        // Quaternion magnitude.

  float x2, xx, xy, xz;                                                                             // Matrix "x*" terms.
  float y2, yy, yz;                                                                                 // Matrix "y*" terms.
  float z2, zz;                                                                                     // Matrix "z*" terms.
  float wx, wy, wz;                                                                                 // Matrix "w*" terms.

  mag   = sqrt (q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);                                     // Computing quaternion's magnitude...

  q[0] /= mag;                                                                                      // Normalizing quaternion...
  q[1] /= mag;                                                                                      // Normalizing quaternion...
  q[2] /= mag;                                                                                      // Normalizing quaternion...
  q[3] /= mag;                                                                                      // Normalizing quaternion...

  x2    = q[0] + q[0];                                                                              // Computing matrix term...
  y2    = q[1] + q[1];                                                                              // Computing matrix term...
  z2    = q[2] + q[2];                                                                              // Computing matrix term...

  xx    = q[0]*x2;                                                                                  // Computing matrix term...
  xy    = q[0]*y2;                                                                                  // Computing matrix term...
  xz    = q[0]*z2;                                                                                  // Computing matrix term...
  yy    = q[1]*y2;                                                                                  // Computing matrix term...
  yz    = q[1]*z2;                                                                                  // Computing matrix term...
  zz    = q[2]*z2;                                                                                  // Computing matrix term...
  wx    = q[3]*x2;                                                                                  // Computing matrix term...
  wy    = q[3]*y2;                                                                                  // Computing matrix term...
  wz    = q[3]*z2;                                                                                  // Computing matrix term...

  M[0]  = 1.0f - (yy + zz); M[3] = 0.0f + (xy - wz); M[6] = 0.0f + (xz + wy);                       // Computing rotation matrix...
  M[1]  = 0.0f + (xy + wz); M[4] = 1.0f - (xx + zz); M[7] = 0.0f + (yz - wx);                       // Computing rotation matrix...
  M[2]  = 0.0f + (xz - wy); M[5] = 0.0f + (yz + wx); M[8] = 1.0f - (xx + yy);                       // Computing rotation matrix...
}

void  euler
(
 float* roll,                                                                                       // Roll angle [rad].
 float* pitch,                                                                                      // Pitch angle [rad].
 float* yaw,                                                                                        // Yaw angle [rad].
 float  q[4]                                                                                        // Rotation quaternion.
)
{
  float sinr_cosp = +0.0f + 2.0f*(q[3]*q[0] + q[1]*q[2]);
  float cosr_cosp = +1.0f - 2.0f*(q[0]*q[0] + q[1]*q[1]);
  float siny_cosp = +0.0f + 2.0f*(q[3]*q[2] + q[0]*q[1]);
  float cosy_cosp = +1.0f - 2.0f*(q[1]*q[1] + q[2]*q[2]);
  float sinp      = +0.0f + 2.0f*(q[3]*q[1] - q[2]*q[0]);

  // Roll (x-axis rotation):
  *roll = atan2 (sinr_cosp, cosr_cosp);

  // Pitch (y-axis rotation):
  if(fabs (sinp) >= 1.0f)
  {
    *pitch = copysign ((float)M_PI/2.0f, sinp);                                                     // Using PI/2 if out of range...
  }

  else
  {
    *pitch = asin (sinp);
  }

  // Yaw (z-axis rotation):
  *yaw = atan2 (siny_cosp, cosy_cosp);
}
