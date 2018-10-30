#include "device.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "DEVICE" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
device::device()
{

}

// PRIVATE METHODS:
size_t device::get_info_size(cl_device_info loc_parameter_name)
{
  cl_int  loc_err;                                                              // Local error code.
  size_t  loc_parameter_size;                                                   // Local parameter size.

  // Getting device information:
  loc_err = clGetDeviceInfo(device_id,                                          // Device id.
                            loc_parameter_name,                                 // Local parameter name.
                            0,                                                  // Dummy parameter size: "0" means we ask for the # of parameters.
                            NULL,                                               // Dummy parameter.
                            &loc_parameter_size);                               // Returned local parameter size.

  if(loc_err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  return (loc_parameter_size);
}

char* device::get_info_value(cl_device_info loc_parameter_name, size_t loc_parameter_size)
{
  cl_int  loc_err;                                                              // Local error code.
  char*   loc_parameter_value;                                                  // Local parameter value.

  // Getting platform information:
  loc_err = clGetDeviceInfo(device_id,                                          // Device id.
                            loc_parameter_name,                                 // Parameter name.
                            loc_parameter_size,                                 // Parameter size.
                            loc_parameter_value,                                // Parameter.
                            NULL);                                              // Returned parameter size (NULL = ignored).

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  return (loc_parameter_value);                                                 // Returning local parameter value...
}

// PUBLIC METHODS:
void device::init(cl_device_id loc_device_id)
{
  info*   device_name               = new info(get_info_size(CL_DEVICE_NAME));
  info*   device_platform           = new info(get_info_size(CL_DEVICE_PLATFORM));

  device_name->value                = get_info_value(CL_DEVICE_NAME, device_name->size);
  device_platform->value            = get_info_value(CL_DEVICE_PLATFORM, device_platform->size);

  device_id = loc_device_id;                                                    // Initializing device_id...
}

device::~device()
{
  delete device_name;
  delete device_platform;
}
