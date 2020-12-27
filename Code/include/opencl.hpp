/// @file     opencl.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of the "opencl" class.
///
/// @details  This class builds up the OpenCL context.
/// The OpenCL context is the hardware place where doing OpenCL computation.
/// In Neutrino, a GPU is detected as the target for running the OpenCL computation.
/// In case the GPU supports the OpenCL/GL interoperability modality, then data can be shared to
/// the OpenGL context for graphics rendering of data already present on the GPU memory thanks to
/// the OpenCL context. This modality allows fast rendering of the results of the computation.

#ifndef opencl_hpp
#define opencl_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "platform.hpp"
#include "device.hpp"
#include "queue.hpp"
#include "kernel.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "opencl" class /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class opencl
/// ### OpenCL class.
/// Declares an OpenCL class.
/// To be used to run OpenCL computation.
class opencl : public opengl                                                                        /// @brief **OpenCL context.**
{
private:
  neutrino*      baseline;                                                                          ///< @brief **Neutrino baseline.**
  cl_device_type device_type;                                                                       ///< @brief **OpenCL device type.**
  std::string    device_type_text;                                                                  ///< @brief **OpenCL device text description.**

  /// @brief **get_platforms_number** function.
  /// @details It gets the number of OpenCL platforms found on the host PC.
  cl_uint        get_platforms_number ();

  /// @brief **get_platform_id** function.
  /// @details It gets the OpenCL platform IDs of a all OpenCL platforms present on the host PC.
  /// It returns the **cl_platform_id** array.
  cl_platform_id get_platform_id (
                                  cl_uint loc_platform_index                                        ///< Platform ID.
                                 );

  /// @brief **get_devices_number** function.
  /// @details It gets the number of OpenCL devices found on an OpenCL platform.
  cl_uint        get_devices_number (
                                     cl_uint loc_platform_index                                     ///< Platform ID.
                                    );

  /// @brief **get_device_id** function.
  /// @details It gets the OpenCL device IDs of a all OpenCL devices present on a platform.
  /// It returns the **cl_device_id** array.
  cl_device_id   get_device_id (
                                cl_uint loc_device_index,                                           ///< Device ID.
                                cl_uint loc_platform_index                                          ///< Platform ID.
                               );

public:
  cl_uint                platforms_number;                                                          ///< @brief **Existing OpenCL platforms number.**
  cl_uint                selected_platform;                                                         ///< @brief **Selected platform index.**
  platform**             opencl_platform;                                                           ///< @brief **OpenCL platform array.**

  cl_uint                devices_number;                                                            ///< @brief **Existing OpenCL device number.**
  cl_uint                selected_device;                                                           ///< @brief **Selected device index.**
  device**               opencl_device;                                                             ///< @brief **OpenCL device array.**

  cl_context_properties* properties;                                                                ///< @brief ** OpenCL context properties.**
  cl_context             context_id;                                                                ///< @brief **OpenCL context ID.**

  /// @brief **Class constructor.**
  /// @details It initializes the opencl_platform, platforms_number, devices_number,
  /// properties, context_id and device_type to their default values.
  opencl(
         size_t      loc_q_num,                                                                     ///< Number of OpenCL queues.
         size_t      loc_k_num,                                                                     ///< Number of OpenCL kernels.
         int         loc_window_size_x,                                                             ///< Window x-size [px].
         int         loc_window_size_y,                                                             ///< Window y-size [px].
         std::string loc_title,                                                                     ///< Window title.
         float       loc_orbit_x_initial,                                                           ///< Initial "near clipping-plane" x-coordinate.
         float       loc_orbit_y_initial,                                                           ///< Initial "near clipping-plane" y-coordinate.
         float       loc_pan_x_initial,                                                             ///< Initial pan-x coordinate.
         float       loc_pan_y_initial,                                                             ///< Initial pan-y coordinate.
         float       loc_pan_z_initial                                                              ///< Initial pan-z coordinate.
        );

  /// @brief **Class initializer.**
  /// @details It checks whether the interoperability modality
  /// is supported by the client GPU or not, it sets the OpenCL target device, it sets the OpenCL
  /// platform and lists its extensions, it sets the OpenCL device and lists its extensions,
  /// it identifies the operating system of hte host PC and it creates the OpenCL context.
  /// The OpenCL context must be created after the OpenGL context.
  void init (
             compute_device_type loc_device_type                                                    ///< Compute device type.
            );

  /// @brief Kernel execution function.
  /// @details This function invokes the execution of an [OpenCL kernel]
  /// (https://en.wikipedia.org/wiki/OpenCL#OpenCL_C_language) on an OpenCL @link queue @endlink .
  /// The execution of different kernels can be scheduled sequentially or concurrently by selecting
  /// appropriate (NU_WAIT or NU_DONT_WAIT) @link kernel_mode @endlink .
  /// The sequential kernel execution scheme guarantees that the subsequent kernel execution starts
  /// after the execution of the current kernel is totally ended. The concurrent scheme is managed
  /// by the GPU: it can be parallelized of serialized depending on the underlying hardware.
  /// Therefore, only the sequential kernel execution (NU_WAIT kernel_mode) can guarantee the
  /// the absence of memory leakages in the GPU memory space if the differnt kernels shares the same
  /// memory (e.g. in case one kernel needs to have all computation done by a previous one before
  /// proceeding with further computation). This is very important in order to implement
  /// synchronization between different kernels: OpenCL does not provide other methods for this.
  /// Inside a kernel instead, notice there are memory [barriers]
  /// (https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/barrier.html) in order to
  /// synchronize different OpenCL work-items within a given OpenCL work-group.
  void execute (
                kernel*     loc_kernel,                                                             ///< OpenCL kernel.
                queue*      loc_queue,                                                              ///< OpenCL queue.
                kernel_mode loc_kernel_mode                                                         ///< OpenCL kernel mode.
               );

  /// @brief **Class destructor.**
  /// @details It deletes the OpenCL device, platform and context.
  ~opencl();

};

#endif
