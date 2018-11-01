#include "info.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "INFO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info(size_t loc_parameter_size)
{
  size = loc_parameter_size;                                                    // Setting value array size...
  value = (char*) malloc(loc_parameter_size);                                   // Allocating value array...
}

info::~info()
{
  free(value);                                                                  // Freeing value array...
}
