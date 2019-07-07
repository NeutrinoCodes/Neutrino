/// @file

#version 410 core

in  vec4 voxel_color;                                                           // Voxel color.
out vec4 fragment_color;                                                        // Fragment color.

void main(void)
{
  fragment_color = voxel_color;                                                 // Setting fragment color...
}
