/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (line_strip, max_vertices = 2) out;                                          // Output points.

in vec4 color_vert[];
in vec4 PR_vert[];
in vec4 PU_vert[];
in vec4 PL_vert[];
in vec4 PD_vert[];

out vec4 color_geom;

void main()
{
  vec4 pippo;

  pippo = PR_vert[0].gl_VertexID;
  color_geom = color_vert[0];

  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(0.05, 0.0, 0.0, 0.0);
  EmitVertex();

  EndPrimitive();
}
