/// @file

#version 410 core

in  vec4 color_PC_geom;                                                         // (R, G, B, A) color, from vertex shader.
out vec4 color_PC_frag;                                                         // The rendered color.

void main(void)
{
  color_PC_frag = color_PC_geom;
}
