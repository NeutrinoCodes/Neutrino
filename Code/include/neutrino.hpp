/// @file     neutrino.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of the "neutrino" class and some macros.
///
/// @details  Neutrino needs a common object to store some information that has to be exchanged
/// between different objects. This class also contains common definitions and common utility
/// member functions. The neutrino.hpp file must be include in all other Neutrino's classes, as it
/// contains a core declaration which are essential to everything in this framework.
///
/// **Cells interlinked within cells interlinked
/// within one stem. And, dreadfully distinct
/// against the dark, a tall white fountain played.**

#ifndef neutrino_hpp
#define neutrino_hpp

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// TERMINAL PARAMETERS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define NU_TERMINAL_REFRESH       20000                                                             ///< Terminal refresh time [us].
#define NU_COLOR_NORMAL           "\x1B[0m"                                                         ///< Default terminal color.
#define NU_COLOR_RED              "\x1B[31m"                                                        ///< Red.
#define NU_COLOR_GREEN            "\x1B[32m"                                                        ///< Green.
#define NU_COLOR_YELLOW           "\x1B[33m"                                                        ///< Yellow.
#define NU_COLOR_BLUE             "\x1B[34m"                                                        ///< Blue.
#define NU_COLOR_MAGENTA          "\x1B[35m"                                                        ///< Magenta.
#define NU_COLOR_CYAN             "\x1B[36m"                                                        ///< Cyan.
#define NU_COLOR_WHITE            "\x1B[37m"                                                        ///< White.
#define NU_ERASE                  "\33[2K\r"                                                        ///< Erase character.

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// WINDOW PARAMETERS /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define NU_ZOOM_INCREMENT         0.1f                                                              ///< Mouse wheel zoom increment [].
#define NU_ZOOM_INCREMENT_PS4     0.02f                                                             ///< PS4 gamepad zoom increment [].
#define NU_ZOOM_THRESHOLD_PS4     -0.95f                                                            ///< PS4 gamepad zoom threshold [].
#define NU_PAN_FACTOR             0.01f                                                             ///< Mouse pan translation factor [].
#define NU_ROTATION_FACTOR        2.0f                                                              ///< Mouse orbit rotation factor [].
#define NU_ROTATION_FACTOR_PS4    4.0f                                                              ///< PS4 gampad rotation factor [].
#define NU_ROTATION_THRESHOLD_PS4 0.1f                                                              ///< PS4 gampad rotation thrshold [].
#define NU_NEAR_Z_CLIP            0.1f                                                              ///< Near z-clipping distance [small, but > 0.0].
#define NU_FAR_Z_CLIP             100.0f                                                            ///< Far z-clipping distance [big, but < +inf].
#define NU_FOV                    60.0f                                                             ///< Field of view [deg].
#define NU_IOD                    0.02f                                                             ///< Intraocular distance.
#define NU_SCREEN_DISTANCE        -2.5f                                                             ///< Screen distance.
#define NU_LINE_WIDTH             3                                                                 ///< Line width [px].
#define NU_KERNEL_NAME            "thekernel"                                                       ///< OpenCL kernel function name.
#define NU_MAX_TEXT_SIZE          128                                                               ///< Maximum number of characters in a text string.
#define NU_MAX_MESSAGE_SIZE       128                                                               ///< Maximum number of characters in a text message.
#define NU_MAX_PATH_SIZE          32768                                                             ///< Maximum number of characters in a text file path.

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// GAMEPAD PARAMETERS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define NU_GAMEPAD_MIN_DECAYTIME  0.01f                                                             ///< Minimum decay time for LP filter [s].
#define NU_GAMEPAD_MAX_DECAYTIME  10.0f                                                             ///< Maximum decay time for LP filter [s].
#define NU_GAMEPAD_MIN_AXES       -1.0f                                                             ///< Minimum axes value.
#define NU_GAMEPAD_MAX_AXES       1.0f                                                              ///< Maximum axes value.
#define NU_GAMEPAD_MIN_ORBIT_RATE 0.01f                                                             ///< Minimum orbit angular rate [rev/s].
#define NU_GAMEPAD_MAX_ORBIT_RATE 10.0f                                                             ///< Maximum orbit angular rate [rev/s].
#define NU_GAMEPAD_MIN_PAN_RATE   0.01f                                                             ///< Minimum orbit angular rate [rev/s].
#define NU_GAMEPAD_MAX_PAN_RATE   10.0f                                                             ///< Maximum orbit angular rate [rev/s].

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Standard C/C++ header files //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cerrno>
#include <algorithm>

