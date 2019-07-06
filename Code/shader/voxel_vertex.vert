/// @file

#version 410 core

//////////////////////////////////////////////////////////////////////////////////
////////// CUBE VERTEX BARICENTRIC COORDINATES (3D binary hypercube) /////////////
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
#define A vec3(-1.0, -1.0, -1.0)
#define B vec3(-1.0, -1.0, +1.0)
#define C vec3(-1.0, +1.0, -1.0)
#define D vec3(-1.0, +1.0, +1.0)
#define E vec3(+1.0, -1.0, -1.0)
#define F vec3(+1.0, -1.0, +1.0)
#define G vec3(+1.0, +1.0, -1.0)
#define H vec3(+1.0, +1.0, +1.0)

#define N1 vec3(-1.0, +0.0, +0.0)
#define N2 vec3(+1.0, +0.0, +0.0)
#define N3 vec3(+0.0, +0.0, -1.0)
#define N4 vec3(+0.0, +0.0, +1.0)
#define N5 vec3(+0.0, +0.0, -1.0)
#define N6 vec3(+0.0, +0.0, +1.0)

#define s 0.005

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
  vec4  light;
  float diffusion_L;
  float diffusion_R;
  float diffusion_D;
  float diffusion_U;
  float diffusion_B;
  float diffusion_F;

  light = vec4(0.0, -1.0, 0.0, 1.0);
  light.xyz = normalize(light.xyz);
  diffusion_L = clamp(dot(light.xyz, gs_in[0].normal_L.xyz), 0.2, 1.0);
  diffusion_R = clamp(dot(light.xyz, gs_in[0].normal_R.xyz), 0.2, 1.0);
  diffusion_D = clamp(dot(light.xyz, gs_in[0].normal_D.xyz), 0.2, 1.0);
  diffusion_U = clamp(dot(light.xyz, gs_in[0].normal_U.xyz), 0.2, 1.0);
  diffusion_B = clamp(dot(light.xyz, gs_in[0].normal_B.xyz), 0.2, 1.0);
  diffusion_F = clamp(dot(light.xyz, gs_in[0].normal_F.xyz), 0.2, 1.0);



  gl_Position = P_mat*V_mat*voxel_center;                                       // Setting voxel position...
  vs_out.voxel_color = voxel_color;                                             // Forwarding voxel color...

  vs_out.vertex_A = P_mat*V_mat*(voxel_center + (s*A, 1.0));
  vs_out.vertex_B = P_mat*V_mat*(voxel_center + (s*B, 1.0));
  vs_out.vertex_C = P_mat*V_mat*(voxel_center + (s*C, 1.0));
  vs_out.vertex_D = P_mat*V_mat*(voxel_center + (s*D, 1.0));
  vs_out.vertex_E = P_mat*V_mat*(voxel_center + (s*E, 1.0));
  vs_out.vertex_F = P_mat*V_mat*(voxel_center + (s*F, 1.0));
  vs_out.vertex_G = P_mat*V_mat*(voxel_center + (s*G, 1.0));
  vs_out.vertex_H = P_mat*V_mat*(voxel_center + (s*H, 1.0));

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////// CUBE FACE BARICENTRIC NORMALS ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.normal_L = P_mat*V_mat*(voxel_center + vec4(-1.0, +0.0, +0.0, +1.0)); // LEFT:  face "ABDC" normal.
  vs_out.normal_R = P_mat*V_mat*(voxel_center + vec4(+1.0, +0.0, +0.0, +1.0)); // RIGHT: face "EFHG" normal.
  vs_out.normal_D = P_mat*V_mat*(voxel_center + vec4(+0.0, +0.0, -1.0, +1.0)); // DOWN:  face "ABFE" normal.
  vs_out.normal_U = P_mat*V_mat*(voxel_center + vec4(+0.0, +0.0, +1.0, +1.0)); // UP:    face "CDHG" normal.
  vs_out.normal_B = P_mat*V_mat*(voxel_center + vec4(+0.0, +0.0, -1.0, +1.0)); // BACK:  face "AEGC" normal.
  vs_out.normal_F = P_mat*V_mat*(voxel_center + vec4(+0.0, +0.0, +1.0, +1.0)); // FRONT: face "BFHD" normal.
}
