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
  gmsh::option::setNumber ("General.Terminal", 0);                                                  // Not allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  entities = entity_list.size ();                                                                   // Getting number of entities...

  gmsh::model::mesh::renumberNodes ();                                                              // Renumbering the node tags in a continuous sequence...
  gmsh::model::mesh::renumberElements ();                                                           // Renumbering the element tags in a continuous sequence...

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

    nodes.push_back (node_list.size ());                                                            // Getting number of nodes...

    for(n = 0; n < nodes[i]; n++)
    {
      node_scalar.x = node_coordinates[3*n + 0];                                                    // Setting "x" node coordinate...
      node_scalar.y = node_coordinates[3*n + 1];                                                    // Setting "y" node coordinate...
      node_scalar.z = node_coordinates[3*n + 2];                                                    // Setting "z" node coordinate...
      node_scalar.w = 1.0f;                                                                         // Setting "w" node coordinate...
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

    types.push_back (type_list.size ());                                                            // Getting number of types...

    for(j = 0; j < types[i]; j++)
    {
      simplexes_scalar.push_back (simplex_tag_matrix[j].size ());                                   // Getting number of simplexes...

      for(k = 0; k < simplexes_scalar[j]; k++)
      {
        // Getting element type properties:
        gmsh::model::mesh::getElementProperties (
                                                 type_list[j],                                      // Simplex type [#].
                                                 type_name,                                         // Simplex type name [string].
                                                 type_dimension,                                    // Simplex type dimension [#].
                                                 type_order,                                        // Simplex type order [#].
                                                 vertexes,                                          // Simplex type number of vertexes [#].
                                                 type_vertex_coordinates,                           // Simplex type vertexes local coordinates [vector].
                                                 type_primary_nodes                                 // Number of primary vertexes [#].
                                                );

        for(m = 0; m < vertexes; m++)
        {
          simplex_scalar.vertex.push_back ((node_matrix[j][k*vertexes + m]) - 1);                   // Setting simplex vertex index...
        }

        simplex_scalar.type = type_list[j];                                                         // Setting simplex type...
        simplex_vector.push_back (simplex_scalar);                                                  // Setting simplex scalar...
        simplex_scalar.vertex.clear ();                                                             // Clearing vertex vector for next simplex...
      }

      simplex_matrix.push_back (simplex_vector);                                                    // Setting simplex vector...
    }

    simplexes.push_back (simplexes_scalar);
    simplexes_scalar.clear ();
    node.push_back (node_vector);                                                                   // Setting node vector...
    simplex.push_back (simplex_matrix);                                                             // Setting simplex matrix...
  }

  // Finding complexes for each node in each entity = finding the indexes of all simplexes having the node "n" in them:
  for(i = 0; i < entities; i++)
  {
    for(n = 0; n < nodes[i]; n++)
    {
      for(j = 0; j < types[i]; j++)
      {
        for(k = 0; k < simplexes[i][j]; k++)
        {
          for(m = 0; m < simplex[i][j][k].vertex.size (); m++)
          {
            if(simplex[i][j][k].vertex[m] == n)
            {
              complex_scalar.push_back (i*entities*types[i] + j*types[i] + k);                      // Setting complex scalar...
              neighbour_scalar.insert (
                                       neighbour_scalar.end (),
                                       simplex[i][j][k].vertex.begin (),
                                       simplex[i][j][k].vertex.end ()
                                      );
            }
          }
        }
      }

      neighbour_scalar.resize (
                               std::distance (
                                              neighbour_scalar.begin (),
                                              std::unique (
                                                           neighbour_scalar.begin (),
                                                           neighbour_scalar.begin () +
                                                           neighbour_scalar.size ()
                                                          )
                                             )
                              );
      complex_vector.push_back (complex_scalar);                                                    // Setting complex vector...
      complex_scalar.clear ();                                                                      // Clearing complex scalar for next complex...
      neighbour_vector.push_back (neighbour_scalar);
      neighbour_scalar.clear ();
    }

    complex.push_back (complex_vector);                                                             // Setting complex vector...
    complex_vector.clear ();                                                                        // Clearing complex vector for next complex...
    neighbour.push_back (neighbour_vector);
    neighbour_vector.clear ();
  }

  baseline->done ();                                                                                // Printing message...
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
