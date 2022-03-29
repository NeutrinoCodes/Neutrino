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
                        logfile_mode loc_mode                                                       // Log file mode.
                       )
{
  time_t      file_time = time (0);
  struct tm   now;
  char        time_text[256];

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
      fileline = "4 +3.567771E-07";
      streamline << fileline;
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
  out_file << loc_string;                                                                           // Writing data...
}

void nu::logfile::write (
                         unsigned int loc_int                                                       // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%d", loc_int);                                                           // Compiling data string...
  out_file << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::write (
                         int loc_int                                                                // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+d", loc_int);                                                          // Compiling data string...
  out_file << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::write (
                         float loc_float                                                            // Float value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+.6E", loc_float);                                                      // Compiling data string...
  out_file << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::read ()
{
}

void nu::logfile::endline ()
{
  out_file << std::endl;
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

nu::logfile::~logfile()
{
  // Doing nothing!
}