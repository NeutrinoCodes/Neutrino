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

  entity_dimension_max = entity_list[0].first;                                                      // Resetting maximum number of entity dimensions...

  // Finding maximum number of dimensions among entities:
  for(n = 0; n < entities; n++)
  {
    entity_dimension.push_back (entity_list[n].first);                                              // Setting entity dimension...

    if(entity_dimension[n] > entity_dimension_max)
    {
      entity_dimension_max = entity_dimension[n];                                                   // Finding maximum dimension...
    }
  }

  // Finding entity index and creating initial empty "tag placeholders":
  for(d = 0; d < (entity_dimension_max + 1); d++)
  {
    e = 0;                                                                                          // Resetting entity index...

    for(n = 0; n < entities; n++)
    {
      if(entity_list[n].first == d)
      {
        entity_index.push_back (e);                                                                 // Setting entity index list...
        e++;                                                                                        // Incrementing entity index..
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

  // Reading mesh:
  for(n = 0; n < entities; n++)
  {
    d          = entity_dimension[n];                                                               // Getting entity dimension [#]...
    e          = entity_index[n];                                                                   // Getting entity index...
    entity_tag = entity_list[n].second;                                                             // Getting entity tag [#]...

    // Getting entity nodes, where:
    // N = number of nodes
    // d = entity dimension
    gmsh::model::mesh::getNodes (
                                 node_list,                                                         // Node tags list [N].
                                 node_coordinates,                                                  // Node coordinates list [3*N].
                                 node_parametric_coordinates,                                       // Node parametric coordinates [dim*N].
                                 d,                                                                 // Entity dimension [#].
                                 entity_tag                                                         // Entity tag [#].
                                );

    nodes = node_list.size ();

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

    std::cout << "Finding nodes..." << std::endl;

    // For each element type in the entity's type list:
    for(t = 0; t < types; t++)
    {
      // Finding nodes for each GMSH's element type:
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
            // Getting the element type properties:
            gmsh::model::mesh::getElementProperties (
                                                     type_list[t],                                  // Element type [#].
                                                     type_name,                                     // Element type name [string].
                                                     type_dimension,                                // Element type dimension [#].
                                                     type_order,                                    // Element type order [#].
                                                     type_nodes,                                    // Element type number of type nodes [#].
                                                     type_node_coordinates,                         // Element type node local coordinates [vector].
                                                     type_primary_nodes                             // Number of primary type nodes [#].
                                                    );

            // Getting the coordinates of the "m_th" node in "k_th" element of type "t":
            for(m = 0; m < type_nodes; m++)
            {
              element_unit.node.push_back ((node_tag[t][k*type_nodes + m]) - 1);                    // Adding type node to "k_th" element unit...
              node_unit.x = (float)node_coordinates[3*m + 0];                                       // Setting node unit "x" coordinate...
              node_unit.y = (float)node_coordinates[3*m + 1];                                       // Setting node unit "y"coordinate...
              node_unit.z = (float)node_coordinates[3*m + 2];                                       // Setting node unit "z" coordinate...
              node_unit.w = 1.0f;                                                                   // Setting node unit "w" coordinate...
              node[d][e][j].push_back (node_unit);                                                  // Adding node unit to node vector...
            }

            element_unit.type = type_list[t];                                                       // Setting element unit type...
            element[d][e][j].push_back (element_unit);                                              // Adding "k_th" element unit to element vector...
          }

          element_unit.node.clear ();                                                               // Clearing element unit for next "k"...
        }
        else
        {
          element[d][e][j].push_back ({});                                                          // Adding empty elment unit to element vector...
          node[d][e][j].push_back ({});                                                             // Adding empty node unit to node vector...
        }
      }


      std::cout << "Finding groups..." << std::endl;

      // Finding groups for each GMSH's element type:
      for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
      {
        group[d][e].push_back ({});                                                                 // Creating "j_th" element placeholder...

        // Checking whether element type "j" is present in the type list or not:
        if(j == type_list[t])
        {
          nodes = node[d][e][j].size ();

          // For each "i_th" node of the elements of type "t":
          for(i = 0; i < nodes; i++)
          {
            std::cout << "i = " << i << std::endl;

            elements = element[d][e][j].size ();

            // For each "k_th" element of type "t":
            for(k = 0; k < elements; k++)
            {


              /*
                 // For each "m_th" node in the "k_th" element of type "t":
                 for(m = 0; m < element[d][e][j][k].node.size (); m++)
                 {
                 // Checking whether the "i_th" node is present in the present in the "k_th" element or not:
                 if(element[d][e][j][k].node[m] == (node_tag[t][i] - 1))
                 {
                  group_unit.element.push_back (k);                                                 // Adding element index "k" to "k_th" group unit...
                 }
                 }
               */
            }

            group[d][e][j].push_back (group_unit);                                                  // Adding "k_th" group unit to group vector...
          }

          group_unit.element.clear ();                                                              // Clearing group unit for next "k"...
        }
        else
        {
          group[d][e][j].push_back ({});                                                            // Adding empty group unit to group vector...
        }
      }



      /*
         std::cout << "Finding neighbours..." << std::endl;

         // Finding neighbours for each GMSH's element type:
         for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
         {
         neighbours = 0;                                                                             // Resetting number of neighbours...
         neighbourhood[d][e].push_back ({});                                                         // Creating "j_th" element placeholder...
         offset[d][e].push_back ({});                                                                // Creating "j_th" element placeholder...

         // Checking whether element type "j" is present in the type list or not:
         if(j == type_list[t])
         {
          // For each "i_th" central node of the elements of type "t":
          for(i = 0; i < node[d][e][j].size (); i++)
          {
            // For each "k_th" element of type "t":
            for(k = 0; k < element[d][e][j].size (); k++)
            {
              // For each "m_th" node in each "k_th" element of type "t":
              for(m = 0; m < element[d][e][j][k].node.size (); m++)
              {
                // Checking whether the "k_th" element of type "t" contains the "i_th" central node:
                if((element[d][e][j][k].node[m] == i))
                {
                  // Appending the element[i] type nodes in the neighbour unit:
                  neighbour_unit.insert (
                                         neighbour_unit.end (),                                     // Insertion point.
                                         element[d][e][j][k].node.begin (),                         // Beginning of vector to be appended.
                                         element[d][e][j][k].node.end ()                            // End of vector to be appended.
                                        );

                  // Erasing the central node from the neighbourhood, hence keeping only its neighbours:
                  neighbour_unit.erase (
                                        neighbour_unit.end () -                                     // Insertion point.
                                        element[d][e][j][k].node.size () +                          // Number of type nodes.
                                        m                                                           // Central node.
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
                                                               neighbour_unit.begin (),             // Beginning of index vector.
                                                               neighbour_unit.end ()                // End of index vector.
                                                              )
                                                 )
                                  );

            // Inserting "k_th" neighbour unit in neighbourhood vector...
            neighbourhood[d][e][j].insert (
                                           neighbourhood[d][e][j].end (),
                                           neighbour_unit.begin (),
                                           neighbour_unit.end ()
                                          );                                                        // Building neighbour tuple...
            neighbours += neighbour_unit.size ();                                                   // Counting neighbour nodes...
            offset[d][e][j].push_back (neighbours);                                                 // Setting neighbour offset...
          }

          neighbour_unit.clear ();                                                                  // Clearing neighbour unit for next "k"...
         }
         else
         {
          neighbourhood[d][e][j].push_back ({});                                                    // Adding empty neighbour unit to neighbourhood vector...
          offset[d][e][j].push_back ({});                                                           // Adding empty offset to offset vector...
         }
         }
       */

      /*
         // Finding links for each GMSH's element type:
         for(j = 1; j < (NU_MSH_MAX_NUM + 1); j++)
         {
         link[d][e].push_back ({});                                                                  // Creating "j_th" element placeholder...

         // Checking whether element type "j" is present in the type list or not:
         if(j == type_list[t])
         {
          // For each "i_th" node of the elements of type "t":
          for(i = 0; i < node[d][e][j].size (); i++)
          {
            s_max = offset[d][e][j][i];                                                             // Setting stride maximum...

            // Computing minimum stride index:
            if(i == 0)
            {
              s_min = 0;                                                                            // Setting stride minimum (first stride)...
            }
            else
            {
              s_min = offset[d][e][j][i - 1];                                                       // Setting stride minimum (all others)...
            }

            // For each "s_th" stride index in the "i_th" stride:
            for(s = s_min; s < s_max; s++)
            {
              k = neighbourhood[d][e][j][s];                                                        // Getting neighbour index...

              // Setting link:
              link[d][e][j].push_back (
              {
                node[d][e][j][k].x - node[d][e][j][i].x,                                            // Computing link "x" component...
                node[d][e][j][k].y - node[d][e][j][i].y,                                            // Computing link "y" component...
                node[d][e][j][k].z - node[d][e][j][i].z,                                            // Computing link "z" component...
                0.0f                                                                                // Computing link "w" component...
              }
                                      );
            }
          }
         }
         else
         {
          link[d][e][j].push_back ({});                                                             // Setting empty link...
         }
         }
       */
    }

    type_list.clear ();
    element_tag.clear ();
    node_tag.clear ();
  }

  neutrino::done ();                                                                                // Printing message...
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
