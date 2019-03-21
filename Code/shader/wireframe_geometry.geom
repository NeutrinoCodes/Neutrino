/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (points, max_vertices = 2) out;                                          // Output points.

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

  gl_Position = gl_in[]...
  EZOR: I can't assign the index. I have to modify the node_index class and transform it
  in a class that stores the coordinates of the neighbours. Basically it will become a point class.

  EndPrimitive();
}
