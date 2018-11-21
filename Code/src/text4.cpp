#include "text4.hpp"

text4::text4()
{

}

// PRIVATE METHODS:
const char* text4::get_error(cl_int loc_error)
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

void text4::init  (
                    neutrino* loc_baseline,
                    const char* loc_text,
                    GLfloat loc_R,
                    GLfloat loc_G,
                    GLfloat loc_B,
                    GLfloat loc_A
                  )
{
  // Printing action message:
  loc_baseline->action  (
                          "initializing OpenGL text...",
                          MAX_MESSAGE_SIZE
                        );

  num_char = strlen(loc_text);                                                  // Total # of characters in input string.
  num_data = 0;                                                                 // Total # of font data in input string.
  num_points = 0;                                                               // Total # of font points in input string.
  num_strokes = 0;                                                              // Total # of font strokes in input string.

  char_code         = new int[num_char];                                        // Ascii code for each character in input string.
  char_item         = new int[num_char];                                        // Font character position for each character in input string.
  char_numdata      = new int[num_char];                                        // # of font data for each character in input string.
  char_numpoints    = new int[num_char];                                        // # of font points for each character in input string.
  char_numstrokes   = new int[num_char];                                        // # of font strokes for each character in input string.
  char_kern         = new int[num_char];                                        // Kern spacing for each character in input string.

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    char_code[i] = (int)loc_text[i];                                            // Getting single character ascii code...

    if ( (ASCII_33 <= char_code[i]) && (char_code[i] <= ASCII_126) )            // Selecting character range...
    {
      char_item[i] = char_code[i] - ASCII_33;                                   // Computing font character position for character in input string...
      char_numdata[i] = loc_baseline->neutrino_font->font_numdata[char_item[i]];// Computing # of data for character in input string...
      char_kern[i]  = ASCII_SPACE_LITTLE;                                       // Setting kern spacing for character in input string...
    }

    if (char_code[i] == 32)                                                     // Handling "SPACE" special case...
    {
      char_item[i] = 0;                                                         // Computing font character position for character in input string...
      char_numdata[i] = 0;                                                      // Setting # of data for character in input string... ("SPACE" has no data)
      char_kern[i] = ASCII_SPACE_LITTLE + ASCII_SPACE_BIG;                      // Setting kern spacing for character in input string...
    }

    char_numpoints[i] = char_numdata[i]/2;                                      // Computing # of font points for each character in input string...
    char_numstrokes[i] = char_numpoints[i]/2;                                   // Computing # of font strokes for each character in input string...
    num_data += char_numdata[i];                                                // Accumulating total # of font data in input string...
    num_points += char_numpoints[i];                                            // Accumulating total # of font points in input string...
    num_strokes += char_numstrokes[i];                                          // Accumulating total # of font strokes in input string...
  }

  data_index = new int[num_data];                                               // Index of font data for each character in input string.
  kern = new int[num_points];                                                   // Kern character spacing for each font point in input string.
  offset = new int[num_points];                                                 // Character offset for each font point in input string.

  x = new GLfloat[num_points];                                                  // "x" data array.
  y = new GLfloat[num_points];                                                  // "y" data array.
  z = new GLfloat[num_points];                                                  // "z" data array.
  w = new GLfloat[num_points];                                                  // "w" data array.

  r = new GLfloat[num_points];                                                  // "r" data array.
  g = new GLfloat[num_points];                                                  // "g" data array.
  b = new GLfloat[num_points];                                                  // "b" data array.
  a = new GLfloat[num_points];                                                  // "a" data array.

  size = num_points;                                                            // Text array size.

  glyph_vao = 0;                                                                // OpenGL glyph data VAO.
  color_vao = 0;                                                                // OpenGL color data VAO.
  glyph_vbo = 0;                                                                // OpenGL glyph data VBO.
  color_vbo = 0;                                                                // OpenGL color data VBO.

  k = 0;                                                                        // Resetting "k" index...

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numdata[i]; j++)                                       // Looping on all font data for each single character...
    {
      data_index[k + j] = loc_baseline->neutrino_font->font_index[char_item[i]] + j;                // Computing index of font data for character in input string...
    }

    k += char_numdata[i];                                                       // Accumulating # of data...
  }

  k = 0;                                                                        // Resetting "k" index...
  shift = 0;                                                                    // Resetting character shift...

  for (i = 0; i < num_char; i++)                                                // Looping on all characters in input string...
  {
    for (j = 0; j < char_numpoints[i]; j++)                                     // Looping on all font strokes for each single character...
    {
      kern[k + j] = char_kern[i];                                               // Computing kern for characters in input string...
      offset[k + j] = shift;                                                    // Computing offset for characters in input string...
    }

    k += char_numpoints[i];                                                     // Accumulating # of points...
    shift += loc_baseline->neutrino_font->font_width[char_item[i]];                                 // Accumulating character shift...
  }

  for (i = 0; i < num_points; i++)                                              // Unwrapping text data...
  {
    even = 2*i;                                                                 // Computing "even" index...
    odd  = 2*i + 1;                                                             // Computing "odd" index...

    // Setting "x" data:
    x[i] = ASCII_SCALE*                                                         // Applying scaling...
           (loc_baseline->neutrino_font->font_vertex[data_index[even]] -                            // Setting vertex data...
            loc_baseline->neutrino_font->font_vertex[data_index[0]] +                               // Subtracting base point...
            offset[i] +                                                         // Adding offset...
            kern[i]);                                                           // Adding kern...

    y[i] = loc_baseline->neutrino_font->font_vertex[data_index[odd]]*ASCII_SCALE;                   // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...

    r[i] = loc_R;                                                               // Setting "r" data...
    g[i] = loc_G;                                                               // Setting "g" data...
    b[i] = loc_B;                                                               // Setting "b" data...
    a[i] = loc_A;                                                               // Setting "a" data...
  }

  glyph_data = new GLfloat[4*size];
  color_data = new GLfloat[4*size];

  for (i = 0; i < size; i++)
  {
    glyph_data[4*i + 0] = x[i];
    glyph_data[4*i + 1] = y[i];
    glyph_data[4*i + 2] = z[i];
    glyph_data[4*i + 3] = w[i];

    color_data[4*i + 0] = r[i];
    color_data[4*i + 1] = g[i];
    color_data[4*i + 2] = b[i];
    color_data[4*i + 3] = a[i];
  }

  // TEXT GLYPHS:
  glGenVertexArrays(1, &glyph_vao);                                             // Generating glyph VAO...
  glBindVertexArray(glyph_vao);                                                 // Binding glyph VAO...
  glGenBuffers(1, &glyph_vbo);                                                  // Generating glyph VBO...

  glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);                                     // Binding glyph VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(size),
               glyph_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, glyph_vbo);                                     // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // TEXT COLORS:
  glGenVertexArrays(1, &color_vao);                                             // Generating color VAO...
  glBindVertexArray(color_vao);                                                 // Binding color VAO...
  glGenBuffers(1, &color_vbo);                                                  // Generating color VBO...
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);                                     // Binding color VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(size),
               color_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);                                     // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  delete[] glyph_data;
  delete[] color_data;

  loc_baseline->done();
}

