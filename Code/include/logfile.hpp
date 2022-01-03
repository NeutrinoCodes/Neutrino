/// @file   logfile.hpp
/// @author Erik ZORZIN
/// @date   03JAN2022
/// @brief  Declaration of the "logfile" class.

#ifndef logfile_hpp
#define logfile_hpp

#include "neutrino.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

namespace nu
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "opengl" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class logfile : public neutrino                                                                     /// @brief **Logfile.**
{
private:
  std::ofstream datafile;                                                                           ///< Data file.

public:
  /// @brief **Class constructor.**
  /// @details It does nothing.
  logfile ();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// PUBLIC METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **Open method.**
  /// @details To be invoked by the user in order to open/create a log file.
  void open (
             std::string loc_log_file_name,                                                         ///< Log file name.
             std::string loc_log_file_extension,                                                    ///< Log file extension.
             bool        loc_datetime                                                               ///< If **true** adds the current date and time to the file name.
            );

  /// @brief **Write method.**
  /// @details To be invoked by the user in order to write **float** data on the log file.
  void write (
              std::string loc_name,                                                                 ///< Variable name.
              float       loc_data                                                                  ///< Variable value.
             );

  /// @brief **Endline method.**
  /// @details To be invoked by the user in order to write a newline on the log file.
  void endline ();

  /// @brief **Close method.**
  /// @details To be invoked by the user in order to close log file.
  void close ();

  /// @brief **Class destructor.**
  /// @details Terminates the logfile.
  ~logfile();
};
}

#endif