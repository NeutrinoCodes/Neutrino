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
class device : public neutrino                                                                      /// @brief **OpenCL device.**
{
private:
  std::string parameter_value;                                                                      ///< @brief **Parameter value.**

  /// @brief **string** getter function.
  /// @details It gets a **string** parameter from the device's information.
  std::string                 get_string (
                                          cl_device_id   loc_platform_id,                           ///< Platform ID.
                                          cl_device_info loc_parameter_name                         ///< Paramenter name.
                                         );

  /// @brief **cl_uint** getter function.
  /// @details It gets a **cl_uint** parameter from the device's information.
  cl_uint                     get_cl_uint (
                                           cl_device_id   loc_device_id,                            ///< OpenCL device ID.
                                           cl_device_info loc_parameter_name                        ///< Parameter name.
                                          );

  /// @brief **cl_bool** getter function.
  /// @details It gets a **cl_bool** parameter from the device's information.
  cl_bool                     get_cl_bool (
                                           cl_device_id   loc_device_id,                            ///< OpenCL device ID.
                                           cl_device_info loc_parameter_name                        ///< Parameter name.
                                          );

  /// @brief **cl_device_fp_config** getter function.
  /// @details It gets a **cl_device_fp_config** parameter from the device's information.
  cl_device_fp_config         get_cl_device_fp_config (
                                                       cl_device_id   loc_device_id,                ///< OpenCL device ID.
                                                       cl_device_info loc_parameter_name            ///< Parameter name.
                                                      );

  /// @brief **cl_device_exec_capabilities** getter function.
  /// @details It gets a **cl_device_exec_capabilities** parameter from the device's information.
  cl_device_exec_capabilities get_cl_device_exec_capabilities (
                                                               cl_device_id   loc_device_id,        ///< OpenCL device ID.
                                                               cl_device_info loc_parameter_name    ///< Parameter name.
                                                              );

  /// @brief **cl_ulong** getter function.
  /// @details It gets a **cl_ulong** parameter from the device's information.
  cl_ulong                    get_cl_ulong (
                                            cl_device_id   loc_device_id,                           ///< OpenCL device ID.
                                            cl_device_info loc_parameter_name                       ///< Parameter name.
                                           );

  /// @brief **cl_device_mem_cache_type** getter function.
  /// @details It gets a **cl_device_mem_cache_type** parameter from the device's information.
  cl_device_mem_cache_type    get_cl_device_mem_cache_type (
                                                            cl_device_id   loc_device_id,           ///< OpenCL device ID.
                                                            cl_device_info loc_parameter_name       ///< Parameter name.
                                                           );

  /// @brief **size_t** getter function.
  /// @details It gets a **size_t** parameter from the device's information.
  size_t                      get_size_t (
                                          cl_device_id   loc_device_id,                             ///< OpenCL device ID.
                                          cl_device_info loc_parameter_name                         ///< Parameter name.
                                         );

  /// @brief **cl_device_local_mem_type** getter function.
  /// @details It gets a **cl_device_local_mem_type** parameter from the device's information.
  cl_device_local_mem_type    get_cl_device_local_mem_type (
                                                            cl_device_id   loc_device_id,           ///< OpenCL device ID.
                                                            cl_device_info loc_parameter_name       ///< Parameter name.
                                                           );

  /// @brief **cl_platform_id** getter function.
  /// @details It gets a **cl_platform_id** parameter from the device's information.
  cl_platform_id              get_cl_platform_id (
                                                  cl_device_id   loc_device_id,                     ///< OpenCL device ID.
                                                  cl_device_info loc_parameter_name                 ///< Parameter name.
                                                 );

  /// @brief **cl_device_type** getter function.
  /// @details It gets a **cl_device_type** parameter from the device's information.
  cl_device_type              get_cl_device_type (
                                                  cl_device_id   loc_device_id,                     ///< OpenCL device ID.
                                                  cl_device_info loc_parameter_name                 ///< Parameter name.
                                                 );

