/// @file

#version 410 core

layout (location = 0) in  vec4 point;                                           // Input point to be processed.
layout (location = 1) in  vec4 color;                                           // Input color to be processed.
layout (location = 2) in  int index_PR;
layout (location = 3) in  int index_PU;
layout (location = 4) in  int index_PL;
layout (location = 5) in  int index_PD;

out vec4 color_vert;                                                            // Output color (for fragment shader).
out vec4 PR_vert;
out vec4 PU_vert;
out vec4 PL_vert;
out vec4 PD_vert;

uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.
uniform samplerBuffer vertex_buffer;                                            // Vertex position array, as buffer texture.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  int vertex = gl_VertexID;

  PR_vert = texelFetch(vertex_buffer, index_PR);
  PU_vert = texelFetch(vertex_buffer, index_PU);
  PL_vert = texelFetch(vertex_buffer, index_PL);
  PD_vert = texelFetch(vertex_buffer, index_PD);
  //gl_PointSize = 5;                                                             // Setting point size...
  gl_Position = Projection_matrix*View_matrix*PD_vert;                            // Rendering "point" position...
  color_vert = color;                                                           // Forwarding "color" as "color_vert" to the geometry shader...


}
