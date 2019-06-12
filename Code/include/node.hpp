#ifndef node_hpp
#define node_hpp

#include "neutrino.hpp"
#include "kernel.hpp"
#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// NODE CLASS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class node
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
  node_structure* node_data;                                                    // Node data structure.
  cl_mem          node_buffer;                                                  // OpenCL NODE data memory buffer.
  int1            node_size;                                                    // Data size.

  #ifdef USE_GRAPHICS
    GLuint        node_vao;                                                     // Node VAO.
    GLuint        node_vbo;                                                     // Node VBO.
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CONSTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  node();
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "INIT" FUNCTION: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   init (
               neutrino* loc_baseline,                                          // Neutrino baseline.
               int1      loc_node_size                                          // Data number.
              );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "SET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   set_position (
                       int1   loc_index,                                        // Data index.
                       float4 loc_value                                         // Data value.
                      );
  void   set_velocity (
                       int1   loc_index,                                        // Data index.
                       float4 loc_value                                         // Data value.
                      );
  void   set_acceleration (
                           int1   loc_index,                                    // Data index.
                           float4 loc_value                                     // Data value.
                          );
  void   set_color (
                    int1   loc_index,                                           // Data index.
                    color4 loc_value                                            // Data value.
                   );
  void   set_mass (
                   int1   loc_index,                                            // Data index.
                   float1 loc_value                                             // Data value.
                  );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "GET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  float4 get_position (
                       int1 loc_index                                           // Data index.
                      );
  float4 get_velocity (
                       int1 loc_index                                           // Data index.
                      );
  float4 get_acceleration (
                           int1 loc_index                                       // Data index.
                          );
  color4 get_color (
                    int1 loc_index                                              // Data index.
                   );
  float1 get_mass (
                   int1 loc_index                                               // Data index.
                  );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// "CONTROL" FUNCTIONS:  ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   push (
               queue* loc_queue                                                 // OpenCL queue.
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
  ~node();
};

#endif
