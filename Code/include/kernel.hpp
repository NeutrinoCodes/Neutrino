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
  char          kernel_home[MAX_PATH_SIZE];                                     // Kernel home directory.
  char          kernel_file_name[MAX_PATH_SIZE];                                // Kernel file name.
  char          compiler_options[MAX_PATH_SIZE];                                // JIT complier options string.
  char*         source;                                                         // Kernel source.
  size_t        source_size;                                                    // Kernel source size [characters].
  cl_program    program;                                                        // Kernel program.
  size_t        size_i;                                                         // Kernel size (i-index).
  size_t        size_j;                                                         // Kernel size (j-index).
  size_t        size_k;                                                         // Kernel size (k-index).
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
             neutrino*   loc_baseline,                                          // Neutrino baseline.
             const char* loc_kernel_home,                                       // Kernel home directory.
             const char* loc_kernel_file_name,                                  // OpenCL kernel file name.
             size_t      loc_kernel_size_i,                                     // OpenCL kernel size (i-index).
             size_t      loc_kernel_size_j,                                     // OpenCL kernel size (j-index).
             size_t      loc_kernel_size_k                                      // OpenCL kernel size (k-index).
            );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// SETARG "float1" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               float1* loc_data,                                                // float1 object.
               cl_uint loc_layout_index                                         // Layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "int1" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               int1*   loc_data,                                                // int1 object.
               cl_uint loc_layout_index                                         // Layout index.
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
