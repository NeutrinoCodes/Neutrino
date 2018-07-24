#ifndef projgeom_hpp
#define projgeom_hpp

  #include "linear_algebra.hpp"

  void frustum(float* F, float left, float right, float bottom,
                  float top, float z_near, float z_far);
  void perspective(float* P, float fov, float aspect_ratio,
                      float z_near, float z_far);
  void rotate(float* R, float* R_old, vector axis, float theta);

  void translate(float* T, vector translation);

  void multiplicate(float* C, float* A, float* B);

#endif
