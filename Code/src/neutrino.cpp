/// @file

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "NEUTRINO" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
neutrino::neutrino()
{
  neutrino_path     = NULL;                                                     // NEUTRINO_PATH environmental variable.
  neutrino_font     = NULL;                                                     // Neutrino font.
  use_cl_gl_interop = true;                                                     // Use OpenCL-OpenGL interop.
  tic               = 0.0;                                                      // Tic time [ms].
  toc               = 0.0;                                                      // Toc time [ms].
  loop_time         = 0.0;                                                      // Loop time [ms].

  context_id        = NULL;                                                     // OpenCL context ID.
  platform_id       = NULL;                                                     // OpenCL platform ID.
  device_id         = NULL;                                                     // OpenCL device ID.
}

/// # OpenCL error get function
/// ### Description:
/// Gets the NEUTRINO_PATH environmental variable.
path* neutrino::get_neutrino_path ()
{
  temp_neutrino_path          = new path;

  temp_neutrino_path -> value = getenv ("NEUTRINO_PATH");                       // Getting neutrino path...
  temp_neutrino_path -> size  = strlen (temp_neutrino_path -> value) + 1;       // Getting neutrino path length...

  if(temp_neutrino_path -> value == NULL)
  {
    printf ("Error:  NEUTRINO_PATH environmental variable not defined!\n");
    exit (1);

  }

  return(temp_neutrino_path);
}

/// # OpenCL error get function
/// ### Description:
/// Gets the neutrino font.
font* neutrino::get_neutrino_font ()
{
  temp_neutrino_font = new font;

  return(temp_neutrino_font);
}

/// # CPU get time function
/// ### Description:
/// Gets the host CPU time [us].
double neutrino::get_cpu_time ()
{
  double time;

  time = glfwGetTime ();
  return time;
}

/// # Initialization function
/// ### Description:
/// Initialises the neutrino object.
void neutrino::init (
                     size_t loc_q_num,
                     size_t loc_k_num,
                     bool   loc_use_cl_gl_interop
                    )
{
  q_num             = loc_q_num;                                                // Getting # of OpenCL queues...
  k_num             = loc_k_num;                                                // Getting # of OpenCL kernels...
  kernel_id         = new cl_kernel[k_num];                                     // Initializing OpenCL kernel ID array...
  use_cl_gl_interop = loc_use_cl_gl_interop;                                    // Setting interop flag...
  terminal_time     = 0;
  prefix_buffer     = new char[MAX_PATH_SIZE];
  size_t i;                                                                     // Index.

  // Initializing neutrino object:
  action ("initializing neutrino object...");                                   // Printing message...

  for(i = 0; i < k_num; i++)                                                    // Scanning OpenCL kernel argument array...
  {
    kernel_id[i] = NULL;                                                        // Resetting kernel ID array...
  }

  done ();                                                                      // Printing message...

  // Initializing NEUTRINO_PATH:
  action ("initializing neutrino path...");                                     // Printing message...

  neutrino_path = get_neutrino_path ();
  done ();                                                                      // Printing message...

  // Initializing font:
  action ("initializing neutrino font...");                                     // Printing message...

  neutrino_font = get_neutrino_font ();                                         // Font object.
  done ();                                                                      // Printing message...
}

/// # Neutrino path prefix function
/// ### Description:
/// Adds the NEUTRINO_PATH before a file name.
char* neutrino::prefix (
                        const char* loc_path
                       )
{
  // Compiling message string:
  snprintf (
            prefix_buffer,                                                      // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s/%s",                                                            // Compiled string.
            get_neutrino_path () -> value,                                      // Neutrino path prefix.
            loc_path                                                            // Path.
           );

  return(prefix_buffer);
}

/// # Neutrino get "tic" function
/// ### Description:
/// Gets the host CPU time "tic" [us].
void neutrino::get_tic ()
{
  tic = get_cpu_time ();
}

