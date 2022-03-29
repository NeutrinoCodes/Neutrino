/// @file     logfile.cpp
/// @author   Erik ZORZIN
/// @date     03JAN2022
/// @brief    Definition of the "nu::logfile" class.

#include "logfile.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// "nu::logfile" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::logfile::logfile ()
{
  // Doing nothing!
}

void nu::logfile::open (
                        std::string  loc_log_file_name,                                             // Log file name.
                        std::string  loc_log_file_extension,                                        // Log file extension.
                        std::string  loc_log_header,                                                // Log file header.
                        std::string  loc_log_delimiter,                                             // Log file delimiter.
                        logfile_mode loc_mode                                                       // Log file mode.
                       )
{
  time_t    file_time = time (0);
  struct tm now;
  char      time_text[256];
  delimiter = loc_log_delimiter;

  #ifdef WIN32
    localtime_s (&now, &file_time);                                                                 // Getting local date and time...
  #endif

  #ifdef __linux__
    localtime_r (&file_time, &now);                                                                 // Getting local date and time...
  #endif

  std::string file_name = loc_log_file_name;
  file_name += "." + loc_log_file_extension;                                                        // Adding file extension...
  strftime (time_text, 256, "%Y-%b-%d_%H-%M-%S", &now);                                             // Compiling time string...

  switch(loc_mode)
  {
    case READ:
      in_file.open (file_name);                                                                     // Opening data log file (read mode)...
      break;

    case WRITE:
      out_file.open (file_name, std::ios::app);                                                     // Opening data log file (appending mode)...
      out_file << loc_log_header << std::endl;                                                      // Writing header...
      out_file << "Time stamp: " << time_text << std::endl;                                         // Writing time stamp...
      out_file << std::endl;                                                                        // Writing blank line...
      break;
  }
}

void nu::logfile::write (
                         std::string loc_string                                                     // String value.
                        )
{
  out_file << loc_string << delimiter;                                                              // Writing data...
}

void nu::logfile::write (
                         unsigned int loc_int                                                       // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%d", loc_int);                                                           // Compiling data string...
  out_file << std::string (buffer) << delimiter;                                                    // Writing data to file...
}

void nu::logfile::write (
                         int loc_int                                                                // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+d", loc_int);                                                          // Compiling data string...
  out_file << std::string (buffer) << delimiter;                                                    // Writing data to file...
}

void nu::logfile::write (
                         float loc_float                                                            // Float value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+.6E", loc_float);                                                      // Compiling data string...
  out_file << std::string (buffer) << delimiter;                                                    // Writing data to file...
}

void nu::logfile::read ()
{
  EOL = true;                                                                                       // Setting end of line...
  fileline.clear ();                                                                                // Clearing fileline...
  streamline.clear ();                                                                              // Clearing streamline...
}

void nu::logfile::endline ()
{
  out_file << std::endl;                                                                            // Ending line...
}

void nu::logfile::close (
                         logfile_mode loc_mode
                        )
{
  switch(loc_mode)
  {
    case READ:
      in_file.close ();                                                                             // Closing file...
      break;

    case WRITE:
      out_file.close ();                                                                            // Closing file...
      break;
  }
}

bool nu::logfile::eof ()
{
  return END;                                                                                       // Returning END...
}

nu::logfile::~logfile()
{
  // Doing nothing!
}