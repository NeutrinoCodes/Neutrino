/// @file

#ifndef opencl_hpp
#define opencl_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "platform.hpp"
#include "device.hpp"
#include "queue.hpp"
#include "kernel.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENCL" CLASS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class opencl
{
private:
  neutrino*      baseline;                                                                          // Neutrino baseline.
  cl_device_type device_type;
  std::string    device_type_text;
  cl_uint        get_platforms_number ();
  cl_platform_id get_platform_id (
                                  cl_uint loc_platform_index
                                 );
  cl_uint        get_devices_number (
                                     cl_uint loc_platform_index
                                    );
  cl_device_id   get_device_id (
                                cl_uint loc_device_index,
                                cl_uint loc_platform_index
                               );

public:
  cl_uint                platforms_number;                                                          // Existing OpenCL platforms number.
  cl_uint                selected_platform;                                                         // Selected platform index.
  platform**             opencl_platform;                                                           // OpenCL platform array.

  cl_uint                devices_number;                                                            // Existing OpenCL device number.
  cl_uint                selected_device;                                                           // Selected device index.
  device**               opencl_device;                                                             // OpenCL device array.

  cl_context_properties* properties;
  cl_context             context_id;

  opencl();
  void init (
             neutrino*           loc_baseline,
             opengl*             loc_gui,
             compute_device_type loc_device_type
            );
  // Kernel execution:
  void execute (
                kernel*     loc_kernel,                                                             // OpenCL kernel.
                queue*      loc_queue,                                                              // OpenCL queue.
                kernel_mode loc_kernel_mode                                                         // OpenCL kernel mode.
               );

  ~opencl();

};

#endif
