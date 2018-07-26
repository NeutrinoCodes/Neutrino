#ifndef linear_algebra_hpp
#define linear_algebra_hpp

  #include <stdio.h>
  #include <math.h>

  float   dot(float a[3], float b[3]);
  float   magnitude(float a[3]);
  void    normalize(float a[3]);
  float   angle(float a[3], float b[3]);
  void    cross(float v[3], float a[3], float b[3]);
  void    rotation_matrix(float M[9], float q[4]);

#endif
