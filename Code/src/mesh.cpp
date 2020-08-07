/// @file     mesh.cpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class.

#include "mesh.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "mesh" class /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::mesh()
{
  entities = 0;                                                                                     // Resetting number of entities...
}

void mesh::init (
                 neutrino*   loc_baseline,                                                          ///< Neutrino baseline.
                 std::string loc_file_name                                                          ///< GMSH .msh file name.
                )
{
  baseline = loc_baseline;                                                                          // Getting Neutrino baseline...
  baseline->action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  entities = entity_list.size ();                                                                   // Getting number of entities...

  for(i = 0; i < entities; i++)
  {
    entity_dimension = entity_list[i].first;                                                        // Getting entity dimension [#]...
    entity_tag       = entity_list[i].second;                                                       // Getting entity tag [#]...

    // Getting entity nodes, where:
    // N = number of nodes
    // dim = entity dimension
    gmsh::model::mesh::getNodes (
                                 node_list,                                                         // Node tags list [N].
                                 node_coordinates,                                                  // Node coordinates list [3*N].
                                 node_parametric_coordinates,                                       // Node parametric coordinates [dim*N].
                                 entity_dimension,                                                  // Entity dimension [#].
                                 entity_tag                                                         // Entity tag [#].
                                );

    nodes = node_list.size ();                                                                      // Getting number of nodes...

    for(n = 0; n < nodes; n++)
    {
      node_scalar.x   = node_coordinates[3*n + 0];                                                  // Setting "x" node coordinate...
      node_scalar.y   = node_coordinates[3*n + 1];                                                  // Setting "y" node coordinate...
      node_scalar.z   = node_coordinates[3*n + 2];                                                  // Setting "z" node coordinate...
      node_scalar.tag = node_list[n];                                                               // Setting node tag...
      node_vector.push_back (node_scalar);                                                          // Setting node vector...
    }

    // Getting entity simplexes, where:
    // i = index of simplex type.
    // j = index of nodes per simplex, for each simplex type.
    // L = number of simplex types.
    // M(i) = number of simplexes per simplex type.
    // N(j) = number of nodes per simplex, for each simplex type.
    gmsh::model::mesh::getElements (
                                    type_list,                                                      // Element type list [L].
                                    simplex_tag_matrix,                                             // Simplex tag matrix LxM(i).
                                    node_matrix,                                                    // Node tag matrix Lx[N(1),N(2),...,N(j),N(M(i))].
                                    entity_dimension,                                               // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types = type_list.size ();                                                                      // Getting number of types...

    for(j = 0; j < types; j++)
    {
      simplexes = simplex_tag_matrix[j].size ();                                                    // Getting number of simplexes...

      for(k = 0; k < simplexes; k++)
      {
        // Getting element type properties:
        gmsh::model::mesh::getElementProperties (
                                                 type_list[j],                                      // Simplex type [#].
                                                 type_name,                                         // Simplex type name [string].
                                                 type_dimension,                                    // Simplex type dimension [#].
                                                 type_order,                                        // Simplex type order [#].
                                                 vertexes,                                          // Simplex type number of vertexes [#].
                                                 type_vertex_coordinates,                           // Simplex type vetexes local coordinates [vector].
                                                 type_primary_nodes                                 // Number of primary vertexes [#].
                                                );

        for(m = 0; m < vertexes; m++)
        {
          simplex_scalar.vertex.push_back (node_matrix[j][k*vertexes + m]);                         // Setting simplex vertex...
        }

        simplex_scalar.type = type_list[j];                                                         // Setting simplex type...
        simplex_scalar.size = vertexes;                                                             // Setting simplex number of vetexes...
        simplex_scalar.tag  = simplex_tag_matrix[j][k];                                             // Setting simplex tag...
      }

      simplex_vector.push_back (simplex_scalar);                                                    // Setting simplex scalar...
    }

    simplex_matrix.push_back (simplex_vector);                                                      // Setting simplex vector...
  }

  node.push_back (node_vector);                                                                     // Setting node vector...
  simplex.push_back (simplex_matrix);                                                               // Setting simplex matrix...

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
