/// @file

#version 410 core

in  vec4 voxel_color;                                                           // (R, G, B, A) color, from geometry shader.
out vec4 fragment_color;                                                        // The rendered color.

void main(void)
{
  fragment_color = voxel_color;                                                 // Setting fragment color...
}
