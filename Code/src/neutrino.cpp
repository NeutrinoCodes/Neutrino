/// @file

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "NEUTRINO" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
neutrino::neutrino()
{
  interop     = false;                                                          // Use OpenCL-OpenGL interop.
  tic         = 0.0;                                                            // Tic time [ms].
  toc         = 0.0;                                                            // Toc time [ms].
  loop_time   = 0.0;                                                            // Loop time [ms].

  context_id  = NULL;                                                           // OpenCL context ID.
  platform_id = NULL;                                                           // OpenCL platform ID.
  device_id   = NULL;                                                           // OpenCL device ID.
}

/// # Initialization function
/// ### Description:
/// Initialises the neutrino object.
void neutrino::init (
                     size_t loc_q_num,
                     size_t loc_k_num,
                     bool   loc_interop
                    )
{
  // Initializing neutrino object:
  action ("initializing NEUTRINO...");                                          // Printing message...

  q_num         = loc_q_num;                                                    // Getting # of OpenCL queues...
  k_num         = loc_k_num;                                                    // Getting # of OpenCL kernels...
  interop       = loc_interop;                                                  // Getting OpenCL/GL interoperability flag...
  kernel_id     = new cl_kernel[k_num];                                         // Initializing OpenCL kernel ID array...
  terminal_time = 0;
  size_t i;                                                                     // Index.

  for(i = 0; i < k_num; i++)                                                    // Scanning OpenCL kernel argument array...
  {
    kernel_id[i] = NULL;                                                        // Resetting kernel ID array...
  }

  done ();                                                                      // Printing message...
}

/// # Neutrino get "tic" function
/// ### Description:
/// Gets the host NU_CPU time "tic" [us].
void neutrino::get_tic ()
{
  tic = glfwGetTime ();
}

/// # Neutrino get "toc" function
/// ### Description:
/// Gets the host NU_CPU time "toc" [us]. Prints the "toc - tic" time difference
/// to the stdout.
void neutrino::get_toc ()
{
  size_t i;                                                                     // Index.
  string text;                                                                  // Text buffer.
  string pad;                                                                   // Text pad.
  size_t pad_size;                                                              // Text pad size.

  toc            = glfwGetTime ();
  loop_time      = size_t (round (1000000.0*double(toc - tic)));                // Loop execution time [us].
  terminal_time += loop_time;

  if(terminal_time > NU_TERMINAL_REFRESH)                                       // Checking terminal time...
  {
    terminal_time = 0;                                                          // Resetting terminal time.
    erase ();

    // Compiling message string:
    text          = NU_COLOR_CYAN +
                    "Action: " +
                    NU_COLOR_NORMAL +
                    "running host loop time = " +
                    to_string (loop_time) +
                    " us";

    pad_size      = NU_MAX_MESSAGE_SIZE - text.length;                          // Computing text padding...

    if(pad_size >= 0)                                                           // Checking padding...
    {
      for(i = 0; i < pad_size; i++)                                             // Compiling padding...
      {
        pad += " ";
      }
    }

    else                                                                        // Generating error message...
    {
      error ("string too big!");                                                // Printing message...
      exit (1);                                                                 // Exiting...
    }

    cout << text + pad << endl;                                                 // Printing buffer...
  }
}

/// # Neutrino load file function
/// ### Description:
/// Loads a file into a buffer.
void neutrino::load_file (
                          const char* file_name,
                          char**      file_buffer,
                          size_t*     file_size
                         )
{
  FILE* handle;

  handle                     = fopen (file_name, "rb");

  if(handle == NULL)
  {
    error ("could not find the file!");                                         // Printing message...
    exit (1);
  }

  fseek (handle, 0, SEEK_END);
  *file_size                 = (size_t)ftell (handle);
  rewind (handle);
  *file_buffer               = (char*)malloc (*file_size + 1);

  if(!*file_buffer)
  {
    error ("unable to allocate buffer memory!");                                // Printing message...
    exit (EXIT_FAILURE);
  }

  fread (*file_buffer, sizeof(char), *file_size, handle);
  fclose (handle);
  file_buffer[0][*file_size] = '\0';
}

