/// @file     neutrino.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of the "neutrino" class and some macros.

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "neutrino" class ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
neutrino::neutrino()
{
}

void neutrino::init
(
 size_t loc_q_num,
 size_t loc_k_num
)
{
  interop     = false;                                                                              // Use OpenCL-OpenGL interop.
  tic         = 0.0;                                                                                // Tic time [us].
  toc         = 0.0;                                                                                // Toc time [us].
  loop_time   = 0.0;                                                                                // Loop time [us].
  context_id  = NULL;                                                                               // OpenCL context ID.
  platform_id = NULL;                                                                               // OpenCL platform ID.
  device_id   = NULL;                                                                               // OpenCL device ID.

  // Setting ANSI color modality for Windows:
  #ifdef WIN32
    DWORD  l_mode;
    HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
    GetConsoleMode (hStdout,&l_mode);
    SetConsoleMode (
                    hStdout,
                    l_mode |
                    ENABLE_VIRTUAL_TERMINAL_PROCESSING |
                    DISABLE_NEWLINE_AUTO_RETURN
                   );
  #endif

  // Initializing neutrino object:
  action ("initializing NEUTRINO...");                                                              // Printing message...

  q_num         = loc_q_num;                                                                        // Getting number of OpenCL queues...
  k_num         = loc_k_num;                                                                        // Getting number of OpenCL kernels...
  kernel_id     = new cl_kernel[k_num];                                                             // Initializing OpenCL kernel ID array...
  terminal_time = 0;                                                                                // Resetting terminal time...
  loop_time     = 0.0;                                                                              // Resetting loop time...
  tic           = 0.0;                                                                              // Resetting tic time...
  toc           = 0.0;                                                                              // Resetting toc time...
  size_t i;                                                                                         // Index.

  for(i = 0; i < k_num; i++)                                                                        // Scanning OpenCL kernel argument array...
  {
    kernel_id[i] = NULL;                                                                            // Resetting kernel ID array...
  }

  done ();                                                                                          // Printing message...
}

void neutrino::get_tic ()
{
  tic = glfwGetTime ();                                                                             // Getting "tic"...
}

void neutrino::get_toc ()
{
  std::string loc_text;                                                                             // Text buffer.
  std::string loc_pad;                                                                              // Text pad.

  toc            = glfwGetTime ();                                                                  // Getting "toc"...
  loop_time      = toc - tic;                                                                       // Loop execution time [s].
  terminal_time += size_t (round (loop_time*1000000.0f));                                           // Terminal time [us].

  if(terminal_time > NU_TERMINAL_REFRESH)                                                           // Checking terminal time...
  {
    terminal_time = 0;                                                                              // Resetting terminal time.
    erase ();                                                                                       // Erasing terminal line...

    // Compiling message string:
    loc_text      = std::string (NU_COLOR_CYAN) +
                    std::string ("Action: ") +
                    std::string (NU_COLOR_NORMAL) +
                    std::string ("running host loop time = ") +
                    std::to_string (long (round (1000000.0*loop_time))) +
                    std::string (" us");

    std::cout << loc_text + loc_pad << std::flush;                                                  // Printing buffer...
  }
}

std::string neutrino::read_file
(
 std::string loc_file_name                                                                          // File name.
)
{
  std::string   loc_data;                                                                           // File data.
  std::ifstream loc_file (loc_file_name, std::ios::in | std::ios::binary);                          // File.

  if(loc_file)
  {
    loc_file.seekg (0, std::ios::end);
    loc_data.resize (loc_file.tellg ());
    loc_file.seekg (0, std::ios::beg);
    loc_file.read (loc_data.data (), loc_data.size ());
    loc_file.close ();
  }
  else
  {
    loc_data = "Error while reading file " + loc_file_name;
    std::cout << loc_data << std::endl;
  }
  return(loc_data);                                                                                 // Returning file content as string...
}

