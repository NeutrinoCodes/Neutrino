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
  neutrino::action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 0);                                                  // Not allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  gmsh::model::mesh::renumberNodes ();                                                              // Renumbering the node tags in a continuous sequence...
  gmsh::model::mesh::renumberElements ();                                                           // Renumbering the element tags in a continuous sequence...
  neutrino::done ();                                                                                // Printing message...
}

void mesh::process (
                    int loc_physical_group_tag,                                                     // Physical group tag.
                    int loc_physical_group_dimension,                                               // Physical group dimension.
                    int loc_element_type                                                            // Element type.
                   )
{
  // NODE VARIABLES:
  std::vector<size_t> loc_node_tag;                                                                 // Node tags of the given physical group.
  std::vector<size_t> loc_node_tag_sorted;                                                          // Sorted node tags of the given physical group.
  std::vector<double> loc_node_coordinates;                                                         // Node coordinates of the given physical group.
  size_t              loc_node_size;                                                                // Number of nodes of the given physical group.
  size_t              loc_node_found;                                                               // Number of element nodes founded to be present in the physical group.
  GLint               loc_node_index;                                                               // Node index (found from given node tag)...

  // INDICES:
  size_t              i;                                                                            // Node index.
  size_t              j;                                                                            // Node tag - 1;
  size_t              loc_element_offset;                                                           // Element offset.
  size_t              k;                                                                            // Element index.
  size_t              m;                                                                            // Element node index.
  size_t              m_min;                                                                        // Minimum index of current element stride.
  size_t              m_max;                                                                        // Maximum index of current element stride.
  size_t              n;                                                                            // Element node counter...
  size_t              s;                                                                            // Stride index...

  // ELEMENT VARIABLES:
  size_t              loc_all_element_size;                                                         // Number of all elements in all entities.
  std::vector<size_t> loc_all_element_tag;                                                          // Tags of all elements in all entities.
  std::vector<size_t> loc_all_element_node;                                                         // Node tags of all elements in all entities.
  size_t              loc_element_size;                                                             // Number of all elements in the physical group.

  // GROUP VARIABLES:
  size_t              loc_group_offset;                                                             // Group offset.

  // TYPE VARIABLES:
  std::string         loc_type_name;                                                                // Element type name.
  int                 loc_type_dimension;                                                           // Element type dimension.
  int                 loc_type_order;                                                               // Element type order.
  std::vector<double> loc_type_node_coordinates;                                                    // Element type node coordinates.
  int                 loc_type_primary_nodes;                                                       // Element primary nodes.
  int                 loc_type_size;                                                                // Number of nodes in element type.

  // NEIGHBOUR VARIABLES:
  std::vector<size_t> loc_neighbour;                                                                // Neighbour unit.
  GLint               loc_neighbour_offset;                                                         // Neighbour offset.
  GLint               loc_neighbour_size;                                                           // Number of neighbours.

  // LINK VARIABLES:
  GLfloat             loc_link_x;                                                                   // Link "x" coordinate.
  GLfloat             loc_link_y;                                                                   // Link "y" coordinate.
  GLfloat             loc_link_z;                                                                   // Link "z" coordinate.
  GLfloat             loc_link_w;                                                                   // Link "w" coordinate.

  neutrino::action ("finding mesh nodes in the given physical group...");                           // Printing message...

  // Getting nodes for given physical group:
  gmsh::model::mesh::getNodesForPhysicalGroup (
                                               loc_physical_group_dimension,                        // Physical group dimension.
                                               loc_physical_group_tag,                              // Physical group tag.
                                               loc_node_tag,                                        // Node tags.
                                               loc_node_coordinates                                 // Node coordinates.
                                              );

  loc_node_size = loc_node_tag.size ();                                                             // Getting node tag vector size...

  neutrino::done ();                                                                                // Printing message...

  // For each node of the given physical group:
  for(i = 0; i < loc_node_size; i++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    node.push_back ((GLint)loc_node_tag[i]);                                                        // Setting node tags...
    loc_node_index = std::find (node.begin (), node.end (), node[i]) - node.begin ();               // Finding node index from node tag...
    node_index.push_back (loc_node_index);                                                          // Setting node index...

    node_coordinates.push_back (
    {
      (float)loc_node_coordinates[3*i + 0],                                                         // Setting node unit "x" coordinate...
      (float)loc_node_coordinates[3*i + 1],                                                         // Setting node unit "y"coordinate...
      (float)loc_node_coordinates[3*i + 2],                                                         // Setting node unit "z" coordinate...
      1.0f                                                                                          // Setting node unit "w" coordinate...
    }
                               );                                                                   // Adding node unit to node vector...
    neutrino::progress ("building node vectors... ", 0, loc_node_size, i);                          // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("finding mesh elements in the given physical group...");                        // Printing message...

  // Getting element type properties:
  gmsh::model::mesh::getElementProperties (
                                           loc_element_type,                                        // Element type [#].
                                           loc_type_name,                                           // Element type name [string].
                                           loc_type_dimension,                                      // Element type dimension [#].
                                           loc_type_order,                                          // Element type order [#].
                                           loc_type_size,                                           // Number of nodes for given element type [#].
                                           loc_type_node_coordinates,                               // Element type node local coordinates [vector].
                                           loc_type_primary_nodes                                   // Number of primary type nodes [#].
                                          );

  // Getting elements for all entities:
  gmsh::model::mesh::getElementsByType (
                                        loc_element_type,
                                        loc_all_element_tag,
                                        loc_all_element_node,
                                        -1,
                                        0,
                                        1
                                       );

  loc_all_element_size = loc_all_element_tag.size ();                                               // Getting number of element among all entities...
  loc_node_tag_sorted  = loc_node_tag;                                                              // Initializing sorted node tags...
  std::sort (loc_node_tag_sorted.begin (), loc_node_tag_sorted.end ());                             // Sorting node tag vector (for fast binary search)...
  s                    = 0;                                                                         // Resetting stride index...

  // For each "k" element:
  for(k = 0; k < loc_all_element_size; k++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    loc_element_offset = k*loc_type_size;                                                           // Computing element offset...
    loc_node_found     = 0;                                                                         // Resetting found nodes counter...

    // For each "n" node in element stride:
    for(n = 0; n < loc_type_size; n++)
    {
      m               = loc_element_offset + n;                                                     // Computing node index...

      // Counting how many "m" nodes of the "k" element are present in the physical group:
      loc_node_found += std::binary_search (
                                            loc_node_tag_sorted.begin (),
                                            loc_node_tag_sorted.end (),
                                            loc_all_element_node[m]
                                           );
    }

    // Checking whether all nodes of the "k" elements are present in the physical group:
    if(loc_node_found == loc_type_size)
    {
      // Building vector of the element nodes present in the physical group:
      for(n = 0; n < loc_type_size; n++)
      {
        m = loc_element_offset + n;                                                                 // Computing node index...
        element.push_back (loc_all_element_node[m]);                                                // Adding node to element vector...
      }

      s += loc_type_size;                                                                           // Incrementing stride index...
      element_offset.push_back (s);                                                                 // Setting element offset...
    }

    neutrino::progress ("building element vectors... ", 0, loc_node_size, i);                       // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...

  loc_element_size     = element_offset.size ();                                                    // Getting the number of elements in the physical group...
  loc_group_offset     = 0;                                                                         // Resetting group offset counter...
  loc_neighbour_offset = 0;                                                                         // Resetting neighbour offeset counter...

  // For each "i" node:
  for(i = 0; i < loc_node_size; i++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    j = loc_node_tag[i];                                                                            // Setting node tag...

    std::cout << "i = " << i << " node tag = " << j << std::endl;

    // For each "k" element:
    for(k = 0; k < loc_element_size; k++)
    {
      // Computing minimum element offset index:
      if(k == 0)
      {
        m_min = 0;                                                                                  // Setting minimum element offset index...
      }
      else
      {
        m_min = element_offset[k - 1];                                                              // Setting minimum element offset index...
      }

      m_max = element_offset[k];                                                                    // Setting maximum element offset index...

      // For each "m" node in the "k" element:
      for(m = m_min; m < m_max; m++)
      {
        // Checking whether the "k" element contains the "i" node (j = loc_node_tag[i]):
        if(element[m] == j)
        {
          group.push_back (k);                                                                      // Adding "k" element to the group...
          loc_group_offset++;                                                                       // Incrementing group offset counter...
          loc_neighbour.insert (
                                loc_neighbour.end (),
                                element.begin () + m_min,
                                element.begin () + m_max
                               );                                                                   // Appending the "k" element type nodes to the neighbour unit...
          loc_neighbour.erase (loc_neighbour.end () - 1 - (m_max - 1 - m_min) + (m - m_min));       // Erasing the central node from the neighbour unit...
        }
      }
    }

    // Eliminating repeated indexes:
    std::sort (loc_neighbour.begin (), loc_neighbour.end ());
    loc_neighbour.resize (
                                                                                                    // Eliminating null indexes...
                          std::distance (
                                                                                                    // Calculating index distance...
                                         loc_neighbour.begin (),
                                         std::unique (
                                                                                                    // Finding unique indexes...
                                                      loc_neighbour.begin (),                       // Beginning of index vector.
                                                      loc_neighbour.end ()                          // End of index vector.
                                                     )
                                        )
                         );

    loc_neighbour_size    = loc_neighbour.size ();                                                  // Counting neighbour nodes...
    loc_neighbour_offset += loc_neighbour_size;                                                     // Incrementing neighbour offset index...
    neighbour_offset.push_back (loc_neighbour_offset);                                              // Setting "i" neighbour offset...
    group_offset.push_back (loc_group_offset);                                                      // Setting "i" group offset...

    std::cout << "loc_neighbour offset = " << loc_neighbour_offset << std::endl;

    // For each "s" neighbour node in the "i" (j = loc_node_tag[i]) stride:
    for(s = 0; s < loc_neighbour_size; s++)
    {
      n          = loc_neighbour[s];                                                                // Getting neighbour index...
      neighbour.push_back (n);                                                                      // Setting neighbour vector...
      loc_link_x = node_coordinates[n].x - node_coordinates[i].x;                                   // Setting link "x" coordinate...
      loc_link_y = node_coordinates[n].y - node_coordinates[i].y;                                   // Setting link "y" coordinate...
      loc_link_z = node_coordinates[n].z - node_coordinates[i].z;                                   // Setting link "z" coordinate...
      loc_link_w = 0.0f;                                                                            // Setting link "w" coordinate...

      // Setting neighbour link vector:
      neighbour_link.push_back (
      {
        loc_link_x,                                                                                 // Setting link "x" component...
        loc_link_y,                                                                                 // Setting link "y" component...
        loc_link_z,                                                                                 // Setting link "z" component...
        loc_link_w                                                                                  // Setting link "w" component...
      }
                               );

      // Setting neighbour length vector:
      neighbour_length.push_back (
                                  sqrt (
                                        pow (loc_link_x, 2) +
                                        pow (loc_link_y, 2) +
                                        pow (loc_link_z, 2)
                                       )
                                 );
    }

    loc_neighbour.clear ();                                                                         // Clearing neighbour unit for next "i"...

    neutrino::progress ("building group and neighbour vectors... ", 0, loc_node_size, i);           // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
