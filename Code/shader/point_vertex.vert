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
  vec4 point_A;
  vec4 point_B;
  vec4 point_C;
  vec4 point_D;
  vec4 point_E;
  vec4 point_F;
  vec4 point_G;
  vec4 point_H;
} vs_out;

uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

/// @function
// Computing rendering point coordinates:
void main(void)
{
  float l = 0.005;
  vec4 D = vec4(l, l, l, 1.0);

  gl_Position = Projection_matrix*View_matrix*point_PC;                         // Rendering "point" position...
  vs_out.color_PC = color_PC;                                                   // Forwarding "color" as "color_vert" to the geometry shader...

  vs_out.point_A = Projection_matrix*View_matrix*(point_PC + D*vec4(-1.0, -1.0, -1.0, 1.0));
  vs_out.point_B = Projection_matrix*View_matrix*(point_PC + D*vec4(-1.0, -1.0, +1.0, 1.0));
  vs_out.point_C = Projection_matrix*View_matrix*(point_PC + D*vec4(-1.0, +1.0, -1.0, 1.0));
  vs_out.point_D = Projection_matrix*View_matrix*(point_PC + D*vec4(-1.0, +1.0, +1.0, 1.0));
  vs_out.point_E = Projection_matrix*View_matrix*(point_PC + D*vec4(+1.0, -1.0, -1.0, 1.0));
  vs_out.point_F = Projection_matrix*View_matrix*(point_PC + D*vec4(+1.0, -1.0, +1.0, 1.0));
  vs_out.point_G = Projection_matrix*View_matrix*(point_PC + D*vec4(+1.0, +1.0, -1.0, 1.0));
  vs_out.point_H = Projection_matrix*View_matrix*(point_PC + D*vec4(+1.0, +1.0, +1.0, 1.0));
}