/// # Neutrino write file function
/// ### Description:
/// Writes a buffer in a file.
void neutrino::write_file (
                           const char* file_name,
                           char*       file_buffer
                          )
{
  FILE* handle;

  printf ("Action: writing file \"%s\"...", file_name);

  handle = fopen (file_name, "a");

  if(handle == NULL)
  {
    printf ("\nError:  could not write the file!\n");
    exit (1);
  }

  fputs (file_buffer, handle);
  fclose (handle);

  printf (" DONE!\n");
}

/// # Neutrino free file buffer function
/// ### Description:
/// Frees the buffer associated to a file.
void neutrino::free_file (
                          char* buffer
                         )
{
  free (buffer);                                                                ///< Freeing buffer...
}

/// # Neutrino query numeric input function
/// ### Description:
/// Asks the user for a numeric input choice.
int neutrino::query_numeric (
                             const char* caption,
                             int         min,
                             int         max
                            )
{
  char buffer[NU_MAX_TEXT_SIZE];                                                // Input buffer.
  int  numeric;                                                                 // Numeric value.
  bool valid_choice = false;                                                    // User's choice.

  printf ("%s", caption);                                                       // Printing caption...

  while(!valid_choice)                                                          // Checking choice validity...
  {
    fgets (buffer, NU_MAX_TEXT_SIZE, stdin);                                    // Reading string from stdin...
    numeric = strtol (buffer, NULL, 10);                                        // Parsing stdin...

    if((min <= numeric) && (numeric <= max) && (errno != ERANGE))
    {
      valid_choice = true;                                                      // Setting flag...
    }

    else
    {
      error ("invalid input! Please, try again!");                              // Printing message...
      printf ("%s", caption);                                                   // Printing question...

      errno = 0;
    }
  }

  return(numeric);                                                              // Returning numeric choice...
}

/// # Neutrino erase stdout current line function
/// ### Description:
/// Erases the stdout current line.
void neutrino::erase ()
{
  printf ("\33[2K\r");                                                          // Erasing terminal stdout current line....
}

/// # Neutrino format and print "action" message function
/// ### Description:
/// Formats and prints "action" messages to stdout.
void neutrino::action (
                       const char* loc_text                                     // Message text.
                      )
{
  char   buffer[NU_MAX_TEXT_SIZE];                                              // Text buffer.
  size_t padding;                                                               // Text padding.
  size_t i;                                                                     // Index.

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            NU_MAX_TEXT_SIZE,                                                   // Size of destination string.
            "%sAction:%s %s",                                                   // Compiled string.
            NU_COLOR_CYAN,                                                      // Red color.
            NU_COLOR_NORMAL,                                                    // Normal color.
            loc_text                                                            // Source string.
           );

  printf ("%s", buffer);                                                        // Printing buffer...
  padding = NU_MAX_MESSAGE_SIZE - strlen (loc_text);                            // Computing text padding...

  if(padding >= 0)                                                              // Checking padding...
  {
    for(i = 0; i < padding; i++)                                                // Compiling padding...
    {
      printf (" ");                                                             // Printing padding...
    }

    fflush (stdout);                                                            // Flushing stdout...
  }

  else                                                                          // Generating error message...
  {
    error ("string too big!");                                                  // Printing message...
    exit (1);                                                                   // Exiting...
  }
}

