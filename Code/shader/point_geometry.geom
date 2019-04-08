/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (points) out;                                                            // Output points.

in VS_OUT
{
  vec4 color_PC;
  vec4 point_PR;
  vec4 point_PU;
  vec4 point_PL;
  vec4 point_PD;
} gs_in[];

out vec4 color_PC_geom;

void main()
{
  color_PC_geom = gs_in[0].color_PC;

  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  EndPrimitive();
}
