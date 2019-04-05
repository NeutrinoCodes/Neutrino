/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (line_strip, max_vertices = 2) out;                                      // Output points.

in vec4 color_PC_vert[];
in vec4 point_PR_vert[];
in vec4 point_PU_vert[];
in vec4 point_PL_vert[];
in vec4 point_PD_vert[];

out vec4 color_PC_geom;

void main()
{
  color_PC_geom = color_PC_vert[0];

  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position = point_PR_vert[0];
  EmitVertex();

  EndPrimitive();
}
