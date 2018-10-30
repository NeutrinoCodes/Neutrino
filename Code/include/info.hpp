/// @file

#ifndef info_hpp
#define info_hpp

  #include <stdio.h>

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "INFO" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class info
  {
    private:

    public:
      char*   value;                                                            // Value array.
      size_t  size;                                                             // Value array size.

      info(size_t loc_parameter_size);
      ~info();
  };

#endif
