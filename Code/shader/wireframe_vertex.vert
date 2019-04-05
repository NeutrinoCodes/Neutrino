/// @file

#version 410 core

layout (location = 0) in  vec4 color_PC;                                        // Input color to be processed.
layout (location = 1) in  vec4 point_PC;                                        // Input point to be processed.
layout (location = 2) in  vec4 point_PR;                                        // Input point to be processed.
layout (location = 3) in  vec4 point_PU;                                        // Input point to be processed.
layout (location = 4) in  vec4 point_PL;                                        // Input point to be processed.
layout (location = 5) in  vec4 point_PD;                                        // Input point to be processed.

out vec4 color_PC_vert;                                                            // Output color (for fragment shader).
//out vec4 point_PR_vert;
//out vec4 point_PU_vert;
//out vec4 point_PL_vert;
//out vec4 point_PD_vert;

uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  //gl_PointSize = 5;                                                           // Setting point size...

  gl_Position = Projection_matrix*View_matrix*point_PC;                         // Rendering "point" position...
  color_PC_vert = color_PC;                                                     // Forwarding "color" as "color_vert" to the geometry shader...
  //point_PR_vert = point_PR;
  //point_PU_vert = point_PU;
  //point_PL_vert = point_PL;
  //point_PD_vert = point_PD;
}
