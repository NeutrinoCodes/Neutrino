/// @file     mesh.hpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class based on GMSH.
///
/// @details  **GMSH** (http://gmsh.info) is "a three-dimensional finite element mesh generator
/// with built-in pre- and post-processing facilities".
/// Neutrino reads GMSH files and reconstructs a group complex out of it.
/// The group complex is used for both computational and rendering purposes.

#ifndef mesh_hpp
#define mesh_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"
#include <gmsh.h>

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the node array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_node
{
  cl_float x;                                                                                       ///< Node "x" coordinate.
  cl_float y;                                                                                       ///< Node "y" coordinate.
  cl_float z;                                                                                       ///< Node "z" coordinate.
  cl_float w;                                                                                       ///< Node "w" coordinate.
} gmsh_node;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the element array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_element
{
  std::vector<size_t> node;                                                                         ///< Node indexes.
} gmsh_element;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the group array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_group
{
  std::vector<size_t> element;                                                                      ///< Element indexes.
} gmsh_group;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the group array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_neighbour
{
  std::vector<size_t> node;                                                                         ///< Neighbour indexes.
  std::vector<gmsh_node> link;                                                                      ///< Neighbour indexes.
  size_t offset;                                                                                    ///< Neighbour offset index.
} gmsh_neighbour;
#pragma pack(pop)

