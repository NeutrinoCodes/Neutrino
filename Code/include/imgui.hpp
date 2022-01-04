/// @file   imgui.hpp
/// @author Erik ZORZIN
/// @date   27DEC2021
/// @brief  Declaration of the "imgui" class.

#ifndef imgui_hpp
#define imgui_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// IMGUI header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// IMPLOT header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <implot.h>
#include <implot_internal.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Utility structure for realtime plot ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
struct ScrollingBuffer
{
  int MaxSize;
  int Offset;
  ImVector<ImVec2> Data;

  ScrollingBuffer(
                  int max_size = 2000
                 )
  {
    MaxSize = max_size;
    Offset  = 0;
    Data.reserve (MaxSize);
  }

  void AddPoint (
                 float x,
                 float y
                )
  {
    if(Data.size () < MaxSize)
    {
      Data.push_back (ImVec2 (x,y));
    }

    else
    {
      Data[Offset] = ImVec2 (x,y);
      Offset       = (Offset + 1) % MaxSize;
    }
  }

  void Erase ()
  {
    if(Data.size () > 0)
    {
      Data.shrink (0);
      Offset = 0;
    }
  }
};

namespace nu
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "opengl" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
class imgui : public neutrino                                                                       /// @brief **ImGui HUD.**
{
private:

public:
  /// @brief **Class constructor.**
  /// @details It does nothing.
  imgui ();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// PUBLIC METHODS //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **Begin method.**
  /// @details To be invoked by the user in order to start using Imgui inside the application loop.
  void begin ();

  /// @brief **Window method.**
  /// @details To be invoked by the user in order to create a window.
  void window (
               std::string loc_name,                                                                ///< Window name.
               int         loc_width                                                                ///< Window width [px].
              );

  /// @brief **Input method.**
  /// @details To be invoked by the user in order to create an input parameter.
  void input (
              std::string loc_description,                                                          ///< Parameter description.
              std::string loc_unit,                                                                 ///< Parameter dimensional unit.
              std::string loc_name,                                                                 ///< Parameter name.
              int*        loc_value                                                                 ///< Parameter value.
             );

  void input (
              std::string loc_description,                                                          ///< Parameter description.
              std::string loc_unit,                                                                 ///< Parameter dimensional unit.
              std::string loc_name,                                                                 ///< Parameter name.
              float*      loc_value,                                                                ///< Parameter value.
              const char* format = "%+.6E"                                                          ///< Parameter format.
             );

  /// @brief **Slider method.**
  /// @details To be invoked by the user in order to create a slider input parameter.
  void slider (
               std::string loc_description,                                                         ///< Parameter description.
               std::string loc_unit,                                                                ///< Parameter dimensional unit.
               std::string loc_name,                                                                ///< Parameter name.
               int*        loc_value,                                                               ///< Parameter value.
               int         loc_min_value,                                                           ///< Parameter minimum value.
               int         loc_max_value                                                            ///< Parameter maximum value.
              );

  void slider (
               std::string loc_description,                                                         ///< Parameter description.
               std::string loc_unit,                                                                ///< Parameter dimensional unit.
               std::string loc_name,                                                                ///< Parameter name.
               float*      loc_value,                                                               ///< Parameter value.
               float       loc_min_value,                                                           ///< Parameter minimum value.
               float       loc_max_value,                                                           ///< Parameter maximum value.
               const char* format = "%+.6E"                                                         ///< Parameter format.
              );

  /// @brief **Output method.**
  /// @details To be invoked by the user in order to create an output parameter.
  void output (
               std::string loc_description,                                                         ///< Parameter description.
               std::string loc_unit,                                                                ///< Parameter dimensional unit.
               std::string loc_name,                                                                ///< Parameter name.
               int         loc_value                                                                ///< Parameter value.
              );

  void output (
               std::string loc_description,                                                         ///< Parameter description.
               std::string loc_unit,                                                                ///< Parameter dimensional unit.
               std::string loc_name,                                                                ///< Parameter name.
               float       loc_value,                                                               ///< Parameter value.
               const char* format = "%+.6E"                                                         ///< Parameter format.
              );

  /// @brief **Plot method.**
  /// @details To be invoked by the user in order to create a scrolling plot of a parameter.
  void plot (
             std::string loc_value_description,                                                     ///< Value description.
             std::string loc_value_name,                                                            ///< Value name.
             std::string loc_error_name,                                                            ///< Error name.
             float       loc_value,                                                                 ///< Value.
             float       loc_error                                                                  ///< Error.
            );

  /// @brief **Button method.**
  /// @details To be invoked by the user in order to create a button.
  bool button (
               std::string loc_name,                                                                ///< Button name.
               int         loc_width                                                                ///< Button width.
              );

  void space (
              int loc_space                                                                         ///< Horizontal space [px].
             );

  void newline ();                                                                                  ///< New line.

  void finish ();

  /// @brief **End method.**
  /// @details To be invoked by the user in order to stop using Imgui inside the application loop.
  void end ();

  /// @brief **Class destructor.**
  /// @details Terminates the HUD context.
  ~imgui();
};
}

#endif