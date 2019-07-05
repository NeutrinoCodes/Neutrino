/// @file

#version 410 core

layout (location = 0) in vec4 voxel_center;                                     // Voxel center.
layout (location = 1) in vec4 voxel_color;                                      // Voxel color.

out VS_OUT
{
  vec4 voxel_color;                                                              // Output color (for fragment shader).
  vec4 vertex_A;
  vec4 vertex_B;
  vec4 vertex_C;
  vec4 vertex_D;
  vec4 vertex_E;
  vec4 vertex_F;
  vec4 vertex_G;
  vec4 vertex_H;
} vs_out;

uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  float l = 0.005;
  vec4 D = vec4(l, l, l, 1.0);

  gl_Position = Projection_matrix*View_matrix*voxel_center;                     // Setting voxel position...
  vs_out.voxel_color = vec4(1.0,1.0,1.0,1.0);                                             // Forwarding voxel color...

  ////////////////////////////////////////////////////////////////////////////////
  ////////// CUBE VERTEX BARICENTRIC COORDINATES (3D binary hypercube) ///////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.vertex_A = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, -1.0, -1.0, 1.0));
  vs_out.vertex_B = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, -1.0, +1.0, 1.0));
  vs_out.vertex_C = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, +1.0, -1.0, 1.0));
  vs_out.vertex_D = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, +1.0, +1.0, 1.0));
  vs_out.vertex_E = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, -1.0, -1.0, 1.0));
  vs_out.vertex_F = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, -1.0, +1.0, 1.0));
  vs_out.vertex_G = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, +1.0, -1.0, 1.0));
  vs_out.vertex_H = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, +1.0, +1.0, 1.0));
}