size_t neutrino::query_numeric
(
 std::string loc_caption,                                                                           // Text query caption.
 int         loc_min,                                                                               // Minimum queried numeric value.
 int         loc_max                                                                                // Maximum queried numeric value.
)
{
  std::string loc_buffer;                                                                           // Text buffer.
  size_t      loc_numeric;                                                                          // Numeric value.
  bool        valid_choice = false;                                                                 // User's choice.

  std::cout << loc_caption;                                                                         // Printing caption...
  std::cin >> loc_buffer;                                                                           // Getting user input...

  loc_numeric = stoi (loc_buffer);                                                                  // Converting input string to numeric value...

  while(!valid_choice)                                                                              // Checking choice validity...
  {
    if((loc_min <= loc_numeric) &&
       (loc_numeric <= loc_max))
    {
      valid_choice = true;                                                                          // Setting flag...
    }

    else
    {
      error ("invalid input! Please, try again!");                                                  // Printing message...
      std::cout << loc_caption;                                                                     // Printing caption...
    }
  }

  return(loc_numeric);                                                                              // Returning numeric choice...
}

void neutrino::erase ()
{
  std::cout << NU_ERASE;                                                                            // Erasing terminal stdout current line....
}

void neutrino::action
(
 std::string loc_text                                                                               // Message text.
)
{
  size_t      i;                                                                                    // Index.
  std::string text;                                                                                 // Text buffer.
  std::string pad;                                                                                  // Text pad.
  size_t      pad_size;                                                                             // Text pad size.

  // Compiling message string:
  text     = std::string (NU_COLOR_CYAN) +
             std::string ("Action: ") +
             std::string (NU_COLOR_NORMAL) +
             loc_text;

  pad_size = NU_MAX_MESSAGE_SIZE - text.size ();                                                    // Computing text padding...

  if(pad_size >= 0)                                                                                 // Checking padding...
  {
    for(i = 0; i < pad_size; i++)                                                                   // Compiling padding...
    {
      pad += " ";                                                                                   // Adding pad...
    }
  }

  else                                                                                              // Generating error message...
  {
    error ("string too big!");                                                                      // Printing message...
    exit (1);                                                                                       // Exiting...
  }

  std::cout << text + pad;                                                                          // Printing buffer...
}

void neutrino::warning (
                        std::string loc_text                                                        ///< User defined text message.
                       )
{
  size_t      i;                                                                                    // Index.
  std::string text;                                                                                 // Text buffer.
  std::string pad;                                                                                  // Text pad.
  size_t      pad_size;                                                                             // Text pad size.

  // Compiling message string:
  text     = std::string (NU_COLOR_YELLOW) +
             std::string ("Warning:") +
             std::string (NU_COLOR_NORMAL) +
             loc_text;

  pad_size = NU_MAX_MESSAGE_SIZE - text.size ();                                                    // Computing text padding...

  if(pad_size >= 0)                                                                                 // Checking padding...
  {
    for(i = 0; i < pad_size; i++)                                                                   // Compiling padding...
    {
      pad += " ";                                                                                   // Adding pad...
    }
  }

  else                                                                                              // Generating error message...
  {
    error ("string too big!");                                                                      // Printing message...
    exit (1);                                                                                       // Exiting...
  }

  std::cout << std::endl << text + pad;
}

void neutrino::error
(
 std::string loc_text                                                                               // User defined text message.
)
{
  size_t      i;                                                                                    // Index.
  std::string text;                                                                                 // Text buffer.
  std::string pad;                                                                                  // Text pad.
  size_t      pad_size;                                                                             // Text pad size.

  // Compiling message string:
  text     = std::string (NU_COLOR_RED) +
             std::string ("Error:  ") +
             std::string (NU_COLOR_NORMAL) +
             loc_text;

  pad_size = NU_MAX_MESSAGE_SIZE - text.size ();                                                    // Computing text padding...

  if(pad_size >= 0)                                                                                 // Checking padding...
  {
    for(i = 0; i < pad_size; i++)                                                                   // Compiling padding...
    {
      pad += " ";
    }
  }

  else                                                                                              // Generating error message...
  {
    error ("string too big!");                                                                      // Printing message...
    exit (1);                                                                                       // Exiting...
  }

  std::cout << text + pad << std::endl;                                                             // Printing buffer...

  terminated ();
}

