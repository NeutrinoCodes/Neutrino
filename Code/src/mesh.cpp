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
                    int loc_physical_group_dimension,                                               // Physical group dimension.
                    int loc_physical_group_tag,                                                     // Physical group tag.
                    int loc_element_type                                                            // Element type.
                   )
{
  std::vector<size_t> Np;                                                                           // Node tags of given physical group.
  std::vector<double> Np_coordinates;                                                               // Node coordinates of given physical group.
  size_t              Np_size;                                                                      // Number of nodes of given pyhsical group.
  size_t              i;                                                                            // Node index.
  size_t              j;
  size_t              k;
  size_t              m;
  size_t              m_min;                                                                        // Minimum index of current element stride.
  size_t              m_max;                                                                        // Maximum index of current element stride.

  int                 T_size;                                                                       // Number of nodes in element type.
  size_t              E_size;                                                                       // Number of all elements among all entities.
  std::vector<size_t> E;                                                                            // Tags of all elements among all entities.
  std::vector<size_t> E_node;                                                                       // Node tags of all elements among all entities.
  std::vector<GLint>  E_offset;                                                                     // Offsets of all elements among all entities.

  // TYPE VARIABLES:
  std::vector<int>    loc_type_list;                                                                // Element type list.
  size_t              loc_types;                                                                    // Number of element types.
  std::string         loc_type_name;                                                                // Element type name.
  int                 loc_type_dimension;                                                           // Element type dimension.
  int                 loc_type_order;                                                               // Element type order.
  std::vector<double> loc_type_node_coordinates;                                                    // Element type node coordinates.
  int                 loc_type_primary_nodes;                                                       // Element primary nodes

  neutrino::action ("finding mesh nodes for given physical group...");                              // Printing message...

  // Getting nodes for given physical group:
  gmsh::model::mesh::getNodesForPhysicalGroup (
                                               loc_physical_group_dimension,                        // Physical group dimension.
                                               loc_physical_group_tag,                              // Physical group tag.
                                               Np,                                                  // Node tags.
                                               Np_coordinates                                       // Node coordinates.
                                              );

  Np_size = Np.size ();

  neutrino::done ();                                                                                // Printing message...

  // For each node:
  for(i = 0; i < Np_size; i++)
  {
    node_coordinates.push_back (
    {
      (float)Np_coordinates[3*i + 0],                                                               // Setting node unit "x" coordinate...
      (float)Np_coordinates[3*i + 1],                                                               // Setting node unit "y"coordinate...
      (float)Np_coordinates[3*i + 2],                                                               // Setting node unit "z" coordinate...
      1.0f                                                                                          // Setting node unit "w" coordinate...
    }
                               );                                                                   // Adding node unit to node vector...
  }

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("finding mesh elements for given physical group...");                           // Printing message...

  // Getting element type properties:
  gmsh::model::mesh::getElementProperties (
                                           loc_element_type,                                        // Element type [#].
                                           loc_type_name,                                           // Element type name [string].
                                           loc_type_dimension,                                      // Element type dimension [#].
                                           loc_type_order,                                          // Element type order [#].
                                           T_size,                                                  // Element type number of type nodes [#].
                                           loc_type_node_coordinates,                               // Element type node local coordinates [vector].
                                           loc_type_primary_nodes                                   // Number of primary type nodes [#].
                                          );

  // Getting elements for all entities:
  gmsh::model::mesh::getElementsByType (
                                        loc_element_type,
                                        E,
                                        E_node,
                                        -1,
                                        0,
                                        1
                                       );

  E_size = E.size ();                                                                               // Getting number of elements among all entities...

  // Computing offsets of the elements of the given type:
  for(i = 0)

    // For each "i" node of the elements within the given physical group:
    for(i = 0; i < Np_size; i++)
    {
      neutrino::work ();                                                                            // Getting initial task time...

      // For each "k" element of the given type:
      for(k = 0; k < E_size; k++)
      {
        E_offset[k] =
          // Computing minimum element offset index:
          if(k == 0)
        {
          m_min = 0;                                                                                // Setting minimum element offset index...
        }
        else
        {
          m_min = E_offset[k - 1];                                                                  // Setting minimum element offset index...
        }

        m_max       = E_offset[k];                                                                  // Setting maximum element offset index...

        // For each "m" node in the "k" element of the given type:
        for(m = m_min; m < m_max; m++)
        {
          // Checking whether the "i" node of the given physical group is present in the "k" element of the given type:
          if(E[m] == Np[i])
          {
            group.push_back (k);                                                                    // Adding element index "k" to the group vector...
            loc_group_offset++;                                                                     // Incrementing group offset...
          }
        }

        group_offset.push_back (loc_group_offset);                                                  // Adding the "k" element offset to the element offset vector...
      }

      neutrino::progress ("finding mesh groups... ", 0, loc_nodes, i);                              // Printing progress message...
    }

  neutrino::done ();                                                                                // Printing message...

}

