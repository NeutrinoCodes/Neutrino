/// @file     device.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of an OpenCL "device" class.
///
/// @details  A Neutrino "device" is an [OpenCL compute device]
/// (https://en.wikipedia.org/wiki/OpenCL#Devices). The @link device @endlink class has got methods
/// to retrieve all information about the OpenCL compute device running the computation. This
/// information is contained and available to the user in form of public variables of the @link
/// device @endlink class.
/// The user should take advantage of this information in order to write [device independent]
/// (https://en.wikipedia.org/wiki/Device_independence) code.

#ifndef device_hpp
#define device_hpp

  #include "neutrino.hpp"
  #include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "device" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class device
/// ### OpenCL compute device.
/// Declares an OpenCL compute device.
/// To be used to run OpenCL computation. Also used to get specific hardware information about the
/// device. See also the OpenCL [clDeviceInfo]
/// (https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/clGetDeviceInfo.html)
/// specifications.
class device
{
private:
  neutrino*   baseline;                                                                             ///< @brief **Neutrino baseline.**
  std::string parameter_value;                                                                      ///< @brief **Parameter value.**

  // OpenCL get info value function:
  std::string                 get_string (
                                          cl_device_id   loc_platform_id,                           ///< @brief **Platform ID.**
                                          cl_device_info loc_parameter_name                         ///< @brief **Paramenter name.**
                                         );

  cl_uint                     get_cl_uint (
                                           cl_device_id   loc_device_id,                            ///< @brief **OpenCL device ID.**
                                           cl_device_info loc_parameter_name                        ///< @brief **Parameter name.**
                                          );

  cl_bool                     get_cl_bool (
                                           cl_device_id   loc_device_id,                            ///< @brief **OpenCL device ID.**
                                           cl_device_info loc_parameter_name                        ///< @brief **Parameter name.**
                                          );

  cl_device_fp_config         get_cl_device_fp_config (
                                                       cl_device_id   loc_device_id,                ///< @brief **OpenCL device ID.**
                                                       cl_device_info loc_parameter_name            ///< @brief **Parameter name.**
                                                      );

  cl_device_exec_capabilities get_cl_device_exec_capabilities (
                                                               cl_device_id   loc_device_id,        ///< @brief **OpenCL device ID.**
                                                               cl_device_info loc_parameter_name    ///< @brief **Parameter name.**
                                                              );

  cl_ulong                    get_cl_ulong (
                                            cl_device_id   loc_device_id,                           ///< @brief **OpenCL device ID.**
                                            cl_device_info loc_parameter_name                       ///< @brief **Parameter name.**
                                           );

  cl_device_mem_cache_type    get_cl_device_mem_cache_type (
                                                            cl_device_id   loc_device_id,           ///< @brief **OpenCL device ID.**
                                                            cl_device_info loc_parameter_name       ///< @brief **Parameter name.**
                                                           );

  size_t                      get_size_t (
                                          cl_device_id   loc_device_id,                             ///< @brief **OpenCL device ID.**
                                          cl_device_info loc_parameter_name                         ///< @brief **Parameter name.**
                                         );

  cl_device_local_mem_type    get_cl_device_local_mem_type (
                                                            cl_device_id   loc_device_id,           ///< @brief **OpenCL device ID.**
                                                            cl_device_info loc_parameter_name       ///< @brief **Parameter name.**
                                                           );

  cl_platform_id              get_cl_platform_id (
                                                  cl_device_id   loc_device_id,                     ///< @brief **OpenCL device ID.**
                                                  cl_device_info loc_parameter_name                 ///< @brief **Parameter name.**
                                                 );

  cl_device_type              get_cl_device_type (
                                                  cl_device_id   loc_device_id,                     ///< @brief **OpenCL device ID.**
                                                  cl_device_info loc_parameter_name                 ///< @brief **Parameter name.**
                                                 );

  cl_command_queue_properties get_cl_command_queue_properties (
                                                               cl_device_id   loc_device_id,        ///< @brief **OpenCL device ID.**
                                                               cl_device_info loc_parameter_name    ///< @brief **Parameter name.**
                                                              );

public:
  cl_device_id id;                                                                                  ///< @brief **OpenCL device id [cl_device_id].**

