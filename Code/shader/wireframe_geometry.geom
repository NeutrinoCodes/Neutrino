/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (line_strip, max_vertices = 2) out;                                      // Output points.

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
  //color_PC_geom = vec4(1.0, 0.0, 0.0, 1.0);

  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position = gs_in[0].point_PR;
  //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
  EmitVertex();

  EndPrimitive();
}
