/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (points, max_vertices = 1) out;                                          // Output points.

// Dummy pass-through geometry shader:
void main()
{
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  EndPrimitive();
}
