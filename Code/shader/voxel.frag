/// @file   voxel.frag
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  This fragment file creates a voxel out of a 4D point coordinates.

#version 410 core

in  vec4 voxel_color;                                                                               // Voxel color.
out vec4 fragment_color;                                                                            // Fragment color.

/// @function main
/// Setting voxel color:
void main(void)
{
  fragment_color = voxel_color;                                                                     // Setting fragment color...
}
