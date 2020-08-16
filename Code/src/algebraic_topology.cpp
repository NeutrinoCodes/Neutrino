/// @file     algebraic_topology.cpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class.

#include "algebraic_topology.hpp"

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
  gmsh::model::getEntities (entity);                                                                // Getting entity list...
  entities = entity.size ();                                                                        // Getting number of entities...

  gmsh::model::mesh::renumberNodes ();                                                              // Renumbering the node tags in a continuous sequence...
  gmsh::model::mesh::renumberElements ();                                                           // Renumbering the element tags in a continuous sequence...

  for(i = 0; i < entities; i++)
  {
    entity_dimension = entity[i].first;                                                             // Getting entity dimension [#]...
    entity_tag       = entity[i].second;                                                            // Getting entity tag [#]...

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

    nodes.push_back (node_list.size ());                                                            // Pushing number of nodes...

    for(n = 0; n < nodes[i]; n++)
    {
      node_i_n.x = node_coordinates[3*n + 0];                                                       // Setting "x" node[i][n] slice coordinate...
      node_i_n.y = node_coordinates[3*n + 1];                                                       // Setting "y" node[i][n] slice coordinate...
      node_i_n.z = node_coordinates[3*n + 2];                                                       // Setting "z" node[i][n] slice coordinate...
      node_i_n.w = 1.0f;                                                                            // Setting "w" node[i][n] slice coordinate...
      node_i.push_back (node_i_n);                                                                  // Pushing node[i][n] slice to node[i] slice...
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
                                    node_tag,                                                       // Node tag matrix Lx[N(1),N(2),...,N(j),N(M(i))].
                                    entity_dimension,                                               // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types.push_back (type_list.size ());                                                            // Getting number of types...

    for(j = 0; j < types[i]; j++)
    {
      simplexes_i.push_back (simplex_tag_matrix[j].size ());                                        // Getting number of simplexes...

      for(k = 0; k < simplexes_i[j]; k++)
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
          simplex_i_j_k_m.vertex.push_back ((node_tag[j][k*vertexes + m]) - 1);                     // Setting simplex[i][j][k][m] slice vertex index...
        }

        simplex_i_j_k_m.type = type_list[j];                                                        // Setting simplex[i][j][j][m] slice type...
        simplex_i_j_k.push_back (simplex_i_j_k_m);                                                  // Pushing simplex[i][j][j][m] slice to simplex[i][j][k] slice...
        simplex_i_j_k_m.vertex.clear ();                                                            // Clearing vertex vector for next simplex...
      }

      simplex_i_j.push_back (simplex_i_j_k);                                                        // Pushing simplex[i][j][k] slice to simplex[i][j] slice...
    }

    simplexes.push_back (simplexes_i);
    simplexes_i.clear ();
    node.push_back (node_i);                                                                        // Setting node vector...
    simplex.push_back (simplex_i_j);                                                                // Setting simplex matrix...
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
              complex_i_n_j_k_m.push_back (i*entities*types[i] + j*types[i] + k);                   // Setting complex scalar...
              neighbour_i_n_j_k_m.insert (
                                          neighbour_i_n_j_k_m.end (),
                                          simplex[i][j][k].vertex.begin (),
                                          simplex[i][j][k].vertex.end ()
                                         );
            }
          }
        }
      }

      neighbour_i_n_j_k_m.resize (
                                  std::distance (
                                                 neighbour_i_n_j_k_m.begin (),
                                                 std::unique (
                                                              neighbour_i_n_j_k_m.begin (),
                                                              neighbour_i_n_j_k_m.begin () +
                                                              neighbour_i_n_j_k_m.size ()
                                                             )
                                                )
                                 );
      complex_i_n_j_k.push_back (complex_i_n_j_k_m);                                                // Setting complex vector...
      complex_i_n_j_k_m.clear ();                                                                   // Clearing complex scalar for next complex...
      neighbour_i_n_j_k.push_back (neighbour_i_n_j_k_m);
      neighbour_i_n_j_k_m.clear ();
    }

    complex.push_back (complex_i_n_j_k);                                                            // Setting complex vector...
    complex_i_n_j_k.clear ();                                                                       // Clearing complex vector for next complex...
    neighbour.push_back (neighbour_i_n_j_k);
    neighbour_i_n_j_k.clear ();
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
