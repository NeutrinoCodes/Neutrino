#include "link.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONSTRUCTOR: /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
link::link()
{

}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "INIT" FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Link init function
/// ### Description:
/// Initializes link object.
void link::init (
                 neutrino* loc_baseline,                                        // Neutrino baseline.
                 int1      loc_link_size                                        // Data array size.
                )
{
  cl_int loc_error;                                                             // Error code.

  int1   node_index;                                                            // Node index.
  int1   neighbour_index;                                                       // Neighbour index.
  int1   neighbour_id;                                                          // Neighbour id.

  baseline        = loc_baseline;                                               // Getting Neutrino baseline...

  baseline->action ("initializing \"link\" object...");                         // Printing message...

  link_size.value = loc_link_size.value;                                        // Array size.

  link_buffer     = NULL;                                                       // OpenCL data buffer.
  opencl_context  = baseline->context_id;                                       // Getting OpenCL context...
  link_data       = new link_structure[link_size.value];                        // Link data array.

  // Filling data arrays with default values:
  for(
      node_index.value = 0;
      node_index.value < link_size.value;
      (node_index.value)++
     )
  {
    for(
        neighbour_id.value = 0;
        neighbour_id.value < NEIGHBOURS_NUM;
        (neighbour_id.value)++
       )
    {
      init_int1 (
                 link_data[node_index.value].index[neighbour_id.value]
                );                                                              // Initializing neighbour index...
      init_color4 (
                   link_data[node_index.value].color[neighbour_id.value]
                  );                                                            // Initializing neighbour color...
      init_float1 (
                   link_data[node_index.value].stiffness[neighbour_id.value]
                  );                                                            // Initializing link stiffness...
      init_float1 (
                   link_data[node_index.value].damping[neighbour_id.value]
                  );                                                            // Initializing link damping...
    }
  }

  #ifdef USE_GRAPHICS
    link_vao = 0;                                                               // Node data VAO.
    link_vbo = 0;                                                               // Node data VBO.

    // Generating VAO...
    glGenVertexArrays (
                       1,                                                       // # of VAOs to generate.
                       &link_vao                                                // VAOs array.
                      );
    glBindVertexArray (link_vao);                                               // Binding node VAO...

    // Generating VBO:
    glGenBuffers (
                  1,                                                            // # of VBOs to generate.
                  &link_vbo                                                     // VBOs array.
                 );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  link_vbo                                                      // VBO to bind.
                 );

    // Creating and initializing a buffer object's data store:
    glBufferData (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  sizeof(link_data)*(link_size.value),                          // VBO size.
                  link_data,                                                    // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               LAYOUT_LINK;                                     // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  link_vbo                                                      // VBO to bind.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           LAYOUT_LINK,                                         // VAO index.
                           sizeof(link_data),                                   // VAO's # of components.
                           GL_FLOAT,                                            // Data type.
                           GL_FALSE,                                            // Not using normalized numbers.
                           0,                                                   // Data stride.
                           0                                                    // Data offset.
                          );

    // Creating OpenCL buffer from OpenGL buffer:
    link_buffer = clCreateFromGLBuffer (
                                        opencl_context,                         // OpenCL context.
                                        CL_MEM_READ_WRITE,                      // Memory flags.
                                        link_vbo,                               // VBO.
                                        &loc_error                              // Returned error.
                                       );
  #else
    // Creating OpenCL memory buffer:
    link_buffer = clCreateBuffer (
                                  opencl_context,                               // OpenCL context.
                                  CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,     // Memory flags.
                                  sizeof(link_data)*link_size.value,            // Data buffer size.
                                  link_data,                                    // Data buffer.
                                  &loc_error                                    // Error code.
                                 );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "SET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Link neighbour index set function
/// ### Description:
/// Sets the neighbour indexes in link structure.
void link::set_neighbour_index (
                                int1 loc_node_index,                            // Node index.
                                int1 loc_neighbour_index,                       // Neighbour index.
                                int1 loc_neighbour_id[NEIGHBOURS_NUM]           // Neighbour id.
                               )
{
  link_data[loc_node_index.value].index[loc_neighbour_id.value] =
    loc_neighbour_index.value;                                                  // Setting neighbour index...
};

/// # Link stiffness set function
/// ### Description:
/// Sets the stiffness in link structure.
void link::set_stiffness (
                          int1   loc_node_index,                                // Node index.
                          float1 loc_value,                                     // Data value.
                          int1   loc_neighbour_id[NEIGHBOURS_NUM]               // Neighbour id.
                         )
{
  link_data[loc_node_index.value].stiffness[loc_neighbour_id.value] =
    loc_value.value;                                                            // Setting link stiffness...
};

/// # Link damping set function
/// ### Description:
/// Sets the damping in link structure.
void link::set_damping (
                        int1   loc_node_index,                                  // Node index.
                        float1 loc_value,                                       // Data value.
                        int1   loc_neighbour_id[NEIGHBOURS_NUM]                 // Neighbour id.
                       )
{
  link_data[loc_node_index.value].damping[loc_neighbour_id.value] =
    loc_value.value;                                                            // Setting link internal damping...
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "GET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Link neighbour index get function
/// ### Description:
/// Gets the neighbour indexes from link structure.
int1 link::get_neighbour_index (
                                int1 loc_node_index,                            // Data index.
                                int1 loc_neighbour_id                           // Neighbour id.
                               )
{
  int1 data;

  data.value =
    link_data[loc_node_index.value].index[loc_neighbour_id.value];              // Getting neighbour index...

  return data;
};

/// # Link stiffness get function
/// ### Description:
/// Gets the stiffness from link structure.
float1 link::get_stiffness (
                            int1 loc_node_index,                                // Data index.
                            int1 loc_neighbour_id                               // Neighbour id.
                           )
{
  float1 data;

  data.value =
    link_data[loc_node_index.value].stiffness[loc_neighbour_id.value];          // Getting link stiffness...

  return data;
};

/// # Link damping get function
/// ### Description:
/// Gets the damping from link structure.
float1 link::get_damping (
                          int1 loc_index,                                       // Data index.
                          int1 loc_neighbour_id                                 // Neighbour id.
                         )
{
  float1 data;

  data.value =
    link_data[loc_node_index.value].damping[loc_neighbour_id.value];            // Getting link internal damping...

  return data;
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// ERROR FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void link::check_error (
                        cl_int loc_error                                        // Error code.
                       )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline->error (get_error (loc_error));                                    // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR: /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
link::~link()
{
  cl_int loc_error;                                                             // Local error.

  baseline->action ("releasing \"link\" object...");                            // Printing message...

  if(link_buffer != NULL)                                                       // Checking buffer...
  {
    loc_error = clReleaseMemObject (link_buffer);                               // Releasing OpenCL buffer object...

    check_error (loc_error);                                                    // Checking returned error code...
  }

  #ifdef USE_GRAPHICS
    {
      glDeleteBuffers (1, &link_vbo);                                           // Releasing OpenGL VBO...
    }
  #endif

  delete[] link_data;                                                           // Deleting array for unfolded data...

  baseline->done ();                                                            // Printing message...
}
