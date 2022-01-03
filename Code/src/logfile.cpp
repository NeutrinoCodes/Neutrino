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
                        std::string loc_log_file_name,                                              // Log file name.
                        std::string loc_log_file_extension,                                         // Log file extension.
                        bool        loc_datetime                                                    // If **true** adds the current date and time to the file name.
                       )
{
  time_t      file_time = time (0);
  struct tm   now;
  char        time_text [256];
  localtime_s (&now, &file_time);
  std::string file_name = loc_log_file_name;

  if(loc_datetime)
  {
    strftime (time_text, 256, "_%Y-%b-%d_%H-%M-%S.", &now);                                         // Compiling time string...
    file_name += time_text + loc_log_file_extension;                                                // Adding time string and file extension...
  }
  else
  {
    file_name += "." + loc_log_file_extension;                                                      // Adding file extension...
  }

  datafile.open (file_name);                                                                        // Opening data log file...
}

void nu::write (
                std::string loc_name,                                                               // Variable name.
                float       loc_data                                                                // Variable value.
               )
{
  datafile << loc_name << " = " << loc_data << "; ";                                                // Writing data...
}

void nu::endline ()
{
  datafile << std::endl;
}

void nu::close ()
{
  datafile.close ();                                                                                // Closing file...
}

nu::logfile::~logfile()
{
  // Doing nothing!
}