void mesh::get_elements (
                         int loc_element_type
                        )
{
  // NODE VARIABLES:
  std::vector<std::vector<size_t> > loc_node_tag;                                                   // Node tag list.

  int                               loc_entity_dimension;
  int                               loc_entity_tag;

  // ELEMENT VARIABLES:
  std::vector<std::vector<size_t> > loc_element_tag;                                                // Element tag list.
  size_t                            loc_elements;                                                   // Number of elements.
  size_t                            loc_element_offset;                                             // Element offset.

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

  element.clear ();                                                                                 // Clearing element vector...
  element_offset.clear ();                                                                          // Clearing element offset vector...
  loc_elements       = 0;                                                                           // Resetting the number of elements of "j" type...
  loc_element_offset = 0;                                                                           // Resetting element offset...

  // EZOR: 14FEB2021
  // 1. Take all the elements, of a given type, of all entities.
  // 2. For each node of those elements, find the neighbours.
  // 3. Take the nodes of a given physical group.
  // 4. For all those nodes, select their neighbour nodes present in the same physical group.
  // 5. Create a "stiffness" vector containing the physical group tag of the neighbours.

  // 2. From those ones, select only the elements having at least one node (central node of a group) being in a given pyhsical group.
  // 3. All links must have a vector telling in which physical group they stay (for later, for setting the correct stiffness).

  loc_entities = entity_list.size ();                                                               // Getting number of entities...

  for(n = 0; n < loc_entities; n++)
  {
    neutrino::work ();                                                                              // Getting initial task time...

    loc_entity_dimension = entity_list[n].first;                                                    // Getting entity dimension [#]...
    loc_entity_tag       = entity_list[n].second;                                                   // Getting entity tag [#]...

    // Getting entity elements, where:
    // i = type index.
    // m = node index of current element.
    // L = number of element types.
    // M(i) = number of elements per element type.
    // N(m) = number of nodes per element, for each element type.
    gmsh::model::mesh::getElements (
                                    loc_type_list,                                                  // Element type list [L].
                                    loc_element_tag,                                                // Element tag list LxM(i).
                                    loc_node_tag,                                                   // Node tag list Lx[N(1),N(2),...,N(m),N(M(i))].
                                    loc_entity_dimension,                                           // Entity dimension [#].
                                    loc_entity_tag                                                  // Entity tag [#].
                                   );

    loc_types = loc_type_list.size ();                                                              // Getting number of types...

    // Finding the number of elements of "j" type...
    for(i = 0; i < loc_types; i++)
    {
      if(loc_type_list[i] == loc_element_type)
      {
        j            = i;                                                                           // Setting current element type index...
        loc_elements = loc_element_tag[j].size ();                                                  // Getting the number of elements of "j" type...
      }
    }

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

    // For each "k" element of "j" type:
    for(k = 0; k < loc_elements; k++)
    {
      neutrino::work ();                                                                            // Getting initial task time...

      // Getting the coordinates of the "m" node in the "k" element of "j" type:
      for(m = 0; m < loc_type_nodes; m++)
      {
        element.push_back ((loc_node_tag[j][k*loc_type_nodes + m]) - 1);                            // Adding the type node to the "k" element unit...
      }

      loc_element_offset += loc_type_nodes;                                                         // Incrementing element offset...
      element_offset.push_back (loc_element_offset);                                                // Adding the "k" element unit to the element vector...
      neutrino::progress ("finding mesh elements... ", 0, loc_elements, k);                         // Printing progress message...
    }

    neutrino::done ();                                                                              // Printing message...
  }

  void mesh::get_groups (
                         int loc_entity_dimension,
                         int loc_entity_tag,
                         int loc_element_type
                        )
  {
    // NODE VARIABLES:
    std::vector<size_t>               loc_node_list;                                                // Node list.
    std::vector<double>               loc_node_coordinates;                                         // Node coordinates.
    std::vector<double>               loc_node_parametric_coordinates;                              // Node parametric coordinates.
    nu_float4_structure               loc_node_unit;                                                // Node unit.
    size_t                            loc_nodes;                                                    // Number of nodes.

    // ELEMENT VARIABLES:
    std::vector<std::vector<size_t> > loc_element_tag;                                              // Element tag list.
    size_t                            loc_elements;                                                 // Number of elements.
    size_t                            loc_element_offsets;                                          // Number of element offsets.

    // GROUP VARIABLES:
    size_t                            loc_group_offset;                                             // Group offset.

    // TYPE VARIABLES:
    std::vector<int>                  loc_type_list;                                                // Element type list.
    size_t                            loc_types;                                                    // Number of element types.
    std::string                       loc_type_name;                                                // Element type name.
    int                               loc_type_dimension;                                           // Element type dimension.
    int                               loc_type_order;                                               // Element type order.
    std::vector<double>               loc_type_node_coordinates;                                    // Element type node coordinates.
    int                               loc_type_primary_nodes;                                       // Element primary nodes
    int                               loc_type_nodes;                                               // Number of type nodes.

    // INDICES:
    size_t                            i;                                                            // Node index.
    size_t                            j;                                                            // Current type.
    size_t                            k;                                                            // Element index.
    size_t                            m;                                                            // Index of current element node stride.
    size_t                            m_min;                                                        // Minimum index of current element stride.
    size_t                            m_max;                                                        // Maximum index of current element stride.

    loc_nodes           = node.size ();                                                             // Getting the number of nodes...
    loc_elements        = element.size ();                                                          // Getting the number of elements...
    loc_element_offsets = element_offset.size ();                                                   // Getting the number of element offsets...
    group.clear ();                                                                                 // Resetting group vector...
    group_offset.clear ();                                                                          // Resetting group indices vector...
    loc_group_offset    = 0;                                                                        // Resetting group offset...

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

    // For each "i" node of the elements of "j" type:
    for(i = 0; i < loc_nodes; i++)
    {
      neutrino::work ();                                                                            // Getting initial task time...

      // For each "k" element of "j" type:
      for(k = 0; k < loc_element_offsets; k++)
      {
        // Computing minimum element offset index:
        if(k == 0)
        {
          m_min = 0;                                                                                // Setting minimum element offset index...
        }
        else
        {
          m_min = element_offset[k - 1];                                                            // Setting minimum element offset index...
        }

        m_max = element_offset[k];                                                                  // Setting maximum element offset index...

        // For each "m" node in the "k" element of "j" type:
        for(m = m_min; m < m_max; m++)
        {
          // Checking whether the "i" node is present in the "k" element or not:
          if(element[m] == i)
          {
            group.push_back (k);                                                                    // Adding element index "k" to the group vector...
            loc_group_offset++;                                                                     // Incrementing group offset...
          }
        }

        group_offset.push_back (loc_group_offset);                                                  // Adding the "k" element offset to the element offset vector...
      }

      neutrino::progress ("finding mesh groups... ", 0, loc_nodes, i);                              // Printing progress message...
    }

    neutrino::done ();                                                                              // Printing message...
  }

  void mesh::get_neighbours (
                             int loc_entity_dimension,
                             int loc_entity_tag,
                             int loc_element_type
                            )

  {
    // NODE VARIABLES:
    std::vector<std::vector<size_t> > loc_node_tag;                                                 // Node tag list.
    size_t                            loc_nodes;                                                    // Number of nodes.

    // ELEMENT VARIABLES:
    std::vector<std::vector<size_t> > loc_element_tag;                                              // Element tag list.
    size_t                            loc_elements;                                                 // Number of elements.
    size_t                            loc_element_offsets;                                          // Number of element offsets.

    // TYPE VARIABLES:
    std::vector<int>                  loc_type_list;                                                // Element type list.
    size_t                            loc_types;                                                    // Number of element types.
    std::string                       loc_type_name;                                                // Element type name.
    int                               loc_type_dimension;                                           // Element type dimension.
    int                               loc_type_order;                                               // Element type order.
    std::vector<double>               loc_type_node_coordinates;                                    // Element type node coordinates.
    int                               loc_type_primary_nodes;                                       // Element primary nodes
    int                               loc_type_nodes;                                               // Number of type nodes.

    // NEIGHBOUR VARIABLES:
    std::vector<size_t>               loc_neighbour;                                                // Neighbour unit.
    GLint                             loc_neighbours;                                               // Number of neighbours.
    GLint                             loc_neighbour_offset;                                         // Neighbour offset.
    GLfloat                           loc_link_x;                                                   // Link "x" coordinate.
    GLfloat                           loc_link_y;                                                   // Link "y" coordinate.
    GLfloat                           loc_link_z;                                                   // Link "z" coordinate.
    GLfloat                           loc_link_w;                                                   // Link "w" coordinate.

    // INDICES:
    size_t                            i;                                                            // Node index.
    size_t                            j;                                                            // Current type.
    size_t                            k;                                                            // Element index.
    size_t                            m;                                                            // Index of current element node stride.
    size_t                            m_min;                                                        // Minimum index of current element stride.
    size_t                            m_max;                                                        // Maximum index of current element stride.
    size_t                            n;                                                            // Node index of current neighbour unit.
    size_t                            s;                                                            // Stride index.

    // Getting entity elements, where:
    // i = type index.
    // m = node index of current element.
    // L = number of element types.
    // M(i) = number of elements per element type.
    // N(m) = number of nodes per element, for each element type.
    gmsh::model::mesh::getElements (
                                    loc_type_list,                                                  // Element type list [L].
                                    loc_element_tag,                                                // Element tag list LxM(i).
                                    loc_node_tag,                                                   // Node tag list Lx[N(1),N(2),...,N(m),N(M(i))].
                                    loc_entity_dimension,                                           // Entity dimension [#].
                                    loc_entity_tag                                                  // Entity tag [#].
                                   );

    loc_types = loc_type_list.size ();                                                              // Getting number of types...

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

    loc_nodes            = node.size ();                                                            // Getting the number of nodes...
    loc_element_offsets  = element_offset.size ();                                                  // Getting the number of element offsets...
    loc_neighbour_offset = 0;                                                                       // Resetting the neighbour offset...
    loc_neighbour.clear ();                                                                         // Clearing neighbour unit vector...

    // For each "i" node of the elements of "j" type:
    for(i = 0; i < loc_nodes; i++)
    {
      neutrino::work ();                                                                            // Getting initial task time...

      // For each "k" element of "j" type:
      for(k = 0; k < loc_element_offsets; k++)
      {
        // Computing minimum element offset index:
        if(k == 0)
        {
          m_min = 0;                                                                                // Setting minimum element offset index...
        }
        else
        {
          m_min = element_offset[k - 1];                                                            // Setting minimum element offset index...
        }

        m_max = element_offset[k];                                                                  // Setting maximum element offset index...

        // For each "m" node in the "k" element of "j" type:
        for(m = m_min; m < m_max; m++)
        {
          // Checking whether the "k" element of "j" type contains the "i" central node:
          if((element[m] == i))
          {
            loc_neighbour.insert (loc_neighbour.end (), element[m_min], element[m_max]);            // Appending the "k" element type nodes to the neighbour unit...
            loc_neighbour.erase (loc_neighbour.begin () + (m - m_min));                             // Erasing the central node from the neighbour unit...
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
                                                        loc_neighbour.begin (),                     // Beginning of index vector.
                                                        loc_neighbour.end ()                        // End of index vector.
                                                       )
                                          )
                           );

      loc_neighbours        = loc_neighbour.size ();                                                // Counting neighbour nodes...
      loc_neighbour_offset += loc_neighbours;                                                       // Incrementing neighbour offset index...
      neighbour_offset.push_back (loc_neighbour_offset);                                            // Setting neighbour offset...

      // For each "s" neighbour node in the "i" stride:
      for(s = 0; s < loc_neighbours; s++)
      {
        n          = loc_neighbour[s];                                                              // Getting neighbour index...
        neighbour.push_back (n);                                                                    // Setting neighbour vector...
        loc_link_x = node[n].x - node[i].x;                                                         // Setting link "x" coordinate...
        loc_link_y = node[n].y - node[i].y;                                                         // Setting link "x" coordinate...
        loc_link_z = node[n].z - node[i].z;                                                         // Setting link "x" coordinate...
        loc_link_w = 0.0f;                                                                          // Setting link "x" coordinate...

        // Setting neighbour link vector:
        neighbour_link.push_back (
        {
          loc_link_x,                                                                               // Setting link "x" component...
          loc_link_y,                                                                               // Setting link "y" component...
          loc_link_z,                                                                               // Setting link "z" component...
          loc_link_w                                                                                // Setting link "w" component...
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

      loc_neighbour.clear ();                                                                       // Clearing neighbour unit for next "i"...

      neutrino::progress ("finding mesh neighbours... ", 0, loc_nodes, i);                          // Printing progress message...
    }

    neutrino::done ();                                                                              // Printing message...
  }

  void mesh::get_physicals (
                            size_t loc_physical_group_dim,                                          // Physical group dimension [#].
                            size_t loc_physical_group_tag                                           // Physical group tag [#].
                           )
  {



  }

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
  mesh::~mesh()
  {
    gmsh::finalize ();                                                                              // Finalizing GMSH...
  }
