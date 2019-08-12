/// @file

#version 410 core

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////// VOXEL: 3D binary hypercube //////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//       (-1.0, +1.0, -1.0)    C--------G  (+1.0, +1.0, -1.0)
//                            /|       /|
//       (-1.0, +1.0, +1.0)  D--------H |  (+1.0, +1.0, +1.0)
//       (-1.0, -1.0, -1.0)  | A------|-E  (+1.0, -1.0, -1.0)
//                           |/       |/
//       (-1.0, -1.0, +1.0)  B--------F    (+1.0, -1.0, +1.0)
//
//                               y (points up)
//                               |
//                               o -- x (points right)
//                              /
//                             z (points out of the screen)
//
//                               UP
//                               |  / BACK
//                               | /
//                     LEFT -----+----- RIGHT
//                              /|
//                       FRONT / |
//                              DOWN
//
//////////////////////////////////////////////////////////////////////////////////
#define A vec3(-1.0, -1.0, -1.0)                                                // Vertex "A".
#define B vec3(-1.0, -1.0, +1.0)                                                // Vertex "B".
#define C vec3(-1.0, +1.0, -1.0)                                                // Vertex "C".
#define D vec3(-1.0, +1.0, +1.0)                                                // Vertex "D".
#define E vec3(+1.0, -1.0, -1.0)                                                // Vertex "E".
#define F vec3(+1.0, -1.0, +1.0)                                                // Vertex "F".
#define G vec3(+1.0, +1.0, -1.0)                                                // Vertex "G".
#define H vec3(+1.0, +1.0, +1.0)                                                // Vertex "H".

#define nL vec3(-1.0, +0.0, +0.0)                                               // Normal "LEFT".
#define nR vec3(+1.0, +0.0, +0.0)                                               // Normal "RIGHT".
#define nD vec3(+0.0, -1.0, +0.0)                                               // Normal "DOWN".
#define nU vec3(+0.0, +1.0, +0.0)                                               // Normal "UP".
#define nB vec3(+0.0, +0.0, -1.0)                                               // Normal "BACK".
#define nF vec3(+0.0, +0.0, +1.0)                                               // Normal "FRONT".

#define s 0.008                                                                 // Voxel side.
#define l vec3(0.0, -1.0, 0.0)                                                  // Light direction.

layout (location = 0) in vec4 voxel_center;                                     // Voxel center.
layout (location = 1) in vec4 voxel_color;                                      // Voxel color.

out VS_OUT
{
  vec4 vertex_A;                                                                // Vertex "A".
  vec4 vertex_B;                                                                // Vertex "B".
  vec4 vertex_C;                                                                // Vertex "C".
  vec4 vertex_D;                                                                // Vertex "D".
  vec4 vertex_E;                                                                // Vertex "E".
  vec4 vertex_F;                                                                // Vertex "F".
  vec4 vertex_G;                                                                // Vertex "G".
  vec4 vertex_H;                                                                // Vertex "H".
  vec4 color_L;                                                                 // LEFT:  face "ABDC" color.
  vec4 color_R;                                                                 // RIGHT: face "EFHG" color.
  vec4 color_D;                                                                 // DOWN:  face "ABFE" color.
  vec4 color_U;                                                                 // UP:    face "CDHG" color.
  vec4 color_B;                                                                 // BACK:  face "AEGC" color.
  vec4 color_F;                                                                 // FRONT: face "BFHD" color.
} vs_out;

