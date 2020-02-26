/// @file     opencl.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of the "opencl" class.

#include "opencl.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "opencl" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
opencl::opencl()
{
  opencl_platform  = NULL;                                                                          // Initializing platforms IDs array...
  platforms_number = 0;                                                                             // Initializing number of platforms...
  devices_number   = 0;                                                                             // Initializing number of devices...
  properties       = NULL;                                                                          // Initializing platforms' properties...
  context_id       = NULL;                                                                          // Initializing platforms' context...
  device_type      = NU_DEFAULT;                                                                    // Initializing device type...
}

cl_uint opencl::get_platforms_number ()
{
  cl_int  loc_error;                                                                                // Error code.
  cl_uint loc_platforms_number;                                                                     // Number of platforms.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting number of existing OpenCL platforms:
  loc_error = clGetPlatformIDs
              (
               0,                                                                                   // "0" = we are asking for the number of platforms.
               NULL,                                                                                // Dummy platfomrs id.
               &loc_platforms_number                                                                // Returned local number of existing platforms.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  return loc_platforms_number;                                                                      // Returning number of existing platforms...
}

cl_platform_id opencl::get_platform_id
(
 cl_uint loc_platform_index                                                                         // OpenCL platform index.
)
{
  cl_int          loc_error;                                                                        // Error code.
  cl_platform_id* loc_platform_id;                                                                  // Platform IDs array.
  cl_platform_id  loc_selected_platform_id;                                                         // Selected platform ID.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("getting OpenCL platform ID...");                                               // Printing message...

  loc_platform_id          = new cl_platform_id[platforms_number];                                  // Allocating platform array...

  // Getting OpenCL platform IDs:
  loc_error                = clGetPlatformIDs
                             (
                              platforms_number,                                                     // Number of existing platforms.
                              loc_platform_id,                                                      // Platform IDs array.
                              NULL                                                                  // Dummy number of platforms.
                             );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  loc_selected_platform_id = loc_platform_id[loc_platform_index];                                   // Setting id of selected platform...
  delete[] loc_platform_id;                                                                         // Deleting platform IDs array...

  baseline->done ();                                                                                // Printing message...

  return(loc_selected_platform_id);                                                                 // Returning selected platform ID...
}

cl_uint opencl::get_devices_number
(
 cl_uint loc_platform_index                                                                         // OpenCL platform index.
)
{
  cl_int  loc_error;                                                                                // Error code.
  cl_uint loc_devices_number;                                                                       // Number of devices.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting number of existing OpenCL devices:
  loc_error = clGetDeviceIDs
              (
               opencl_platform[loc_platform_index]->id,                                             // Platform ID.
               device_type,                                                                         // Device type.
               0,                                                                                   // "0" means we are asking for the number of devices.
               NULL,                                                                                // Dummy device.
               &loc_devices_number                                                                  // Returned local number of existing devices.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  return(loc_devices_number);                                                                       // Returning number of existing devices...
}

cl_device_id opencl::get_device_id
(
 cl_uint loc_device_index,                                                                          // OpenCL platform index.
 cl_uint loc_platform_index                                                                         // OpenCL device index.
)
{
  cl_int        loc_error;                                                                          // OpenCL error code.
  cl_device_id* loc_device_id;                                                                      // Opencl device ID.
  cl_device_id  loc_selected_device_id;                                                             // OpenCL selected device ID.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  devices_number = get_devices_number (loc_platform_index);                                         // Getting number of existing devices...
  loc_device_id  = new cl_device_id[devices_number];                                                // Allocating platform array...

  baseline->action ("getting OpenCL device ID...");                                                 // Printing message...

  // Getting OpenCL device IDs:
  loc_error      = clGetDeviceIDs
                   (
                    opencl_platform[loc_platform_index]->id,                                        // Platform ID.
                    device_type,                                                                    // Device type.
                    platforms_number,                                                               // Number of existing platforms.
                    loc_device_id,                                                                  // Device IDs array.
                    NULL                                                                            // Dummy number of platforms.
                   );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  loc_selected_device_id = loc_device_id[loc_device_index];                                         // Setting ID of selected device...
  delete[] loc_device_id;                                                                           // Deleting device IDs array...

  baseline->done ();                                                                                // Printing message...

  return(loc_selected_device_id);                                                                   // Returning selected device ID...
}

void opencl::init
(
 neutrino*           loc_baseline,                                                                  // Neutrino baseline.
 opengl*             loc_gui,                                                                       // OpenGL gui.
 compute_device_type loc_device_type                                                                // OpenCL device type.
)
{
  cl_int  loc_error;                                                                                // Error code.
  cl_uint i;                                                                                        // Index.
  bool    loc_platform_interop = false;                                                             // Platform interoperability flag.
  bool    loc_device_interop   = false;                                                             // Device interoperability flag.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("initializing OpenCL...");                                                      // Printing message...

  baseline         = loc_baseline;                                                                  // Getting Neutrino baseline...
  device_type_text = new char[NU_MAX_TEXT_SIZE];                                                    // Device type text [string].

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// SETTING TARGET DEVICE TYPE ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  switch(loc_device_type)                                                                           // Selecting device type...
  {
    case NU_CPU:
      device_type      = CL_DEVICE_TYPE_CPU;                                                        // Setting device type = NU_CPU...
      device_type_text = std::string ("NU_CPU");                                                    // Setting device_type_text...
      break;

    case NU_GPU:
      device_type      = CL_DEVICE_TYPE_GPU;                                                        // Setting device type = NU_GPU...
      device_type_text = std::string ("NU_GPU");                                                    // Setting device_type_text...
      break;

    case NU_ACCELERATOR:
      device_type      = CL_DEVICE_TYPE_ACCELERATOR;                                                // Setting device type = NU_ACCELERATOR...
      device_type_text = std::string ("NU_ACCELERATOR");                                            // Setting device_type_text...
      break;

    case NU_DEFAULT:
      device_type      = CL_DEVICE_TYPE_DEFAULT;                                                    // Setting device type = NU_DEFAULT...
      device_type_text = std::string ("NU_DEFAULT");                                                // Setting device_type_text...
      break;

    case NU_ALL:
      device_type      = CL_DEVICE_TYPE_ALL;                                                        // Setting device type = NU_ALL...
      device_type_text = std::string ("NU_ALL");                                                    // Setting device_tyep_text...
      break;

    default:
      device_type      = CL_DEVICE_TYPE_DEFAULT;                                                    // Setting device type = NU_DEFAULT...
      device_type_text = std::string ("NU_DEFAULT");                                                // Printing message...
      break;
  }

  baseline->done ();                                                                                // Printing message...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// SETTING OPENCL PLATFORM /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  platforms_number = get_platforms_number ();                                                       // Getting number of existing platforms [#]...
  opencl_platform  = new platform*[platforms_number];                                               // Initializing platform...

  for(i = 0; i < platforms_number; i++)                                                             // Checking all platforms:
  {
    opencl_platform[i] = new platform ();
    opencl_platform[i]->init (get_platform_id (i));

    std::cout << "        PLATFORM #: " +
      std::to_string (i + 1) << std::endl;                                                          // Printing message...
    std::cout << "        --> profile:    " +
      opencl_platform[i]->profile << std::endl;                                                     // Printing message...
    std::cout << "        --> version:    " +
      opencl_platform[i]->version << std::endl;                                                     // Printing message...
    std::cout << "        --> name:       " +
      opencl_platform[i]->name << std::endl;                                                        // Printing message...
    std::cout << "        --> vendor:     " +
      opencl_platform[i]->vendor << std::endl;                                                      // Printing message...
    std::cout << "        --> extensions: ";                                                        // Printing message (24 characters long)...

    // Listing platform extensions:
    baseline->list (
                    opencl_platform[i]->extensions,                                                 // Extension value.
                    " ",                                                                            // Extension delimiter.
                    24                                                                              // Previous text string padding.
                   );
  }

  if(platforms_number == 1)
  {
    selected_platform = 0;                                                                          // Setting 1st platform, in case it is the only found one...
  }

  if (platforms_number > 1)                                                                         // Asking to select a platform...
  {
      std::cout << "Action: please select a platform [1..." + std::to_string(platforms_number);     // Formulating query...

      selected_platform = (
          (cl_uint)baseline->query_numeric
          (
              " + enter]: ",                                                                        // Query text.
              1,                                                                                    // Minimum numeric choice in query answer.
              platforms_number                                                                      // Maximum numeric choice in query answer.
          )
          ) - 1;                                                                                    // Setting selected platform index...
  }
  
  baseline->platform_id = opencl_platform[selected_platform]->id;                                   // Setting neutrino OpenCL platform ID...

  if(baseline->property (opencl_platform[selected_platform]->extensions, NU_INTEROP))               // Checking for platform interoperability flag...
  {
    loc_platform_interop = true;                                                                    // Setting platform interoperability flag...
  }
  else
  {
    loc_platform_interop = false;                                                                   // Resetting platform interoperability flag...
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// SETTING OPENCL DEVICE ////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  devices_number        = get_devices_number (selected_platform);                                   // Getting number of existing NU_GPU devices [#]...

  opencl_device         = new device*[devices_number];                                              // Initializing platform...

  devices_number = 1; // EZOR 25FEB2020 test.

  for(i = 0; i < devices_number; i++)                                                               // Checking all devices:
  {
    opencl_device[i] = new device ();
    opencl_device[i]->init (get_device_id (i, selected_platform));                                  // Initializing OpenCL device...

    std::cout << "        DEVICE #: ";
    std::cout << std::to_string (i + 1) << std::endl;                                               // Printing message...

    std::cout << "        --> available: ";
    std::cout << opencl_device[i]->available << std::endl;                                          // Printing message...

    std::cout << "        --> profile: ";
    std::cout << opencl_device[i]->profile << std::endl;                                            // Printing message...

    std::cout << "        --> version: ";
    std::cout << opencl_device[i]->version << std::endl;                                            // Printing message...

    std::cout << "        --> name:     ";
    std::cout << opencl_device[i]->name << std::endl;                                               // Printing message...

    std::cout << "        --> type: ";
    std::cout << opencl_device[i]->type << std::endl;                                               // Printing message...

    std::cout << "        --> vendor: ";
    std::cout << opencl_device[i]->vendor << std::endl;                                             // Printing message...

    std::cout << "        --> vendor id: ";
    std::cout << opencl_device[i]->vendor_id << std::endl;                                          // Printing message...

    std::cout << "        --> driver version: ";
    std::cout << opencl_device[i]->driver_version << std::endl;                                     // Printing message...

    std::cout << "        --> platform: ";
    std::cout << opencl_device[i]->profile << std::endl;                                            // Printing message...

    // Listing device extensions:
    std::cout << "        --> extensions: ";
    baseline->list
    (
     opencl_device[i]->extensions,                                                                  // Extension value.
     " ",                                                                                           // Extension delimiter.
     24                                                                                             // Previous text string padding.
    );

    std::cout << "        --> address bits: ";
    std::cout << opencl_device[i]->address_bits << std::endl;                                       // Printing message...

    std::cout << "        --> double fp config: ";
    std::cout << opencl_device[i]->double_fp_config << std::endl;                                   // Printing message...

    std::cout << "        --> endian little: ";
    std::cout << opencl_device[i]->endian_little << std::endl;                                      // Printing message...

    std::cout << "        --> error correction support: ";
    std::cout << opencl_device[i]->error_correction_support << std::endl;                           // Printing message...

    std::cout << "        --> execution capabilities: ";
    std::cout << opencl_device[i]->execution_capabilities << std::endl;                             // Printing message...

    std::cout << "        --> global mem cache size: ";
    std::cout << opencl_device[i]->global_mem_cache_size << std::endl;                              // Printing message...

    std::cout << "        --> global mem cache type: ";
    std::cout << opencl_device[i]->global_mem_cache_type << std::endl;                              // Printing message...

    std::cout << "        --> global mem cacheline size: ";
    std::cout << opencl_device[i]->global_mem_cacheline_size << std::endl;                          // Printing message...

    std::cout << "        --> global mem size: ";
    std::cout << opencl_device[i]->global_mem_size << std::endl;                                    // Printing message...

    std::cout << "        --> local mem size: ";
    std::cout << opencl_device[i]->local_mem_size << std::endl;                                     // Printing message...

    std::cout << "        --> local mem type: ";
    std::cout << opencl_device[i]->local_mem_type << std::endl;                                     // Printing message...

    std::cout << "        --> single fp config: ";
    std::cout << opencl_device[i]->single_fp_config << std::endl;                                   // Printing message...

    std::cout << "        --> half fp config: ";
    std::cout << opencl_device[i]->half_fp_config << std::endl;                                     // Printing message...

    std::cout << "        --> image support: ";
    std::cout << opencl_device[i]->image_support << std::endl;                                      // Printing message...

    std::cout << "        --> image 2D max height: ";
    std::cout << opencl_device[i]->image2D_max_height << std::endl;                                 // Printing message...

    std::cout << "        --> image 2D max width: ";
    std::cout << opencl_device[i]->image2D_max_width << std::endl;                                  // Printing message...

    std::cout << "        --> image 3D max depth: ";
    std::cout << opencl_device[i]->image3D_max_depth << std::endl;                                  // Printing message...

    std::cout << "        --> image 3D max height: ";
    std::cout << opencl_device[i]->image3D_max_height << std::endl;                                 // Printing message...

    std::cout << "        --> image 3D max width: ";
    std::cout << opencl_device[i]->image3D_max_width << std::endl;                                  // Printing message...

    std::cout << "        --> max clock frequency: ";
    std::cout << opencl_device[i]->max_clock_frequency << std::endl;                                // Printing message...

    std::cout << "        --> max compute units: ";
    std::cout << opencl_device[i]->max_compute_units << std::endl;                                  // Printing message...

    std::cout << "        --> max constant args: ";
    std::cout << opencl_device[i]->max_constant_args << std::endl;                                  // Printing message...

    std::cout << "        --> max constant buffer size: ";
    std::cout << opencl_device[i]->max_constant_buffer_size << std::endl;                           // Printing message...

    std::cout << "        --> max mem alloc size: ";
    std::cout << opencl_device[i]->max_mem_alloc_size << std::endl;                                 // Printing message...

    std::cout << "        --> max parameter size: ";
    std::cout << opencl_device[i]->max_parameter_size << std::endl;                                 // Printing message...

    std::cout << "        --> max read image args: ";
    std::cout << opencl_device[i]->max_read_image_args << std::endl;                                // Printing message...

    std::cout << "        --> max write image args: ";
    std::cout << opencl_device[i]->max_write_image_args << std::endl;                               // Printing message...

    std::cout << "        --> max samplers: ";
    std::cout << opencl_device[i]->max_samplers << std::endl;                                       // Printing message...

    std::cout << "        --> max work group size: ";
    std::cout << opencl_device[i]->max_work_group_size << std::endl;                                // Printing message...

    std::cout << "        --> max work item dimensions: ";
    std::cout << opencl_device[i]->max_work_item_dimensions << std::endl;                           // Printing message...

    /*
       std::cout << "        --> max work time sizes: ";
       std::cout << opencl_device[i]->max_work_item_sizes << std::endl;                // Printing message...
     */

    std::cout << "        --> mem base addr align: ";
    std::cout << opencl_device[i]->mem_base_addr_align << std::endl;                                // Printing message...

    std::cout << "        --> min data type align size: ";
    std::cout << opencl_device[i]->min_data_type_align_size << std::endl;                           // Printing message...

    std::cout << "        --> preferred vector width char: ";
    std::cout << opencl_device[i]->preferred_vector_width_char << std::endl;                        // Printing message...

    std::cout << "        --> preferred vector width short: ";
    std::cout << opencl_device[i]->preferred_vector_width_short << std::endl;                       // Printing message...

    std::cout << "        --> preferred vector width int: ";
    std::cout << opencl_device[i]->preferred_vector_width_int << std::endl;                         // Printing message...

    std::cout << "        --> preferred vector width long: ";
    std::cout << opencl_device[i]->preferred_vector_width_long << std::endl;                        // Printing message...

    std::cout << "        --> preferred vector width float: ";
    std::cout << opencl_device[i]->preferred_vector_width_double << std::endl;                      // Printing message...

    std::cout << "        --> device profiling timer resolution: ";
    std::cout << opencl_device[i]->profiling_timer_resolution << std::endl;                         // Printing message...

    std::cout << "        --> queue properties: ";
    std::cout << opencl_device[i]->queue_properties << std::endl;                                   // Printing message...
  }

  if(devices_number == 1)
  {
    if(baseline->property (opencl_device[0]->extensions, NU_INTEROP))                               // Checking for device interoperability flag...
    {
      loc_device_interop = true;                                                                    // Setting device interoperability flag...
    }
    else
    {
      loc_device_interop = false;                                                                   // Resetting device interoperability flag...
    }
  }

  if(devices_number > 1)                                                                            // Asking to select a platform...
  {
    std::cout << "Action: please select a device [1..." +
      std::to_string (devices_number);                                                              // Formulating query...
    selected_device = (
                       (cl_uint) baseline->query_numeric
                       (
                        " + enter]: ",                                                              // Query text.
                        1,                                                                          // Minimum numeric choice in query answer.
                        devices_number                                                              // Maximum numeric choice in query answer.
                       )
                      ) - 1;                                                                        // Setting selected device index...
    if(baseline->property (opencl_device[selected_device]->extensions, NU_INTEROP))                 // Checking for device interoperability flag...
    {
      loc_device_interop = true;                                                                    // Setting device interoperability flag...
    }
    else
    {
      loc_device_interop = false;                                                                   // Resetting device interoperability flag...
    }
  }

  else
  {
    selected_device = 0;                                                                            // Setting 1st device, in case it is the only found one...
  }

  if(loc_platform_interop && loc_device_interop)                                                    // Evaluating interoperability flag...
  {
    baseline->interop = true;                                                                       // Setting interoperability flag...
  }
  else
  {
    baseline->interop = false;                                                                      // Resetting interoperability flag...
  }

  // EZOR 02NOV2019: non-interop test.
  // It looks it works also when interop = false.
  // baseline->interop   = false;

  baseline->device_id = opencl_device[selected_device]->id;                                         // Setting neutrino OpenCL device ID...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// IDENTIFYING OS //////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  baseline->action ("identifying operating system...");                                             // Printing message...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  #ifdef __APPLE__                                                                                  // Checking for APPLE system...
    baseline->done ();
    std::cout << "        --> OS: APPLE" << std::endl;                                              // Printing message...

    cl_context_properties properties[3];

    baseline->action ("verifying OpenCL/GL interoperability support...");                           // Printing message...
    if(baseline->interop)
    {
      baseline->done ();                                                                            // Printing message...

      CGLContextObj    kCGLContext    = CGLGetCurrentContext ();
      CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup (kCGLContext);
      properties[0] = CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE;                                 // Setting APPLE with CL-GL interop...
      properties[1] = (cl_context_properties) kCGLShareGroup;
      properties[2] = 0;
    }
    else
    {
      baseline->warning ("could not find OpenCL/GL interoperability!");                             // Printing message...
      baseline->unfulfilled ();                                                                     // Printing message...
      baseline->action ("switching to non-interoperability modality...");                           // Printing message...

      properties[0] = CL_CONTEXT_PLATFORM;                                                          // Setting APPLE without CL-GL interop...
      properties[1] = (cl_context_properties)baseline->platform_id;
      properties[2] = 0;

      baseline->done ();                                                                            // Printing message...
    }
  #endif

  #ifdef __linux__                                                                                  // Checking for LINUX system...
    baseline->done ();
    std::cout << "        --> OS: LINUX" << std::endl;                                              // Printing message...

    cl_context_properties properties[7];

    baseline->action ("verifying OpenCL/GL interoperability support...");                           // Printing message...
    if(baseline->interop)
    {
      baseline->done ();                                                                            // Printing message...

      properties[0] = CL_GL_CONTEXT_KHR;                                                            // Setting LINUX with CL-GL interop...
      properties[1] = (cl_context_properties)glfwGetGLXContext
                      (
                       loc_gui->glfw_window
                      );
      properties[2] = CL_GLX_DISPLAY_KHR;
      properties[3] = (cl_context_properties)glfwGetX11Display ();
      properties[4] = CL_CONTEXT_PLATFORM;
      properties[5] = (cl_context_properties)baseline->platform_id;
      properties[6] = 0;
    }
    else
    {
      baseline->warning ("could not find OpenCL/GL interoperability!");                             // Printing message...
      baseline->unfulfilled ();                                                                     // Printing message...
      baseline->action ("switching to non-interoperability modality...");                           // Printing message...

      properties[0] = CL_CONTEXT_PLATFORM;                                                          // Setting LINUX without CL-GL interop...
      properties[1] = (cl_context_properties)baseline->platform_id;
      properties[2] = 0;

      baseline->done ();                                                                            // Printing message...
    }
  #endif

  #ifdef WIN32                                                                                      // Checking for WINDOWS system...
    baseline->done ();
    std::cout << "        --> OS: WINDOWS" << std::endl;                                            // Printing message...

    cl_context_properties properties[7];

    baseline->action ("verifying OpenCL/GL interoperability support...");                           // Printing message...
    if(baseline->interop)
    {
      baseline->done ();                                                                            // Printing message...

      properties[0] = CL_GL_CONTEXT_KHR;                                                            // Setting WINDOWS with CL-GL interop...
      properties[1] = (cl_context_properties)glfwGetWGLContext
                      (
                       loc_gui->glfw_window
                      );
      properties[2] = CL_WGL_HDC_KHR;
      properties[3] = (cl_context_properties)GetDC
                      (
                       glfwGetWin32Window
                       (
                        loc_gui->glfw_window
                       )
                      );
      properties[4] = CL_CONTEXT_PLATFORM;
      properties[5] = (cl_context_properties)baseline->platform_id;
      properties[6] = 0;
    }
    else
    {
      baseline->warning ("could not find OpenCL/GL interoperability!");                             // Printing message...
      baseline->unfulfilled ();                                                                     // Printing message...
      baseline->action ("switching to non-interoperability modality...");                           // Printing message...

      properties[0] = CL_CONTEXT_PLATFORM;                                                          // Setting WINDOWS without CL-GL interop...
      properties[1] = (cl_context_properties)baseline->platform_id;
      properties[2] = 0;

      baseline->done ();                                                                            // Printing message...
    }
  #endif

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CREATING OPENCL CONTEXT ///////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  baseline->action ("creating OpenCL context...");                                                  // Printing message...

  context_id = clCreateContext
               (
                properties,                                                                         // Context properties.
                1,                                                                                  // Number of devices on selected platform.
                &opencl_device[selected_device]->id,                                                // Pointer to the selected device on selected platform.
                NULL,                                                                               // Context error report callback function.
                NULL,                                                                               // Context error report callback function argument.
                &loc_error                                                                          // Error code.
               );

  baseline->check_error (loc_error);                                                                // Checking returned error code...
  baseline->context_id = context_id;                                                                // Setting neutrino OpenCL context ID...

  baseline->done ();                                                                                // Printing message...
}

void opencl::execute
(
 kernel*     loc_kernel,                                                                            // OpenCL kernel.
 queue*      loc_queue,                                                                             // OpenCL queue.
 kernel_mode loc_kernel_mode                                                                        // Kernel mode.
)
{
  cl_int  loc_error;                                                                                // Error code.
  cl_uint kernel_dimension;                                                                         // Kernel dimension.
  size_t* kernel_size;                                                                              // Kernel size array.
  bool    kernel_valid = false;                                                                     // Validity flag.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (loc_queue->queue_id);                                                                   // Waiting for OpenCL to finish...

  // Selecting kernel size:
  if(
     (loc_kernel->size_i > 0) &&
     (loc_kernel->size_j == 0) &&
     (loc_kernel->size_k == 0)
    )
  {
    kernel_dimension = 1;
    kernel_size      = new size_t[kernel_dimension];
    kernel_size[0]   = loc_kernel->size_i;
    kernel_valid     = true;
  }

  if(
     (loc_kernel->size_i > 0) &&
     (loc_kernel->size_j > 0) &&
     (loc_kernel->size_k == 0)
    )
  {
    kernel_dimension = 2;
    kernel_size      = new size_t[kernel_dimension];
    kernel_size[0]   = loc_kernel->size_i;
    kernel_size[1]   = loc_kernel->size_j;
    kernel_valid     = true;
  }

  if(
     (loc_kernel->size_i > 0) &&
     (loc_kernel->size_j > 0) &&
     (loc_kernel->size_k > 0)
    )
  {
    kernel_dimension = 3;
    kernel_size      = new size_t[kernel_dimension];
    kernel_size[0]   = loc_kernel->size_i;
    kernel_size[1]   = loc_kernel->size_j;
    kernel_size[2]   = loc_kernel->size_k;
    kernel_valid     = true;
  }

  if(!kernel_valid)
  {
    baseline->error ("invalid kernel size!");
    exit (EXIT_FAILURE);
  }

  // Enqueueing OpenCL kernel (as a single task):
  loc_error = clEnqueueNDRangeKernel
              (
               loc_queue->queue_id,                                                                 // Queue ID.
               loc_kernel->kernel_id,                                                               // Kernel ID.
               kernel_dimension,                                                                    // Kernel dimension.
               NULL,                                                                                // Global work offset.
               kernel_size,                                                                         // Global work size.
               NULL,                                                                                // Local work size.
               0,                                                                                   // Number of events.
               NULL,                                                                                // Event list.
               &loc_kernel->event                                                                   // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  clFinish (loc_queue->queue_id);                                                                   // Waiting for OpenCL to finish...

  // Selecting kernel mode:
  switch(loc_kernel_mode)
  {
    case NU_WAIT:
      loc_error = clWaitForEvents (1, &loc_kernel->event);                                          // Waiting for kernel to be completed (host blocking)...
      baseline->check_error (loc_error);                                                            // Checking error...
      break;

    case NU_DONT_WAIT:
      // Doing nothing, without waiting!
      break;

    default:
      loc_error = clWaitForEvents (1, &loc_kernel->event);                                          // Waiting for kernel to be completed (host blocking)...
      baseline->check_error (loc_error);                                                            // Checking error...
      break;
  }
}

opencl::~opencl()
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("releasing OpenCL context...");                                                 // Printing message...

  delete[] opencl_platform;                                                                         // Deleting platform...
  delete[] opencl_device;                                                                           // Deleting device...

  loc_error = clReleaseContext (context_id);                                                        // Releasing OpenCL context...

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  baseline->done ();                                                                                // Printing message...
}