/// # Neutrino format and print "error" message function
/// ### Description:
/// Formats and prints "error" messages to stdout.
void neutrino::error (
                      const char* loc_text
                     )
{
  char   buffer[NU_MAX_TEXT_SIZE];                                              // Text buffer.
  size_t padding;                                                               // Text padding.
  size_t i;                                                                     // Index.
  char   error_of_error[NU_MAX_TEXT_SIZE];                                      // Error message.

  padding = NU_MAX_MESSAGE_SIZE - strlen (loc_text);                            // Computing text padding...

  printf ("\n");                                                                // Printing new line...

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            NU_MAX_TEXT_SIZE,                                                   // Size of destination string.
            "%sError:%s  %s",                                                   // Compiled string.
            NU_COLOR_RED,                                                       // Red color.
            NU_COLOR_NORMAL,                                                    // Normal color.
            loc_text                                                            // Source string.
           );

  printf ("%s", buffer);                                                        // Printing buffer...

  if(padding >= 0)                                                              // Checking padding...
  {
    for(i = 0; i < padding; i++)                                                // Compiling padding...
    {
      printf (" ");                                                             // Printing padding...
      fflush (stdout);                                                          // Flushing stdout...
    }
  }

  else                                                                          // Generating error message...
  {
    // Compiling message string:
    snprintf (
              buffer,                                                           // Destination string.
              NU_MAX_TEXT_SIZE,                                                 // Size of destination string.
              "%sError:%s  %s",                                                 // Compiled string.
              NU_COLOR_RED,                                                     // Red color.
              NU_COLOR_NORMAL,                                                  // Normal color.
              "string too big!"                                                 // Source string.
             );

    padding = NU_MAX_MESSAGE_SIZE - strlen ("string too big!");                 // Computing text padding...

    if(padding >= 0)                                                            // Checking padding...
    {
      for(i = 0; i < padding; i++)                                              // Compiling padding...
      {
        printf (" ");                                                           // Printing padding...
        fflush (stdout);                                                        // Flushing stdout...
      }
    }
  }

  terminated ();

  exit (1);                                                                     // Exiting...
}

/// # Neutrino list message function
/// ### Description:
/// Justifies and prints messages to stdout.
void neutrino::list (
                     char*  loc_text,
                     size_t loc_length,
                     char   loc_delimiter,
                     size_t loc_tab
                    )
{
  char*  buffer = new char[loc_length];
  size_t i;
  size_t j;

  for(i = 0; i < loc_length; i++)
  {
    if(loc_text[i] == loc_delimiter)
    {
      printf ("\n");

      for(j = 0; j < loc_tab; j++)
      {
        printf (" ");
      }
    }

    else
    {
      printf ("%c", loc_text[i]);
    }
  }

  printf ("\n");
}

/// # Neutrino format and print "done" message function
/// ### Description:
/// Formats and prints "done" messages to stdout.
void neutrino::done ()
{
  char buffer[NU_MAX_TEXT_SIZE];                                                // Text buffer.

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            NU_MAX_TEXT_SIZE,                                                   // Size of destination string.
            "%sDONE!%s",                                                        // Compiled string.
            NU_COLOR_GREEN,                                                     // Green color.
            NU_COLOR_NORMAL                                                     // Normal color.
           );

  printf ("%s\n", buffer);                                                      // Printing buffer...
}

void neutrino::terminated ()
{
  char buffer[NU_MAX_TEXT_SIZE];                                                // Text buffer.

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            NU_MAX_TEXT_SIZE,                                                   // Size of destination string.
            "%sTERMINATED!%s",                                                  // Compiled string.
            NU_COLOR_RED,                                                       // Green color.
            NU_COLOR_NORMAL                                                     // Normal color.
           );

  printf ("%s\n", buffer);                                                      // Printing buffer...
}

/// # OpenCL error get function
/// ### Description:
/// Translates an OpenCL numeric error code into a human-readable string.
const char* neutrino::get_error (
                                 cl_int loc_error                               // Local error code.
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
void neutrino::check_error (
                            cl_int loc_error                                    // Error code.
                           )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    error (get_error (loc_error));                                              // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

neutrino::~neutrino()
{
  delete[]  kernel_id;
}
