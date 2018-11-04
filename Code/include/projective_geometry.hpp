/// @file

#ifndef projective_geometry_hpp
#define projective_geometry_hpp

  //////////////////////////////////////////////////////////////////////////
  //////////////////////// Standard C header files /////////////////////////
  //////////////////////////////////////////////////////////////////////////
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

  void frustum(float F[16], float left, float right, float bottom,
                  float top, float z_near, float z_far);
  void perspective(float P[16], float fov, float aspect_ratio,
                      float z_near, float z_far);
  void rotate(float R[16], float R_old[16], float axis[3], float theta);

  void translate(float T[16], float translation[3]);

  void multiplicate(float C[16], float A[16], float B[16]);

#endif
