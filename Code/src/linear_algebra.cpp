#include "linear_algebra.hpp"

vector::vector()
{
  x = 0.0;
  y = 0.0;
  z = 0.0;
}

vector::~vector()
{

}

quaternion::quaternion()
{
  x = 0.0;                                                                      // Vector component "x".
  y = 0.0;                                                                      // Vector component "y".
  z = 0.0;                                                                      // Vector component "z".
  w = 0.0;                                                                      // Scalar component "w".
}

quaternion::~quaternion()
{

}

matrix::matrix()
{
  a_11 = 0.0; a_12 = 0.0; a_13 = 0.0;
  a_21 = 0.0; a_22 = 0.0; a_23 = 0.0;
  a_31 = 0.0; a_32 = 0.0; a_33 = 0.0;
}

matrix::~matrix()
{

}

float dot(vector a, vector b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

float magnitude(vector a)
{
  return sqrt(dot(a, a));
}

vector normalize(vector a)
{
  vector  v;
  float   mag;

  mag = magnitude(a);

  v.x = a.x/mag;
  v.y = a.y/mag;
  v.z = a.z/mag;

  return v;
}

float angle(vector a, vector b)
{
  float cos_theta;
  float theta;

  cos_theta = dot(normalize(a), normalize(b));                                  // Computing cos_theta...

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

vector cross(vector a, vector b)
{
  vector v;

  v.x =    a.y*b.z - a.z*b.y;
  v.y = - (a.x*b.z - a.z*b.x);
  v.z =    a.x*b.y - a.y*b.x;

  return v;
}

matrix rotation_matrix(quaternion q)
{
  float mag;

  float x2, xx, xy, xz;
  float y2, yy, yz;
  float z2, zz;
  float wx, wy, wz;

  matrix M;

  mag = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);

  q.x /= mag;
  q.y /= mag;
  q.z /= mag;
  q.w /= mag;

  x2 = q.x + q.x,
  y2 = q.y + q.y,
  z2 = q.z + q.z,

  xx = q.x * x2,
  xy = q.x * y2,
  xz = q.x * z2,
  yy = q.y * y2,
  yz = q.y * z2,
  zz = q.z * z2,
  wx = q.w * x2,
  wy = q.w * y2,
  wz = q.w * z2;

  M.a_11 = 1.0 - (yy + zz); M.a_12 = xy + wz; M.a_13 = xz - wy;
  M.a_21 = xy - wz; M.a_22 = 1.0 - (xx + zz); M.a_23 = yz + wx;
  M.a_31 = xz + wy; M.a_32 = yz - wx; M.a_33 = 1.0 - (xx + yy);

  return M;
}
