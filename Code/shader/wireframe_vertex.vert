/// @file

#version 410 core

layout (location = 0) in  vec4 color_PC;                                        // Input color to be processed.
layout (location = 1) in  vec4 point_PC;                                        // Input point to be processed.
layout (location = 2) in  vec4 point_PR;                                        // Input point to be processed.
layout (location = 3) in  vec4 point_PU;                                        // Input point to be processed.
layout (location = 4) in  vec4 point_PL;                                        // Input point to be processed.
layout (location = 5) in  vec4 point_PD;                                        // Input point to be processed.

out VS_OUT
{
  vec4 color_PC;                                                                // Output color (for fragment shader).
  vec4 point_PR;
  vec4 point_PU;
  vec4 point_PL;
  vec4 point_PD;
} vs_out;


uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  //gl_PointSize = 5;                                                           // Setting point size...

  gl_Position = Projection_matrix*View_matrix*point_PC;                         // Rendering "point" position...
  vs_out.color_PC = color_PC;                                                     // Forwarding "color" as "color_vert" to the geometry shader...
  vs_out.point_PR = Projection_matrix*View_matrix*point_PR;
  vs_out.point_PU = Projection_matrix*View_matrix*point_PU;
  vs_out.point_PL = Projection_matrix*View_matrix*point_PL;
  vs_out.point_PD = Projection_matrix*View_matrix*point_PD;
}