  /// @brief **cl_command_queue_properties** getter function.
  /// @details It gets a **cl_command_queue_properties** parameter from the device's information.
  cl_command_queue_properties get_cl_command_queue_properties (
                                                               cl_device_id   loc_device_id,        ///< OpenCL device ID.
                                                               cl_device_info loc_parameter_name    ///< Parameter name.
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

  /// @details Is CL_TRUE if the OpenCL device is a little endian device and CL_FALSE otherwise.
  cl_bool                     endian_little;                                                        ///< @brief **OpenCL device endian_little [cl_bool].**

  /// @details Is CL_TRUE if the device implements error correction for the memories, caches,
  /// registers etc. in the device. Is CL_FALSE if the device does not implement error correction.
  /// This can be a requirement for certain clients of OpenCL.
  cl_bool                     error_correction_support;                                             ///< @brief **OpenCL device error_correction_support [cl_bool].**

  /// @details Describes the execution capabilities of the device. This is a bit-field that
  /// describes one or more of the following values:
  /// - CL_EXEC_KERNEL - The OpenCL device can execute OpenCL kernels.
  /// - CL_EXEC_NATIVE_KERNEL - The OpenCL device can execute native kernels.
  ///
  /// The mandated minimum capability is CL_EXEC_KERNEL.
  cl_device_exec_capabilities execution_capabilities;                                               ///< @brief **OpenCL device execution_capabilities [cl_device_exec_capabilities].**

  /// @details Returns a space separated list of extension names (the extension names themselves
  /// do not contain any spaces). The list of extension names returned currently can include one
  /// or more of the following approved extension names:
  /// - [cl_khr_fp64](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html)
  /// - [cl_khr_select_fprounding_mode](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_select_fprounding_mode.html)
  /// - [cl_khr_global_int32_base_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_global_int32_base_atomics.html)
  /// - [cl_khr_global_int32_extended_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_global_int32_extended_atomics.html)
  /// - [cl_khr_local_int32_base_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_local_int32_base_atomics.html)
  /// - [cl_khr_local_int32_extended_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_local_int32_extended_atomics.html)
  /// - [cl_khr_int64_base_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_int64_base_atomics.html)
  /// - [cl_khr_int64_extended_atomics](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_int64_extended_atomics.html)
  /// - [cl_khr_3d_image_writes](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_3d_image_writes.html)
  /// - [cl_khr_byte_addressable_store](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_byte_addressable_store.html)
  /// - [cl_khr_fp16](https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp16.html)
  std::string              extensions;                                                              ///< @brief **OpenCL device extensions [std::string].**

  /// @details Size of global memory cache in bytes.
  cl_ulong                 global_mem_cache_size;                                                   ///< @brief **OpenCL device global_mem_cache_size [cl_ulong].**

  /// @details Type of global memory cache supported. Valid values are: CL_NONE,
  /// CL_READ_ONLY_CACHE, and CL_READ_WRITE_CACHE.
  cl_device_mem_cache_type global_mem_cache_type;                                                   ///< @brief **OpenCL device global_mem_cache_type [cl_device_mem_cache_type].**

  /// @details Size of global memory cache line in bytes.
  cl_uint                  global_mem_cacheline_size;                                               ///< @brief **OpenCL device global_mem_cacheline_size [cl_uint].**

  /// @details Size of global device memory in bytes.
  cl_ulong                 global_mem_size;                                                         ///< @brief **OpenCL device global_mem_size [cl_ulong].**

  /// @details Describes the OPTIONAL half precision floating-point capability of the OpenCL device.
  /// This is a bit-field that describes one or more of the following values:
  /// - CL_FP_DENORM - denorms are supported.
  /// - CL_FP_INF_NAN - INF and NaNs are supported.
  /// - CL_FP_ROUND_TO_NEAREST - round to nearest even rounding mode supported.
  /// - CL_FP_ROUND_TO_ZERO - round to zero rounding mode supported.
  /// - CL_FP_ROUND_TO_INF - round to +ve and -ve infinity rounding modes supported.
  /// - CL_FP_FMA - IEEE754-2008 fused multiply-add is supported.
  ///
  /// The required minimum half precision floating-point capability as implemented by this extension
  ///is CL_FP_ROUND_TO_ZERO | CL_FP_ROUND_TO_INF | CL_FP_INF_NAN.
  cl_device_fp_config      half_fp_config;                                                          ///< @brief **OpenCL device half_fp_config [cl_device_fp_config].**

  /// @details Is CL_TRUE if images are supported by the OpenCL device and CL_FALSE otherwise.
  cl_bool                  image_support;                                                           ///< @brief **OpenCL device image_support [cl_bool].**

  /// @details Max height of 2D image in pixels. The minimum value is 8192 if
  /// CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  size_t                   image2D_max_height;                                                      ///< @brief **OpenCL device image2D_max_height [size_t].**

  /// @details Max width of 2D image in pixels. The minimum value is 8192 if
  /// CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  size_t                   image2D_max_width;                                                       ///< @brief **OpenCL device image2D_max_width [size_t].**

  /// @details Max depth of 3D image in pixels. The minimum value is 2048 if
  /// CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  size_t                   image3D_max_depth;                                                       ///< @brief **OpenCL device image3D_max_depth [size_t].**

  /// @details Max height of 3D image in pixels. The minimum value is 2048 if
  /// CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  size_t                   image3D_max_height;                                                      ///< @brief **OpenCL device image3D_max_height [size_t].**

  /// @details Max width of 3D image in pixels. The minimum value is 2048 if
  /// CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  size_t                   image3D_max_width;                                                       ///< @brief **OpenCL device image3D_max_width [size_t].**

  /// @details Size of local memory arena in bytes. The minimum value is 16 KB.
  cl_ulong                 local_mem_size;                                                          ///< @brief **OpenCL device local_mem_size [cl_ulong].**

  /// @details Type of local memory supported. This can be set to CL_LOCAL implying dedicated
  /// local memory storage such as SRAM, or CL_GLOBAL.
  cl_device_local_mem_type local_mem_type;                                                          ///< @brief **OpenCL device local_mem_type [cl_device_local_mem_type].**

  /// @details Maximum configured clock frequency of the device in MHz.
  cl_uint                  max_clock_frequency;                                                     ///< @brief **OpenCL device max_clock_frequency [cl_uint].**

  /// @details The number of parallel compute cores on the OpenCL device. The minimum value is 1.
  cl_uint                  max_compute_units;                                                       ///< @brief **OpenCL device max_compute_units [cl_uint].**

  /// @details Max number of arguments declared with the [__constant]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/constant.html
  /// qualifier in a kernel. The minimum value is 8.
  cl_uint                  max_constant_args;                                                       ///< @brief **OpenCL device max_constant_args [cl_uint].**

  /// @details Max size in bytes of a constant buffer allocation. The minimum value is 64 KB.
  cl_ulong                 max_constant_buffer_size;                                                ///< @brief **OpenCL device max_constant_buffer_size [cl_ulong].**

  /// @details Max size of memory object allocation in bytes. The minimum value is max
  /// (1/4th of CL_DEVICE_GLOBAL_MEM_SIZE, 128*1024*1024)
  cl_ulong                 max_mem_alloc_size;                                                      ///< @brief **OpenCL device max_mem_alloc_size [cl_ulong].**

  /// @details Max size in bytes of the arguments that can be passed to a kernel.
  /// The minimum value is 256.
  size_t                   max_parameter_size;                                                      ///< @brief **OpenCL device max_parameter_size [size_t].**

  /// @details Max number of simultaneous image objects that can be read by a kernel.
  /// The minimum value is 128 if CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  cl_uint                  max_read_image_args;                                                     ///< @brief **OpenCL device max_read_image_args [cl_uint].**

  /// @details Maximum number of samplers that can be used in a kernel.
  /// The minimum value is 16 if CL_DEVICE_IMAGE_SUPPORT is CL_TRUE. (Also see [sampler_t]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/sampler_t.html).)
  cl_uint                  max_samplers;                                                            ///< @brief **OpenCL device max_samplers [cl_uint].**

  /// @details Maximum number of work-items in a work-group executing a kernel using the data
  /// parallel execution model. (Refer to [clEnqueueNDRangeKernel]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clEnqueueNDRangeKernel.html)).
  /// The minimum value is 1.
  size_t                   max_work_group_size;                                                     ///< @brief **OpenCL device max_work_group_size [size_t].**

  /// @details Maximum dimensions that specify the global and local work-item IDs used by the data
  /// parallel execution model. (Refer to [clEnqueueNDRangeKernel]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clEnqueueNDRangeKernel.html)).
  /// The minimum value is 3.
  cl_uint                  max_work_item_dimensions;                                                ///< @brief **OpenCL device max_work_item_dimensions [cl_uint].**

  /// @details Maximum number of work-items that can be specified in each dimension of the
  /// work-group to [clEnqueueNDRangeKernel]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clEnqueueNDRangeKernel.html).
  /// Returns n size_t entries, where n is the value returned by the query for
  /// CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS. The minimum value is (1, 1, 1).
  //std::string                 max_work_item_sizes;                                                ///< @brief **OpenCL device max_work_item_sizes [std::string].**

  /// @details Max number of simultaneous image objects that can be written to by a kernel.
  /// The minimum value is 8 if CL_DEVICE_IMAGE_SUPPORT is CL_TRUE.
  cl_uint                     max_write_image_args;                                                 ///< @brief **OpenCL device max_write_image_args [cl_uint].**

  /// @details Describes the alignment in bits of the base address of any allocated memory object.
  cl_uint                     mem_base_addr_align;                                                  ///< @brief **OpenCL device mem_base_addr_align [cl_uint].**

  /// @details The smallest alignment in bytes which can be used for any data type.
  cl_uint                     min_data_type_align_size;                                             ///< @brief **OpenCL device min_data_type_align_size [cl_uint].**

  /// @details Device name string.
  std::string                 name;                                                                 ///< @brief **OpenCL device name [std::string].**

  /// @details The platform associated with this device.
  cl_platform_id              platform;                                                             ///< @brief **OpenCL device platform [cl_platform_id].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_char;                                          ///< @brief **OpenCL device preferred_vector_width_char [cl_uint].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_short;                                         ///< @brief **OpenCL device preferred_vector_width_short [cl_uint].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_int;                                           ///< @brief **OpenCL device preferred_vector_width_int [cl_uint].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_long;                                          ///< @brief **OpenCL device preferred_vector_width_long [cl_uint].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_float;                                         ///< @brief **OpenCL device preferred_vector_width_float [cl_uint].**

  /// @details Preferred native vector width size for built-in scalar types that can be put into
  /// vectors. The vector width is defined as the number of scalar elements that can be stored
  /// in the vector. If the [cl_khr_fp64]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/cl_khr_fp64.html) extension
  /// is not supported, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE must return 0.
  cl_uint                     preferred_vector_width_double;                                        ///< @brief **OpenCL device preferred_vector_width_double [cl_uint].**

  /// @details OpenCL profile string. Returns the profile name supported by the device (see note).
  /// The profile name returned can be one of the following strings:
  /// - FULL_PROFILE - if the device supports the OpenCL specification
  ///   (functionality defined as part of the core specification and does
  ///   not require any extensions to be supported).
  /// - EMBEDDED_PROFILE - if the device supports the OpenCL embedded profile.
  std::string                 profile;                                                              ///< @brief **OpenCL device profile [std::string].**

  /// @details Describes the resolution of device timer. This is measured in nanoseconds.
  size_t                      profiling_timer_resolution;                                           ///< @brief **OpenCL device profiling_timer_resolution [size_t].**

  /// @details Describes the command-queue properties supported by the device.
  /// This is a bit-field that describes one or more of the following values:
  /// - CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
  /// - CL_QUEUE_PROFILING_ENABLE
  ///
  /// These properties are described in the table for [clCreateCommandQueue]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clCreateCommandQueue.html).
  /// The mandated minimum capability is CL_QUEUE_PROFILING_ENABLE.
  cl_command_queue_properties queue_properties;                                                     ///< @brief **OpenCL device queue_properties [cl_command_queue_properties].**

  /// @details Describes single precision floating-point capability of the device.
  /// This is a bit-field that describes one or more of the following values:
  /// - CL_FP_DENORM - denorms are supported
  /// - CL_FP_INF_NAN - INF and quiet NaNs are supported
  /// - CL_FP_ROUND_TO_NEAREST - round to nearest even rounding mode supported
  /// - CL_FP_ROUND_TO_ZERO - round to zero rounding mode supported
  /// - CL_FP_ROUND_TO_INF - round to +ve and -ve infinity rounding modes supported
  /// - CL_FP_FMA - IEEE754-2008 fused multiply-add is supported
  ///
  /// The mandated minimum floating-point capability is CL_FP_ROUND_TO_NEAREST | CL_FP_INF_NAN.
  cl_device_fp_config single_fp_config;                                                             ///< @brief **OpenCL device single_fp_config [cl_device_fp_config].**

  /// @details The OpenCL device type. Currently supported values are one of or a combination of:
  /// CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_ACCELERATOR, or CL_DEVICE_TYPE_DEFAULT.
  cl_device_type      type;                                                                         ///< @brief **OpenCL device type [cl_device_type].**

  /// @details Vendor name string.
  std::string         vendor;                                                                       ///< @brief **OpenCL device vendor [std::string].**

  /// @details A unique device vendor identifier. An example of a unique device identifier could
  /// be the PCIe ID.
  cl_uint             vendor_id;                                                                    ///< @brief **OpenCL device vendor_id [cl_uint].**

  /// @details OpenCL version string. Returns the OpenCL version supported by the device.
  /// This version string has the following format:
  /// OpenCL<space><major_version.minor_version><space><vendor-specific information>
  ///
  /// The major_version.minor_version value returned will be 1.0.
  std::string         version;                                                                      ///< @brief **OpenCL device version [std::string].**

  /// @details OpenCL software driver version string in the form major_number.minor_number.
  std::string         driver_version;                                                               ///< @brief **OpenCL device driver_version [std::string].**

  /// @brief **Class constructor.**
  /// @details It does nothing.
  device        ();

  /// @brief **Class initializer.**
  /// @details It gets all information from the OpenCL hardware client GPU device and store it
  /// in the corresponding public variables.
  void init (
             cl_device_id loc_device_id                                                             ///< Device ID.
            );

  /// @brief **Class destructor.**
  /// @details It does nothing.
  ~device();
};

#endif
