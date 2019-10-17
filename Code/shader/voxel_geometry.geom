/// @file   voxel_geometry.geom
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  This geometry file creates a voxel out of a 4D point coordinates.

#version 410 core

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////// VOXEL: triangulation scheme //////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//                             C--------G
//                            /|       /|
//                           D--------H |
//                           | A------|-E
//                           |/       |/
//                           B--------F
//
//  Triangle strip sequence:
//
//             CDG +
//                 | UP
//           (DG)H +---+
//                     | [HGH]: degenerate triangle (for face color change)
//        +--- GHF +---+
//        |    HFD +
//        |        | FRONT
//        |  (FD)B +
//        |    DBC +
//  RIGHT |        | LEFT
//        |  (BC)A +
//        |    CAG +
//        |        | BACK
//        |  (AG)E +
//        +--- GEF +---+
//                     | [EFE]: degenerate triangle (for face color change)
//             EFA +---+
//                 | DOWN
//           (FA)B +
//
//////////////////////////////////////////////////////////////////////////////////

layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 26) out;                                 // Output points.

in VS_OUT
{
  vec4 vertex_A;                                                                // Vertex "A".
  vec4 vertex_B;                                                                // Vertex "B".
  vec4 vertex_C;                                                                // Vertex "C".
  vec4 vertex_D;                                                                // Vertex "D".
  vec4 vertex_E;                                                                // Vertex "E".
  vec4 vertex_F;                                                                // Vertex "F".
  vec4 vertex_G;                                                                // Vertex "G".
  vec4 vertex_H;                                                                // Vertex "H".
  vec4 color_L;                                                                 // LEFT:  face "ABDC" color.
  vec4 color_R;                                                                 // RIGHT: face "EFHG" color.
  vec4 color_D;                                                                 // DOWN:  face "ABFE" color.
  vec4 color_U;                                                                 // UP:    face "CDHG" color.
  vec4 color_B;                                                                 // BACK:  face "AEGC" color.
  vec4 color_F;                                                                 // FRONT: face "BFHD" color.
} gs_in[];

out vec4 voxel_color;                                                           // Voxel color (for fragment shader).

void main()
{
  //////////////////////////////// CDG + (DG)H ///////////////////////////////////
  voxel_color = gs_in[0].color_U;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_C;                                              // Setting voxel position...
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_U;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_D;                                              // Setting voxel position...
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_U;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_G;                                              // Setting voxel position...
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_U;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_H;                                              // Setting voxel position...
  EmitVertex();                                                                 // "H" vertex.

  //////////////////////////////////// GHF ///////////////////////////////////////
  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_G;                                              // Setting voxel position...
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_H;                                              // Setting voxel position...
  EmitVertex();                                                                 // "H" vertex.

  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_F;                                              // Setting voxel position...
  EmitVertex();                                                                 // "F" vertex.

  //////////////////////////////// HFD + (FD)B ///////////////////////////////////
  voxel_color = gs_in[0].color_F;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_H;                                              // Setting voxel position...
  EmitVertex();                                                                 // "H" vertex.

  voxel_color = gs_in[0].color_F;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_F;                                              // Setting voxel position...
  EmitVertex();                                                                 // "F" vertex.

  voxel_color = gs_in[0].color_F;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_D;                                              // Setting voxel position...
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_F;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_B;                                              // Setting voxel position...
  EmitVertex();                                                                 // "B" vertex.

  //////////////////////////////// DBC + (BC)A ///////////////////////////////////
  voxel_color = gs_in[0].color_L;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_D;                                              // Setting voxel position...
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_L;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_B;                                              // Setting voxel position...
  EmitVertex();                                                                 // "B" vertex.

  voxel_color = gs_in[0].color_L;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_C;                                              // Setting voxel position...
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_L;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_A;                                              // Setting voxel position...
  EmitVertex();                                                                 // "A" vertex.

  //////////////////////////////// CAG + (AG)E ///////////////////////////////////
  voxel_color = gs_in[0].color_B;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_C;                                              // Setting voxel position...
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_B;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_A;                                              // Setting voxel position...
  EmitVertex();                                                                 // "A" vertex.

  voxel_color = gs_in[0].color_B;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_G;                                              // Setting voxel position...
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_B;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_E;                                              // Setting voxel position...
  EmitVertex();                                                                 // "E" vertex.

  ///////////////////////////////////// GEF //////////////////////////////////////
  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_G;                                              // Setting voxel position...
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_E;                                              // Setting voxel position...
  EmitVertex();                                                                 // "E" vertex.

  voxel_color = gs_in[0].color_R;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_F;                                              // Setting voxel position...
  EmitVertex();                                                                 // "F" vertex.

  //////////////////////////////// EFA + (FA)B ///////////////////////////////////
  voxel_color = gs_in[0].color_D;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_E;                                              // Setting voxel position...
  EmitVertex();                                                                 // "E" vertex.

  voxel_color = gs_in[0].color_D;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_F;                                              // Setting voxel position...
  EmitVertex();                                                                 // "F" vertex.

  voxel_color = gs_in[0].color_D;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_A;                                              // Setting voxel position...
  EmitVertex();                                                                 // "A" vertex.

  voxel_color = gs_in[0].color_D;                                               // Setting voxel color...
  gl_Position = gs_in[0].vertex_B;                                              // Setting voxel position...
  EmitVertex();                                                                 // "B" vertex.

  EndPrimitive();
}
