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
  size_t                                 i;                                                         ///< Index.
  size_t                                 j;                                                         ///< Index.
  size_t                                 k;                                                         ///< Index.
  size_t                                 i_node;                                                    ///< Neutrino node index.
  size_t                                 i_simplex;                                                 ///< Neutrino simplex index.
  size_t                                 n;                                                         ///< Index.
  int                                    dim;                                                       ///< Entity dimension.
  int                                    tag;                                                       ///< Entity tag.
  std::vector<std::pair<int, int> >      entities;                                                  ///< Entity array.
  std::vector<std::size_t>               nodeTags;                                                  ///< Node tags array...
  std::vector<std::size_t>               nodeList;                                                  ///< Node tags full array...
  std::vector<double>                    nodeCoords;                                                ///< Node coordinates array...
  std::vector<double>                    nodeParams;
  std::vector<int>                       elemTypes;                                                 ///< Element type array...
  std::vector<std::vector<std::size_t> > elemTags;                                                  ///< Element tags array...
  std::vector<std::vector<std::size_t> > elemNodeTags;                                              ///< Element node tags array...
  std::string                            elemName;                                                  ///< Element name...
  int                                    order;
  int                                    numNodes;
  int                                    numPrimaryNodes;
  std::vector<double>                    param;
  int                                    d;

public:
  size_t                                 node_num;                                                  ///< Number of mesh nodes.
  size_t                                 simplex_num;                                               ///< Number of mesh simplexes.
  size_t                                 complex_num;                                               ///< Number of mesh complexes.

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
