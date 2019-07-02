/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 14) out;                                 // Output points.

in VS_OUT
{
  vec4 voxel_color;
  vec4 voxel_A;
  vec4 voxel_B;
  vec4 voxel_C;
  vec4 voxel_D;
  vec4 voxel_E;
  vec4 voxel_F;
  vec4 voxel_G;
  vec4 voxel_H;
} gs_in[];

out vec4 color_PC_geom;

void main()
{
  color_PC_geom = gs_in[0].color_PC;

  gl_Position = gs_in[0].point_C;
  EmitVertex();
  gl_Position = gs_in[0].point_D;
  EmitVertex();
  gl_Position = gs_in[0].point_G;
  EmitVertex();
  gl_Position = gs_in[0].point_H;
  EmitVertex();
  gl_Position = gs_in[0].point_F;
  EmitVertex();
  gl_Position = gs_in[0].point_D;
  EmitVertex();
  gl_Position = gs_in[0].point_B;
  EmitVertex();
  gl_Position = gs_in[0].point_C;
  EmitVertex();
  gl_Position = gs_in[0].point_A;
  EmitVertex();
  gl_Position = gs_in[0].point_G;
  EmitVertex();
  gl_Position = gs_in[0].point_E;
  EmitVertex();
  gl_Position = gs_in[0].point_F;
  EmitVertex();
  gl_Position = gs_in[0].point_A;
  EmitVertex();
  gl_Position = gs_in[0].point_B;
  EmitVertex();

  EndPrimitive();
}
