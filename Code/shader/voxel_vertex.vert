/// @file

#version 410 core

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////
#define A vec3(-1.0, -1.0, -1.0)
#define B vec3(-1.0, -1.0, +1.0)
#define C vec3(-1.0, +1.0, -1.0)
#define D vec3(-1.0, +1.0, +1.0)
#define E vec3(+1.0, -1.0, -1.0)
#define F vec3(+1.0, -1.0, +1.0)
#define G vec3(+1.0, +1.0, -1.0)
#define H vec3(+1.0, +1.0, +1.0)

#define nL vec3(-1.0, +0.0, +0.0)
#define nR vec3(+1.0, +0.0, +0.0)
#define nD vec3(+0.0, -1.0, +0.0)
#define nU vec3(+0.0, +1.0, +0.0)
#define nB vec3(+0.0, +0.0, -1.0)
#define nF vec3(+0.0, +0.0, +1.0)

#define s 0.008
#define l vec3(0.0, -1.0, 0.0)

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
  vec4 color_L;
  vec4 color_R;
  vec4 color_D;
  vec4 color_U;
  vec4 color_B;
  vec4 color_F;
} vs_out;

uniform mat4 V_mat;                                                             // View matrix.
uniform mat4 P_mat;                                                             // Projection matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  vec3 normal_L;
  vec3 normal_R;
  vec3 normal_D;
  vec3 normal_U;
  vec3 normal_B;
  vec3 normal_F;

  vec3 light;

  float diffusion_L;
  float diffusion_R;
  float diffusion_D;
  float diffusion_U;
  float diffusion_B;
  float diffusion_F;

  gl_Position = P_mat*V_mat*voxel_center;                                       // Setting voxel position...
  vs_out.voxel_color = voxel_color;                                             // Forwarding voxel color...
  light = -normalize(l);

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// VOXEL'S FACE BARICENTRIC NORMALS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  normal_L = vec3(P_mat*V_mat*(voxel_center + vec4(nL, +1.0)));                 // LEFT:  face "ABDC" normal.
  normal_R = vec3(P_mat*V_mat*(voxel_center + vec4(nR, +1.0)));                 // RIGHT: face "EFHG" normal.
  normal_D = vec3(P_mat*V_mat*(voxel_center + vec4(nD, +1.0)));                 // DOWN:  face "ABFE" normal.
  normal_U = vec3(P_mat*V_mat*(voxel_center + vec4(nU, +1.0)));                 // UP:    face "CDHG" normal.
  normal_B = vec3(P_mat*V_mat*(voxel_center + vec4(nB, +1.0)));                 // BACK:  face "AEGC" normal.
  normal_F = vec3(P_mat*V_mat*(voxel_center + vec4(nF, +1.0)));                 // FRONT: face "BFHD" normal.

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// VOXEL'S FACE DIFFUSION COEFFICIENTS //////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  diffusion_L = clamp(dot(light, normal_L), 0.2, 1.0);
  diffusion_R = clamp(dot(light, normal_R), 0.2, 1.0);
  diffusion_D = clamp(dot(light, normal_D), 0.2, 1.0);
  diffusion_U = clamp(dot(light, normal_U), 0.2, 1.0);
  diffusion_B = clamp(dot(light, normal_B), 0.2, 1.0);
  diffusion_F = clamp(dot(light, normal_F), 0.2, 1.0);

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////// VOXEL'S VERTEX BARICENTRIC COORDINATES /////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.vertex_A = P_mat*V_mat*(voxel_center + vec4(s*A, 1.0));
  vs_out.vertex_B = P_mat*V_mat*(voxel_center + vec4(s*B, 1.0));
  vs_out.vertex_C = P_mat*V_mat*(voxel_center + vec4(s*C, 1.0));
  vs_out.vertex_D = P_mat*V_mat*(voxel_center + vec4(s*D, 1.0));
  vs_out.vertex_E = P_mat*V_mat*(voxel_center + vec4(s*E, 1.0));
  vs_out.vertex_F = P_mat*V_mat*(voxel_center + vec4(s*F, 1.0));
  vs_out.vertex_G = P_mat*V_mat*(voxel_center + vec4(s*G, 1.0));
  vs_out.vertex_H = P_mat*V_mat*(voxel_center + vec4(s*H, 1.0));

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// VOXEL'S FACE COLORS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.color_L = vec4(diffusion_L*vec3(voxel_color), 1.0);
  vs_out.color_R = vec4(diffusion_R*vec3(voxel_color), 1.0);
  vs_out.color_D = vec4(diffusion_D*vec3(voxel_color), 1.0);
  vs_out.color_U = vec4(diffusion_U*vec3(voxel_color), 1.0);
  vs_out.color_B = vec4(diffusion_B*vec3(voxel_color), 1.0);
  vs_out.color_F = vec4(diffusion_F*vec3(voxel_color), 1.0);
}