  /// @details The default compute device address space size specified as an unsigned integer
  /// value in bits. Currently supported values are 32 or 64 bits.
  cl_uint      address_bits;                                                                        ///< @brief **OpenCL device address_bits [cl_uint].**

  /// @details Is CL_TRUE if the device is available and CL_FALSE if the device is not available.
  cl_bool      available;                                                                           ///< @brief **OpenCL device available [cl_bool].**

  /// @details Is CL_FALSE if the implementation does not have a compiler available to compile the
  /// program source. Is CL_TRUE if the compiler is available. This can be CL_FALSE for the
  /// embededed platform profile only.
  cl_bool      compiler_available;                                                                  ///< @brief **OpenCL device compiler_available [cl_bool].**

  /// @details Describes the OPTIONAL double precision floating-point capability of the OpenCL
  ///device. This is a bit-field that describes one or more of the following values:
  /// - CL_FP_DENORM - denorms are supported.
  /// - CL_FP_INF_NAN - INF and NaNs are supported.
  /// - CL_FP_ROUND_TO_NEAREST - round to nearest even rounding mode supported.
  /// - CL_FP_ROUND_TO_ZERO - round to zero rounding mode supported.
  /// - CL_FP_ROUND_TO_INF - round to +ve and -ve infinity rounding modes supported.
  /// - CL_FP_FMA - IEEE754-2008 fused multiply-add is supported.
  ///
  /// The mandated minimum double precision floating - point capability is CL_FP_FMA |
  /// CL_FP_ROUND_TO_NEAREST | CL_FP_ROUND_TO_ZERO | CL_FP_ROUND_TO_INF | CL_FP_INF_NAN |
  /// CL_FP_DENORM.
  cl_device_fp_config         double_fp_config;                                                     ///< @brief **OpenCL device double_fp_config [cl_device_fp_config].**

  /// @details
  cl_bool                     endian_little;                                                        ///< @brief **OpenCL device endian_little [cl_bool].**

  /// @details
  cl_bool                     error_correction_support;                                             ///< @brief **OpenCL device error_correction_support [cl_bool].**

  /// @details
  cl_device_exec_capabilities execution_capabilities;                                               ///< @brief **OpenCL device execution_capabilities [cl_device_exec_capabilities].**

  /// @details
  std::string                 extensions;                                                           ///< @brief **OpenCL device extensions [std::string].**

  /// @details
  cl_ulong                    global_mem_cache_size;                                                ///< @brief **OpenCL device global_mem_cache_size [cl_ulong].**

  /// @details
  cl_device_mem_cache_type    global_mem_cache_type;                                                ///< @brief **OpenCL device global_mem_cache_type [cl_device_mem_cache_type].**

  /// @details
  cl_uint                     global_mem_cacheline_size;                                            ///< @brief **OpenCL device global_mem_cacheline_size [cl_uint].**

  /// @details
  cl_ulong                    global_mem_size;                                                      ///< @brief **OpenCL device global_mem_size [cl_ulong].**

  /// @details
  cl_device_fp_config         half_fp_config;                                                       ///< @brief **OpenCL device half_fp_config [cl_device_fp_config].**

  /// @details
  cl_bool                     image_support;                                                        ///< @brief **OpenCL device image_support [cl_bool].**

  /// @details
  size_t                      image2D_max_height;                                                   ///< @brief **OpenCL device image2D_max_height [size_t].**

  /// @details
  size_t                      image2D_max_width;                                                    ///< @brief **OpenCL device image2D_max_width [size_t].**

  /// @details
  size_t                      image3D_max_depth;                                                    ///< @brief **OpenCL device image3D_max_depth [size_t].**

  /// @details
  size_t                      image3D_max_height;                                                   ///< @brief **OpenCL device image3D_max_height [size_t].**

  /// @details
  size_t                      image3D_max_width;                                                    ///< @brief **OpenCL device image3D_max_width [size_t].**

  /// @details
  cl_ulong                    local_mem_size;                                                       ///< @brief **OpenCL device local_mem_size [cl_ulong].**

  /// @details
  cl_device_local_mem_type    local_mem_type;                                                       ///< @brief **OpenCL device local_mem_type [cl_device_local_mem_type].**

  /// @details
  cl_uint                     max_clock_frequency;                                                  ///< @brief **OpenCL device max_clock_frequency [cl_uint].**

