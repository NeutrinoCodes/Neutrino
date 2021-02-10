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

std::vector<gmsh_node> mesh::node (
                                   int loc_entity_dimension,                                        // Entity dimension.
                                   int loc_entity_tag,                                              // Entity tag.
                                   int loc_element_type                                             // Element type.
                                  )
{
  // NODE VARIABLES:
  std::vector<size_t>               loc_node_list;                                                  // Node list.
  std::vector<double>               loc_node_coordinates;                                           // Node coordinates.
  std::vector<double>               loc_node_parametric_coordinates;                                // Node parametric coordinates.
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.
  gmsh_node                         loc_node_unit;                                                  // Node unit.
  std::vector<gmsh_node>            loc_node_vector;                                                // Node vector.

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

  neutrino::action ("finding mesh nodes...");                                                       // Printing message...

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
      loc_node_vector.push_back (loc_node_unit);                                                    // Adding node unit to node vector...
    }
  }

  neutrino::done ();                                                                                // Printing message...

  return loc_node_vector;                                                                           // Returning node vector...
}

std::vector<gmsh_element> mesh::element (
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
  std::vector<gmsh_element>         loc_element_vector;                                             // Element vector to be returned.
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

  neutrino::action ("finding mesh elements...");                                                    // Printing message...

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

    loc_element_vector.push_back (loc_element_unit);                                                // Adding the "k" element unit to the element vector...
    loc_element_unit.node.clear ();                                                                 // Clearing element unit for next "k"...
  }

  neutrino::done ();                                                                                // Printing message...

  return loc_element_vector;                                                                        // Returning element vector...
}

std::vector<gmsh_group> mesh::group (
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
  std::vector<gmsh_node>            loc_node_vector;                                                // Node vector.
  size_t                            loc_nodes;                                                      // Number of nodes.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  std::vector<gmsh_element>         loc_element_vector;                                             // Element vector.
  size_t                            loc_elements;                                                   // Number of elements.

  // TYPE VARIABLES:
  size_t                            loc_types;                                                      // Number of element types.
  int                               loc_type_order;                                                 // Element type order.
  int                               loc_type_primary_nodes;                                         // Element primary nodes
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // GROUP VARIABLES:
  gmsh_group                        loc_group_unit;                                                 // Group unit.
  std::vector<gmsh_group>           loc_group_vector;                                               // Group vector.

  // INDICES:
  size_t                            i;                                                              // Node index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.

  neutrino::action ("finding mesh groups...");                                                      // Printing message...

  loc_node_vector    = this->node (loc_entity_dimension, loc_entity_tag, loc_element_type);         // Getting nodes...
  loc_nodes          = loc_node_vector.size ();                                                     // Getting the number of nodes...
  loc_element_vector = this->element (loc_entity_dimension, loc_entity_tag, loc_element_type);      // Getting elements...
  loc_elements       = loc_element_vector.size ();                                                  // Getting the number of elements...
  loc_type_nodes     = loc_element_vector[0].node.size ();                                          // Getting the number of node of the "j" type...

  // For each "i" node of the elements of "j" type:
  for(i = 0; i < loc_nodes; i++)
  {
    // For each "k" element of "j" type:
    for(k = 0; k < loc_elements; k++)
    {
      // For each "m" node in the "k" element of "j" type:
      for(m = 0; m < loc_type_nodes; m++)
      {
        // Checking whether the "i" node is present in the "k" element or not:
        if(loc_element_vector[k].node[m] == i)
        {
          loc_group_unit.element.push_back (k);                                                     // Adding element index "k" to the group unit...
        }
      }
    }

    loc_group_vector.push_back (loc_group_unit);                                                    // Adding "k" group unit to group vector...
    loc_group_unit.element.clear ();                                                                // Clearing group unit for next "k"...
  }

  neutrino::done ();                                                                                // Printing message...

  return loc_group_vector;                                                                          // Returning group vector...
}

std::vector<gmsh_neighbour> mesh::neighbour (
                                             int loc_entity_dimension,
                                             int loc_entity_tag,
                                             int loc_element_type
                                            )

