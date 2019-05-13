/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 14) out;                                 // Output points.

in VS_OUT
{
  vec4 color_PC;
  vec4 point_A;
  vec4 point_B;
  vec4 point_C;
  vec4 point_D;
  vec4 point_E;
  vec4 point_F;
  vec4 point_G;
  vec4 point_H;
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
