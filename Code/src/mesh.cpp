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
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
  entities = entity_list.size ();                                                                   // Getting number of entities...

  std::vector<std::size_t> types_vector;

  std::cout << "number of entities = " << entities << std::endl;

  for(entity = 0; entity < entities; entity++)
  {
    std::cout << "entity = " << entity << std::endl;

    entity_dimension = entity_list[entity].first;                                                   // Getting entity dimension [#]...
    entity_tag       = entity_list[entity].second;                                                  // Getting entity tag [#]...

    // Getting entity nodes:
    // where:
    // N = number of nodes
    // dim = entity dimension
    gmsh::model::mesh::getNodes (
                                 node_list,                                                         // Node tags list [N].
                                 node_coordinates,                                                  // Node coordinates list [3*N].
                                 node_parametric_coordinates,                                       // Node parametric coordinates [dim*N].
                                 entity_dimension,                                                  // Entity dimension [#].
                                 entity_tag                                                         // Entity tag [#].
                                );

    int       i;
    gmsh_node pippo;

    for(i = 0; i < node_list.size (); i++)
    {
      pippo.tag = node_list[i];
    }

    nodes.push_back (node_list);
    // Finding the index corresponding to each node tag in the node tag list:
    loc_simplicialcomplex->data[node] = std::distance (
                                                       node_list.begin (),
                                                       std::find (
                                                                  nodeTags_list.begin (),
                                                                  nodeTags_list.end (),
                                                                  elemNodeTags[type][vertex]
                                                                 )
                                                      );                                            // Setting number of nodes...
    std::cout << "number of nodes = " << node_list.size () << std::endl;

    // Getting entity simplexes:
    // where:
    // i = index of simplex type.
    // j = index of nodes per simplex, for each simplex type.
    // L = number of simplex types.
    // M(i) = number of simplexes per simplex type.
    // N(j) = number of nodes per simplex, for each simplex type.

    gmsh::model::mesh::getElements (
                                    type_list,                                                      // Element type list [L].
                                    element_array,                                                  // Element tag array LxM(i).
                                    node_array,                                                     // Node tag array Lx[N(1),N(2),...,N(j),N(M(i))].
                                    entity_dimension,                                               // Entity dimension [#].
                                    entity_tag                                                      // Entity tag [#].
                                   );

    types.push_back (type_list);                                                                    // Setting simplex types...
    simplexes.push_back (element_array);                                                            // Getting number of simplexes...
  }

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
  /*
     gmsh::model::getEntities (entity_list);                                                           // Getting entity list...
     entities = entity_list.size ();                                                                   // Getting number of entities...

     for(entity = 0; entity < entities; entity++)
     {
     entity_dimension = entity_list[entity].first;                                                   // Getting entity dimension...
     entity_tag       = entity_list[entity].second;                                                  // Getting entity tag...

     // Getting entity mesh nodes:
     gmsh::model::mesh::getNodes (
                                 node_list,                                                         // Node tags.
                                 nodeCoords,                                                        // Node coordinates.
                                 nodeParams,                                                        // Node parametric coordinates.
                                 entity_dimension,                                                  // Entity dimension.
                                 entity_tag                                                         // Entity tag.
                                );

     nodeTags_num = node_list.size ();                                                               // Getting number of nodeTags...

     for(node = 0; node < nodeTags_num; node++)
     {
      loc_node->data[node].x = (cl_float)nodeCoords[3*node + 0];                                    // Setting "x" coordinate...
      loc_node->data[node].y = (cl_float)nodeCoords[3*node + 1];                                    // Setting "y" coordinate...
      loc_node->data[node].z = (cl_float)nodeCoords[3*node + 2];                                    // Setting "z" coordinate...
      loc_node->data[node].w = (cl_float)1.0;                                                       // Setting "w" coordinate...
      nodeTags_list.push_back (nodeTags[node]);                                                     // Setting node tag in the list...
     }

     // Getting entity mesh elements:
     gmsh::model::mesh::getElements (
                                    type_list,                                                      // Element type list.
                                    element_list,                                                   // Element tag list.
                                    elemNodeTags,                                                   // Node tag list, for each element.
                                    entity_dimension,                                               // Entity dimension.
                                    entity_tag                                                      // Entity tag.
                                   );

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
   */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
