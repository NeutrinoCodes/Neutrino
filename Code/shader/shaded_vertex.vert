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
  vec4 normal_RU;
  vec4 normal_LD;
} vs_out;


uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  vec3 D_RP;
  vec3 D_UP;
  vec3 D_LP;
  vec3 D_DP;

  gl_Position = Projection_matrix*View_matrix*point_PC;                         // Rendering "point" position...
  vs_out.color_PC = color_PC;                                                     // Forwarding "color" as "color_vert" to the geometry shader...
  vs_out.point_PR = Projection_matrix*View_matrix*point_PR;
  vs_out.point_PU = Projection_matrix*View_matrix*point_PU;
  vs_out.point_PL = Projection_matrix*View_matrix*point_PL;
  vs_out.point_PD = Projection_matrix*View_matrix*point_PD;

  D_RP = (point_PR - point_PC).xyz;
  D_UP = (point_PU - point_PC).xyz;
  D_LP = (point_PL - point_PC).xyz;
  D_DP = (point_PD - point_PC).xyz;

  vs_out.normal_RU = Projection_matrix*View_matrix*vec4(normalize(cross(D_RP, D_UP)), 1.0);
  vs_out.normal_LD = Projection_matrix*View_matrix*vec4(normalize(cross(D_LP, D_DP)), 1.0);
}
