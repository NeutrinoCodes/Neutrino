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
                 neutrino*   loc_baseline,                                                          ///< Neutrino baseline.
                 std::string loc_file_name                                                          ///< GMSH .msh file name.
                )
{
  baseline  = loc_baseline;                                                                         // Getting Neutrino baseline...
  baseline->action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  nodes     = 0;                                                                                    // Resetting number of nodes...
  simplexes = 0;                                                                                    // Resetting number of simplexes...
  complexes = 0;                                                                                    // Resetting number of complexes...
  entities  = entity_list.size ();                                                                  // Getting number of entities...

  for(entity = 0; entity < entities; entity++)
  {
    dim    = entity_list[entity].first;                                                             // Getting entity dimension...
    tag    = entity_list[entity].second;                                                            // Getting entity tag...

    // Getting entity mesh nodes:
    gmsh::model::mesh::getNodes (
                                 nodeTags,
                                 nodeCoords,
                                 nodeParams,
                                 dim,
                                 tag
                                );
    nodes += nodeTags.size ();                                                                      // Accumulating number of nodes...

    gmsh::model::mesh::getElements (type_list, element_list, elemNodeTags, dim, tag);               // Getting entity mesh elements...
    types  = type_list.size ();                                                                     // Getting number of elemTypes...

    for(type = 0; type < types; type++)
    {
      // Getting element properties:
      gmsh::model::mesh::getElementProperties (
                                               type_list[type],                                     // Element type.
                                               elemName,                                            // Element name.
                                               d,                                                   // Element dimension.
                                               order,                                               // Element order.
                                               vertexes_num,                                        // Number of vertexes.
                                               param,                                               // Local coordinates of the vertexes.
                                               numPrimaryNodes                                      // Number of primary vertexes.
                                              );

      elements = element_list[type].size ();                                                        // Getting number of elemTags...

      for(element = 0; element < elements; element++)
      {
        simplexes++;                                                                                // Accumulating number of simplexes...
      }
    }
  }

  std::cout << "number of nodes = " << nodes << std::endl;
  std::cout << "number of simplexes = " << simplexes << std::endl;

  baseline->done ();                                                                                // Printing message...
}

void mesh::read_msh (
                     float4G* loc_node,                                                             // Node coordinates.
                     int1*    loc_simplicialcomplex,                                                // Simplicial complex.
                     int1*    loc_order,                                                            // Simplex orders.
                     int1*    loc_cell,                                                             // Cell indexes.
                     int1*    loc_adjacencies                                                       // Simplex adjacencies.
                    )
{
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  entities = entity_list.size ();                                                                   // Getting number of entities...

  for(entity = 0; entity < entities; entity++)
  {
    dim          = entity_list[entity].first;                                                       // Getting entity dimension...
    tag          = entity_list[entity].second;                                                      // Getting entity tag...
    gmsh::model::mesh::getNodes (nodeTags, nodeCoords, nodeParams, dim, tag);                       // Getting entity mesh nodes...
    nodeTags_num = nodeTags.size ();                                                                // Getting number of nodeTags...

    for(node = 0; node < nodeTags_num; node++)
    {
      loc_node->data[node].x = (cl_float)nodeCoords[3*node + 0];                                    // Setting "x" coordinate...
      loc_node->data[node].y = (cl_float)nodeCoords[3*node + 1];                                    // Setting "y" coordinate...
      loc_node->data[node].z = (cl_float)nodeCoords[3*node + 2];                                    // Setting "z" coordinate...
      loc_node->data[node].w = (cl_float)1.0;                                                       // Setting "w" coordinate...
      nodeTags_list.push_back (nodeTags[node]);                                                     // Setting node tag in the list...
    }

    gmsh::model::mesh::getElements (type_list, element_list, elemNodeTags, dim, tag);               // Getting entity mesh elements...
    types = type_list.size ();                                                                      // Getting number of elemTypes...

    for(type = 0; type < types; type++)
    {
      // Getting element properties:
      gmsh::model::mesh::getElementProperties (
                                               type_list[type],                                     // Element type.
                                               elemName,                                            // Element name.
                                               d,                                                   // Element dimension.
                                               order,                                               // Element order.
                                               vertexes_num,                                        // Number of vertexes.
                                               param,                                               // Local coordinates of the vertexes.
                                               numPrimaryNodes                                      // Number of primary vertexes.
                                              );

      elements = element_list[type].size ();                                                        // Getting number of elemTags...

      for(element = 0; element < elemTags_num; element++)
      {
        simplex                  = type*types + element;                                            // Setting simplex index...
        loc_order->data[simplex] = vertexes_num;                                                    // Setting simplex order...
        simplexTags_list.push_back (element_list[type][element]);                                   // Setting simplex tag in list...

        for(vertex = 0; vertex < vertexes_num; vertex++)
        {
          node                              = type*types*elemTags_num +
                                              element*elemTags_num +
                                              vertex;

          // Finding the index corresponding to each node tag in the node tag list:
          loc_simplicialcomplex->data[node] = std::distance (
                                                             nodeTags_list.begin (),
                                                             std::find (
                                                                        nodeTags_list.begin (),
                                                                        nodeTags_list.end (),
                                                                        elemNodeTags[type][vertex]
                                                                       )
                                                            );
        }
      }
    }
  }

  std::cout << "simplexTags_list = " << simplexTags_list.size () << std::endl;

  nodeTags_list.clear ();                                                                           // Clearing full node array...
  simplexTags_list.clear ();                                                                        // Clearing full simplex array...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