{
  // NODE VARIABLES:
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.
  std::vector<gmsh_node>            loc_node_vector;                                                // Node vector.
  size_t                            loc_nodes;                                                      // Number of nodes.

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  std::vector<gmsh_element>         loc_element_vector;                                             // Element vector.
  size_t                            loc_elements;                                                   // Number of elements.

  // TYPE VARIABLES:
  std::vector<int>                  loc_type_list;                                                  // Element type list.
  size_t                            loc_types;                                                      // Number of element types.
  int                               loc_type_nodes;                                                 // Number of type nodes.

  // NEIGHBOUR VARIABLES:
  gmsh_neighbour                    loc_neighbour_unit;                                             // Neighbour unit.
  std::vector<gmsh_neighbour>       loc_neighbour_vector;                                           // Neighbour vector.
  size_t                            loc_neighbours;                                                 // Number of neighbours.
  size_t                            loc_offset;                                                     // Neighbour Offset.

  // INDICES:
  size_t                            i;                                                              // Node index.
  size_t                            j;                                                              // Current type.
  size_t                            k;                                                              // Element index.
  size_t                            m;                                                              // Node index of current element.
  size_t                            n;                                                              // Node index of current neighbour unit.
  size_t                            s;                                                              // Stride index.
  size_t                            s_min;                                                          // Stride minimum index.
  size_t                            s_min_old;                                                      // Stride minimum index (old value).
  size_t                            s_max;                                                          // Stride maximum index.

  neutrino::action ("finding mesh neighbours...");                                                  // Printing message...

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
  std::cout << "puppo" << std::endl;
  loc_types = loc_type_list.size ();                                                                // Getting number of types...
  std::cout << "puppo" << std::endl;

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

  std::cout << "puppo" << std::endl;

  loc_node_vector    = this->node (loc_entity_dimension, loc_entity_tag, loc_element_type);         // Getting nodes...
  loc_nodes          = loc_node_vector.size ();                                                     // Getting the number of nodes...
  std::cout << "puppo" << std::endl;
  loc_element_vector = this->element (loc_entity_dimension, loc_entity_tag, loc_element_type);      // Getting elements...
  loc_elements       = loc_element_vector.size ();                                                  // Getting the number of elements...
  loc_type_nodes     = loc_element_vector[0].node.size ();                                          // Getting the number of node of the "j" type...
  loc_offset         = 0;                                                                           // Resetting the neighbour offset...
  s_min_old          = 0;                                                                           // Setting stride minimum (first stride)...

  std::cout << "puppo" << std::endl;

  // For each "i" node of the elements of "j" type:
  for(i = 0; i < loc_nodes; i++)
  {
    std::cout << "pippo i = " << i << std::endl;

    // For each "k" element of "j" type:
    for(k = 0; k < loc_elements; k++)
    {
      // For each "m" node in the "k" element of "j" type:
      for(m = 0; m < loc_type_nodes; m++)
      {
        // Checking whether the "k" element of "j" type contains the "i" central node:
        if((loc_element_vector[k].node[m] == i))
        {
          // Appending the "k" element type nodes to the neighbour unit:
          std::cout << "puppo" << std::endl;
          loc_neighbour_unit.node.insert (
                                          loc_neighbour_unit.node.end (),                           // Insertion point.
                                          loc_element_vector[k].node.begin (),                      // Beginning of vector to be appended.
                                          loc_element_vector[k].node.end ()                         // End of vector to be appended.
                                         );
          std::cout << "poppo" << std::endl;

          // Erasing the central node from the neighbour unit:
          loc_neighbour_unit.node.erase (
                                         loc_neighbour_unit.node.end () -                           // Insertion point.
                                         loc_type_nodes +                                           // Number of type nodes.
                                         m                                                          // Central node.
                                        );
          std::cout << "pappo" << std::endl;
        }
      }
    }

    std::cout << "peppa" << std::endl;
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
    std::cout << "peppa" << std::endl;
    // Building neighbour vector (node part):

    loc_neighbours            = loc_neighbour_unit.node.size ();                                    // Counting neighbour nodes...
    loc_offset               += loc_neighbours;

    // Building neighbour vector (offset part):
    loc_neighbour_unit.offset = loc_offset;                                                         // Setting neighbour offset...

    // Building neighbour vector (link part):
    //s_max                     = loc_neighbour_unit.offset;                                          // Setting stride maximum...
    //s_min                     = s_min_old;                                                          // Setting stride minimum (first stride)...
    //s_min_old                 = s_max;

    // For each "s" neighbour node in the "i" stride:
    for(s = 0; s < loc_neighbours; s++)
    {
      std::cout << "pyppa" << std::endl;
      n = loc_neighbour_unit.node[s];                                                               // Getting neighbour index...
      loc_neighbour_unit.link.push_back (
      {
        loc_node_vector[n].x - loc_node_vector[i].x,                                                // Setting link "x" component...
        loc_node_vector[n].y - loc_node_vector[i].y,                                                // Setting link "y" component...
        loc_node_vector[n].z - loc_node_vector[i].z,                                                // Setting link "z" component...
        0.0f                                                                                        // Setting link "w" component...
      }
                                        );
    }

    loc_neighbour_vector.push_back (loc_neighbour_unit);                                            // Adding "i" neighbour unit to neighbour vector...
    loc_neighbour_unit.node.clear ();                                                               // Clearing neighbour unit for next "i"...
    loc_neighbour_unit.link.clear ();                                                               // Clearing neighbour unit for next "i"...
    std::cout << "pjppa" << std::endl;
  }

  neutrino::done ();                                                                                // Printing message...

  return loc_neighbour_vector;                                                                      // Returning neighbour vector...
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
