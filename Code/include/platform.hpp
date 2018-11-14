/// @file

#ifndef platform_hpp
#define platform_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "PLATFORM" CLASS /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class platform
  {
    private:
      // OpenCL error get function:
      const char*             get_error   (
                                            cl_int loc_error                    // Local error code.
                                          );

      // OpenCL error check function:
      void                    check_error (
                                            cl_int loc_error                    // Error code.
                                          );

      size_t  get_info_size(cl_platform_id loc_platform_id, cl_platform_info loc_parameter_name);
      char*   get_info_value(cl_platform_id loc_platform_id, cl_platform_info loc_parameter_name, size_t loc_parameter_size);

    public:
      cl_platform_id          platform_id;                                      // OpenCL platform id.
      info*                   profile;                                          // Platform parameter.
      info*                   version;                                          // Platform parameter.
      info*                   name;                                             // Platform parameter.
      info*                   vendor;                                           // Platform parameter.
      info*                   extensions;                                       // Platform parameter.

                              platform  (cl_platform_id loc_platform_id);
                              ~platform ();
  };

#endif
