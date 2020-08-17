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
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  gmsh::model::mesh::renumberNodes ();                                                              // Renumbering the node tags in a continuous sequence...
  gmsh::model::mesh::renumberElements ();                                                           // Renumbering the element tags in a continuous sequence...

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
      node_structure.x = node_coordinates[3*n + 0];                                                 // Setting node[i] "x" coordinate...
      node_structure.y = node_coordinates[3*n + 1];                                                 // Setting node[i] "y"coordinate...
      node_structure.z = node_coordinates[3*n + 2];                                                 // Setting node[i] "z" coordinate...
      node_structure.w = 1.0f;                                                                      // Setting node[i] "w" coordinate...
      node.push_back (node_structure);                                                              // Pushing node[i] to node vector...
    }

    // Getting entity simplexes, where:
    // i = index of simplex type.
    // j = index of nodes per simplex, for each simplex type.
    // L = number of simplex types.
    // M(i) = number of simplexes per simplex type.
    // N(j) = number of nodes per simplex, for each simplex type.
    gmsh::model::mesh::getElements (
                                    type_list,                                                      // Element type list [L].
                                    simplex_tag,                                                    // Simplex tag list LxM(i).
                                    node_tag,                                                       // Node tag list Lx[N(1),N(2),...,N(j),N(M(i))].
                                    entity_dimension,                                               // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types = type_list.size ();                                                                      // Getting number of types...

    for(j = 0; j < types; j++)
    {
      simplexes = simplex_tag[j].size ();                                                           // Getting number of simplexes...

      for(k = 0; k < simplexes; k++)
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
          simplex_structure.vertex.push_back ((node_tag[j][k*vertexes + m]) - 1);                   // Setting simplex[i] vertex index...
        }

        simplex_structure.type = type_list[j];                                                      // Setting simplex[i] type...
        simplex.push_back (simplex_structure);                                                      // Pushing simplex[i] to simplex vector...
        simplex_structure.vertex.clear ();                                                          // Clearing vertex vector for next simplex...
      }
    }
  }

  // Finding complexes for each node in each entity = finding the indexes of all simplexes having the node "n" in them:
    for(n = 0; n < node.size();n++)
    {
        for(i = 0; i < simplex.size(); i++)
        {
          for(m = 0; m < simplex[i].vertex.size (); m++)
          {
            if(simplex[i].vertex[m] == n)
            {
              complex_structure.simplex.push_back (i);                   // Pushing simplex index ot complex structure...

              // Appending simplex[i][j][k] vertexes in neighbour[i][n][j][k][m] slice:
              neighbour_i_n_j_k_m.insert (
                                          neighbour_i_n_j_k_m.end (),                               // Beginning of append = end of current neighbour slice.
                                          simplex[i][j][k].vertex.begin (),                         // Beginning of slice to be appended.
                                          simplex[i][j][k].vertex.end ()                            // End of slice to be appended.
                                         );

              // Erasing central node from neighbourhood:
              neighbour_i_n_j_k_m.erase (
                                         neighbour_i_n_j_k_m.end () -                               // Beginning of erase = end of current neighbour slice.
                                         simplex[i][j][k].vertex.size () +                          // Number of vertexes.
                                         m                                                          // Central node.
                                        );

            }
          }
        }
      }

      // Eliminating repeated indexes:
      neighbour_i_n_j_k_m.resize (
                                                                                                    // Eliminating null indexes...
                                  std::distance (
                                                                                                    // Calculating index distance...
                                                 neighbour_i_n_j_k_m.begin (),
                                                 std::unique (
                                                                                                    // Finding unique indexes...
                                                              neighbour_i_n_j_k_m.begin (),         // Beginning of index slice.
                                                              neighbour_i_n_j_k_m.end ()            // End of index slice.
                                                             )
                                                )
                                 );

      complex_i_n_j_k.push_back (complex_i_n_j_k_m);                                                // Pushing complex[i][n][j][k][m] slice to complex[i][n][j][k] slice...
      complex_i_n_j_k_m.clear ();                                                                   // Clearing complex[i][n][j][k][m] slice...
      neighbour_i_n_j_k.push_back (neighbour_i_n_j_k_m);                                            // Pushing neighbour[i][n][j][k][m] slice to neighbour[i][n][j][k] slice...
      neighbour_i_n_j_k_m.clear ();                                                                 // Clearing neighbour[i][n][j][k][m] slice...
    }

    complex.push_back (complex_i_n_j_k);                                                            // Setting complex vector...
    complex_i_n_j_k.clear ();                                                                       // Clearing complex vector for next complex...
    neighbour.push_back (neighbour_i_n_j_k);                                                        // Pushing neighbour[i][n][j][k] slice to neighbour tensor...
    neighbour_i_n_j_k.clear ();                                                                     // Clearing neighbour[i][n][j][k] slice...
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
