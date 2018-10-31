/// @file

#ifndef path_hpp
#define path_hpp

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <errno.h>

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "PATH" CLASS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class path
  {
    private:

    public:
      char*   value;                                                            // Value array.
      size_t  size;                                                             // Value array size.

      path(size_t loc_path_size);
      ~path();
  };

#endif