namespace nu
{
// Element types in .msh file format (numbers should not be changed):
const int MSH_LIN_2    = 1;
const int MSH_TRI_3    = 2;
const int MSH_QUA_4    = 3;
const int MSH_TET_4    = 4;
const int MSH_HEX_8    = 5;
const int MSH_PRI_6    = 6;
const int MSH_PYR_5    = 7;
const int MSH_LIN_3    = 8;
const int MSH_TRI_6    = 9;
const int MSH_QUA_9    = 10;
const int MSH_TET_10   = 11;
const int MSH_HEX_27   = 12;
const int MSH_PRI_18   = 13;
const int MSH_PYR_14   = 14;
const int MSH_PNT      = 15;
const int MSH_QUA_8    = 16;
const int MSH_HEX_20   = 17;
const int MSH_PRI_15   = 18;
const int MSH_PYR_13   = 19;
const int MSH_TRI_9    = 20;
const int MSH_TRI_10   = 21;
const int MSH_TRI_12   = 22;
const int MSH_TRI_15   = 23;
const int MSH_TRI_15I  = 24;
const int MSH_TRI_21   = 25;
const int MSH_LIN_4    = 26;
const int MSH_LIN_5    = 27;
const int MSH_LIN_6    = 28;
const int MSH_TET_20   = 29;
const int MSH_TET_35   = 30;
const int MSH_TET_56   = 31;
const int MSH_TET_22   = 32;
const int MSH_TET_28   = 33;
const int MSH_POLYG_   = 34;
const int MSH_POLYH_   = 35;
const int MSH_QUA_16   = 36;
const int MSH_QUA_25   = 37;
const int MSH_QUA_36   = 38;
const int MSH_QUA_12   = 39;
const int MSH_QUA_16I  = 40;
const int MSH_QUA_20   = 41;
const int MSH_TRI_28   = 42;
const int MSH_TRI_36   = 43;
const int MSH_TRI_45   = 44;
const int MSH_TRI_55   = 45;
const int MSH_TRI_66   = 46;
const int MSH_QUA_49   = 47;
const int MSH_QUA_64   = 48;
const int MSH_QUA_81   = 49;
const int MSH_QUA_100  = 50;
const int MSH_QUA_121  = 51;
const int MSH_TRI_18   = 52;
const int MSH_TRI_21I  = 53;
const int MSH_TRI_24   = 54;
const int MSH_TRI_27   = 55;
const int MSH_TRI_30   = 56;
const int MSH_QUA_24   = 57;
const int MSH_QUA_28   = 58;
const int MSH_QUA_32   = 59;
const int MSH_QUA_36I  = 60;
const int MSH_QUA_40   = 61;
const int MSH_LIN_7    = 62;
const int MSH_LIN_8    = 63;
const int MSH_LIN_9    = 64;
const int MSH_LIN_10   = 65;
const int MSH_LIN_11   = 66;
const int MSH_LIN_B    = 67;
const int MSH_TRI_B    = 68;
const int MSH_POLYG_B  = 69;
const int MSH_LIN_C    = 70;
// TETS COMPLETE (6->10)
const int MSH_TET_84   = 71;
const int MSH_TET_120  = 72;
const int MSH_TET_165  = 73;
const int MSH_TET_220  = 74;
const int MSH_TET_286  = 75;
// TETS INCOMPLETE (6->10)
const int MSH_TET_34   = 79;
const int MSH_TET_40   = 80;
const int MSH_TET_46   = 81;
const int MSH_TET_52   = 82;
const int MSH_TET_58   = 83;
//
const int MSH_LIN_1    = 84;
const int MSH_TRI_1    = 85;
const int MSH_QUA_1    = 86;
const int MSH_TET_1    = 87;
const int MSH_HEX_1    = 88;
const int MSH_PRI_1    = 89;
const int MSH_PRI_40   = 90;
const int MSH_PRI_75   = 91;
// HEXES COMPLETE (3->9)
const int MSH_HEX_64   = 92;
const int MSH_HEX_125  = 93;
const int MSH_HEX_216  = 94;
const int MSH_HEX_343  = 95;
const int MSH_HEX_512  = 96;
const int MSH_HEX_729  = 97;
const int MSH_HEX_1000 = 98;
// HEXES INCOMPLETE (3->9)
const int MSH_HEX_32   = 99;
const int MSH_HEX_44   = 100;
const int MSH_HEX_56   = 101;
const int MSH_HEX_68   = 102;
const int MSH_HEX_80   = 103;
const int MSH_HEX_92   = 104;
const int MSH_HEX_104  = 105;
// PRISMS COMPLETE (5->9)
const int MSH_PRI_126  = 106;
const int MSH_PRI_196  = 107;
const int MSH_PRI_288  = 108;
const int MSH_PRI_405  = 109;
const int MSH_PRI_550  = 110;
// PRISMS INCOMPLETE (3->9)
const int MSH_PRI_24   = 111;
const int MSH_PRI_33   = 112;
const int MSH_PRI_42   = 113;
const int MSH_PRI_51   = 114;
const int MSH_PRI_60   = 115;
const int MSH_PRI_69   = 116;
const int MSH_PRI_78   = 117;
// PYRAMIDS COMPLETE (3->9)
const int MSH_PYR_30   = 118;
const int MSH_PYR_55   = 119;
const int MSH_PYR_91   = 120;
const int MSH_PYR_140  = 121;
const int MSH_PYR_204  = 122;
const int MSH_PYR_285  = 123;
const int MSH_PYR_385  = 124;
// PYRAMIDS INCOMPLETE (3->9)
const int MSH_PYR_21   = 125;
const int MSH_PYR_29   = 126;
const int MSH_PYR_37   = 127;
const int MSH_PYR_45   = 128;
const int MSH_PYR_53   = 129;
const int MSH_PYR_61   = 130;
const int MSH_PYR_69   = 131;
// Additional types
const int MSH_PYR_1    = 132;
const int MSH_PNT_SUB  = 133;
const int MSH_LIN_SUB  = 134;
const int MSH_TRI_SUB  = 135;
const int MSH_TET_SUB  = 136;
const int MSH_TET_16   = 137;
const int MSH_TRI_MINI = 138;
const int MSH_TET_MINI = 139;
const int MSH_TRIH_4   = 140;
const int MSH_MAX_NUM  = 140;                                                                       ///< GMSH: keep this up-to-date when adding new type!

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "mesh" class /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class mesh
/// ### Mesh.
/// Declares a mesh class.
/// To be used to run mesh operations.
class mesh : public neutrino                                                                        /// @brief **Mesh.**
{
private:
  // ENTITY VARIABLES:
  size_t                            entities;                                                       ///< Number of entities.
  std::vector<std::pair<int, int> > entity_list;                                                    ///< Entity list.
  GLint                             entity_dimension;                                               ///< Entity dimension.
  GLint                             entity_tag;                                                     ///< Entity tag.
  std::vector<size_t>               all_node_list;                                                  ///< Node list.
  std::vector<double>               all_node_coordinates;                                           ///< All node coordinates.
  std::vector<double>               all_node_parametric_coordinates;                                ///< All node coordinates.
  size_t                            all_nodes;
  std::vector<GLint>                all_node;                                                       ///< Node tags.

public:

  std::vector<GLint>                node;                                                           ///< Node indices (all nodes on physical group).
  std::vector<nu_float4_structure>  node_coordinates;                                               ///< Node coordinates (all nodes on all entities).

  std::vector<GLint>                element;                                                        ///< Element indices.
  std::vector<GLint>                element_offset;                                                 ///< Element offset indices.

  std::vector<GLint>                group;                                                          ///< Group indices.
  std::vector<GLint>                group_offset;                                                   ///< Group offset indices.

  std::vector<GLint>                neighbour;                                                      ///< Neighbour indices.
  std::vector<GLint>                neighbour_center;                                               ///< Neighbour center indices.
  std::vector<GLint>                neighbour_offset;                                               ///< Neighbour offset indices.
  std::vector<nu_float4_structure>  neighbour_link;                                                 ///< Neighbour links.
  std::vector<GLfloat>              neighbour_length;                                               ///< Neighbour link lengths.

  mesh (
        std::string loc_file_name                                                                   ///< GMSH .msh file name.
       );

  void process (
                int loc_physical_group_tag,                                                         ///< Physical group tag.
                int loc_physical_group_dimension,                                                   ///< Physical group dimension.
                int loc_element_type                                                                ///< Element type.
               );

  ~mesh();
};
}
#endif