text4::~text4()
{
  glDeleteBuffers(1, &glyph_vbo);                                               // Releasing OpenGL glyph VBO...
  glDeleteBuffers(1, &glyph_vao);                                               // Releasing OpenGL glyph VAO...
  glDeleteBuffers(1, &color_vbo);                                               // Releasing OpenGL color VBO...
  glDeleteBuffers(1, &color_vao);                                               // Releasing OpenGL color VAO...

  delete[] char_code;                                                           // Releasing ascii code for each character in input string...
  delete[] char_item;                                                           // Releasing font character position for each character in input string...
  delete[] char_numdata;                                                        // Releasing # of font data for each character in input string...
  delete[] char_numpoints;                                                      // Releasing # of font points for each character in input string...
  delete[] char_numstrokes;                                                     // Releasing # of font strokes for each character in input string...
  delete[] char_kern;                                                           // Releasing kern spacing for each character in input string...

  delete[] data_index;                                                          // Releasing index of font data for each character in input string...
  delete[] kern;                                                                // Releasing kern character spacing for each font point in input string...
  delete[] offset;                                                              // Releasing character offset for each font point in input string...

  delete[] x;                                                                   // Releasing "x" data array...
  delete[] y;                                                                   // Releasing "y" data array...
  delete[] z;                                                                   // Releasing "z" data array...
  delete[] w;                                                                   // Releasing "w" data array...

  delete[] r;                                                                   // Releasing "r" data array...
  delete[] g;                                                                   // Releasing "g" data array...
  delete[] b;                                                                   // Releasing "b" data array...
  delete[] a;                                                                   // Releasing "a" data array...
}
