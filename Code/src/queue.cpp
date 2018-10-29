#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue(cl_context loc_context_id, cl_device_id loc_device_id)
{
  queue_id = NULL;                                                              // Initializing thequeue...
  context_id = loc_context_id;                                                  // Initializing context...
  device_id = loc_device_id;                                                    // Initializing thedevice_id...
}

void queue::init()
{
  cl_int  loc_err;                                                              // Local error code.

  printf("Action: creating OpenCL command queue... ");

  // Creating OpenCL queue:
  queue_id = clCreateCommandQueue(context_id,                                   // OpenCL context.
                                  device_id,                                    // Device id.
                                  0,                                            // Queue properties (con be used for enabling profiling).
                                  &loc_err);                                    // Local error code.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("DONE!\n");
}

queue::~queue()
{
  cl_int  loc_err;                                                              // Local error code.

  printf("Action: releasing the OpenCL command queue... ");

  loc_err = clReleaseCommandQueue(queue_id);                                    // Releasing OpenCL queue...

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("DONE!\n");
}
