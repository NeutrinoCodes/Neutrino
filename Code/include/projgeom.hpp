#ifndef projgeom_hpp
#define projgeom_hpp

  #include "linalg.hpp"

  void    frustum(float* frustum_matrix, float left, float right, float bottom,
                  float top, float z_near, float z_far);
  void    perspective(float* perspective_matrix, float fov, float aspect_ratio,
                      float z_near, float z_far);
  void    projective_rotation(float* rotation_matrix, vector axis, float theta);
  void    projective_accumulation(float* M1, float*M2);

#endif
