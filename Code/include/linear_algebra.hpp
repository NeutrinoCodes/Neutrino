/// @file

#ifndef linear_algebra_hpp
#define linear_algebra_hpp

  //////////////////////////////////////////////////////////////////////////
  //////////////////////// Standard C header files /////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

  /// **Dot product of two 3D vectors:**
  float   dot(float a[3], float b[3]);

  /// **Magnitude of a 3D vector:**
  float   magnitude(float a[3]);

  /// **Normalization of a 3D vector:**
  void    normalize(float a[3]);

  /// **Angle between two 3D vectors:**
  float   angle(float a[3], float b[3]);

  /// **Cross product between two 3D vectors:***
  void    cross(float v[3], float a[3], float b[3]);

  /// **Associated 3x3 matrix representing the quaternion rotation:**
  void    rotation_matrix(float M[9], float q[4]);

#endif
