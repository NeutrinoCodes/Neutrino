/// @file     mesh.hpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class based on GMSH.
///
/// @details  **GMSH** (http://gmsh.info) is "a three-dimensional finite element mesh generator
/// with built-in pre- and post-processing facilities".
/// Neutrino reads GMSH files and reconstructs a simplicial complex out of it.
/// The simplicial complex is used for both computational and rendering purposes.

#ifndef mesh_hpp
#define mesh_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"
#include <gmsh.h>

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the node array. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _gmhs_node
{
  cl_float x;                                                                                       ///< Node "x" coordinate.
  cl_float y;                                                                                       ///< Node "y" coordinate.
  cl_float z;                                                                                       ///< Node "z" coordinate.
  size_t tag;                                                                                       ///< Node tag.
} gmsh_node;
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
  neutrino*                                            baseline;                                    ///< @brief **Neutrino baseline.**

  size_t                                               entity;                                      ///< Entity index.
  size_t                                               type;                                        ///< Type index.
  size_t                                               element;                                     ///< Element index.
  size_t                                               node;                                        ///< Node index.
  size_t                                               vertex;                                      ///< Vertex index.
  size_t                                               simplex;                                     ///< Simplex index.

  int                                                  entity_dimension;                            ///< Entity dimension.
  int                                                  entity_tag;                                  ///< Entity tag.

  std::vector<std::pair<int, int> >                    entity_list;                                 ///< Entity list.

  std::vector<int>                                     type_list;                                   ///< Element type list...
  std::vector<std::size_t>                             node_list;                                   ///< Node tags list...

  std::vector<std::vector<std::size_t> >               element_array;                               ///< Element tags array...
  std::vector<std::vector<std::size_t> >               node_array;                                  ///< Element node tags array...

  std::vector<std::size_t>                             simplexTags_list;                            ///< Simplex tags list...
  std::vector<double>                                  node_coordinates;                            ///< Node coordinates array...
  std::vector<double>                                  node_parametric_coordinates;                 ///< Node parametric coordinates.



  std::string                                          elemName;                                    ///< Element name...
  int                                                  order;

  int                                                  nodes_num;
  int                                                  vertexes_num;
  int                                                  nodeTags_num;

  int                                                  elemTags_num;
  int                                                  elements;
  int                                                  numPrimaryNodes;
  std::vector<double>                                  param;
  int                                                  d;

public:
  size_t                                               entities;                                    ///< Number of entities.
  std::vector<std::size_t>                             complexes;                                   ///< Number of complexes.
  std::vector<std::vector<std::vector<std::size_t> > > simplexes;                                   ///< Number of simplexes.
  std::vector<std::vector<int> >                       types;                                       ///< Number of types.
  std::vector<std::size_t>                             vertexes;                                    ///< Number of vertexes.

  std::vector<std::vector<gmsh_node> >                 nodes;                                       ///< Number of nodes.

  mesh ();

  void init (
             neutrino*   loc_baseline,                                                              ///< Neutrino baseline.
             std::string loc_file_name                                                              ///< GMSH .msh file name.
            );

  void read_msh (
                 float4G* loc_node,                                                                 ///< GMSH node coordinates.
                 int1*    loc_simplex,                                                              ///< GMSH simplex: node index list.
                 int1*    loc_simplex_stride,                                                       ///< GMSH simplex: strides.
                 int1*    loc_complex,                                                              ///< GMSH complex: simplex index list.
                 int1*    loc_complex_stride                                                        ///< GMSH complex: strides.
                );

  ~mesh();
};

#endif
