/// @file     mesh.cpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class.

#include "mesh.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "mesh" class /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::mesh(
           std::string loc_file_name                                                                // GMSH .msh file name.
          )
{
  entities             = 0;                                                                         // Resetting number of entities...
  neutrino::action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 0);                                                  // Not allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  gmsh::model::mesh::renumberNodes ();                                                              // Renumbering the node tags in a continuous sequence...
  gmsh::model::mesh::renumberElements ();                                                           // Renumbering the element tags in a continuous sequence...

  entities             = entity_list.size ();                                                       // Getting number of entities...

  entity_dimension_max = entity_list[0].first;

  for(n = 0; n < entities; n++)
  {
    entity_dimension.push_back (entity_list[n].first);
    std::cout << "entity dimension = " << entity_dimension[n] << std::endl;

    if(entity_dimension[n] > entity_dimension_max)
    {
      entity_dimension_max = entity_dimension[n];
    }
  }

  std::cout << "entity dimension max = " << entity_dimension_max << std::endl;

  for(d = 0; d < (entity_dimension_max + 1); d++)
  {
    e = 0;

    for(n = 0; n < entities; n++)
    {
      if(entity_list[n].first == d)
      {
        entity_index.push_back (e);
        std::cout << "entity index = " << e << std::endl;
        e++;
      }
    }

    element.push_back ({});                                                                         // Creating element "dimension" placeholder...
    node.push_back ({});                                                                            // Creating node "dimension" placeholder...
    group.push_back ({});                                                                           // Creating group "dimension" placeholder...
    neighbourhood.push_back ({});                                                                   // Creating group "dimension" placeholder...
    offset.push_back ({});                                                                          // Creating offset "dimension" placeholder...
    link.push_back ({});                                                                            // Creating link "dimension" placeholder...

    for(e = 0; e < entity_index.size (); e++)
    {
      element[d].push_back ({});                                                                    // Creating element "tag" placeholder...
      node[d].push_back ({});                                                                       // Creating node "tag" placeholder...
      group[d].push_back ({});                                                                      // Creating group "tag" placeholder...
      neighbourhood[d].push_back ({});                                                              // Creating group "tag" placeholder...
      offset[d].push_back ({});                                                                     // Creating offset "tag" placeholder...
      link[d].push_back ({});                                                                       // Creating link "tag" placeholder...
    }
  }

  for(n = 0; n < entities; n++)
  {
    d          = entity_dimension[n];                                                               // Getting entity dimension [#]...
    e          = entity_index[n];
    entity_tag = entity_list[n].second;                                                             // Getting entity tag [#]...

    std::cout << "d = " << d << " e = " << e << std::endl;

    // Getting entity nodes, where:
    // N = number of nodes
    // dim = entity dimension
    gmsh::model::mesh::getNodes (
                                 node_list,                                                         // Node tags list [N].
                                 node_coordinates,                                                  // Node coordinates list [3*N].
                                 node_parametric_coordinates,                                       // Node parametric coordinates [dim*N].
                                 d,                                                                 // Entity dimension [#].
                                 entity_tag                                                         // Entity tag [#].
                                );

    nodes = node_list.size ();                                                                      // Getting number of nodes...

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
                                    d,                                                              // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types = type_list.size ();                                                                      // Getting number of types...

    element[d][e].push_back ({});                                                                   // Creating "0_th" element placeholder ("j" starts from "1")...
    node[d][e].push_back ({});                                                                      // Creating "0_th" node placeholder ("j" starts from "1")...
    group[d][e].push_back ({});                                                                     // Creating "0_th" group placeholder ("j" starts from "1")...
    neighbourhood[d][e].push_back ({});                                                             // Creating "0_th" group placeholder ("j" starts from "1")...
    offset[d][e].push_back ({});                                                                    // Creating "0_th" offset placeholder ("j" starts from "1")...
    link[d][e].push_back ({});                                                                      // Creating "0_th" link placeholder ("j" starts from "1")...

    // For each element type in the entity's type list:
    for(t = 0; t < types; t++)
    {
      // For each GMSH's element type:
      for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
      {
        element[d][e].push_back ({});                                                               // Creating "j_th" element placeholder...
        node[d][e].push_back ({});                                                                  // Creating "j_th" node placeholder...

        // Checking whether element type "j" is present in the type list or not:
        if(j == type_list[t])
        {
          elements = element_tag[t].size ();                                                        // Getting the number of elements of "t" type...

          // For each "k_th" element of type "t":
          for(k = 0; k < elements; k++)
          {
            // Getting element type properties:
            gmsh::model::mesh::getElementProperties (
                                                     type_list[t],                                  // Element type [#].
                                                     type_name,                                     // Element type name [string].
                                                     type_dimension,                                // Element type dimension [#].
                                                     type_order,                                    // Element type order [#].
                                                     type_nodes,                                    // Element type number of type nodes [#].
                                                     type_node_coordinates,                         // Element type node local coordinates [vector].
                                                     type_primary_nodes                             // Number of primary type nodes [#].
                                                    );

            // Processing the "m_th" node in "k_th" element of type "t":
            for(m = 0; m < type_nodes; m++)
            {
              element_unit.node.push_back ((node_tag[t][k*type_nodes + m]) - 1);                    // Adding type node to element unit...
              node_unit.x = (float)node_coordinates[3*m + 0];                                       // Setting node unit "x" coordinate...
              node_unit.y = (float)node_coordinates[3*m + 1];                                       // Setting node unit "y"coordinate...
              node_unit.z = (float)node_coordinates[3*m + 2];                                       // Setting node unit "z" coordinate...
              node_unit.w = 1.0f;                                                                   // Setting node unit "w" coordinate...
              node[d][e][j].push_back (node_unit);                                                  // Adding node unit to node vector...
            }

            element_unit.type = type_list[t];                                                       // Setting element unit type...
            element[d][e][j].push_back (element_unit);                                              // Adding element[k] to element vector...
          }

          element_unit.node.clear ();                                                               // Clearing element unit node vector...
        }
        else
        {
          element[d][e][j].push_back ({});                                                          // Adding empty elment unit to element vector...
          node[d][e][j].push_back ({});                                                             // Adding empty node unit to node vector...
        }
      }

      /*
          for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
          {
            group[d][e].push_back ({});                                                                 // Creating "j_th" element placeholder...

            // Checking whether element type "j" is present in the type list or not:
            if(j == type_list[t])
            {
              // Finding groups for each node:
              for(i = 0; i < node[d][e][j].size (); i++)
              {
                for(k = 0; k < element[d][e][j].size (); k++)
                {
                  for(m = 0; m < element[d][e][j][k].node.size (); m++)
                  {
                    if(element[d][e][j][k].node[m] == i)
                    {
                      group_unit.element.push_back (k);                                                 // Adding element index to group unit...
                    }
                  }
                }

                if(node[d][e][j].size () > 0)
                {
                  group[d][e][j].push_back (group_unit);                                                // Adding group unit to group vector...
                  group_unit.element.clear ();                                                          // Clearing group unit element vector...
                  std::cout << "peppo" << std::endl;
                }
                else
                {
                  group[d][e][j].push_back ({});                                                        // Adding empty group unit to group vector...
                  std::cout << "pappo" << std::endl;
                }
              }
            }
          }

          for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
          {
            neighbours = 0;                                                                             // Resetting number of neighbours...
            neighbourhood[d][e].push_back ({});                                                         // Creating "j_th" element placeholder...
            offset[d][e].push_back ({});                                                                // Creating "j_th" element placeholder...
            link[d][e].push_back ({});                                                                  // Creating "j_th" element placeholder...

            // Checking whether element type "j" is present in the type list or not:
            if(j == type_list[t])
            {
              for(i = 0; i < node[j].size (); i++)
              {
                neighbour_unit = this->neighbour (d, e, j, i);                                          // Getting neighbourhood indices...
                neighbourhood[d][e][j].insert (
                                               neighbourhood[d][e][j].end (),
                                               neighbour_unit.begin (),
                                               neighbour_unit.end ()
                                              );                                                        // Building neighbour tuple...
                neighbours    += neighbour_unit.size ();                                                // Counting neighbour nodes...

                if(node[d][e][j].size () > 0)
                {
                  offset[d][e][j].push_back (neighbours);                                               // Setting neighbour offset...
                }
                else
                {
                  offset[d][e][j].push_back ({});                                                       // Setting empty neighbour offset...
                }
              }

              neighbour_unit.clear ();

              for(i = 0; i < node[d][e][j].size (); i++)
              {
                s_max = offset[d][e][j][i];                                                             // Setting stride maximum...

                if(i == 0)
                {
                  s_min = 0;                                                                            // Setting stride minimum (first stride)...
                }
                else
                {
                  s_min = offset[d][e][j][i - 1];                                                       // Setting stride minimum (all others)...
                }

                for(s = s_min; s < s_max; s++)
                {
                  k = neighbourhood[d][e][j][s];                                                        // Getting neighbour index...
                  if(node[j].size () > 0)
                  {
                    // Setting link:
                    link[d][e][j].push_back (
                    {
                      node[d][e][j][k].x - node[d][e][j][i].x,                                          // Computing link "x" component...
                      node[d][e][j][k].y - node[d][e][j][i].y,                                          // Computing link "y" component...
                      node[d][e][j][k].z - node[d][e][j][i].z,                                          // Computing link "z" component...
                      0.0f                                                                              // Computing link "w" component...
                    }
                                            );
                  }
                  else
                  {
                    link[d][e][j].push_back ({});                                                       // Setting empty link...
                  }
                }
              }
            }
          }
       */
    }
  }


  neutrino::done ();                                                                                // Printing message...
}

std::vector<size_t> mesh::neighbour (
                                     int    loc_element_dimension,                                  // Element dimension.
                                     int    loc_element_tag,                                        // Element tag.
                                     int    loc_type,                                               // Element type.
                                     size_t loc_node                                                // Central node index [x].
                                    )
{
  neighbour_unit.clear ();

  int d = loc_element_dimension;
  int e = loc_element_tag;

  for(k = 0; k < element[d][e].size (); k++)
  {
    for(m = 0; m < element[d][e][loc_type][k].node.size (); m++)
    {
      if((element[d][e][loc_type][k].node[m] == loc_node))
      {
        // Appending element[i] type nodes in neighbour unit:
        neighbour_unit.insert (
                               neighbour_unit.end (),                                               // Insertion point.
                               element[d][e][loc_type][k].node.begin (),                            // Beginning of vector to be appended.
                               element[d][e][loc_type][k].node.end ()                               // End of vector to be appended.
                              );

        // Erasing central node from neighbourhood:
        neighbour_unit.erase (
                              neighbour_unit.end () -                                               // Insertion point.
                              element[d][e][loc_type][k].node.size () +                             // Number of type nodes.
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
