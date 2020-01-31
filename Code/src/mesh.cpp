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
  gmsh::model::add ("boolean");
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  baseline->done ();                                                                                // Printing message...
}

void mesh::read_msh (
                     std::string loc_file_name                                                      ///< GMSH .msh file name.
                    )
{
  size_t                            i;
  size_t                            j;
  size_t                            k;

  gmsh::open (loc_file_name.c_str ());

  // get all elementary entities in the model
  std::vector<std::pair<int, int> > entities;
  gmsh::model::getEntities (entities);

  for(i = 0; i < entities.size (); i++)
  {
    // get the mesh nodes for each elementary entity
    std::vector<std::size_t> nodeTags;
    std::vector<double>      nodeCoords, nodeParams;
    int                      dim = entities[i].first, tag = entities[i].second;
    gmsh::model::mesh::getNodes (nodeTags, nodeCoords, nodeParams, dim, tag);

    //std::cout << "nodeTags.size = " << nodeTags.size () << std::endl;
    //std::cout << "nodeCoords.size = " << nodeCoords.size () << std::endl;

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

    // get the mesh elements for each elementary entity
    std::vector<int>                       elemTypes;
    std::vector<std::vector<std::size_t> > elemTags, elemNodeTags;
    gmsh::model::mesh::getElements (elemTypes, elemTags, elemNodeTags, dim, tag);

    std::cout << "pippo" << std::endl;

    for(j = 0; j < elemTags.size (); j++)
    {
      std::cout << "element types " << elemTypes[j] << std::endl;

      for(k = 0; k < elemTypes[j]; k++)
      {
        std::cout << elemTags[j][k]
                  << " "
                  << std::endl;
      }

      /*<< " "
         << elemNodeTags[4*j + 0]
         << ","
         << elemNodeTags[4*j + 1]
         << ","
         << elemNodeTags[4*j + 2]
         << ","
         << elemNodeTags[4*j + 3]
       */

    }


    // report some statistics
    int              numElem = 0;

    for(unsigned int i = 0; i < elemTags.size (); i++)
      numElem += elemTags[i].size ();

    std::string      type;
    gmsh::model::getType (dim, tag, type);
    std::cout << nodeTags.size () << " mesh nodes and "
              << numElem << " mesh elements on entity ("
              << dim << "," << tag << ") of type " << type << "\n";
    std::vector<int> partitions;
    gmsh::model::getPartitions (dim, tag, partitions);
    if(partitions.size ())
    {
      std::cout << " - Partition tag(s):";

      for(unsigned int i = 0; i < partitions.size (); i++)
        std::cout << " " << partitions[i];

      int parentDim, parentTag;
      gmsh::model::getParent (dim, tag, parentDim, parentTag);
      std::cout << " - parent entity (" << parentDim << "," << parentTag << ")\n";
    }

    for(unsigned int i = 0; i < elemTypes.size (); i++) {
      std::string         name;
      int                 d, order, numv, numpv;
      std::vector<double> param;
      gmsh::model::mesh::getElementProperties (
                                               elemTypes[i],
                                               name,
                                               d,
                                               order,
                                               numv,
                                               param,
                                               numpv
                                              );
      std::cout << " - Element type: " << name << ", order " << order << "\n";
      std::cout << "   with " << numv << " nodes in param coord: (";

      for(unsigned int j = 0; j < param.size (); j++)
        std::cout << param[j] << " ";

      std::cout << ")\n";
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