uniform mat4 V_mat;                                                             // View matrix.
uniform mat4 P_mat;                                                             // Projection matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  vec3 light;                                                                   // Light direction.

  vec3 normal_L;                                                                // LEFT:  face "ABDC" normal.
  vec3 normal_R;                                                                // RIGHT: face "EFGH" normal.
  vec3 normal_D;                                                                // DOWN:  face "ABFE" normal.
  vec3 normal_U;                                                                // UP:    face "CDHG" normal.
  vec3 normal_B;                                                                // BACK:  face "AEGC" normal.
  vec3 normal_F;                                                                // FRONT: face "BFHD" normal.

  float diffusion_L;                                                            // LEFT:  face "ABDC" diffusion coefficient.
  float diffusion_R;                                                            // RIGHT: face "EFGH" diffusion coefficient.
  float diffusion_D;                                                            // DOWN:  face "ABFE" diffusion coefficient.
  float diffusion_U;                                                            // UP:    face "CDHG" diffusion coefficient.
  float diffusion_B;                                                            // BACK:  face "AEGC" diffusion coefficient.
  float diffusion_F;                                                            // FRONT: face "BFHD" diffusion coefficient.

  gl_Position = P_mat*V_mat*voxel_center;                                       // Setting voxel position...
  light = -normalize(l);                                                        // Normalizing and inverting light direction...

  //voxel_color = vec4(1.0, 0.0, 0.0, 1.0);
  //voxel_center = vec4(0.0, 0.0, 0.0, 1.0);

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// VOXEL'S FACE BARICENTRIC NORMALS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  normal_L = vec3(P_mat*V_mat*(voxel_center + vec4(nL, +1.0)));                 // LEFT:  computing face "ABDC" normal.
  normal_R = vec3(P_mat*V_mat*(voxel_center + vec4(nR, +1.0)));                 // RIGHT: fcomputing face "EFHG" normal.
  normal_D = vec3(P_mat*V_mat*(voxel_center + vec4(nD, +1.0)));                 // DOWN:  computing face "ABFE" normal.
  normal_U = vec3(P_mat*V_mat*(voxel_center + vec4(nU, +1.0)));                 // UP:    computing face "CDHG" normal.
  normal_B = vec3(P_mat*V_mat*(voxel_center + vec4(nB, +1.0)));                 // BACK:  computing face "AEGC" normal.
  normal_F = vec3(P_mat*V_mat*(voxel_center + vec4(nF, +1.0)));                 // FRONT: computing face "BFHD" normal.

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////// VOXEL'S FACE DIFFUSION COEFFICIENTS //////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  diffusion_L = clamp(dot(light, normal_L), 0.2, 1.0);                          // LEFT:  computing face "ABDC" diffusion coefficient.
  diffusion_R = clamp(dot(light, normal_R), 0.2, 1.0);                          // RIGHT: computing face "EFGH" diffusion coefficient.
  diffusion_D = clamp(dot(light, normal_D), 0.2, 1.0);                          // DOWN:  computing face "ABFE" diffusion coefficient.
  diffusion_U = clamp(dot(light, normal_U), 0.2, 1.0);                          // UP:    computing face "CDHG" diffusion coefficient.
  diffusion_B = clamp(dot(light, normal_B), 0.2, 1.0);                          // BACK:  computing face "AEGC" diffusion coefficient.
  diffusion_F = clamp(dot(light, normal_F), 0.2, 1.0);                          // FRONT: computing face "BFHD" diffusion coefficient.

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////// VOXEL'S NU_VERTEX BARICENTRIC COORDINATES /////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.vertex_A = P_mat*V_mat*(voxel_center + vec4(s*A, 1.0));                // Computing vertex "A".
  vs_out.vertex_B = P_mat*V_mat*(voxel_center + vec4(s*B, 1.0));                // Computing vertex "B".
  vs_out.vertex_C = P_mat*V_mat*(voxel_center + vec4(s*C, 1.0));                // Computing vertex "C".
  vs_out.vertex_D = P_mat*V_mat*(voxel_center + vec4(s*D, 1.0));                // Computing vertex "D".
  vs_out.vertex_E = P_mat*V_mat*(voxel_center + vec4(s*E, 1.0));                // Computing vertex "E".
  vs_out.vertex_F = P_mat*V_mat*(voxel_center + vec4(s*F, 1.0));                // Computing vertex "F".
  vs_out.vertex_G = P_mat*V_mat*(voxel_center + vec4(s*G, 1.0));                // Computing vertex "G".
  vs_out.vertex_H = P_mat*V_mat*(voxel_center + vec4(s*H, 1.0));                // Computing vertex "H".

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// VOXEL'S FACE COLORS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  vs_out.color_L = vec4(diffusion_L*vec3(voxel_color), 1.0);                    // LEFT:  computing face "ABDC" color.
  vs_out.color_R = vec4(diffusion_R*vec3(voxel_color), 1.0);                    // RIGHT: computing face "EFHG" color.
  vs_out.color_D = vec4(diffusion_D*vec3(voxel_color), 1.0);                    // DOWN:  computing face "ABFE" color.
  vs_out.color_U = vec4(diffusion_U*vec3(voxel_color), 1.0);                    // UP:    computing face "CDHG" color.
  vs_out.color_B = vec4(diffusion_B*vec3(voxel_color), 1.0);                    // BACK:  computing face "AEGC" color.
  vs_out.color_F = vec4(diffusion_F*vec3(voxel_color), 1.0);                    // FRONT: computing face "BFHD" color.
}
