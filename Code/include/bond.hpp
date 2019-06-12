#ifndef bond_hpp
#define bond_hpp

#include "neutrino.hpp"
#include "kernel.hpp"
#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// LINK CLASS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class bond
{
private:
  neutrino*       baseline;                                                     // Neutrino baseline.
  // OpenCL error get function:
  const char* get_error (
                         cl_int loc_error                                       // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                     // Error code.
                          );

  cl_context      opencl_context;                                               // OpenCL context.

public:
  bond_structure* bond_data[NEIGHBOURS_NUM];                                    // Bond data structure.
  cl_mem          bond_buffer;                                                  // OpenCL bond data memory buffer.
  int1            bond_size;                                                    // Data size.

  #ifdef USE_GRAPHICS
    GLuint        bond_vao;                                                     // Bond VAO.
    GLuint        bond_vbo;                                                     // Bond VBO.
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CONSTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  bond();
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "INIT" FUNCTION: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   init (
               neutrino* loc_baseline,                                          // Neutrino baseline.
               int1      loc_bond_size                                          // Data size.
              );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "SET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   set_neighbour_index (
                              int1 loc_node_index,                              // Node index.
                              int1 loc_neighbour_index,                         // Neighbour index.
                              int1 loc_neighbour_id[NEIGHBOURS_NUM]             // Neighbour id.
                             );
  void   set_stiffness (
                        int1   loc_node_index,                                  // Node index.
                        float1 loc_value,                                       // Data value.
                        int1   loc_neighbour_id[NEIGHBOURS_NUM]                 // Neighbour id.
                       );
  void   set_damping (
                      int1   loc_node_index,                                    // Node index.
                      float1 loc_value,                                         // Data value.
                      int1   loc_neighbour_id[NEIGHBOURS_NUM]                   // Neighbour id.
                     );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "GET" FUNCTIONS: /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  int1   get_neighbour_index (
                              int1 loc_node_index,                              // Node index.
                              int1 loc_neighbour_id                             // Neighbour id.
                             );
  float1 get_stiffness (
                        int1 loc_node_index,                                    // Node index.
                        int1 loc_neighbour_id                                   // Neighbour id.
                       );
  float1 get_damping (
                      int1 loc_node_index,                                      // Node index.
                      int1 loc_neighbour_id                                     // Neighbour id.
                     );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// "CONTROL" FUNCTIONS: ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   push (
               kernel* loc_kernel,                                              // Kernel.
               queue*  loc_queue                                                // OpenCL queue.
              );
  void   pull (
               queue* loc_queue                                                 // OpenCL queue.
              );
  void   acquire (
                  queue* loc_queue                                              // OpenCL queue.
                 );
  void   release (
                  queue* loc_queue                                              // OpenCL queue.
                 );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~bond();
};

#endif
