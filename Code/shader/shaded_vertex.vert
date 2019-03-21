/// @file

#version 410 core

layout (location = 0) in  vec4 point;                                           // Input point to be processed.
layout (location = 1) in  vec4 color;                                           // Input color to be processed.
out vec4 color_vert;                                                            // Output color (for fragment shader).
uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  //gl_PointSize = 5;                                                             // Setting point size...
  gl_Position = Projection_matrix*View_matrix*point;                            // Rendering "point" position...
  color_vert = color;                                                           // Forwarding "color" as "color_vert" to the geometry shader...
}