#ifdef __APPLE__                                                                                    // Detecting Mac OS...
  #include <math.h>
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <math.h>
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <windows.h>
  #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004                                                 ///< Enabling ANSI terminal in Windows...
  #define DISABLE_NEWLINE_AUTO_RETURN        0x0008                                                 ///< Disabling new line auto return in Windows terminal...

  #include <cmath>
  #ifndef M_PI
    #define M_PI                             3.14159265358979323846f
  #endif
#endif

#include "data_classes.hpp"                                                                         // Neutrino data classes.

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "neutrino" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class neutrino
/// ### Neutrino baseline.
/// Declares a Neutrino baseline object.
/// This class contains common definitions and utility functions which are used in various points
/// in the code.
class neutrino : public nu::data                                                                    /// @brief **Neutrino baseline.**
{
private:
  size_t                        terminal_time;                                                      ///< @brief **Terminal time (for refresh) [us].**
  size_t                        terminal_task;                                                      ///< @brief **Terminal time (for task percentage) [us].**

public:
  static bool                   interop;                                                            ///< @brief **Use OpenCL-OpenGL interop.**
  static double                 tic;                                                                ///< @brief **Tic application time [s].**
  static double                 toc;                                                                ///< @brief **Toc application time [s].**
  static double                 loop_time;                                                          ///< @brief **Loop time [s].**
  static double                 task_tic;                                                           ///< @brief **Tic task time [s].**
  static double                 task_toc;                                                           ///< @brief **Toc task time [s].**
  static double                 task_time;                                                          ///< @brief **Task time [s].**
  static cl_context             context_id;                                                         ///< @brief **OpenCL context ID.**
  static cl_platform_id         platform_id;                                                        ///< @brief **OpenCL platform ID.**
  static cl_device_id           device_id;                                                          ///< @brief **OpenCL device ID.**
  static cl_command_queue       queue_id;                                                           ///< @brief **OpenCL queue ID.**
  static std::vector<cl_kernel> kernel_id;                                                          ///< @brief **OpenCL kernel ID array.**
  static GLFWwindow*            glfw_window;                                                        ///< @brief **Window handle.**
  static bool                   init_done;                                                          ///< @brief **init_done flag.**

  /// @brief **Class constructor.**
  /// @details Resets interop, tic, toc, loop_time, context_id, platform_id and device_id to their
  /// default values.
  neutrino();

  /// @brief **Class initializer.**
  /// @details Initializes Neutrino.
  void        init ();

  /// @brief **Getter of "tic" time.**
  /// @details Gets a "tic" time, which is the value of operating system precision timer at the
  /// beginning of the application loop. To be used in combination with the "toc" time in order
  /// to measure the duration of the host PC processes during the application loop.
  /// This time is also used to manage timing-related operations within the Neutrino GUI, such as
  /// the low-pass filtering of the gamepad inputs.
  /// It does not measure the execution time of the kernel on the client GPU.
  void        get_tic ();

  /// @brief **Getter of "toc" time.**
  /// @details Gets a "toc" time, which is the value of operating system precision timer at the
  /// end of the application loop. To be used in combination with the "tic" time in order
  /// to measure the duration of the host PC processes during the application loop.
  /// This time is also used to manage timing-related operations within the Neutrino GUI, such as
  /// the low-pass filtering of the gamepad inputs.
  /// It does not measure the execution time of the kernel on the client GPU.
  void        get_toc ();

  /// @brief **Timestamp function.**
  /// @details Return a time stamp in the format %Y-%b-%d_%H-%M-%S according to the "struct tm", as a string.
  std::string get_timestamp ();

