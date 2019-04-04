/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (points, max_vertices = 1) out;                                          // Output points.

in vec4 color_vert[];
in uint index_PR_vert[];

out vec4 color_geom;
out uint index_PR_geom;

// Dummy pass-through geometry shader:
void main()
{
  color_geom = color_vert[0];
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  EndPrimitive();
}
