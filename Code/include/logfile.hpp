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
// File modes:
typedef enum
{
  READ,                                                                                             ///< Opens a file in read mode.
  WRITE                                                                                             ///< Opens a file in write mode.
} logfile_mode;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu::logfile" class /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class logfile : public neutrino                                                                     /// @brief **Logfile.**
{
private:
  std::ifstream     in_file;                                                                        ///< Data file.
  std::ofstream     out_file;                                                                       ///< Data file.
  std::string       fileline;                                                                       ///< File line.
  std::stringstream streamline;                                                                     ///< Stream line.
  bool              EOL = true;                                                                     ///< End of line flag.
  bool              END = false;                                                                    ///< End of file flag.

  template<typename T>
  struct remove_pointer
  {
    typedef T type;
  };

  template<typename T>
  struct remove_pointer<T*>
  {
    typedef typename remove_pointer<T>::type type;
  };

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
             std::string  loc_log_file_name,                                                        ///< Log file name.
             std::string  loc_log_file_extension,                                                   ///< Log file extension.
             std::string  loc_log_header,                                                           ///< Log file header.
             logfile_mode loc_mode                                                                  ///< Log file mode.
            );

  /// @brief **Write method.**
  /// @details To be invoked by the user in order to write **string** data on the log file.
  void write (
              std::string loc_string                                                                ///< String value.
             );

  /// @details To be invoked by the user in order to write **unsigned integer** data on the log file.
  void write (
              unsigned int loc_int                                                                  ///< Unsigned integer value.
             );

  /// @details To be invoked by the user in order to write **integer** data on the log file.
  void write (
              int loc_int                                                                           ///< Integer value.
             );

  /// @details To be invoked by the user in order to write **float** data on the log file.
  void write (
              float loc_float                                                                       ///< Float value.
             );

  void read ();

  template <typename T, typename ... Types>
  void read (
             T var1,
             Types... var2
            )
  {
    std::string token;                                                                              // Token.

    if(EOL)
    {
      // Reading single line from file:
      if(std::getline (in_file, fileline))
      {
        streamline << fileline;                                                                     // Copying file line to stream line...
        END = false;
      }

      else
      {
        END = true;
      }
    }

    if(!END)
    {
      // Extracting token from streamline:
      if(std::getline (streamline, token, ' '))
      {
        typename remove_pointer<T>::type::value_type value;                                         // Creating value by getting the type from the current vector argument...
        std::stringstream                            streamtoken (token);                           // Creating stream from extracted token...
        streamtoken >> value;                                                                       // Streaming token to value for current vector argument...
        var1->push_back (value);                                                                    // Appending value to current vector argument...
        EOL = false;                                                                                // Resetting end of line flag...
      }
    }
    read (var2 ...);                                                                                // Recursive self-invocation...
  };

  /// @brief **Endline method.**
  /// @details To be invoked by the user in order to write a newline on the log file.
  void endline ();

  /// @brief **Close method.**
  /// @details To be invoked by the user in order to close log file.
  void close (
              logfile_mode loc_mode                                                                 ///< Log file mode.
             );

  bool eof ();

  /// @brief **Class destructor.**
  /// @details Terminates the logfile.
  ~logfile();
};
}

#endif