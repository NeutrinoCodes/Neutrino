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
  std::vector<ScrollingBuffer> scrollplot_data;                                                     ///< Scroll plot data buffer array.
  std::vector<float>           scrollplot_time;                                                     ///< Scroll plot time buffer array.
  std::vector<float>           history_time;                                                        ///< History plot time buffer array.
  std::vector<ScrollingBuffer> scrollplot_up_error;                                                 ///< Scroll plot up errorbar buffer array.
  std::vector<ScrollingBuffer> scrollplot_down_error;                                               ///< Scroll plot down errorbar buffer array.

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

  /// @brief **Timeplot method.**
  /// @details To be invoked by the user in order to create a scrolling plot of a variable vs time.
  void timeplot (
                 int         loc_ID,                                                                ///< Plot unique ID.
                 float       dt,                                                                    ///< Time step.
                 float       loc_data,                                                              ///< Data value.
                 float       loc_error,                                                             ///< Error value.
                 std::string loc_title,                                                             ///< Plot title.
                 std::string loc_data_axis,                                                         ///< Data axis label.
                 std::string loc_data_legend,                                                       ///< Data legend.
                 std::string loc_error_legend                                                       ///< Error legend.
                );

  /// @brief **Lineplot method.**
  /// @details To be invoked by the user in order to create a plot of a variable vs another one.
  void lineplot (
                 int                loc_ID,                                                         ///< Plot unique ID.
                 std::vector<float> loc_x_data,                                                     ///< x-data values.
                 std::vector<float> loc_y_data,                                                     ///< y-data values.
                 std::string        loc_title,                                                      ///< Plot title.
                 std::string        loc_x_axis,                                                     ///< x-axis label.
                 std::string        loc_y_axis,                                                     ///< y-axis label.
                 std::string        loc_data_legend                                                 ///< Data legend.
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