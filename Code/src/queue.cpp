#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  queue_id = NULL;                                                              // Initializing queue id...
  context_id = NULL;                                                            // Initializing context id...
  device_id = NULL;                                                             // Initializing device id...
}

void queue::init(opencl* loc_opencl_context)
{
  cl_int  loc_err;                                                              // Local error code.

  printf("Action: creating OpenCL command queue... ");

  context_id = loc_opencl_context->context_id;                                  // Initializing context id...
  device_id = loc_opencl_context->existing_device[choosen_device];              // Initializing device id...

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