  /// @brief **Getter of "task" percentage.**
  /// @details Gets a "task" time percentage, which is the value of operating system precision timer at the
  /// beginning of a task. To be used in combination with the "progress" time in order
  /// to measure the perecentage of execution of a task.
  void        work ();

  /// @brief **Getter of "progress" percentage.**
  /// @details Prints the percentage of progress of a task.
  void        progress (
                        std::string loc_message,                                                    ///< Message.
                        size_t      loc_start,                                                      ///< Starting progress value.
                        size_t      loc_stop,                                                       ///< Final progress value.
                        size_t      loc_value                                                       ///< Current progress value.
                       );

  /// @brief **Loader file function.**
  /// @details Loads a file.
  std::string read_file (
                         std::string loc_file_name                                                  ///< File name.
                        );

  /// @brief **Query numeric input from stdin function.**
  /// @details Parses a user numeric input from stdin on a terminal console.
  /// The input number is constrained to stay within a minimum and a maximum.
  size_t      query_numeric (
                             std::string caption,                                                   ///< Text query caption.
                             int         min,                                                       ///< Minimum queried numeric value.
                             int         max                                                        ///< Maximum queried numeric value.
                            );

  /// @brief **Current stdout terminal line erase function.**
  /// @details Erases the current line from the stdout of the terminal console.
  void        erase ();

  /// @brief **Action message function.**
  /// @details Prints an "action" message on the terminal console.
  void        action (
                      std::string loc_text                                                          ///< User defined text message.
                     );

  /// @brief **Warning message function.**
  /// @details Prints a "warning" message on the terminal console.
  void        warning (
                       std::string loc_text                                                         ///< User defined text message.
                      );

  /// @brief **Error message function.**
  /// @details Prints an "error" message on the terminal console.
  void        error (
                     std::string loc_text                                                           ///< User defined text message.
                    );

  /// @brief **List message function.**
  /// @details Prints a "list" message on the terminal console.
  void        list (
                    std::string loc_text,                                                           ///< User defined text message.
                    std::string loc_delimiter,                                                      ///< User defined text delimiter.
                    size_t      loc_tab                                                             ///< User defined text tab size.
                   );

  /// @brief **Property search function.**
  /// @details Searches an input string for a text property.
  bool        property (
                        std::string loc_input,                                                      // Input string.
                        std::string loc_property                                                    // Property string.
                       );

  /// @brief **Done message function.**
  /// @details Prints a "done" message on the terminal console.
  void        done ();

  /// @brief **Not done message function.**
  /// @details Prints an "unfulfilled" message on the terminal console.
  void        unfulfilled ();

  /// @brief **Terminated message function.**
  /// @details Prints a "terminated" message on the terminal console.
  void        terminated ();

  /// @brief **Constrainer function for double numbers.**
  /// @details Constrains a double number to stay within a minimum and a maximum value.
  double      constrain_double (
                                double loc_input,                                                   ///< Input number to be constrained.
                                double loc_min,                                                     ///< Minimum constraint.
                                double loc_max                                                      ///< Maximum constraint.
                               );

  /// @brief **Constrainer function for nu_float3_structure numbers.**
  /// @details Constrains a float number to stay within a minimum and a maximum value.
  float       constrain_float (
                               float loc_input,                                                     ///< Input number to be constrained.
                               float loc_min,                                                       ///< Minimum constraint.
                               float loc_max                                                        ///< Maximum constraint.
                              );

  /// @brief **OpenCL error get function.**
  /// @details Translates an OpenCL numeric error code into a human-readable string.
  std::string get_error (
                         cl_int loc_error                                                           ///< OpenCL Error code.
                        );

  /// @brief **OpenCL error check function.**
  /// @details Checks for an OpenCL error code and print it to stdout.
  void        check_error (
                           cl_int loc_error                                                         ///< OpenCL Error code.
                          );

  /// @brief **Class destructor.**
  /// @details It deletes the kernel ID array.
  ~neutrino();
};

#endif
