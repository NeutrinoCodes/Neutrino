/// @file

#version 410 core

//////////////////////////////////////////////////////////////////////////////////
//
//                             C--------G
//                            /|       /|
//                           D--------H |
//                           | A------|-E
//                           |/       |/
//                           B--------F
//
//  TRIANGULATION SCHEME:
//
//             CDG +
//                 | UP
//           (DG)H +---+
//                     | [HGH]: degenerate triangle
//         +   GHF +---+
//         |   HFD +
//         |       | FRONT
//         | (FD)B +
//         |   DBC +
//   RIGHT |       | LEFT
//         | (BC)A +
//         |   CAG +
//         |       | BACK
//         | (AG)E +
//         +   GEF +---+
//                     | [EFE]: degenerate triangle
//             EFA +---+
//                 | DOWN
//           (FA)B +
//
//////////////////////////////////////////////////////////////////////////////////


layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 26) out;                                 // Output points.

in VS_OUT
{
  vec4 voxel_color;
  vec4 vertex_A;
  vec4 vertex_B;
  vec4 vertex_C;
  vec4 vertex_D;
  vec4 vertex_E;
  vec4 vertex_F;
  vec4 vertex_G;
  vec4 vertex_H;
  vec4 color_L;
  vec4 color_R;
  vec4 color_D;
  vec4 color_U;
  vec4 color_B;
  vec4 color_F;
} gs_in[];

out vec4 voxel_color;

void main()
{
  //////////////////////////////// CDG + (DG)H ///////////////////////////////////
  voxel_color = gs_in[0].color_U;
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_U;
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_U;
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_U;
  gl_Position = gs_in[0].vertex_H;
  EmitVertex();                                                                 // "H" vertex.

  //////////////////////////////////// GHF ///////////////////////////////////////
  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_H;
  EmitVertex();                                                                 // "H" vertex.

  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();                                                                 // "F" vertex.

  //////////////////////////////// HFD + (FD)B ///////////////////////////////////
  voxel_color = gs_in[0].color_F;
  gl_Position = gs_in[0].vertex_H;
  EmitVertex();                                                                 // "H" vertex.

  voxel_color = gs_in[0].color_F;
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();                                                                 // "F" vertex.

  voxel_color = gs_in[0].color_F;
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_F;
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();                                                                 // "B" vertex.

  //////////////////////////////// DBC + (BC)A ///////////////////////////////////
  voxel_color = gs_in[0].color_L;
  gl_Position = gs_in[0].vertex_D;
  EmitVertex();                                                                 // "D" vertex.

  voxel_color = gs_in[0].color_L;
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();                                                                 // "B" vertex.

  voxel_color = gs_in[0].color_L;
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_L;
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();                                                                 // "A" vertex.

  //////////////////////////////// CAG + (AG)E ///////////////////////////////////
  voxel_color = gs_in[0].color_B;
  gl_Position = gs_in[0].vertex_C;
  EmitVertex();                                                                 // "C" vertex.

  voxel_color = gs_in[0].color_B;
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();                                                                 // "A" vertex.

  voxel_color = gs_in[0].color_B;
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_B;
  gl_Position = gs_in[0].vertex_E;
  EmitVertex();                                                                 // "E" vertex.

  ///////////////////////////////////// GEF //////////////////////////////////////
  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_G;
  EmitVertex();                                                                 // "G" vertex.

  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_E;
  EmitVertex();                                                                 // "E" vertex.

  voxel_color = gs_in[0].color_R;
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();                                                                 // "F" vertex.

  //////////////////////////////// EFA + (FA)B ///////////////////////////////////
  voxel_color = gs_in[0].color_D;
  gl_Position = gs_in[0].vertex_E;
  EmitVertex();                                                                 // "E" vertex.

  voxel_color = gs_in[0].color_D;
  gl_Position = gs_in[0].vertex_F;
  EmitVertex();                                                                 // "F" vertex.

  voxel_color = gs_in[0].color_D;
  gl_Position = gs_in[0].vertex_A;
  EmitVertex();                                                                 // "A" vertex.

  voxel_color = gs_in[0].color_D;
  gl_Position = gs_in[0].vertex_B;
  EmitVertex();                                                                 // "B" vertex.

  EndPrimitive();
}
