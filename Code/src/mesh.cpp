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
}

void mesh::init (
                 std::string loc_file_name                                                          // GMSH .msh file name.
                )
{
  entities = 0;                                                                                     // Resetting number of entities...
  neutrino::action ("initializing GMSH...");                                                        // Printing message...
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
      node_unit.x = (float)node_coordinates[3*i + 0];                                               // Setting node unit "x" coordinate...
      node_unit.y = (float)node_coordinates[3*i + 1];                                               // Setting node unit "y"coordinate...
      node_unit.z = (float)node_coordinates[3*i + 2];                                               // Setting node unit "z" coordinate...
      node_unit.w = 1.0f;                                                                           // Setting node unit "w" coordinate...
      node.push_back (node_unit);                                                                   // Adding node unit to node vector...
    }

    // Getting entity elements, where:
    // i = index of element type.
    // j = index of nodes per element, for each element type.
    // L = number of element types.
    // M(i) = number of elements per element type.
    // N(j) = number of nodes per element, for each element type.
    gmsh::model::mesh::getElements (
                                    type_list,                                                      // Element type list [L].
                                    element_tag,                                                    // Element tag list LxM(i).
                                    node_tag,                                                       // Node tag list Lx[N(1),N(2),...,N(j),N(M(i))].
                                    entity_dimension,                                               // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types = type_list.size ();                                                                      // Getting number of types...

    for(j = 0; j < types; j++)
    {
      elements = element_tag[j].size ();                                                            // Getting number of elements...

      for(k = 0; k < elements; k++)
      {
        // Getting element type properties:
        gmsh::model::mesh::getElementProperties (
                                                 type_list[j],                                      // Element type [#].
                                                 type_name,                                         // Element type name [string].
                                                 type_dimension,                                    // Element type dimension [#].
                                                 type_order,                                        // Element type order [#].
                                                 type_nodes,                                        // Element type number of type nodes [#].
                                                 type_node_coordinates,                             // Element type node local coordinates [vector].
                                                 type_primary_nodes                                 // Number of primary type nodes [#].
                                                );

        for(m = 0; m < type_nodes; m++)
        {
          element_unit.node.push_back ((node_tag[j][k*type_nodes + m]) - 1);                        // Adding type node to element unit...
        }

        element_unit.type = type_list[j];                                                           // Setting element unit type...
        element.push_back (element_unit);                                                           // Adding element[k] to element vector...
        element_unit.node.clear ();                                                                 // Clearing element unit node vector...
      }
    }
  }

  // Finding groups for each node:
  for(i = 0; i < node.size (); i++)
  {
    for(k = 0; k < element.size (); k++)
    {
      for(m = 0; m < element[k].node.size (); m++)
      {
        if(element[k].node[m] == i)
        {
          group_unit.element.push_back (k);                                                         // Adding element index to group unit...
        }
      }
    }

    group.push_back (group_unit);                                                                   // Adding group unit to group vector...
    group_unit.element.clear ();                                                                    // Clearing group unit element vector...
  }

  neighbours = 0;                                                                                   // Resetting number of neighbours...

  for(i = 0; i < node.size (); i++)
  {
    neighbour_unit = this->neighbour (i);                                                           // Getting neighbourhood indices...
    neighbourhood.insert (
                          neighbourhood.end (),
                          neighbour_unit.begin (),
                          neighbour_unit.end ()
                         );                                                                         // Building neighbour tuple...
    neighbours    += neighbour_unit.size ();                                                        // Counting neighbour nodes...
    offset.push_back (neighbours);                                                                  // Setting neighbour offset...
  }

  neutrino::done ();                                                                                // Printing message...
}

std::vector<size_t> mesh::neighbour (
                                     size_t loc_node                                                // Central node index [x].
                                    )
{
  neighbour_unit.clear ();

  for(k = 0; k < element.size (); k++)
  {
    for(m = 0; m < element[k].node.size (); m++)
    {
      if(element[k].node[m] == loc_node)
      {
        // Appending element[i] type nodes in neighbour unit:
        neighbour_unit.insert (
                               neighbour_unit.end (),                                               // Insertion point.
                               element[k].node.begin (),                                            // Beginning of vector to be appended.
                               element[k].node.end ()                                               // End of vector to be appended.
                              );

        // Erasing central node from neighbourhood:
        neighbour_unit.erase (
                              neighbour_unit.end () -                                               // Insertion point.
                              element[k].node.size () +                                             // Number of type nodes.
                              m                                                                     // Central node.
                             );
      }
    }
  }

  // Eliminating repeated indexes:
  std::sort (neighbour_unit.begin (), neighbour_unit.end ());
  neighbour_unit.resize (
                                                                                                    // Eliminating null indexes...
                         std::distance (
                                                                                                    // Calculating index distance...
                                        neighbour_unit.begin (),
                                        std::unique (
                                                                                                    // Finding unique indexes...
                                                     neighbour_unit.begin (),                       // Beginning of index vector.
                                                     neighbour_unit.end ()                          // End of index vector.
                                                    )
                                       )
                        );

  return (neighbour_unit);                                                                          // Returning neighbour unit vector...
}

std::vector<size_t> mesh::physical (
                                    size_t loc_physical_group_dim,                                  // Physical group dimension [#].
                                    size_t loc_physical_group_tag                                   // Physical group tag [#].
                                   )
{
  std::vector<size_t> loc_node_tags;                                                                // Node tags.
  std::vector<double> loc_node_coordinates;                                                         // Node coordinates.

  // Getting nodes for given physical group:
  gmsh::model::mesh::getNodesForPhysicalGroup (
                                               loc_physical_group_dim,                              // Physical group dimension.
                                               loc_physical_group_tag,                              // Physical group tag.
                                               loc_node_tags,                                       // Node tags.
                                               loc_node_coordinates                                 // Node coordinates.
                                              );

  // Adjusting node index according to Neutrino (1st index = 0):
  for(size_t i = 0; i < loc_node_tags.size (); i++)
  {
    loc_node_tags[i]--;                                                                             // Adjusting node index...
  }

  loc_node_coordinates.clear ();                                                                    // Clearing unnecessary coordinates vector...
  return (loc_node_tags);                                                                           // Returning node index vector...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
