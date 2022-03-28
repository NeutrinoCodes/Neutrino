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
  char        time_text[256];

  #ifdef WIN32
    localtime_s (&now, &file_time);                                                                 // Getting local date and time...
  #endif

  #ifdef __linux__
    localtime_r (&file_time, &now);                                                                 // Getting local date and time...
  #endif

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
                         unsigned int loc_int                                                       // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%d", loc_int);                                                           // Compiling data string...
  datafile << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::write (
                         int loc_int                                                                // Integer value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+d", loc_int);                                                          // Compiling data string...
  datafile << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::write (
                         float loc_float                                                            // Float value.
                        )
{
  char buffer[1024];                                                                                // Text buffer.

  snprintf (buffer, 1024, "%+.6E", loc_float);                                                      // Compiling data string...
  datafile << std::string (buffer);                                                                 // Writing data to file...
}

void nu::logfile::read ()
{
};

/*
   void nu::logfile::read (
                        T        var1,
                        Types... var2
                       )
   {

     for(std::string line; std::getline(source, line); )   //read stream line by line
     {
     std::istringstream in(line);      //make a stream for the line itself

     std::string type;
     in >> type;                  //and read the first whitespace-separated token

     if(type == "triangle")       //and check its value
     {
        float x, y, z;
        in >> x >> y >> z;       //now read the whitespace-separated floats
     }
     else if(...)
        ...
     else
        ...
     }


   cout << var1 << endl;

   print (var2 ...);
   }*/


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