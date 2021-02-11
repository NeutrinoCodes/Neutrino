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

void mesh::get_nodes (
                      int loc_entity_dimension,                                                     // Entity dimension.
                      int loc_entity_tag,                                                           // Entity tag.
                      int loc_element_type                                                          // Element type.
                     )
{
  // NODE VARIABLES:
  std::vector<size_t>               loc_node_list;                                                  // Node list.
  std::vector<double>               loc_node_coordinates;                                           // Node coordinates.
  std::vector<double>               loc_node_parametric_coordinates;                                // Node parametric coordinates.
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.
  gmsh_node                         loc_node_unit;                                                  // Node unit.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  size_t                            loc_elements;                                                   // Number of elements.

  // TYPE VARIABLES:
  std::vector<int>                  loc_type_list;                                                  // Element type list.
  size_t                            loc_types;                                                      // Number of element types.
  std::string                       loc_type_name;                                                  // Element type name.
  int                               loc_type_dimension;                                             // Element type dimension.
  int                               loc_type_order;                                                 // Element type order.
  std::vector<double>               loc_type_node_coordinates;                                      // Element type node coordinates.
  int                               loc_type_primary_nodes;                                         // Element primary nodes
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // INDICES:
  size_t                            i;                                                              // Type index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.

  // Getting entity nodes:
  gmsh::model::mesh::getNodes (
                               loc_node_list,                                                       // Node tags list [N].
                               loc_node_coordinates,                                                // Node coordinates list [3*N].
                               loc_node_parametric_coordinates,                                     // Node parametric coordinates [dim*N].
                               loc_entity_dimension,                                                // Entity dimension [#].
                               loc_entity_tag                                                       // Entity tag [#].
                              );

  // Getting entity elements, where:
  // i = type index.
  // m = node index of current element.
  // L = number of element types.
  // M(i) = number of elements per element type.
  // N(m) = number of nodes per element, for each element type.
  gmsh::model::mesh::getElements (
                                  loc_type_list,                                                    // Element type list [L].
                                  loc_element_tag,                                                  // Element tag list LxM(i).
                                  loc_node_tag,                                                     // Node tag list Lx[N(1),N(2),...,N(m),N(M(i))].
                                  loc_entity_dimension,                                             // Entity dimension [#].
                                  loc_entity_tag                                                    // Entity tag [#].
                                 );

  loc_types = loc_type_list.size ();                                                                // Getting number of types...

  // Finding the number of elements of "j" type...
  for(i = 0; i < loc_types; i++)
  {
    if(loc_type_list[i] == loc_element_type)
    {
      j            = i;                                                                             // Setting current element type index...
      loc_elements = loc_element_tag[j].size ();                                                    // Getting the number of elements of "j" type...
    }
    else
    {
      loc_elements = 0;                                                                             // Resetting the number of elements of "j" type...
    }
  }

  // For each "k" element of "j" type:
  for(k = 0; k < loc_elements; k++)
  {
    neutrino::work ();                                                                              // Getting initial task time...
    // Getting the element type properties:
    gmsh::model::mesh::getElementProperties (
                                             loc_element_type,                                      // Element type [#].
                                             loc_type_name,                                         // Element type name [string].
                                             loc_type_dimension,                                    // Element type dimension [#].
                                             loc_type_order,                                        // Element type order [#].
                                             loc_type_nodes,                                        // Element type number of type nodes [#].
                                             loc_type_node_coordinates,                             // Element type node local coordinates [vector].
                                             loc_type_primary_nodes                                 // Number of primary type nodes [#].
                                            );

    // Getting the coordinates of the "m" node in the "k" element of "j" type:
    for(m = 0; m < loc_type_nodes; m++)
    {
      loc_node_unit.x = (float)loc_node_coordinates[3*m + 0];                                       // Setting node unit "x" coordinate...
      loc_node_unit.y = (float)loc_node_coordinates[3*m + 1];                                       // Setting node unit "y"coordinate...
      loc_node_unit.z = (float)loc_node_coordinates[3*m + 2];                                       // Setting node unit "z" coordinate...
      loc_node_unit.w = 1.0f;                                                                       // Setting node unit "w" coordinate...
      node.push_back (loc_node_unit);                                                               // Adding node unit to node vector...
    }

    neutrino::progress ("finding mesh nodes... ", 0, loc_elements, k);                              // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...
}

void mesh::get_elements (
                         int loc_entity_dimension,
                         int loc_entity_tag,
                         int loc_element_type
                        )
{
  // NODE VARIABLES:
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  size_t                            loc_elements;                                                   // Number of elements.
  gmsh_element                      loc_element_unit;                                               // Element unit.

  // TYPE VARIABLES:
  std::vector<int>                  loc_type_list;                                                  // Element type list.
  size_t                            loc_types;                                                      // Number of element types.
  std::string                       loc_type_name;                                                  // Element type name.
  int                               loc_type_dimension;                                             // Element type dimension.
  int                               loc_type_order;                                                 // Element type order.
  std::vector<double>               loc_type_node_coordinates;                                      // Element type node coordinates.
  int                               loc_type_primary_nodes;                                         // Element primary nodes
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // INDICES:
  size_t                            i;                                                              // Type index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.

  // Getting entity elements, where:
  // i = type index.
  // m = node index of current element.
  // L = number of element types.
  // M(i) = number of elements per element type.
  // N(m) = number of nodes per element, for each element type.
  gmsh::model::mesh::getElements (
                                  loc_type_list,                                                    // Element type list [L].
                                  loc_element_tag,                                                  // Element tag list LxM(i).
                                  loc_node_tag,                                                     // Node tag list Lx[N(1),N(2),...,N(m),N(M(i))].
                                  loc_entity_dimension,                                             // Entity dimension [#].
                                  loc_entity_tag                                                    // Entity tag [#].
                                 );

  loc_types = loc_type_list.size ();                                                                // Getting number of types...

  // Finding the number of elements of "j" type...
  for(i = 0; i < loc_types; i++)
  {
    if(loc_type_list[i] == loc_element_type)
    {
      j            = i;                                                                             // Setting current element type index...
      loc_elements = loc_element_tag[j].size ();                                                    // Getting the number of elements of "j" type...
    }
    else
    {
      loc_elements = 0;                                                                             // Resetting the number of elements of "j" type...
    }
  }

  // For each "k" element of "j" type:
  for(k = 0; k < loc_elements; k++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    // Getting the element type properties:
    gmsh::model::mesh::getElementProperties (
                                             loc_element_type,                                      // Element type [#].
                                             loc_type_name,                                         // Element type name [string].
                                             loc_type_dimension,                                    // Element type dimension [#].
                                             loc_type_order,                                        // Element type order [#].
                                             loc_type_nodes,                                        // Element type number of type nodes [#].
                                             loc_type_node_coordinates,                             // Element type node local coordinates [vector].
                                             loc_type_primary_nodes                                 // Number of primary type nodes [#].
                                            );

    // Getting the coordinates of the "m" node in the "k" element of "j" type:
    for(m = 0; m < loc_type_nodes; m++)
    {
      loc_element_unit.node.push_back ((loc_node_tag[j][k*loc_type_nodes + m]) - 1);                // Adding the type node to the "k" element unit...
    }

    element.push_back (loc_element_unit);                                                           // Adding the "k" element unit to the element vector...
    loc_element_unit.node.clear ();                                                                 // Clearing element unit for next "k"...
    neutrino::progress ("finding mesh elements... ", 0, loc_elements, k);                           // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...
}

void mesh::get_groups (
                       int loc_entity_dimension,
                       int loc_entity_tag,
                       int loc_element_type
                      )
{
  // NODE VARIABLES:
  std::vector<size_t>               loc_node_list;                                                  // Node list.
  std::vector<double>               loc_node_coordinates;                                           // Node coordinates.
  std::vector<double>               loc_node_parametric_coordinates;                                // Node parametric coordinates.
  gmsh_node                         loc_node_unit;                                                  // Node unit.
  size_t                            loc_nodes;                                                      // Number of nodes.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  size_t                            loc_elements;                                                   // Number of elements.

  // TYPE VARIABLES:
  size_t                            loc_types;                                                      // Number of element types.
  int                               loc_type_order;                                                 // Element type order.
  int                               loc_type_primary_nodes;                                         // Element primary nodes
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // GROUP VARIABLES:
  gmsh_group                        loc_group_unit;                                                 // Group unit.

  // INDICES:
  size_t                            i;                                                              // Node index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.

  //loc_node_vector    = this->node (loc_entity_dimension, loc_entity_tag, loc_element_type);         // Getting nodes...
  loc_nodes      = node.size ();                                                                    // Getting the number of nodes...
  //loc_element_vector = this->element (loc_entity_dimension, loc_entity_tag, loc_element_type);      // Getting elements...
  loc_elements   = element.size ();                                                                 // Getting the number of elements...
  loc_type_nodes = element[0].node.size ();                                                         // Getting the number of node of the "j" type...

  // For each "i" node of the elements of "j" type:
  for(i = 0; i < loc_nodes; i++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    // For each "k" element of "j" type:
    for(k = 0; k < loc_elements; k++)
    {
      // For each "m" node in the "k" element of "j" type:
      for(m = 0; m < loc_type_nodes; m++)
      {
        // Checking whether the "i" node is present in the "k" element or not:
        if(element[k].node[m] == i)
        {
          loc_group_unit.element.push_back (k);                                                     // Adding element index "k" to the group unit...
        }
      }
    }

    group.push_back (loc_group_unit);                                                               // Adding "k" group unit to group vector...
    loc_group_unit.element.clear ();                                                                // Clearing group unit for next "k"...
    neutrino::progress ("finding mesh groups... ", 0, loc_nodes, i);                                // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...

  //return loc_group_vector;                                                                          // Returning group vector...
}

void mesh::get_neighbours (
                           int loc_entity_dimension,
                           int loc_entity_tag,
                           int loc_element_type
                          )

{
  // NODE VARIABLES:
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.
  size_t                            loc_nodes;                                                      // Number of nodes.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  size_t                            loc_elements;                                                   // Number of elements.

  // TYPE VARIABLES:
  std::vector<int>                  loc_type_list;                                                  // Element type list.
  size_t                            loc_types;                                                      // Number of element types.
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // NEIGHBOUR VARIABLES:
  gmsh_neighbour                    loc_neighbour_unit;                                             // Neighbour unit.
  size_t                            loc_neighbours;                                                 // Number of neighbours.
  size_t                            loc_offset;                                                     // Neighbour Offset.

  // INDICES:
  size_t                            i;                                                              // Node index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.
  size_t                            n;                                                              // Node index of current neighbour unit.
  size_t                            s;                                                              // Stride index.

  // Getting entity elements, where:
  // i = type index.
  // m = node index of current element.
  // L = number of element types.
  // M(i) = number of elements per element type.
  // N(m) = number of nodes per element, for each element type.
  gmsh::model::mesh::getElements (
                                  loc_type_list,                                                    // Element type list [L].
                                  loc_element_tag,                                                  // Element tag list LxM(i).
                                  loc_node_tag,                                                     // Node tag list Lx[N(1),N(2),...,N(m),N(M(i))].
                                  loc_entity_dimension,                                             // Entity dimension [#].
                                  loc_entity_tag                                                    // Entity tag [#].
                                 );

  loc_types = loc_type_list.size ();                                                                // Getting number of types...

  // Finding the number of elements of "j" type...
  for(i = 0; i < loc_types; i++)
  {
    if(loc_type_list[i] == loc_element_type)
    {
      j            = i;                                                                             // Setting current element type index...
      loc_elements = loc_element_tag[j].size ();                                                    // Getting the number of elements of "j" type...
    }
    else
    {
      loc_elements = 0;                                                                             // Resetting the number of elements of "j" type...
    }
  }

  //loc_node_vector    = this->node (loc_entity_dimension, loc_entity_tag, loc_element_type);         // Getting nodes...
  loc_nodes      = node.size ();                                                                    // Getting the number of nodes...
  //loc_element_vector = this->element (loc_entity_dimension, loc_entity_tag, loc_element_type);      // Getting elements...
  loc_elements   = element.size ();                                                                 // Getting the number of elements...
  loc_type_nodes = element[0].node.size ();                                                         // Getting the number of node of the "j" type...
  loc_offset     = 0;                                                                               // Resetting the neighbour offset...

  // For each "i" node of the elements of "j" type:
  for(i = 0; i < loc_nodes; i++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    // For each "k" element of "j" type:
    for(k = 0; k < loc_elements; k++)
    {
      // For each "m" node in the "k" element of "j" type:
      for(m = 0; m < loc_type_nodes; m++)
      {
        // Checking whether the "k" element of "j" type contains the "i" central node:
        if((element[k].node[m] == i))
        {
          // Appending the "k" element type nodes to the neighbour unit:
          loc_neighbour_unit.node.insert (
                                          loc_neighbour_unit.node.end (),                           // Insertion point.
                                          element[k].node.begin (),                                 // Beginning of vector to be appended.
                                          element[k].node.end ()                                    // End of vector to be appended.
                                         );

          // Erasing the central node from the neighbour unit:
          loc_neighbour_unit.node.erase (
                                         loc_neighbour_unit.node.end () -                           // Insertion point.
                                         loc_type_nodes +                                           // Number of type nodes.
                                         m                                                          // Central node.
                                        );
        }
      }
    }

    // Eliminating repeated indexes:
    std::sort (loc_neighbour_unit.node.begin (), loc_neighbour_unit.node.end ());
    loc_neighbour_unit.node.resize (
                                                                                                    // Eliminating null indexes...
                                    std::distance (
                                                                                                    // Calculating index distance...
                                                   loc_neighbour_unit.node.begin (),
                                                   std::unique (
                                                                                                    // Finding unique indexes...
                                                                loc_neighbour_unit.node.
                                                                begin (),                           // Beginning of index vector.
                                                                loc_neighbour_unit.node.
                                                                end ()                              // End of index vector.
                                                               )
                                                  )
                                   );

    loc_neighbours            = loc_neighbour_unit.node.size ();                                    // Counting neighbour nodes...
    loc_offset               += loc_neighbours;                                                     // Incrementing neighbour offset index...
    loc_neighbour_unit.offset = loc_offset;                                                         // Setting neighbour offset...

    // For each "s" neighbour node in the "i" stride:
    for(s = 0; s < loc_neighbours; s++)
    {
      n = loc_neighbour_unit.node[s];                                                               // Getting neighbour index...
      loc_neighbour_unit.link.push_back (
      {
        node[n].x - node[i].x,                                                                      // Setting link "x" component...
        node[n].y - node[i].y,                                                                      // Setting link "y" component...
        node[n].z - node[i].z,                                                                      // Setting link "z" component...
        0.0f                                                                                        // Setting link "w" component...
      }
                                        );
    }

    neighbour.push_back (loc_neighbour_unit);                                                       // Adding "i" neighbour unit to neighbour vector...
    loc_neighbour_unit.node.clear ();                                                               // Clearing neighbour unit for next "i"...
    loc_neighbour_unit.link.clear ();                                                               // Clearing neighbour unit for next "i"...
    neutrino::progress ("finding mesh neighbours... ", 0, loc_nodes, i);                            // Printing progress message...
  }

  neutrino::done ();                                                                                // Printing message...

  //return loc_neighbour_vector;                                                                      // Returning neighbour vector...
}

void mesh::get_physicals (
                          size_t loc_physical_group_dim,                                            // Physical group dimension [#].
                          size_t loc_physical_group_tag                                             // Physical group tag [#].
                         )
{
  std::vector<double> loc_node_coordinates;                                                         // Node coordinates.

  neutrino::action ("finding mesh physical groups...");                                             // Printing message...

  // Getting nodes for given physical group:
  gmsh::model::mesh::getNodesForPhysicalGroup (
                                               loc_physical_group_dim,                              // Physical group dimension.
                                               loc_physical_group_tag,                              // Physical group tag.
                                               physical,                                            // Node tags.
                                               loc_node_coordinates                                 // Node coordinates.
                                              );

  // Adjusting node index according to Neutrino (1st index = 0):
  for(size_t i = 0; i < physical.size (); i++)
  {
    physical[i]--;                                                                                  // Adjusting node index...
  }

  loc_node_coordinates.clear ();                                                                    // Clearing unnecessary coordinates vector...

  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