/// # Neutrino get "toc" function
/// ### Description:
/// Gets the host CPU time "toc" [us]. Prints the "toc - tic" time difference
/// to the stdout.
void neutrino::get_toc ()
{
  size_t padding;                                                               // Text padding.
  size_t i;                                                                     // Index.
  char   buffer[MAX_TEXT_SIZE];                                                 // Text buffer.
  char   text[MAX_TEXT_SIZE];                                                   // Text buffer.

  toc            = get_cpu_time ();
  loop_time      = size_t (round (1000000.0*double(toc - tic)));                // Loop execution time [us].
  terminal_time += loop_time;

  if(terminal_time > 20000)
  {
    terminal_time = 0;                                                          // Resetting terminal time.
    erase ();

    // Compiling message string:
    snprintf (
              buffer,                                                           // Destination string.
              MAX_TEXT_SIZE,                                                    // Size of destination string.
              "%sAction:%s %s%zu us",                                           // Compiled string.
              COLOR_CYAN,                                                       // Red color.
              COLOR_NORMAL,                                                     // Normal color.
              "running host: loop time = ",                                     // Source string.
              loop_time                                                         // Host loop time [us].
             );

    printf ("%s", buffer);                                                      // Printing buffer...

    padding = MAX_MESSAGE_SIZE - strlen (buffer);                               // Computing text padding...

    if(padding >= 0)                                                            // Checking padding...
    {
      for(i = 0; i < padding; i++)                                              // Compiling padding...
      {
        printf (" ");                                                           // Printing padding...
      }

      fflush (stdout);
    }

    else                                                                        // Generating error message...
    {
      printf ("Error: string too big!\n");                                      // Printing message...
      exit (1);                                                                 // Exiting...
    }
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
    printf ("\nError:  could not find the file!\n");
    exit (1);
  }

  fseek (handle, 0, SEEK_END);
  *file_size                 = (size_t)ftell (handle);
  rewind (handle);
  *file_buffer               = (char*)malloc (*file_size + 1);

  if(!*file_buffer)
  {
    printf ("\nError:  unable to allocate buffer memory!\n");
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
  char buffer[MAX_TEXT_SIZE];                                                   // Input buffer.
  int  numeric;                                                                 // Numeric value.
  bool valid_choice = false;                                                    // User's choice.

  printf ("%s", caption);                                                       // Printing caption...

  while(!valid_choice)                                                          // Checking choice validity...
  {
    fgets (buffer, MAX_TEXT_SIZE, stdin);                                       // Reading string from stdin...
    numeric = strtol (buffer, NULL, 10);                                        // Parsing stdin...

    if((min <= numeric) && (numeric <= max) && (errno != ERANGE))
    {
      valid_choice = true;                                                      // Setting flag...
    }

    else
    {
      printf ("\nError:  invalid input! Please, try again!\n");                 // Printing message...
      printf ("\n");                                                            // Printing message...
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
  char   buffer[MAX_TEXT_SIZE];                                                 // Text buffer.
  size_t padding;                                                               // Text padding.
  size_t i;                                                                     // Index.

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            MAX_TEXT_SIZE,                                                      // Size of destination string.
            "%sAction:%s %s",                                                   // Compiled string.
            COLOR_CYAN,                                                         // Red color.
            COLOR_NORMAL,                                                       // Normal color.
            loc_text                                                            // Source string.
           );

  printf ("%s", buffer);                                                        // Printing buffer...
  padding = MAX_MESSAGE_SIZE - strlen (buffer);                                 // Computing text padding...

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
    printf ("Error: string too big!\n");                                        // Printing message...
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
  char   buffer[MAX_TEXT_SIZE];                                                 // Text buffer.
  size_t padding;                                                               // Text padding.
  size_t i;                                                                     // Index.

  padding = MAX_MESSAGE_SIZE - strlen (loc_text);                               // Computing text padding...

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            MAX_TEXT_SIZE,                                                      // Size of destination string.
            "%sError:%s  %s",                                                   // Compiled string.
            COLOR_RED,                                                          // Red color.
            COLOR_NORMAL,                                                       // Normal color.
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
    printf ("Error: string too big!\n");                                        // Printing message...
    exit (1);                                                                   // Exiting...
  }

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            MAX_TEXT_SIZE,                                                      // Size of destination string.
            "%sTERMINATED!%s",                                                  // Compiled string.
            COLOR_RED,                                                          // Red color.
            COLOR_NORMAL                                                        // Normal color.
           );

  printf ("%s\n", buffer);                                                      // Printing buffer...
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
  char   buffer[loc_length];
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
  char buffer[MAX_TEXT_SIZE];                                                   // Text buffer.

  // Compiling message string:
  snprintf (
            buffer,                                                             // Destination string.
            MAX_TEXT_SIZE,                                                      // Size of destination string.
            "%sDONE!%s",                                                        // Compiled string.
            COLOR_GREEN,                                                        // Green color.
            COLOR_NORMAL                                                        // Normal color.
           );

  printf ("%s\n", buffer);                                                      // Printing buffer...
}

neutrino::~neutrino()
{
  delete    temp_neutrino_path;
  delete    temp_neutrino_font;
  delete[]  kernel_id;
  delete[]  prefix_buffer;
}
