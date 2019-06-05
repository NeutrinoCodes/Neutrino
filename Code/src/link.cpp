#include "link.hpp"

link::link()
{

}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void link::check_error (
                        cl_int loc_error                                        // Error code.
                       )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline -> error (get_error (loc_error));                                  // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

void link::init (
                 neutrino*  loc_baseline,                                       // Neutrino baseline.
                 GLsizeiptr loc_data_size                                       // Data array size.
                )
{
  cl_int       loc_error;                                                       // Error code.

  #ifdef USE_GRAPHICS
    GLsizeiptr i;                                                               // Index.
  #else
    size_t     i;                                                               // Index.
  #endif

  baseline       = loc_baseline;                                                // Getting Neutrino baseline...
  position       = new size_t[baseline -> k_num];                               // Initializing kernel argument position array...

  baseline -> action ("initializing \"point4\" object...");                     // Printing message...

  data_size      = loc_data_size;                                               // Array size.
  buffer         = NULL;                                                        // OpenCL data buffer.
  opencl_context = baseline -> context_id;                                      // Getting OpenCL context...
  link_data      = new link[data_size];                                         // Link data array.

  for(i = 0; i < data_size; i++)                                                // Filling data arrays with default values...
  {
    // Initializing neighbour indexes:
    link_data . up_index    = i;                                                // Initializing "up" neighbour index...
    link_data . down_index  = i;                                                // Initializing "down" neighbour index...
    link_data . left_index  = i;                                                // Initializing "left" neighbour index...
    link_data . right_index = i;                                                // Initializing "right" neighbour index...

    // Initializing neighbour colors:
    init_color4 (link_data . up_color);                                         // Initializing "up" neighbour color...
    init_color4 (link_data . down_color);                                       // Initializing "down" neighbour color...
    init_color4 (link_data . left_color);                                       // Initializing "left" neighbour color...
    init_color4 (link_data . right_color);                                      // Initializing "right" neighbour color...

    // Initializing link properties:
    link_data . stiffness   = 0.0;                                              // Initializing link stiffness...
    link_data . damping     = 0.0;                                              // Initializing link damping...
  }

  #ifdef USE_GRAPHICS
    link_vao = 0;                                                               // Link data VAO.
    link_vbo = 0;                                                               // Link data VBO.

    // Creating OpenCL buffer from OpenGL buffer for LINK structure:
    cl_create_from_gl_buffer<link> (
                                    link,
                                    link,
                                    LINK,
                                    link,
                                    data_size,
                                    opencl_context,
                                    link_buffer
                                   );

  #else
    // Creating OpenCL buffer for LINK structure:
    cl_create_buffer<link> (
                            link_data,
                            data_size,
                            opencl_context,
                            link_buffer
                           );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}
