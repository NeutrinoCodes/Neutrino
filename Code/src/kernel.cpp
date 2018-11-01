#include "kernel.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::kernel()
{
  source              = NULL;                                                   // Initializing kernel source...
  program             = NULL;                                                   // Initializing kernel program...
  size                = 0;                                                      // Initializing kernel size...
  dimension           = 0;                                                      // Initializing kernel dimension..
  event               = NULL;                                                   // Initializing kernel event...
  kernel_id           = NULL;                                                   // Initializing kernel id...
}

void kernel::init (
                    path* loc_neutrino_path,
                    char* loc_kernel_filename,
                    size_t* loc_kernel_size,
                    cl_uint loc_kernel_dimension,
                    cl_context loc_context_id,
                    cl_device_id* loc_existing_device_id
                  )
{
  cl_int        loc_err;                                                        // Local error code.
  cl_device_id* loc_existing_device_id;                                         // Local existing device id array.
  size_t        loc_kernel_source_size;                                         // Local kernel source size [characters].
  int           i;                                                              // Index.

  file_name = kernel_filename;
  size      = kernel_size;
  dimension = kernel_dimension;

  printf("Action: loading OpenCL kernel source from file... ");

  load_file(neutrino_path, file_name, &source, &source_size);

  printf("Action: creating OpenCL program from kernel source... ");

  // Creating OpenCL program from its source:
  program = clCreateProgramWithSource(loc_neutrino->opencl_context->context_id,
                                      1,
                                      (const char**)&source,
                                      &source_size,
                                      &err);

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  free(source);                                                                 // Freeing OpenCL kernel buffer...
  printf("DONE!\n");

  printf("Action: building OpenCL program... ");

  loc_existing_device_id = (cl_device_id*) malloc(loc_neutrino->opencl_context->devices_number);

  for(i = 0; i < loc_neutrino->opencl_context->devices_number; i++)
  {
    loc_existing_device_id[i] = loc_neutrino->opencl_context->existing_device[i]->device_id;                  // Initializing existing devices...
  }

  // Building OpenCL program:
  loc_err = clBuildProgram(program,
                           1,
                           loc_existing_device_id,
                           "",
                           NULL,
                           NULL);

  if (loc_err != CL_SUCCESS)                                                    // Checking compiled kernel...
  {
    printf("\nError:  %s\n", get_error(loc_err));

    // Getting OpenCL compiler information:
    loc_err = clGetProgramBuildInfo(program,
                                    loc_existing_device_id[loc_neutrino->opencl_context->choosen_device],                      // EZOR 25OCT2018: to be generalized...
                                    CL_PROGRAM_BUILD_LOG,
                                    0,
                                    NULL,
                                    &log_size);

    if(loc_err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(loc_err));
      exit(loc_err);
    }

    log = (char*) calloc(log_size + 1, sizeof(char));                           // Allocating log buffer...

    if (!log)
    {
      printf("\nError:  unable to allocate buffer memory log!\n");
      exit(EXIT_FAILURE);
    }

    // Reading OpenCL compiler error log:
    loc_err = clGetProgramBuildInfo(program,
                                    existing_device_id[loc_neutrino->opencl_context],                          // EZOR 25OCT2018: to be generalized...
                                    CL_PROGRAM_BUILD_LOG,
                                    log_size + 1,
                                    log,
                                    NULL);

    if(loc_err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(loc_err));
      exit(loc_err);
    }

    printf("%s\n", log);                                                        // Displaying log...
    free(log);                                                                  // Freeing log...
    exit(loc_err);                                                              // Exiting...
  }

  printf("DONE!\n");

  printf("Action: creating OpenCL kernel object from program... ");

  // Creating OpenCL kernel:
  kernel_id = clCreateKernel(program,
                             KERNEL_NAME,
                             &err);

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("DONE!\n");
}

void kernel::execute(queue* q, kernel_event k_ev)
{
  err = clEnqueueNDRangeKernel(q->thequeue,                                     // Enqueueing OpenCL kernel (as a single task)...
                               thekernel,
                               dimension,
                               NULL,
                               &size,
                               NULL,
                               0,
                               NULL,
                               &event);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  switch(k_ev)
  {
    case WAIT:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;

    case DONT_WAIT:
                                                                                // Doing nothing!
    break;

    default:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;
  }


}

kernel::~kernel()
{
  printf("Action: releasing OpenCL kernel... ");

  err = clReleaseKernel(thekernel);                                             // Releasing OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL kernel event... ");
  err = clReleaseEvent(event);                                                  // Releasing OpenCL event...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL program... ");

  err = clReleaseProgram(program);                                              // Releasing OpenCL program...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}
