/// @file

#ifndef device_hpp
#define device_hpp

  #include "neutrino.hpp"
  #include "datatypes.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "DEVICE" CLASS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class device
{
private:
  neutrino*    baseline;                                                        // Neutrino baseline.
  std::string  parameter_value;                                                 // Parameter value.
  // OpenCL get info value function:
  std::string get_info (
                        cl_device_id   loc_platform_id,                         // Platform ID.
                        cl_device_info loc_parameter_name                       // Paramenter name.
                       );

public:
  cl_device_id id;                                                              // OpenCL device id.
  cl_uint      address_bits;
  std::string  available;
  std::string  compiler_available;
  std::string  endian_little;
  std::string  error_correction_support;
  std::string  execution_capabilities;
  std::string  extensions;
  std::string  global_mem_cache_size;
  std::string  global_mem_cache_type;
  std::string  global_mem_cacheline_size;
  std::string  global_mem_size;
  std::string  image_support;
  std::string  image2D_max_height;
  std::string  image2D_max_width;
  std::string  image3D_max_depth;
  std::string  image3D_max_height;
  std::string  image3D_max_width;
  std::string  local_mem_size;
  std::string  local_mem_type;
  std::string  max_clock_frequency;
  std::string  max_compute_units;
  std::string  max_constant_args;
  std::string  max_constant_buffer_size;
  std::string  max_mem_alloc_size;
  std::string  max_parameter_size;
  std::string  max_read_image_args;
  std::string  max_samplers;
  std::string  max_work_group_size;
  std::string  max_work_item_dimensions;
  std::string  max_work_item_sizes;
  std::string  max_write_image_args;
  std::string  mem_base_addr_align;
  std::string  min_data_type_align_size;
  std::string  name;
  std::string  platform;
  std::string  preferred_vector_width_char;
  std::string  preferred_vector_width_double;
  std::string  preferred_vector_width_float;
  std::string  preferred_vector_width_int;
  std::string  preferred_vector_width_long;
  std::string  preferred_vector_width_short;
  std::string  profile;
  std::string  profiling_timer_resolution;
  std::string  queue_properties;
  std::string  single_fp_config;
  std::string  type;
  std::string  vendor_id;
  std::string  vendor;
  std::string  version;
  std::string  driver_version;

  device        ();
  void init (
             cl_device_id loc_device_id                                         // Device ID.
            );

  ~device();
};

#endif
