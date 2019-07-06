/// @file

#version 410 core

layout (location = 0) in vec4 voxel_center;                                     // Voxel center.
layout (location = 1) in vec4 voxel_color;                                      // Voxel color.

out VS_OUT
{
  vec4 voxel_color;                                                             // Output color (for fragment shader).
  vec4 vertex_A;
  vec4 vertex_B;
  vec4 vertex_C;
  vec4 vertex_D;
  vec4 vertex_E;
  vec4 vertex_F;
  vec4 vertex_G;
  vec4 vertex_H;
  vec4 normal_L;
  vec4 normal_R;
  vec4 normal_D;
  vec4 normal_U;
  vec4 normal_B;
  vec4 normal_F;
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
  vs_out.voxel_color = voxel_color;                                             // Forwarding voxel color...

  ////////////////////////////////////////////////////////////////////////////////
  ////////// CUBE VERTEX BARICENTRIC COORDINATES (3D binary hypercube) ///////////
  ////////////////////////////////////////////////////////////////////////////////
  //
  //       (-1.0, +1.0, -1.0)    C--------G  (+1.0, +1.0, -1.0)
  //                            /|       /|
  //       (-1.0, +1.0, +1.0)  D--------H |  (+1.0, +1.0, +1.0)
  //       (-1.0, -1.0, -1.0)  | A------|-E  (+1.0, -1.0, -1.0)
  //                           |/       |/
  //       (-1.0, -1.0, +1.0)  B--------F    (+1.0, -1.0, +1.0)
  //
  //         y
  //         |
  //         o -- x
  //        /
  //       z
  //
  vs_out.vertex_A = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, -1.0, -1.0, +1.0));
  vs_out.vertex_B = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, -1.0, +1.0, +1.0));
  vs_out.vertex_C = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, +1.0, -1.0, +1.0));
  vs_out.vertex_D = Projection_matrix*View_matrix*(voxel_center + D*vec4(-1.0, +1.0, +1.0, +1.0));
  vs_out.vertex_E = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, -1.0, -1.0, +1.0));
  vs_out.vertex_F = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, -1.0, +1.0, +1.0));
  vs_out.vertex_G = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, +1.0, -1.0, +1.0));
  vs_out.vertex_H = Projection_matrix*View_matrix*(voxel_center + D*vec4(+1.0, +1.0, +1.0, +1.0));

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////// CUBE FACE BARICENTRIC NORMALS ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.normal_L = Projection_matrix*View_matrix*(voxel_center + vec4(-1.0, +0.0, +0.0, +1.0)); // LEFT:  face "ABDC" normal.
  vs_out.normal_R = Projection_matrix*View_matrix*(voxel_center + vec4(+1.0, +0.0, +0.0, +1.0)); // RIGHT: face "EFHG" normal.
  vs_out.normal_D = Projection_matrix*View_matrix*(voxel_center + vec4(+0.0, +0.0, -1.0, +1.0)); // DOWN:  face "ABFE" normal.
  vs_out.normal_U = Projection_matrix*View_matrix*(voxel_center + vec4(+0.0, +0.0, +1.0, +1.0)); // UP:    face "CDHG" normal.
  vs_out.normal_B = Projection_matrix*View_matrix*(voxel_center + vec4(+0.0, +0.0, -1.0, +1.0)); // BACK:  face "AEGC" normal.
  vs_out.normal_F = Projection_matrix*View_matrix*(voxel_center + vec4(+0.0, +0.0, +1.0, +1.0)); // FRONT: face "BFHD" normal.
}
