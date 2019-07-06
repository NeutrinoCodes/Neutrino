/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 14) out;                                 // Output points.

in VS_OUT
{
  vec4 voxel_color;
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
} gs_in[];

out vec4 voxel_color;

void main()
{
  ////////////////////////////////////////////////////////////////////////////////
  /////////// CUBE TRIANGULATION (Evans, Skiena, Varshney: IEEE - 1996) //////////
  ////////////////////////////////////////////////////////////////////////////////
  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_U*voxel_color.xyz;
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_U*voxel_color.xyz;
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_U*voxel_color.xyz;                                // "CDG" triangle.
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_U*voxel_color.xyz;                                // "DGH" triangle.
  gl_Position = gs_in[0].vertex_H;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_R*voxel_color.xyz;                                // "GHF" triangle.
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_F*voxel_color.xyz;                                // "HFD" triangle.
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_F*voxel_color.xyz;                                // "FDB" triangle.
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_L*voxel_color.xyz;                                // "DBC" triangle.
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_L*voxel_color.xyz;                                // "BCA" triangle.
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_B*voxel_color.xyz;                                // "CAG" triangle.
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_B*voxel_color.xyz;                                // "AGE" triangle.
  gl_Position = gs_in[0].vertex_E;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_R*voxel_color.xyz;                                // "GEF" triangle.
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_D*voxel_color.xyz;                                // "EFA" triangle.
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();

  voxel_color = gs_in[0].voxel_color;
  voxel_color.xyz = diffusion_D*voxel_color.xyz;                                // "FAB" triangle.
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();

  EndPrimitive();
}
