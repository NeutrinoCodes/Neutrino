#include "info.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "INFO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info()
{

}

void info::init(size_t loc_parameter_size, char* loc_parameter_value)
{
  size  = loc_parameter_size;                                                   // Setting value array size...
  value = loc_parameter_value;                                                  // Assigning value...
}

info::~info()
{

}
