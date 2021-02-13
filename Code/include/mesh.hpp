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

// Element types in .msh file format (numbers should not be changed):
#define NU_MSH_LIN_2    1
#define NU_MSH_TRI_3    2
#define NU_MSH_QUA_4    3
#define NU_MSH_TET_4    4
#define NU_MSH_HEX_8    5
#define NU_MSH_PRI_6    6
#define NU_MSH_PYR_5    7
#define NU_MSH_LIN_3    8
#define NU_MSH_TRI_6    9
#define NU_MSH_QUA_9    10
#define NU_MSH_TET_10   11
#define NU_MSH_HEX_27   12
#define NU_MSH_PRI_18   13
#define NU_MSH_PYR_14   14
#define NU_MSH_PNT      15
#define NU_MSH_QUA_8    16
#define NU_MSH_HEX_20   17
#define NU_MSH_PRI_15   18
#define NU_MSH_PYR_13   19
#define NU_MSH_TRI_9    20
#define NU_MSH_TRI_10   21
#define NU_MSH_TRI_12   22
#define NU_MSH_TRI_15   23
#define NU_MSH_TRI_15I  24
#define NU_MSH_TRI_21   25
#define NU_MSH_LIN_4    26
#define NU_MSH_LIN_5    27
#define NU_MSH_LIN_6    28
#define NU_MSH_TET_20   29
#define NU_MSH_TET_35   30
#define NU_MSH_TET_56   31
#define NU_MSH_TET_22   32
#define NU_MSH_TET_28   33
#define NU_MSH_POLYG_   34
#define NU_MSH_POLYH_   35
#define NU_MSH_QUA_16   36
#define NU_MSH_QUA_25   37
#define NU_MSH_QUA_36   38
#define NU_MSH_QUA_12   39
#define NU_MSH_QUA_16I  40
#define NU_MSH_QUA_20   41
#define NU_MSH_TRI_28   42
#define NU_MSH_TRI_36   43
#define NU_MSH_TRI_45   44
#define NU_MSH_TRI_55   45
#define NU_MSH_TRI_66   46
#define NU_MSH_QUA_49   47
#define NU_MSH_QUA_64   48
#define NU_MSH_QUA_81   49
#define NU_MSH_QUA_100  50
#define NU_MSH_QUA_121  51
#define NU_MSH_TRI_18   52
#define NU_MSH_TRI_21I  53
#define NU_MSH_TRI_24   54
#define NU_MSH_TRI_27   55
#define NU_MSH_TRI_30   56
#define NU_MSH_QUA_24   57
#define NU_MSH_QUA_28   58
#define NU_MSH_QUA_32   59
#define NU_MSH_QUA_36I  60
#define NU_MSH_QUA_40   61
#define NU_MSH_LIN_7    62
#define NU_MSH_LIN_8    63
#define NU_MSH_LIN_9    64
#define NU_MSH_LIN_10   65
#define NU_MSH_LIN_11   66
#define NU_MSH_LIN_B    67
#define NU_MSH_TRI_B    68
#define NU_MSH_POLYG_B  69
#define NU_MSH_LIN_C    70
// TETS COMPLETE (6->10)
#define NU_MSH_TET_84   71
#define NU_MSH_TET_120  72
#define NU_MSH_TET_165  73
#define NU_MSH_TET_220  74
#define NU_MSH_TET_286  75
// TETS INCOMPLETE (6->10)
#define NU_MSH_TET_34   79
#define NU_MSH_TET_40   80
#define NU_MSH_TET_46   81
#define NU_MSH_TET_52   82
#define NU_MSH_TET_58   83
//
#define NU_MSH_LIN_1    84
#define NU_MSH_TRI_1    85
#define NU_MSH_QUA_1    86
#define NU_MSH_TET_1    87
#define NU_MSH_HEX_1    88
#define NU_MSH_PRI_1    89
#define NU_MSH_PRI_40   90
#define NU_MSH_PRI_75   91
// HEXES COMPLETE (3->9)
#define NU_MSH_HEX_64   92
#define NU_MSH_HEX_125  93
#define NU_MSH_HEX_216  94
#define NU_MSH_HEX_343  95
#define NU_MSH_HEX_512  96
#define NU_MSH_HEX_729  97
#define NU_MSH_HEX_1000 98
// HEXES INCOMPLETE (3->9)
#define NU_MSH_HEX_32   99
#define NU_MSH_HEX_44   100
#define NU_MSH_HEX_56   101
#define NU_MSH_HEX_68   102
#define NU_MSH_HEX_80   103
#define NU_MSH_HEX_92   104
#define NU_MSH_HEX_104  105
// PRISMS COMPLETE (5->9)
#define NU_MSH_PRI_126  106
#define NU_MSH_PRI_196  107
#define NU_MSH_PRI_288  108
#define NU_MSH_PRI_405  109
#define NU_MSH_PRI_550  110
// PRISMS INCOMPLETE (3->9)
#define NU_MSH_PRI_24   111
#define NU_MSH_PRI_33   112
#define NU_MSH_PRI_42   113
#define NU_MSH_PRI_51   114
#define NU_MSH_PRI_60   115
#define NU_MSH_PRI_69   116
#define NU_MSH_PRI_78   117
// PYRAMIDS COMPLETE (3->9)
#define NU_MSH_PYR_30   118
#define NU_MSH_PYR_55   119
#define NU_MSH_PYR_91   120
#define NU_MSH_PYR_140  121
#define NU_MSH_PYR_204  122
#define NU_MSH_PYR_285  123
#define NU_MSH_PYR_385  124
// PYRAMIDS INCOMPLETE (3->9)
#define NU_MSH_PYR_21   125
#define NU_MSH_PYR_29   126
#define NU_MSH_PYR_37   127
#define NU_MSH_PYR_45   128
#define NU_MSH_PYR_53   129
#define NU_MSH_PYR_61   130
#define NU_MSH_PYR_69   131
// Additional types
#define NU_MSH_PYR_1    132
#define NU_MSH_PNT_SUB  133
#define NU_MSH_LIN_SUB  134
#define NU_MSH_TRI_SUB  135
#define NU_MSH_TET_SUB  136
#define NU_MSH_TET_16   137
#define NU_MSH_TRI_MINI 138
#define NU_MSH_TET_MINI 139
#define NU_MSH_TRIH_4   140
#define NU_MSH_MAX_NUM  140                                                                         ///< GMSH: keep this up-to-date when adding new type!

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// "mesh" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class mesh
/// ### Mesh.
/// Declares a mesh class.
/// To be used to run mesh operations.
class mesh : public neutrino                                                                        /// @brief **Mesh.**
{
private:
  // ENTITY VARIABLES:
  std::vector<std::pair<int, int> > entity_list;                                                    ///< Entity list.

public:
  std::vector<nu_float4_structure>  node;                                                           ///< Nodes.
  std::vector<GLint>                element;                                                        ///< Elements.
  std::vector<GLint>                element_offset;                                                 ///< Element offset indices.
  std::vector<GLint>                group;                                                          ///< Group.
  std::vector<GLint>                group_offset;                                                   ///< Group offset indices.
  std::vector<GLint>                neighbour;                                                      ///< Neighbours.
  std::vector<GLint>                neighbour_offset;                                               ///< Neighbour offset indices.
  std::vector<nu_float4_structure>  neighbour_link;                                                 ///< Neighbour links.
  std::vector<GLfloat>              neighbour_length;                                               ///< Neighbour link lengths.
  std::vector<size_t>               physical;                                                       ///< Physicals.

  mesh (
        std::string loc_file_name                                                                   ///< GMSH .msh file name.
       );

  void get_nodes (
                  int loc_entity_dimension,
                  int loc_entity_tag
                 );

  void get_elements (
                     int loc_entity_dimension,
                     int loc_entity_tag,
                     int loc_element_type
                    );

  void get_groups (
                   int loc_entity_dimension,
                   int loc_entity_tag,
                   int loc_element_type
                  );

  void get_neighbours (
                       int loc_entity_dimension,
                       int loc_entity_tag,
                       int loc_element_type
                      );

  void get_physicals (
                      size_t loc_physical_group_dim,                                                ///< Physical group dimension.
                      size_t loc_physical_group_tag                                                 ///< Physical group tag.
                     );

  ~mesh();
};

#endif
