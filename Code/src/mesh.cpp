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

void mesh::init
(
 neutrino* loc_baseline                                                                             // Neutrino baseline.
)
{
  baseline = loc_baseline;                                                                          // Getting Neutrino baseline...
  baseline->action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  baseline->done ();                                                                                // Printing message...
}

void mesh::read_msh (
                     std::string loc_file_name                                                      // GMSH .msh file name.
                    )
{
  size_t                                 i;
  size_t                                 j;
  size_t                                 k;
  size_t                                 n;
  size_t                                 dim;
  size_t                                 tag;
  std::vector<std::pair<int, int> >      entities;
  std::vector<std::size_t>               nodeTags;
  std::vector<double>                    nodeCoords;
  std::vector<double>                    nodeParams;
  std::vector<int>                       elemTypes;
  std::vector<std::vector<std::size_t> > elemTags;
  std::vector<std::vector<std::size_t> > elemNodeTags;

  std::string                            elemName;
  int                                    order;
  int                                    numNodes;
  int                                    numPrimaryNodes;
  std::vector<double>                    param;
  int                                    d;

  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...
  gmsh::model::getEntities (entities);                                                              // Getting all entities...

  for(i = 0; i < entities.size (); i++)
  {
    dim = entities[i].first;
    tag = entities[i].second;
    gmsh::model::mesh::getNodes (nodeTags, nodeCoords, nodeParams, dim, tag);                       // Getting the mesh nodes for each entity...

    for(j = 0; j < nodeTags.size (); j++)
    {
      std::cout << nodeTags[j]
                << " "
                << nodeCoords[3*j + 0]
                << ","
                << nodeCoords[3*j + 1]
                << ","
                << nodeCoords[3*j + 2]
                << std::endl;
    }

    gmsh::model::mesh::getElements (elemTypes, elemTags, elemNodeTags, dim, tag);                   // Getting the mesh elements for each entity...

    for(j = 0; j < elemTypes.size (); j++)
    {
      gmsh::model::mesh::getElementProperties (
                                               elemTypes[j],
                                               elemName,
                                               d,
                                               order,
                                               numNodes,
                                               param,
                                               numPrimaryNodes
                                              );

      std::cout << "element type = " << elemTypes[j] << std::endl;
      std::cout << "elementNodeTags.size = " << elemNodeTags[j].size ()<< std::endl;

      for(k = 0; k < elemNodeTags[j].size (); k += 1)
      {
        for(n = 0; n < numNodes; n++)
        {
          std::cout << elemNodeTags[j][k + n] << " ";
        }

        std::cout << std::endl;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
