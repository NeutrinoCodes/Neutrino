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
                        logfile_mode loc_timestamp                                                  // Log file mode.
                       )
{
  time_t      file_time = time (0);
  struct tm   now;
  char        time_text [256];
  localtime_s (&now, &file_time);
  std::string file_name = loc_log_file_name;
  strftime (time_text, 256, "%Y-%b-%d_%H-%M-%S", &now);                                             // Compiling time string...

  switch(loc_timestamp)
  {
    case TIMESTAMP:
      file_name += "_";                                                                             // Adding underscore...
      file_name += time_text;                                                                       // Adding time stamp...
      file_name += "." + loc_log_file_extension;                                                    // Adding time file extension...
      break;

    case NO_TIMESTAMP:
      file_name += "." + loc_log_file_extension;                                                    // Adding file extension...
      break;

    default:
      file_name += "_";                                                                             // Adding underscore...
      file_name += time_text;                                                                       // Adding time stamp...
      file_name += "." + loc_log_file_extension;                                                    // Adding file extension...
      break;
  }

  datafile.open (file_name, std::ios::app);                                                         // Opening data log file (appending mode)...
  datafile << loc_log_header << std::endl;                                                          // Writing header...
  datafile << "Time stamp: " << time_text << std::endl;                                             // Writing time stamp...
  datafile << std::endl;                                                                            // Writing blank line...
}

void nu::logfile::write (
                         std::string loc_string                                                     // String value.
                        )
{
  datafile << loc_string;                                                                           // Writing data...
}

void nu::logfile::write (
                         int loc_int                                                                // Integer value.
                        )
{
  datafile << loc_int;                                                                              // Writing data...
}

void nu::logfile::write (
                         float loc_float                                                            // Float value.
                        )
{
  datafile <<                                                                                       // File...
    loc_float <<                                                                                    // Data...
    //std::setprecision (8) <<                                                                        // Precision (max)...
    std::scientific;                                                                                // Notation...
}

void nu::logfile::endline ()
{
  datafile << std::endl;
}

void nu::logfile::close ()
{
  datafile.close ();                                                                                // Closing file...
}

nu::logfile::~logfile()
{
  // Doing nothing!
}