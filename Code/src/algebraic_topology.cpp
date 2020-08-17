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

  for(n = 0; n < entities; n++)
  {
    entity_dimension = entity_list[n].first;                                                        // Getting entity dimension [#]...
    entity_tag       = entity_list[n].second;                                                       // Getting entity tag [#]...

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

    for(i = 0; i < nodes; i++)
    {
      node_structure.x = node_coordinates[3*i + 0];                                                 // Setting node structure "x" coordinate...
      node_structure.y = node_coordinates[3*i + 1];                                                 // Setting node structure "y"coordinate...
      node_structure.z = node_coordinates[3*i + 2];                                                 // Setting node structure "z" coordinate...
      node_structure.w = 1.0f;                                                                      // Setting node structure "w" coordinate...
      node.push_back (node_structure);                                                              // Adding node structure to node vector...
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
          simplex_structure.vertex.push_back ((node_tag[j][k*vertexes + m]) - 1);                   // Adding vertex to simplex structure...
        }

        simplex_structure.type = type_list[j];                                                      // Setting simplex structure type...
        simplex.push_back (simplex_structure);                                                      // Adding simplex[k] to simplex vector...
        simplex_structure.vertex.clear ();                                                          // Clearing simplex structure vertex vector...
      }
    }
  }

  // Finding complexes for each node:
  for(i = 0; i < node.size (); i++)
  {
    for(k = 0; k < simplex.size (); k++)
    {
      for(m = 0; m < simplex[k].vertex.size (); m++)
      {
        if(simplex[k].vertex[m] == i)
        {
          complex_structure.simplex.push_back (k);                                                  // Adding simplex index to complex structure...

          // Appending simplex[i] vertexes in neighbour structure:
          neighbour_structure.index.insert (
                                            neighbour_structure.index.end (),                       // Insertion point.
                                            simplex[k].vertex.begin (),                             // Beginning of vector to be appended.
                                            simplex[k].vertex.end ()                                // End of vector to be appended.
                                           );

          // Erasing central node from neighbourhood:
          neighbour_structure.index.erase (
                                           neighbour_structure.index.end () -                       // Insertion point.
                                           simplex[k].vertex.size () +                              // Number of vertexes.
                                           m                                                        // Central node.
                                          );
        }
      }
    }

    // Eliminating repeated indexes:
    std::sort (neighbour_structure.index.begin (), neighbour_structure.index.end ());
    neighbour_structure.index.resize (
                                                                                                    // Eliminating null indexes...
                                      std::distance (
                                                                                                    // Calculating index distance...
                                                     neighbour_structure.index.begin (),
                                                     std::unique (
                                                                                                    // Finding unique indexes...
                                                                  neighbour_structure.index.
                                                                  begin (),                         // Beginning of index vector.
                                                                  neighbour_structure.index.
                                                                  end ()                            // End of index vector.
                                                                 )
                                                    )
                                     );

    complex.push_back (complex_structure);                                                          // Adding complex structure to complex vector...
    complex_structure.simplex.clear ();                                                             // Clearing complex structure simplex vector...
    neighbour.push_back (neighbour_structure);                                                      // Adding neighbour structure to neighbour vector...
    neighbour_structure.index.clear ();                                                             // Clearing neighbour structure index vector...
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
