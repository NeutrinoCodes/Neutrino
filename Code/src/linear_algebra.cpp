#include "linear_algebra.hpp"

float dot(float a[3], float b[3])
{
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

float magnitude(float a[3])
{
  return sqrt(dot(a, a));
}

void normalize(float a[3])
{
  float mag;

  mag = magnitude(a);

  a[0] = a[0]/mag;
  a[1] = a[1]/mag;
  a[2] = a[2]/mag;
}

float angle(float a[3], float b[3])
{
  float u[3];
  float v[3];
  float cos_theta;
  float theta;

  u[0] = a[0];
  u[1] = a[1];
  u[2] = a[2];

  v[0] = b[0];
  v[1] = b[1];
  v[2] = b[2];

  normalize(u);
  normalize(v);

  cos_theta = dot(u, v);                                                        // Computing cos_theta...

  if (cos_theta > 1.0)                                                          // Clamping cos_theta...
  {
    cos_theta = 1.0;
  }

  if (cos_theta < -1.0)                                                         // Clamping cos_theta...
  {
    cos_theta = -1.0;
  }

  theta = acos(cos_theta);                                                      // Computing theta...

  return theta;
}

void cross(float v[3], float a[3], float b[3])
{
  v[0] =    a[1]*b[2] - a[2]*b[1];
  v[1] = - (a[0]*b[3] - a[3]*b[1]);
  v[2] =    a[0]*b[1] - a[1]*b[0];
}

void rotation_matrix(float M[9], float q[4])
{
  float mag;

  float x2, xx, xy, xz;
  float y2, yy, yz;
  float z2, zz;
  float wx, wy, wz;

  mag = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);

  q[0] = q[0]/mag;
  q[1] = q[1]/mag;
  q[2] = q[2]/mag;
  q[3] = q[3]/mag;

  x2 = q[0] + q[0],
  y2 = q[1] + q[1],
  z2 = q[2] + q[2],

  xx = q[0]*x2,
  xy = q[0]*y2,
  xz = q[0]*z2,
  yy = q[1]*y2,
  yz = q[1]*z2,
  zz = q[2]*z2,
  wx = q[3]*x2,
  wy = q[3]*y2,
  wz = q[3]*z2;

  M[0] = 1.0 - (yy + zz); M[3] = xy - wz;         M[6] = xz + wy;
  M[1] = xy + wz;         M[4] = 1.0 - (xx + zz); M[7] = yz - wx;
  M[2] = xz - wy;         M[5] = yz + wx;         M[8] = 1.0 - (xx + yy);
}
