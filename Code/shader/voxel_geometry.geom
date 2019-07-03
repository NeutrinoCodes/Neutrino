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
} gs_in[];

out vec4 voxel_color;

void main()
{
  voxel_color = gs_in[0].voxel_color;

  ////////////////////////////////////////////////////////////////////////////////
  /////////// CUBE TRIANGULATION (Evans, Skiena, Varshney: IEEE - 1996) //////////
  ////////////////////////////////////////////////////////////////////////////////
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();
  gl_Position = gs_in[0].vertex_H;
  EmitVertex();
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();
  gl_Position = gs_in[0].vertex_E;
  EmitVertex();
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();

  EndPrimitive();
}
