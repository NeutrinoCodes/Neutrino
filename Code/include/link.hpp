#ifndef link_hpp
#define link_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"
#include "data.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// LINK CLASS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class link
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
  link_structure* link_data[NEIGHBOURS_NUM];                                    // Link data structure.
  cl_mem          link_buffer;                                                  // OpenCL link data memory buffer.
  int1            link_size;                                                    // Data size.

  #ifdef USE_GRAPHICS
    GLuint        link_vao;                                                     // Node VAO.
    GLuint        link_vbo;                                                     // Node VBO.
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CONSTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  link();
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "INIT" FUNCTION: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   init (
               neutrino* loc_baseline,                                          // Neutrino baseline.
               int1      loc_link_size,                                         // Data number.
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
               queue* loc_queue,                                                // OpenCL queue.
              );
  void   pull (
               queue* loc_queue,                                                // OpenCL queue.
              );
  void   acquire (
                  queue* loc_queue,                                             // OpenCL queue.
                 );
  void   release (
                  queue* loc_queue,                                             // OpenCL queue.
                 );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~link();
};

#endif
