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
  size_t                                 entity;                                                    ///< Entity index.
  size_t                                 type;                                                      ///< Type index.
  size_t                                 element;                                                   ///< Element index.
  size_t                                 node;                                                      ///< Node index.
  size_t                                 vertex;                                                    ///< Vertex index.
  size_t                                 simplex;                                                   ///< Simplex index.
  int                                    dim;                                                       ///< Entity dimension.
  int                                    tag;                                                       ///< Entity tag.
  std::vector<std::pair<int, int> >      entity_list;                                               ///< Entity list.
  std::vector<std::size_t>               nodeTags;                                                  ///< Node tags array...
  std::vector<std::size_t>               nodeTags_list;                                             ///< Node tags list...
  std::vector<std::size_t>               simplexTags_list;                                          ///< Simplex tags list...
  std::vector<double>                    nodeCoords;                                                ///< Node coordinates array...
  std::vector<double>                    nodeParams;
  std::vector<int>                       type_list;                                                 ///< Element type list...
  std::vector<std::vector<std::size_t> > element_list;                                              ///< Element tags list...
  std::vector<std::vector<std::size_t> > elemNodeTags;                                              ///< Element node tags array...
  std::string                            elemName;                                                  ///< Element name...
  int                                    order;
  int                                    entities;
  int                                    nodes_num;
  int                                    vertexes_num;
  int                                    nodeTags_num;
  int                                    types;
  int                                    elemTags_num;
  int                                    elements;
  int                                    numPrimaryNodes;
  std::vector<double>                    param;
  int                                    d;

public:
  size_t                                 nodes;                                                     ///< Number of nodes.
  size_t                                 simplexes;                                                 ///< Number of simplexes.
  size_t                                 vertexes;                                                  ///< Number of vertexes.
  size_t                                 complexes;                                                 ///< Number of complexes.

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
