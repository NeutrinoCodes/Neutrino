/// @file     algebraic_topology.hpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class based on GMSH.
///
/// @details  **GMSH** (http://gmsh.info) is "a three-dimensional finite element mesh generator
/// with built-in pre- and post-processing facilities".
/// Neutrino reads GMSH files and reconstructs a simplicial complex out of it.
/// The simplicial complex is used for both computational and rendering purposes.

#ifndef algebraic_topology_hpp
#define algebraic_topology_hpp

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
/// @details  This structure is used as data storage in the neighbour array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_neighbour
{
  std::vector<size_t> index;                                                                        ///< Neighbour indexes.
} gmsh_neighbour;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the simplex array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_simplex
{
  std::vector<size_t> vertex;                                                                       ///< Vertex indexes.
  int type;                                                                                         ///< Simplex type.
} gmsh_simplex;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the complex array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmsh_complex
{
  std::vector<size_t> simplex;                                                                      ///< Simplex indexes.
} gmsh_complex;
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
class mesh                                                                                          /// @brief **Mesh.**
{
private:
  neutrino*                              baseline;                                                  ///< @brief **Neutrino baseline.**

  // TENSOR INDEXES:
  size_t                                 i;                                                         ///< Node index.
  size_t                                 j;                                                         ///< Type index.
  size_t                                 k;                                                         ///< Simplex index.
  size_t                                 m;                                                         ///< Vertex index.
  size_t                                 n;                                                         ///< Entity index.

  // TENSOR SIZES:
  size_t                                 entities;                                                  ///< Number of entities.
  size_t                                 nodes;                                                     ///< Number of nodes.
  size_t                                 types;                                                     ///< Number of simplex types.
  size_t                                 simplexes;                                                 ///< Number of simplexes.
  int                                    vertexes;                                                  ///< Number of vertexes.

  // ENTITY VARIABLES:
  std::vector<std::pair<int, int> >      entity_list;                                               ///< Entity list.
  int                                    entity_dimension;                                          ///< Entity dimension.
  int                                    entity_tag;                                                ///< Entity tag.

  // NODE VARIABLES:
  gmsh_node                              node_structure;                                            ///< Node structure.
  std::vector<std::size_t>               node_list;                                                 ///< Node list.
  std::vector<double>                    node_coordinates;                                          ///< Node coordinates.
  std::vector<double>                    node_parametric_coordinates;                               ///< Node parametric coordinates.
  std::vector<std::vector<std::size_t> > node_tag;                                                  ///< Node tag.

  // TYPE VARIABLES:
  std::vector<int>                       type_list;                                                 ///< Simplex type list.
  std::string                            type_name;                                                 ///< Simplex type name.
  int                                    type_dimension;                                            ///< Simplex type dimension.
  int                                    type_order;                                                ///< Simplex type order.
  std::vector<double>                    type_vertex_coordinates;                                   ///< Simplex vertex coordinates.
  int                                    type_primary_nodes;                                        ///< Simplex primary nodes

  // SIMPLEX VARIABLES:
  gmsh_simplex                           simplex_structure;                                         ///< Simplex structure.
  std::vector<std::vector<std::size_t> > simplex_tag;                                               ///< Simplex tag list.

  // COMPLEX VARIABLES:
  gmsh_complex                           complex_structure;                                         ///< Complex structure.

  // NEIGHBOUR VARIABLES:
  gmsh_neighbour                         neighbour_structure;                                       ///< Neighbour structure.

public:
  std::vector<gmsh_node>                 node;                                                      ///< node[i].
  std::vector<gmsh_simplex>              simplex;                                                   ///< simplex[k].
  std::vector<gmsh_complex>              complex;                                                   ///< complex[i].
  std::vector<gmsh_neighbour>            neighbour;                                                 ///< neighbour[i].

  mesh ();

  void init (
             neutrino*   loc_baseline,                                                              ///< Neutrino baseline.
             std::string loc_file_name                                                              ///< GMSH .msh file name.
            );

  ~mesh();
};

#endif