void neutrino::list
(
 std::string loc_text,                                                                              // User defined text message.
 std::string loc_delimiter,                                                                         // User defined text delimiter.
 size_t      loc_tab                                                                                // User defined text tab size.
)
{
  size_t      loc_pos;                                                                              // Position of delimiter.
  size_t      loc_pos_new;                                                                          // New position of delimiter.
  std::string loc_pad;                                                                              // Blank string.
  std::string loc_token;                                                                            // Token string.
  size_t      i;                                                                                    // Index.

  loc_pos     = 0;                                                                                  // Resetting delimiter position...
  loc_pos_new = 0;
  loc_pad     = "";                                                                                 // Resetting pad string...
  loc_token   = "";                                                                                 // Resetting token string...


  for(i = 0; i < loc_tab; i++)
  {
    loc_pad += " ";                                                                                 // Filling pad string...
  }

  while(loc_pos_new != std::string::npos)
  {
    loc_pos_new = loc_text.find
                  (
                   loc_delimiter,
                   loc_pos
                  );                                                                                // Finding delimiter's position...

    loc_token   = loc_text.substr
                  (
                   loc_pos,
                   loc_pos_new - loc_pos
                  );                                                                                // Extracting between delimiters...
    std::cout << loc_token << std::endl << loc_pad;                                                 // Printing resulting string...
    loc_pos     = loc_pos_new + loc_delimiter.size ();                                              // Updating delimiter position...
  }

  std::cout << NU_ERASE;                                                                            // Erasing current text line...
}

bool neutrino::property (
                         std::string loc_input,                                                     // Input string.
                         std::string loc_property                                                   // Property string.
                        )
{
  std::transform (loc_input.begin (), loc_input.end (), loc_input.begin (), ::tolower);             // Convert complete given String to lower case
  std::transform (loc_property.begin (), loc_property.end (), loc_property.begin (), ::tolower);    // Convert complete given Sub String to lower case

  // Looking for substring:
  if(loc_input.find (loc_property, 0) != std::string::npos)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void neutrino::done ()
{
  std::string loc_text;                                                                             // Text buffer.

  // Compiling message string:
  loc_text = std::string (NU_COLOR_GREEN) +
             std::string ("DONE!") +
             std::string (NU_COLOR_NORMAL);

  std::cout << loc_text << std::endl;                                                               // Printing message...
}

void neutrino::unfulfilled ()
{
  std::string loc_text;                                                                             // Text buffer.

  // Compiling message string:
  loc_text = std::string (NU_COLOR_YELLOW) +
             std::string ("UNFULFILLED!") +
             std::string (NU_COLOR_NORMAL);

  std::cout << loc_text << std::endl;                                                               // Printing message...
}

void neutrino::terminated ()
{
  std::string loc_text;                                                                             // Text buffer.

  // Compiling message string:
  loc_text = std::string (NU_COLOR_RED) +
             std::string ("TERMINATED!") +
             std::string (NU_COLOR_NORMAL);

  std::cout << loc_text << std::endl;                                                               // Printing message...
}

double neutrino::constrain_double
(
 double loc_input,                                                                                  // Input number to be constrained.
 double loc_min,                                                                                    // Minimum constraint.
 double loc_max                                                                                     // Maximum constraint.
)
{
  double loc_output;                                                                                // Output value.

  if((loc_min <= loc_input) &&
     (loc_input <= loc_max))
  {
    loc_output = loc_input;                                                                         // Setting output...
  }

  if(loc_input < loc_min)
  {
    loc_output = loc_min;                                                                           // Constraining output towards minimum...
  }

  if(loc_max < loc_input)
  {
    loc_output = loc_max;                                                                           // Constraining output towards maximum...
  }

  return loc_output;                                                                                // Returning output...
}

float neutrino::constrain_float
(
 float loc_input,                                                                                   // Input number to be constrained.
 float loc_min,                                                                                     // Minimum constraint.
 float loc_max                                                                                      // Maximum constraint.
)
{
  float loc_output;                                                                                 // Output value.

  if((loc_min <= loc_input) &&
     (loc_input <= loc_max))
  {
    loc_output = loc_input;                                                                         // Setting output...
  }

  if(loc_input < loc_min)
  {
    loc_output = loc_min;                                                                           // Constraining output towards minimum...
  }

  if(loc_max < loc_input)
  {
    loc_output = loc_max;                                                                           // Constraining output towards maximum...
  }

  return loc_output;                                                                                // Returning output...
}

std::string neutrino::get_error
(
 cl_int loc_error                                                                                   // Local error code.
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

void neutrino::check_error
(
 cl_int loc_error                                                                                   // Error code.
)
{
  if(loc_error != CL_SUCCESS)                                                                       // Checking local error code...
  {
    error (get_error (loc_error));                                                                  // Printing error message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }
}

neutrino::~neutrino()
{
  delete[]  kernel_id;                                                                              // Deleting kernel ID array...
}
