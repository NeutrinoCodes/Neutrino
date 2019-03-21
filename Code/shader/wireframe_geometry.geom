/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (points, max_vertices = 2) out;                                          // Output points.

in vec4 color_vert[];
out vec4 color_geom;

// Dummy pass-through geometry shader:
void main()
{
  color_geom = color_vert[0];
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  
  EndPrimitive();
}