  /// @details
  cl_uint                     max_compute_units;                                                    ///< @brief **OpenCL device max_compute_units [cl_uint].**

  /// @details
  cl_uint                     max_constant_args;                                                    ///< @brief **OpenCL device max_constant_args [cl_uint].**

  /// @details
  cl_ulong                    max_constant_buffer_size;                                             ///< @brief **OpenCL device max_constant_buffer_size [cl_ulong].**

  /// @details
  cl_ulong                    max_mem_alloc_size;                                                   ///< @brief **OpenCL device max_mem_alloc_size [cl_ulong].**

  /// @details
  size_t                      max_parameter_size;                                                   ///< @brief **OpenCL device max_parameter_size [size_t].**

  /// @details
  cl_uint                     max_read_image_args;                                                  ///< @brief **OpenCL device max_read_image_args [cl_uint].**

  /// @details
  cl_uint                     max_samplers;                                                         ///< @brief **OpenCL device max_samplers [cl_uint].**

  /// @details
  size_t                      max_work_group_size;                                                  ///< @brief **OpenCL device max_work_group_size [size_t].**

  /// @details
  cl_uint                     max_work_item_dimensions;                                             ///< @brief **OpenCL device max_work_item_dimensions [cl_uint].**

  /// @details
  //std::string                 max_work_item_sizes;                                                ///< @brief **OpenCL device max_work_item_sizes [std::string].**

  /// @details
  cl_uint                     max_write_image_args;                                                 ///< @brief **OpenCL device max_write_image_args [cl_uint].**

  /// @details
  cl_uint                     mem_base_addr_align;                                                  ///< @brief **OpenCL device mem_base_addr_align [cl_uint].**

  /// @details
  cl_uint                     min_data_type_align_size;                                             ///< @brief **OpenCL device min_data_type_align_size [cl_uint].**

  /// @details
  std::string                 name;                                                                 ///< @brief **OpenCL device name [std::string].**

  /// @details
  cl_platform_id              platform;                                                             ///< @brief **OpenCL device platform [cl_platform_id].**

  /// @details
  cl_uint                     preferred_vector_width_char;                                          ///< @brief **OpenCL device preferred_vector_width_char [cl_uint].**

  /// @details
  cl_uint                     preferred_vector_width_short;                                         ///< @brief **OpenCL device preferred_vector_width_short [cl_uint].**

  /// @details
  cl_uint                     preferred_vector_width_int;                                           ///< @brief **OpenCL device preferred_vector_width_int [cl_uint].**

  /// @details
  cl_uint                     preferred_vector_width_long;                                          ///< @brief **OpenCL device preferred_vector_width_long [cl_uint].**

  /// @details
  cl_uint                     preferred_vector_width_float;                                         ///< @brief **OpenCL device preferred_vector_width_float [cl_uint].**

  /// @details
  cl_uint                     preferred_vector_width_double;                                        ///< @brief **OpenCL device preferred_vector_width_double [cl_uint].**

  /// @details
  std::string                 profile;                                                              ///< @brief **OpenCL device profile [std::string].**

  /// @details
  size_t                      profiling_timer_resolution;                                           ///< @brief **OpenCL device profiling_timer_resolution [size_t].**

  /// @details
  cl_command_queue_properties queue_properties;                                                     ///< @brief **OpenCL device queue_properties [cl_command_queue_properties].**

  /// @details
  cl_device_fp_config         single_fp_config;                                                     ///< @brief **OpenCL device single_fp_config [cl_device_fp_config].**

  /// @details
  cl_device_type              type;                                                                 ///< @brief **OpenCL device type [cl_device_type].**

  /// @details
  std::string                 vendor;                                                               ///< @brief **OpenCL device vendor [std::string].**

  /// @details
  cl_uint                     vendor_id;                                                            ///< @brief **OpenCL device vendor_id [cl_uint].**

  /// @details
  std::string                 version;                                                              ///< @brief **OpenCL device version [std::string].**

  /// @details
  std::string                 driver_version;                                                       ///< @brief **OpenCL device driver_version [std::string].**

  device        ();

  void init (
             cl_device_id loc_device_id                                                             // Device ID.
            );

  ~device();
};

#endif
