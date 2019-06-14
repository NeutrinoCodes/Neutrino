#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  queue_id   = NULL;                                                            // Initializing queue id...
  context_id = NULL;                                                            // Initializing context id...
  device_id  = NULL;                                                            // Initializing device id...
}

/// # OpenCL error get function
/// ### Description:
/// Translates an OpenCL numeric error code into a human-readable string.
const char* queue::get_error (
                              cl_int loc_error                                  // Local error code.
                             )
{
  switch(loc_error)
  {
    // Run-time and JIT compiler errors:
    case      0: return "CL_SUCCESS";
    case     -1: return "CL_DEVICE_NOT_FOUND";
    case     -2: return "CL_DEVICE_NOT_AVAILABLE";
    case     -3: return "CL_COMPILER_NOT_AVAILABLE";
    case     -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case     -5: return "CL_OUT_OF_RESOURCES";
    case     -6: return "CL_OUT_OF_HOST_MEMORY";
    case     -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case     -8: return "CL_MEM_COPY_OVERLAP";
    case     -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case    -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case    -11: return "CL_BUILD_PROGRAM_FAILURE";
    case    -12: return "CL_MAP_FAILURE";
    case    -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case    -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case    -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case    -16: return "CL_LINKER_NOT_AVAILABLE";
    case    -17: return "CL_LINK_PROGRAM_FAILURE";
    case    -18: return "CL_DEVICE_PARTITION_FAILED";
    case    -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // Compile-time errors:
    case    -30: return "CL_INVALID_VALUE";
    case    -31: return "CL_INVALID_DEVICE_TYPE";
    case    -32: return "CL_INVALID_PLATFORM";
    case    -33: return "CL_INVALID_DEVICE";
    case    -34: return "CL_INVALID_CONTEXT";
    case    -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case    -36: return "CL_INVALID_COMMAND_QUEUE";
    case    -37: return "CL_INVALID_HOST_PTR";
    case    -38: return "CL_INVALID_MEM_OBJECT";
    case    -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case    -40: return "CL_INVALID_IMAGE_SIZE";
    case    -41: return "CL_INVALID_SAMPLER";
    case    -42: return "CL_INVALID_BINARY";
    case    -43: return "CL_INVALID_BUILD_OPTIONS";
    case    -44: return "CL_INVALID_PROGRAM";
    case    -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case    -46: return "CL_INVALID_KERNEL_NAME";
    case    -47: return "CL_INVALID_KERNEL_DEFINITION";
    case    -48: return "CL_INVALID_KERNEL";
    case    -49: return "CL_INVALID_ARG_INDEX";
    case    -50: return "CL_INVALID_ARG_VALUE";
    case    -51: return "CL_INVALID_ARG_SIZE";
    case    -52: return "CL_INVALID_KERNEL_ARGS";
    case    -53: return "CL_INVALID_WORK_DIMENSION";
    case    -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case    -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case    -56: return "CL_INVALID_GLOBAL_OFFSET";
    case    -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case    -58: return "CL_INVALID_EVENT";
    case    -59: return "CL_INVALID_OPERATION";
    case    -60: return "CL_INVALID_GL_OBJECT";
    case    -61: return "CL_INVALID_BUFFER_SIZE";
    case    -62: return "CL_INVALID_MIP_LEVEL";
    case    -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case    -64: return "CL_INVALID_PROPERTY";
    case    -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case    -66: return "CL_INVALID_COMPILER_OPTIONS";
    case    -67: return "CL_INVALID_LINKER_OPTIONS";
    case    -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // Extension errors:
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default: return "Unknown OpenCL error";
  }
}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void queue::check_error (
                         cl_int loc_error                                       // Error code.
                        )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline->error (get_error (loc_error));                                    // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

/// # Initialisation function
/// ### Description:
/// Creates the OpenCL command queue.
void queue::init (
                  neutrino* loc_baseline
                 )
{
  cl_int loc_error;                                                             // Local error code.

  baseline   = loc_baseline;                                                    // Getting Neutrino baseline...
  baseline->action ("creating OpenCL command queue...");                        // Printing message...

  context_id = baseline->context_id;                                            // Initializing context id...
  device_id  = baseline->device_id;                                             // Initializing device id...

  // Creating OpenCL queue:
  queue_id   = clCreateCommandQueue (
                                     context_id,                                // OpenCL context ID.
                                     device_id,                                 // Device ID.
                                     0,                                         // Queue properties (con be used for enabling profiling).
                                     &loc_error
                                    );                                          // Error code.

  check_error (loc_error);                                                      // Checking error...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ACQUIRE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::acquire (
                     point* loc_data                                            // Data object.
                    )
{
  cl_int loc_error;                                                             // Local error code.

  glFinish ();                                                                  // Ensuring that all OpenGL routines have completed all operations...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects (
                                         queue_id,                              // Queue.
                                         1,                                     // # of memory objects.
                                         &loc_data.buffer,                      // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  check_error (loc_error);                                                      // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// RELEASE /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::release (
                     point* loc_data                                            // Data object.
                    )
{
  cl_int loc_error;                                                             // Local error code.

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects (
                                         queue_id,                              // Queue.
                                         1,                                     // # of memory objects.
                                         &loc_data.buffer,                      // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  clFinish (queue_id);                                                          // Ensuring that all OpenCL routines have completed all operations...

  check_error (loc_error);                                                      // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::~queue()
{
  cl_int loc_error;                                                             // Local error code.

  baseline->action ("releasing OpenCL command queue...");                       // Printing message...

  loc_error = clReleaseCommandQueue (queue_id);                                 // Releasing OpenCL queue...

  check_error (loc_error);                                                      // Checking error...

  baseline->done ();                                                            // Printing message...
}
