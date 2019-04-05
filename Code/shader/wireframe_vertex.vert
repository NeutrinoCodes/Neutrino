/// @file

#version 410 core

layout (location = 0) in  vec4 point;                                           // Input point to be processed.
layout (location = 1) in  vec4 color;                                           // Input color to be processed.
layout (location = 2) in  uint index_PR;
layout (location = 3) in  uint index_PU;
layout (location = 4) in  uint index_PL;
layout (location = 5) in  uint index_PD;

out vec4 color_vert;                                                            // Output color (for fragment shader).
out uint index_PR_vert;
out uint index_PU_vert;
out uint index_PL_vert;
out uint index_PD_vert;

uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  //gl_PointSize = 5;                                                             // Setting point size...
  gl_Position = Projection_matrix*View_matrix*point;                            // Rendering "point" position...
  color_vert = color;                                                           // Forwarding "color" as "color_vert" to the geometry shader...
  index_PR_vert = index_PR;
  index_PU_vert = index_PU;
  index_PL_vert = index_PL;
  index_PD_vert = index_PD;
}
