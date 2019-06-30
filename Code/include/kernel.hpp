/// @file

#ifndef kernel_hpp
#define kernel_hpp

#include "neutrino.hpp"
#include "host_datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class kernel
{
private:
  neutrino*     baseline;                                                       // Neutrino baseline.
  cl_device_id* device_id;                                                      // Device ID array.

public:
  cl_kernel     kernel_id;                                                      // Kernel id.
  char*         file_name;                                                      // Kernel file name.
  char*         source;                                                         // Kernel source.
  size_t        source_size;                                                    // Kernel source size [characters].
  cl_program    program;                                                        // Kernel program.
  size_t*       size;                                                           // Kernel size(s) [size_t x dimension array].
  cl_uint       dimension;                                                      // Kernel dimension.
  cl_event      event;                                                          // Kernel event.
  char*         log_value;                                                      // OpenCL compiler log value array.
  size_t        log_size;                                                       // OpenCL compiler log size array.

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// CONSTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  kernel();
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// INIT ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino* loc_baseline,                                            // Neutrino baseline.
             char*     loc_kernel_filename,                                     // OpenCL kernel file name.
             size_t*   loc_kernel_size,                                         // OpenCL kernel size.
             cl_uint   loc_kernel_dimension                                     // OpenCL kernel dimension.
            );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// SETARG "float4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               float4* loc_data,                                                // Float4 object.
               cl_uint loc_layout_index                                         // Layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "int4" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               int4*   loc_data,                                                // Int4 object.
               cl_uint loc_layout_index                                         // Layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "point" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               point* loc_data,                                                 // Point object.
               GLuint loc_layout_index                                          // Layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "color" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               color* loc_data,                                                 // Color object.
               GLuint loc_layout_index                                          // Layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~kernel();
};

#endif
