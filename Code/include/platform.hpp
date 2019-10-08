/// @file     platform.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of an OpenCL "platform" class.
///
/// @details  Declares methods in order to retrieve information about an OpenCL platform.

#ifndef platform_hpp
#define platform_hpp

  #include "neutrino.hpp"
  #include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "platform" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class platform
{
private:
  neutrino*   baseline;                                                                             ///< @brief **Neutrino baseline.**
  std::string parameter;                                                                            ///< @brief **Parameter value.**

  // Gets size information:
  size_t      get_info_size (
                             cl_platform_id   loc_platform_id,                                      ///< Platform ID.
                             cl_platform_info loc_parameter_name                                    ///< Paramenter name.
                            );

  // Gets size information:
  std::string get_info_value (
                              cl_platform_id   loc_platform_id,                                     ///< Platform ID.
                              cl_platform_info loc_parameter_name,                                  ///< Paramenter name.
                              size_t           loc_parameter_size                                   ///< Parameter size.
                             );

public:
  cl_platform_id id;                                                                                ///< @brief **OpenCL platform id.**
  std::string    profile;                                                                           ///< @brief **Platform parameter.**
  std::string    version;                                                                           ///< @brief **Platform parameter.**
  std::string    name;                                                                              ///< @brief **Platform parameter.**
  std::string    vendor;                                                                            ///< @brief **Platform parameter.**
  std::string    extensions;                                                                        ///< @brief **Platform parameter.**

  /// @brief **Class constructor.**
  /// @details It does nothing.
  platform  ();

  /// @brief **Class initializer.**
  /// @details It gets all information about the selected OpenCL platform and store it in the
  /// corresponding public variables.
  void init (
             cl_platform_id loc_platform_id                                                         ///< Platform ID.
            );

  /// @brief **Class destructor.**
  /// @details It does nothing.
  ~platform ();
};

#endif
