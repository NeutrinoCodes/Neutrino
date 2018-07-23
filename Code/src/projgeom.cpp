#include "projgeom.hpp"

void frustum(float* frustum_matrix, float left, float right, float bottom,
             float top, float z_near, float z_far)
{
  frustum_matrix[0] = (2.0*z_near)/(right - left);
  frustum_matrix[1] = 0.0;
  frustum_matrix[2] = 0.0;
  frustum_matrix[3] = 0.0;
  frustum_matrix[4] = 0.0;
  frustum_matrix[5] = (2.0*z_near)/(top - bottom);
  frustum_matrix[6] = 0.0;
  frustum_matrix[7] = 0.0;
  frustum_matrix[8] = (right + left)/(right - left);
  frustum_matrix[9] = (top + bottom)/(top - bottom);
  frustum_matrix[10] = (-z_far - z_near) /(z_far - z_near);
  frustum_matrix[11] = -1.0;
  frustum_matrix[12] = 0.0;
  frustum_matrix[13] = 0.0;
  frustum_matrix[14] = (-(2.0*z_near)*z_far)/(z_far - z_near);
  frustum_matrix[15] = 0.0;
}

void perspective(float* perspective_matrix, float fov, float aspect_ratio,
                    float z_near, float z_far)
{
    float x_max;
    float y_max;
    float x_min;
    float y_min;

    y_max = z_near * tanf(fov * M_PI / 360.0);
    x_max = y_max * aspect_ratio;
    y_min = -y_max;
    x_min = -x_max;

    frustum(perspective_matrix, x_min, x_max, y_min, y_max, z_near, z_far);
}

void rotate_view(float* rotation_matrix, vector axis, float theta)
{
  quaternion q;
  matrix M;
  float* rotation;

  axis = normalize(axis);

  q.a = cos(theta/2.0);
  q.b = axis.x*sin(theta/2.0);
  q.c = axis.y*sin(theta/2.0);
  q.d = axis.z*sin(theta/2.0);

  M = rotate(q);

  rotation[0]  = M.a_11;
  rotation[1]  = M.a_21;
  rotation[2]  = M.a_31;
  rotation[3]  = 0.0;

  rotation[4]  = M.a_12;
  rotation[5]  = M.a_22;
  rotation[6]  = M.a_32;
  rotation[7]  = 0.0;

  rotation[8]  = M.a_13;
  rotation[9]  = M.a_23;
  rotation[10] = M.a_33;
  rotation[11] = 0.0;

  rotation[12] = 0.0;
  rotation[13] = 0.0;
  rotation[14] = 0.0;
  rotation[15] = 1.0;

  rotation_matrix = rotation_matrix*rotation;    // to be implemented, column major!
}

void projective_multiplication(float* M, float* A, float* B)
{
  int i;
  int j;
  int k;

  // Column major multiplication: to be integrated with rotate_view function...
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      M[4*j + i] = 0;

      for (k = 0; k < 4; k++)
      {
        M[4*j + i] += A[4*k + i]*B[4*j + k];
      }
    }
  }

}
