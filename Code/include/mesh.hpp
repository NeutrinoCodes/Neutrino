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
  int type;                                                                                         ///< Element type.
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

#define GMHS_2_NODE_LINE                              1
#define GMSH_3_NODE_TRIANGLE                          2
#define GMSH_4_NODE_QUADRANGLE                        3
#define GMSH_4_NODE_TETRAHEDRON                       4
#define GMSH_8_NODE_HEXAHEDRON                        5
#define GMSH_6_NODE_PRISM                             6
#define GMSH_5_NODE_PYRAMID                           7
#define GMSH_3_NODE_SECOND_ORDER_LINE                 8
#define GMSH_6_NODE_SECOND_ORDER_TRIANGLE             9
#define GMSH_9_NODE_SECOND_ORDER_QUADRANGLE           10
#define GMSH_10_NODE_SECOND_ORDER_TETRAHEDRON         11
#define GMSH_27_NODE_SECOND_ORDER_HEXAHEDRON          12
#define GMSH_18_NODE_SECOND_ORDER_PRISM               13
#define GMSH_14_NODE_SECOND_ORDER_PYRAMID             14
#define GMSH_1_NODE_POINT                             15
#define GMSH_8_NODE_SECOND_ORDER_QUADRANGLE           16
#define GMSH_20_NODE_SECOND_ORDER_HEXAHEDRON          17
#define GMSH_15_NODE_SECOND_ORDER_PRISM               18
#define GMSH_13_NODE_SECOND_ORDER_PYRAMID             19
#define GMSH_9_NODE_THIRD_ORDER_INCOMPLETE_TRIANGLE   20
#define GMSH_10_NODE_THIRD_ORDER_TRIANGLE             21
#define GMSH_12_NODE_FOURTH_ORDER_INCOMPLETE_TRIANGLE 22
#define GMSH_15_NODE_FOURTH_ORDER_TRIANGLE            23
#define GMSH_15_NODE_FIFTH_ORDER_INCOMPLETE_TRIANGLE  24
#define GMSH_21_NODE_FIFTH_ORDER_COMPLETE_TRIANGLE    25
#define GMSH_4_NODE_THIRD_ORDER_EDGE                  26
#define GMSH_5_NODE_FOURTH_ORDER_EDGE                 27
#define GMSH_6_NODE_FIFTH_ORDER_EDGE                  28
#define GMSH_20_NODE_THIRD_ORDER_TETRAHEDRON          29
#define GMSH_35_NODE_FOURTH_ORDER_TETRAHEDRON         30
#define GMSH_56_NODE_FIFTH_ORDER_TETRAHEDRON          31
#define GMSH_64_NODE_THIRD_ORDER_HEXAHEDRON           92
#define GMSH_125_NODE_FOURTH_ORDER_HEXAHEDRON         93

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

  // INDEXES:
  size_t                            i;                                                              ///< Node index.
  size_t                            j;                                                              ///< Type index.
  size_t                            k;                                                              ///< Element index.
  size_t                            m;                                                              ///< Type node index.
  size_t                            n;                                                              ///< Entity index.

  // SIZES:
  size_t                            nodes;                                                          ///< Number of nodes.
  size_t                            types;                                                          ///< Number of simplex types.
  size_t                            elements;                                                       ///< Number of elements.
  int                               type_nodes;                                                     ///< Number of type_nodes.
  size_t                            entities;                                                       ///< Number of entities.

  // NODE VARIABLES:
  gmsh_node                         node_unit;                                                      ///< Node unit.
  std::vector<size_t>               node_list;                                                      ///< Node list.
  std::vector<double>               node_coordinates;                                               ///< Node coordinates.
  std::vector<double>               node_parametric_coordinates;                                    ///< Node parametric coordinates.
  std::vector<std::vector<size_t> > node_tag;                                                       ///< Node tag.

  // TYPE VARIABLES:
  std::vector<int>                  type_list;                                                      ///< Element type list.
  std::string                       type_name;                                                      ///< Element type name.
  int                               type_dimension;                                                 ///< Element type dimension.
  int                               type_order;                                                     ///< Element type order.
  std::vector<double>               type_node_coordinates;                                          ///< Element type node coordinates.
  int                               type_primary_nodes;                                             ///< Element primary nodes

  // ELEMENT VARIABLES:
  gmsh_element                      element_unit;                                                   ///< Element unit.
  std::vector<std::vector<size_t> > element_tag;                                                    ///< Element tag list.

  // ENTITY VARIABLES:
  std::vector<std::pair<int, int> > entity_list;                                                    ///< Entity list.
  int                               entity_dimension;                                               ///< Entity dimension.
  int                               entity_tag;                                                     ///< Entity tag.

  // GROUP VARIABLES:
  gmsh_group                        group_unit;                                                     ///< Group unit.

  // NEIGHBOUR VARIABLES:
  std::vector<size_t>               neighbour_unit;                                                 ///< Neighbour unit.

public:
  std::vector<gmsh_node>            node;                                                           ///< node[i].
  std::vector<gmsh_element>         element;                                                        ///< element[k].
  std::vector<gmsh_group>           group;                                                          ///< group[i].

  mesh ();

  void                init (
                            std::string loc_file_name                                               ///< GMSH .msh file name.
                           );

  std::vector<size_t> neighbours (
                                  size_t loc_node                                                   ///< Node index.
                                 );

  std::vector<size_t> physical (
                                size_t loc_physical_group_dim,                                      ///< Physical group dimension.
                                size_t loc_physical_group_tag                                       ///< Physical group tag.
                               );

  ~mesh();
};

#endif
