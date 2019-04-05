/// @file

#version 410 core

layout (location = 0) in  vec4 color;                                           // Input color to be processed.
layout (location = 1) in  vec4 point;                                           // Input point to be processed.

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
  //int vertex = gl_VertexID % 3;
  PR_vert = point;
  //PU_vert = texelFetch(vertex_buffer, 1);
  //PL_vert = texelFetch(vertex_buffer, 2);
  //PD_vert = texelFetch(vertex_buffer, 3);

  //gl_PointSize = 5;                                                             // Setting point size...

  gl_Position = Projection_matrix*View_matrix*point;                            // Rendering "point" position...
  color_vert = color;                                                           // Forwarding "color" as "color_vert" to the geometry shader...


  //EZOR: interesting link:
  //https://stackoverflow.com/questions/28437241/get-vertex-positions-in-fragment-shader

}
