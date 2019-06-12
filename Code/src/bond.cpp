#include "link.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONSTRUCTOR: /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
bond::bond()
{
// Doing nothing because we need a deferred init after OpenGL and OpenCL initialization.
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "INIT" FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Bond init function
/// ### Description:
/// Initializes bond object.
void bond::init (
                 neutrino* loc_baseline,                                        // Neutrino baseline.
                 int1      loc_link_size                                        // Data array size.
                )
{
  cl_int loc_error;                                                             // Error code.

  int1   node_index;                                                            // Node index.
  int1   neighbour_index;                                                       // Neighbour index.
  int1   neighbour_id;                                                          // Neighbour id.

  baseline        = loc_baseline;                                               // Getting Neutrino baseline...

  baseline->action ("initializing \"bond\" object...");                         // Printing message...

  bond_size.value = loc_bond_size.value;                                        // Array size.

  bond_buffer     = NULL;                                                       // OpenCL data buffer.
  opencl_context  = baseline->context_id;                                       // Getting OpenCL context...
  bond_data       = new link_structure[bond_size.value];                        // Bond data array.

  // Filling data arrays with default values:
  for(
      node_index.value = 0;
      node_index.value < bond_size.value;
      (node_index.value)++
     )
  {
    for(
        neighbour_id.value = 0;
        neighbour_id.value < NEIGHBOURS;
        (neighbour_id.value)++
       )
    {
      init_int1 (
                 bond_data[node_index.value].index[neighbour_id.value]
                );                                                              // Initializing neighbour index...
      init_color4 (
                   bond_data[node_index.value].color[neighbour_id.value]
                  );                                                            // Initializing neighbour color...
      init_float1 (
                   bond_data[node_index.value].stiffness[neighbour_id.value]
                  );                                                            // Initializing link stiffness...
      init_float1 (
                   bond_data[node_index.value].damping[neighbour_id.value]
                  );                                                            // Initializing link damping...
    }
  }

  #ifdef USE_GRAPHICS
    // Generating VAO...
    glGenVertexArrays (
                       1,                                                       // # of VAOs to generate.
                       &bond_vao                                                // VAOs array.
                      );
    glBindVertexArray (bond_vao);                                               // Binding node VAO...

    // Generating VBO:
    glGenBuffers (
                  1,                                                            // # of VBOs to generate.
                  &bond_vbo                                                     // VBOs array.
                 );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  bond_vbo                                                      // VBO to bind.
                 );

    // Creating and initializing a buffer object's data store:
    glBufferData (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  sizeof(bond_data)*(bond_size.value),                          // VBO size.
                  bond_data,                                                    // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           LAYOUT_LINK,                                         // VAO index.
                           sizeof(bond_data),                                   // VAO's # of components.
                           GL_FLOAT,                                            // Data type.
                           GL_FALSE,                                            // Not using normalized numbers.
                           0,                                                   // Data stride.
                           0                                                    // Data offset.
                          );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               LAYOUT_LINK;                                     // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  bond_vbo                                                      // VBO to bind.
                 );

    // Creating OpenCL buffer from OpenGL buffer:
    bond_buffer = clCreateFromGLBuffer (
                                        opencl_context,                         // OpenCL context.
                                        CL_MEM_READ_WRITE,                      // Memory flags.
                                        bond_vbo,                               // VBO.
                                        &loc_error                              // Returned error.
                                       );
  #else
    // Creating OpenCL memory buffer:
    bond_buffer = clCreateBuffer (
                                  opencl_context,                               // OpenCL context.
                                  CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,     // Memory flags.
                                  sizeof(bond_data)*bond_size.value,            // Data buffer size.
                                  bond_data,                                    // Data buffer.
                                  &loc_error                                    // Error code.
                                 );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "SET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Bond index set function
/// ### Description:
/// Sets the bond indexes in bond structure.
void bond::set_neighbour_index (
                                int1 loc_node_index,                            // Node index.
                                int1 loc_bond_index[NEIGHBOURS]                 // Bond index value.
                               )
{
  size_t i;

  for(i = 0; i < NEIGHBOURS; i++)
  {
    bond_data[loc_node_index.value].index[i] = loc_bond_index[i].value;         // Setting bond index...
  }
};

/// # BOnd stiffness set function
/// ### Description:
/// Sets the stiffness in bond structure.
void bond::set_stiffness (
                          int1   loc_node_index,                                // Node index.
                          float1 loc_bond_stiffness[NEIGHBOURS]                 // Bond stiffness value.
                         )
{
  size_t i;

  for(i = 0; i < NEIGHBOURS; i++)
  {
    bond_data[loc_node_index.value].stiffness[i] =
      loc_bond_stiffness[i].value;                                              // Setting bond stiffness...
  }
};

