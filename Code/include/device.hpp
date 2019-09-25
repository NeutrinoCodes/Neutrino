/// @file   device.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  This header file contains the declaration of an "OpenCL device" class.

#ifndef device_hpp
#define device_hpp

  #include "neutrino.hpp"
  #include "data_classes.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "DEVICE" CLASS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class device
{
private:
  neutrino*   baseline;                                                                             // Neutrino baseline.
  std::string parameter_value;                                                                      // Parameter value.
  // OpenCL get info value function:
  std::string                 get_string (
                                          cl_device_id   loc_platform_id,                           // Platform ID.
                                          cl_device_info loc_parameter_name                         // Paramenter name.
                                         );
  cl_uint                     get_cl_uint (
                                           cl_device_id   loc_device_id,                            // OpenCL device ID.
                                           cl_device_info loc_parameter_name                        // Parameter name.
                                          );
  cl_bool                     get_cl_bool (
                                           cl_device_id   loc_device_id,                            // OpenCL device ID.
                                           cl_device_info loc_parameter_name                        // Parameter name.
                                          );
  cl_device_fp_config         get_cl_device_fp_config (
                                                       cl_device_id   loc_device_id,                // OpenCL device ID.
                                                       cl_device_info loc_parameter_name            // Parameter name.
                                                      );
  cl_device_exec_capabilities get_cl_device_exec_capabilities (
                                                               cl_device_id   loc_device_id,        // OpenCL device ID.
                                                               cl_device_info loc_parameter_name    // Parameter name.
                                                              );
  cl_ulong                    get_cl_ulong (
                                            cl_device_id   loc_device_id,                           // OpenCL device ID.
                                            cl_device_info loc_parameter_name                       // Parameter name.
                                           );
  cl_device_mem_cache_type    get_cl_device_mem_cache_type (
                                                            cl_device_id   loc_device_id,           // OpenCL device ID.
                                                            cl_device_info loc_parameter_name       // Parameter name.
                                                           );
  size_t                      get_size_t (
                                          cl_device_id   loc_device_id,                             // OpenCL device ID.
                                          cl_device_info loc_parameter_name                         // Parameter name.
                                         );
  cl_device_local_mem_type    get_cl_device_local_mem_type (
                                                            cl_device_id   loc_device_id,           // OpenCL device ID.
                                                            cl_device_info loc_parameter_name       // Parameter name.
                                                           );
  cl_platform_id              get_cl_platform_id (
                                                  cl_device_id   loc_device_id,                     // OpenCL device ID.
                                                  cl_device_info loc_parameter_name                 // Parameter name.
                                                 );
  cl_device_type              get_cl_device_type (
                                                  cl_device_id   loc_device_id,                     // OpenCL device ID.
                                                  cl_device_info loc_parameter_name                 // Parameter name.
                                                 );
  cl_command_queue_properties get_cl_command_queue_properties (
                                                               cl_device_id   loc_device_id,        // OpenCL device ID.
                                                               cl_device_info loc_parameter_name    // Parameter name.
                                                              );

public:
  cl_device_id                id;                                                                   // OpenCL device id.
  cl_uint                     address_bits;
  cl_bool                     available;
  cl_bool                     compiler_available;
  cl_device_fp_config         double_fp_config;
  cl_bool                     endian_little;
  cl_bool                     error_correction_support;
  cl_device_exec_capabilities execution_capabilities;
  std::string                 extensions;
  cl_ulong                    global_mem_cache_size;
  cl_device_mem_cache_type    global_mem_cache_type;
  cl_uint                     global_mem_cacheline_size;
  cl_ulong                    global_mem_size;
  cl_device_fp_config         half_fp_config;
  cl_bool                     image_support;
  size_t                      image2D_max_height;
  size_t                      image2D_max_width;
  size_t                      image3D_max_depth;
  size_t                      image3D_max_height;
  size_t                      image3D_max_width;
  cl_ulong                    local_mem_size;
  cl_device_local_mem_type    local_mem_type;
  cl_uint                     max_clock_frequency;
  cl_uint                     max_compute_units;
  cl_uint                     max_constant_args;
  cl_ulong                    max_constant_buffer_size;
  cl_ulong                    max_mem_alloc_size;
  size_t                      max_parameter_size;
  cl_uint                     max_read_image_args;
  cl_uint                     max_samplers;
  size_t                      max_work_group_size;
  cl_uint                     max_work_item_dimensions;
  //std::string                 max_work_item_sizes;
  cl_uint                     max_write_image_args;
  cl_uint                     mem_base_addr_align;
  cl_uint                     min_data_type_align_size;
  std::string                 name;
  cl_platform_id              platform;
  cl_uint                     preferred_vector_width_char;
  cl_uint                     preferred_vector_width_short;
  cl_uint                     preferred_vector_width_int;
  cl_uint                     preferred_vector_width_long;
  cl_uint                     preferred_vector_width_float;
  cl_uint                     preferred_vector_width_double;
  std::string                 profile;
  size_t                      profiling_timer_resolution;
  cl_command_queue_properties queue_properties;
  cl_device_fp_config         single_fp_config;
  cl_device_type              type;
  std::string                 vendor;
  cl_uint                     vendor_id;
  std::string                 version;
  std::string                 driver_version;

  device        ();
  void init (
             cl_device_id loc_device_id                                                             // Device ID.
            );

  ~device();
};

#endif
