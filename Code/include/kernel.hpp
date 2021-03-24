/// @file     kernel.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of an OpenCL "kernel" class.
///
/// @details  A Neutrino "kernel" is an [OpenCL kernel]
/// (https://en.wikipedia.org/wiki/OpenCL#OpenCL_C_language). The @link kernel @endlink class has
/// got methods to set arguments on the OpenCL kernel: this operation tells Neutrino which are the
/// arguments present in the @link thekernel @endlink function of the kernel source file.
/// The argument in the kernel object must correspond to the argument in the OpenCL kernel
/// source file.

#ifndef kernel_hpp
#define kernel_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"

namespace nu
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "kernel" class //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class kernel
/// ### OpenCL kernel.
/// Declares an OpenCL kernel.
/// To be used to run OpenCL computation.
class kernel : public neutrino                                                                      ///< @brief **OpenCL kernel.**
{
private:
  cl_device_id*            device_id;                                                               ///< @brief **Device ID array.**

public:
  cl_kernel                kernel_id;                                                               ///< @brief **Kernel id.**
  std::vector<std::string> kernel_source;                                                           ///< @brief **Kernel source array [std::string].**
  std::string              compiler_options;                                                        ///< @brief **OpenCL JIT complier options string [std::string].**
  std::string              compiler_log;                                                            ///< @brief **OpenCL JIT compiler error log [std::string].**
  cl_program               program;                                                                 ///< @brief **Kernel program.**
  size_t                   size_i;                                                                  ///< @brief **Kernel size (i-index) [#].**
  size_t                   size_j;                                                                  ///< @brief **Kernel size (j-index) [#].**
  size_t                   size_k;                                                                  ///< @brief **Kernel size (k-index) [#].**
  cl_event                 event;                                                                   ///< @brief **Kernel event.**

  /// @brief **Class constructor.**
  /// @details It resets the @link source @endlink, @link program @endlink, @link size_i @endlink,
  /// @link size_j @endlink, @link size_k @endlink, @link event @endlink and @link kernel_id
  /// @endlink default values.
  /// The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link kernel::init @endlink method.
  kernel();

  /// @brief **Kernel source adder function.**
  /// @details Loads an OpenCL kernel source from its corresponding source file.
  void addsource (
                  std::string loc_kernel_file_name                                                  ///< OpenCL kernel file name.
                 );

  /// @brief **OpenCL kernel builder.**
  /// @details Creates an OpenCL program from the kernel sources and builds it.
  void build (
              size_t loc_kernel_size_i,                                                             ///< OpenCL kernel size (i-index).
              size_t loc_kernel_size_j,                                                             ///< OpenCL kernel size (j-index).
              size_t loc_kernel_size_k                                                              ///< OpenCL kernel size (k-index).
             );

  /// @brief **Kernel argument setter function.**
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_int* loc_data,                                                                    ///< nu_int data.
               GLuint  loc_layout_index                                                             ///< Layout index.
              );

  /// @overload setarg(nu_int2* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_int2* loc_data,                                                                   ///< nu_int2 data.
               GLuint   loc_layout_index                                                            ///< Layout index.
              );

  /// @overload setarg(nu_int3* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_int3* loc_data,                                                                   ///< nu_int3 data.
               GLuint   loc_layout_index                                                            ///< Layout index.
              );

  /// @overload setarg(nu_int4* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_int4* loc_data,                                                                   ///< nu_int4 data.
               GLuint   loc_layout_index                                                            ///< Layout index.
              );

  /// @overload setarg(nu_float* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_float* loc_data,                                                                  ///< nu_float data.
               GLuint    loc_layout_index                                                           ///< Layout index.
              );

  /// @overload setarg(nu_float2* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_float2* loc_data,                                                                 ///< nu_float2 data.
               GLuint     loc_layout_index                                                          ///< Layout index.
              );

  /// @overload setarg(nu_float3* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_float3* loc_data,                                                                 ///< nu_float3 data.
               GLuint     loc_layout_index                                                          ///< Layout index.
              );

  /// @overload setarg(nu_float4* loc_data, cl_uint loc_layout_index)
  /// @details Sets an argument on the Neutrino kernel object. The argument in the kernel object
  /// must correspond to the argument in the OpenCL kernel source file.
  /// This operation tells Neutrino which are the arguments present in the @link thekernel @endlink
  /// function of the kernel source file.
  /// The setter function has two arguments:
  /// - **loc_data**, which contains the user data to be exchanged between the host PC and the
  ///   client GPU.
  /// - **loc_layout_index**, which is an integer incremental number starting from 0 and specified
  ///   by the user for each instace of this function. This number tells Neutrino the place of the
  ///   argument in the @link thekernel @endlink function of the kernel source file.
  void setarg (
               nu_float4* loc_data,                                                                 ///< nu_float4 data.
               GLuint     loc_layout_index                                                          ///< Layout index.
              );

  /// @brief **Class destructor.**
  /// @details Releases the OpenCL kernel object, releases the OpenCL kernel event,
  /// releases the OpenCL program, releases the device ID array.
  ~kernel();
};
}
#endif
