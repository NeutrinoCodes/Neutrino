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
  a = 0.0;
  b = 0.0;
  c = 0.0;
  d = 0.0;
}

quaternion::~quaternion()
{

}

matrix::matrix()
{
  a_11 = 0.0;
  a_12 = 0.0;
  a_13 = 0.0;

  a_21 = 0.0;
  a_22 = 0.0;
  a_23 = 0.0;

  a_31 = 0.0;
  a_32 = 0.0;
  a_33 = 0.0;
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

  v.x = a.y*b.z - a.z*b.y;
  v.y = a.x*b.z - a.z*b.x;
  v.z = a.x*b.y - a.y*b.x;

  return v;
}

matrix rotation_matrix(quaternion q)
{
  float mag;

  float aa;
  float ab;
  float ac;
  float ad;

  float bb;
  float bc;
  float bd;

  float cc;
  float cd;

  matrix M;

  mag = sqrt(q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d);

  q.a /= mag;
  q.b /= mag;
  q.c /= mag;
  q.d /= mag;

  aa = q.a*q.a;
  ab = q.a*q.b;
  ac = q.a*q.c;
  ad = q.a*q.d;

  bb = q.b*q.b;
  bc = q.b*q.c;
  bd = q.b*q.d;

  cc = q.c*q.c;
  cd = q.c*q.d;

  M.a_11 = 1.0 - 2.0*(bb - cc);
  M.a_12 = 0.0 + 2.0*(ab - cd);
  M.a_13 = 0.0 + 2.0*(ac - bd);

  M.a_21 = 0.0 + 2.0*(ab - cd);
  M.a_22 = 1.0 - 2.0*(aa - cc);
  M.a_23 = 0.0 + 2.0*(bc - ad);

  M.a_31 = 0.0 + 2.0*(ac - bd);
  M.a_32 = 0.0 + 2.0*(bc - ad);
  M.a_33 = 1.0 - 2.0*(aa - bb);

  return M;
}