/// # Link damping set function
/// ### Description:
/// Sets the damping in link structure.
void bond::set_damping (
                        int1   loc_node_index,                                  // Node index.
                        float1 loc_bond_damping[NEIGHBOURS]                     // Bond stiffness value.
                       )
{
  size_t i;

  for(i = 0; i < NEIGHBOURS; i++)
  {
    bond_data[loc_node_index.value].stiffness[i] =
      loc_bond_damping[i].value;                                                // Setting bond damping...
  }
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "GET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Link neighbour index get function
/// ### Description:
/// Gets the neighbour indexes from link structure.
int1 bond::get_neighbour_index (
                                int1 loc_node_index,                            // Data index.
                                int1 loc_neighbour_id                           // Neighbour id.
                               )
{
  int1 data;

  data.value =
    bond_data[loc_node_index.value].index[loc_neighbour_id.value];              // Getting neighbour index...

  return data;
};

/// # Link stiffness get function
/// ### Description:
/// Gets the stiffness from link structure.
float1 bond::get_stiffness (
                            int1 loc_node_index,                                // Data index.
                            int1 loc_neighbour_id                               // Neighbour id.
                           )
{
  float1 data;

  data.value =
    bond_data[loc_node_index.value].stiffness[loc_neighbour_id.value];          // Getting link stiffness...

  return data;
};

/// # Link damping get function
/// ### Description:
/// Gets the damping from link structure.
float1 bond::get_damping (
                          int1 loc_index,                                       // Data index.
                          int1 loc_neighbour_id                                 // Neighbour id.
                         )
{
  float1 data;

  data.value =
    bond_data[loc_node_index.value].damping[loc_neighbour_id.value];            // Getting link internal damping...

  return data;
};

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// "CONTROL" FUNCTIONS: /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL push function:
/// ### Description:
/// Writes to an OpenCL client.
void bond::push (
                 kernel* loc_kernel,                                            // Kernel.
                 queue*  loc_queue                                              // Queue.
                )
{
  cl_int loc_error;                                                             // Local error code.

  baseline->action ("setting \"bond\" kernel argument...");                     // Printing message...

  // Setting OpenCL buffer as kernel argument:
  loc_error = clSetKernelArg (
                              loc_kernel->kernel_id,                            // Kernel.
                              LAYOUT_NODE,                                      // Kernel argument index.
                              sizeof(cl_mem),                                   // Kernel argument size.
                              &bond_buffer                                      // Kernel argument value.
                             );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline->done ();                                                            // Printing message...

  #ifdef USE_GRAPHICS
    baseline->action ("acquiring \"bond\" OpenCL buffer...");                   // Printing message...

    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Acquiring OpenCL buffer:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &bond_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...

    baseline->done ();                                                          // Printing message...
  #endif

  baseline->action ("writing \"bond\" OpenCL buffer...");                       // Printing message...

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    loc_queue->queue_id,                        // OpenCL queue ID.
                                    bond_buffer,                                // Data buffer.
                                    CL_TRUE,                                    // Blocking write flag.
                                    0,                                          // Data buffer offset.
                                    sizeof(bond_data)*bond_size.value,          // Data buffer size.
                                    bond_data,                                  // Data buffer.
                                    0,                                          // Number of events in the list.
                                    NULL,                                       // Event list.
                                    NULL                                        // Event.
                                   );

  check_error (loc_error);

  baseline->done ();                                                            // Printing message...

  #ifdef USE_GRAPHICS
    baseline->action ("releasing \"link\" OpenCL buffer...");                   // Printing message...

    // Releasing openCL buffer:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &bond_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue->queue_id);                                             // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...

    baseline->done ();                                                          // Printing message...
  #endif
}

/// # OpenCL pull function:
/// ### Description:
/// Reads from an OpenCL client.
void bond::pull (
                 queue* loc_queue                                               // Queue.
                )
{
  cl_int loc_error;                                                             // Local error code.

  loc_error = clEnqueueReadBuffer (
                                   loc_queue->queue_id,                         // OpenCL queue ID.
                                   bond_buffer,                                 // Data buffer.
                                   CL_TRUE,                                     // Blocking write flag.
                                   0,                                           // Data buffer offset.
                                   sizeof(bond_data)*bond_size.value,           // Data buffer size.
                                   bond_data,                                   // Data buffer.
                                   0,                                           // Number of events in the list.
                                   NULL,                                        // Event list.
                                   NULL                                         // Event.
                                  );

  check_error (loc_error);
}

/// # OpenCL acquire function:
/// ### Description:
/// Acquires an OpenCL buffer.
void bond::acquire (
                    queue* loc_queue                                            // Queue.
                   )
{
  #ifdef USE_GRAPHICS
    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Acquiring OpenCL buffer:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &bond_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...
  #endif
}

/// # OpenCL release function:
/// ### Description:
/// Releases an OpenCL buffer.
void bond::release (
                    queue* loc_queue                                            // Queue.
                   )
{
  #ifdef USE_GRAPHICS
    // Releasing openCL buffer:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &bond_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue->queue_id);                                             // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...
  #endif
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// ERROR FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void bond::check_error (
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
bond::~bond()
{
  cl_int loc_error;                                                             // Local error.

  baseline->action ("releasing \"bond\" object...");                            // Printing message...

  if(bond_buffer != NULL)                                                       // Checking buffer...
  {
    loc_error = clReleaseMemObject (bond_buffer);                               // Releasing OpenCL buffer object...

    check_error (loc_error);                                                    // Checking returned error code...
  }

  #ifdef USE_GRAPHICS
    {
      glDeleteBuffers (1, &bond_vbo);                                           // Releasing OpenGL VBO...
    }
  #endif

  delete[] bond_data;                                                           // Deleting array for unfolded data...

  baseline->done ();                                                            // Printing message...
}
