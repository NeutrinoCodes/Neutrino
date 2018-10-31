/// @file

#ifndef path_hpp
#define path_hpp

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
