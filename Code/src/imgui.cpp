/// @file     imgui.cpp
/// @author   Erik ZORZIN
/// @date     27DEC2021
/// @brief    Definition of the "nu::imgui" class.

#include "imgui.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu::imgui" class //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::imgui::imgui ()
{
  // Doing nothing!
}

void nu::imgui::begin ()
{
  ImGui_ImplOpenGL3_NewFrame ();                                                                    // Initializing ImGui...
  ImGui_ImplGlfw_NewFrame ();                                                                       // Initializing ImGui...
  ImGui::NewFrame ();                                                                               // Initializing ImGui...
}

void nu::imgui::window (
                        std::string loc_name,                                                       // Window name.
                        int         loc_width                                                       // Window width [px].
                       )
{
  ImGui::Begin (loc_name.c_str (), NULL, ImGuiWindowFlags_AlwaysAutoResize);                        // Beginning window...
  ImGui::PushItemWidth ((float)loc_width);                                                          // Setting window width [px]...
}

void nu::imgui::input (
                       std::string loc_description,                                                 // Parameter description.
                       std::string loc_unit,                                                        // Parameter dimensional unit.
                       std::string loc_name,                                                        // Parameter name.
                       int*        loc_value                                                        // Parameter value.
                      )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::InputInt ((" = " + loc_name).c_str (), loc_value);                                         // Adding input field...
}

void nu::imgui::input (
                       std::string loc_description,                                                 // Parameter description.
                       std::string loc_unit,                                                        // Parameter dimensional unit.
                       std::string loc_name,                                                        // Parameter name.
                       float*      loc_value,                                                       // Parameter value.
                       const char* format                                                           // Parameter format.
                      )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::InputFloat ((" = " + loc_name).c_str (), loc_value, 0.0f, 0.0f, format);                   // Adding input field...
}

void nu::imgui::slider (
                        std::string loc_description,                                                // Parameter description.
                        std::string loc_unit,                                                       // Parameter dimensional unit.
                        std::string loc_name,                                                       // Parameter name.
                        int*        loc_value,                                                      // Parameter value.
                        int         loc_min_value,                                                  // Parameter minimum value.
                        int         loc_max_value                                                   // Parameter maximum value.
                       )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...                                                                                // Staying on same line...
  ImGui::SliderInt ((" = " + loc_name).c_str (), loc_value, loc_min_value, loc_max_value);          // Adding input field...
}

void nu::imgui::slider (
                        std::string loc_description,                                                // Parameter description.
                        std::string loc_unit,                                                       // Parameter dimensional unit.
                        std::string loc_name,                                                       // Parameter name.
                        float*      loc_value,                                                      // Parameter value.
                        float       loc_min_value,                                                  // Parameter minimum value.
                        float       loc_max_value,                                                  // Parameter maximum value.
                        const char* format                                                          // Parameter format.
                       )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...                                                                                // Staying on same line...
  ImGui::SliderFloat ((" = " + loc_name).c_str (), loc_value, loc_min_value, loc_max_value);        // Adding input field...
}

void nu::imgui::output (
                        std::string loc_description,                                                // Parameter description.
                        std::string loc_unit,                                                       // Parameter dimensional unit.
                        std::string loc_name,                                                       // Parameter name.
                        int         loc_value                                                       // Parameter value.
                       )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (1.0f, 1.0f, 1.0f, 1.0f), "%d", loc_value);                            // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (1.0f, 1.0f, 1.0f, 1.0f), (" = " + loc_name).c_str ());                // Writing text...
}

void nu::imgui::output (
                        std::string loc_description,                                                // Parameter description.
                        std::string loc_unit,                                                       // Parameter dimensional unit.
                        std::string loc_name,                                                       // Parameter name.
                        float       loc_value,                                                      // Parameter value.
                        const char* format                                                          // Parameter format.
                       )
{
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_description.c_str ());                   // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (0.0f, 1.0f, 0.0f, 1.0f), loc_unit.c_str ());                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (1.0f, 1.0f, 1.0f, 1.0f), format, loc_value);                          // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::TextColored (ImVec4 (1.0f, 1.0f, 1.0f, 1.0f), (" = " + loc_name).c_str ());                // Writing text...
}

void nu::imgui::timeplot (
                          int         loc_ID,                                                       // Plot unique ID.
                          float       dt,                                                           // Time step.
                          float       loc_data,                                                     // Data value.
                          float       loc_error,                                                    // Error value.
                          std::string loc_title,                                                    // Plot title.
                          std::string loc_data_axis,                                                // Data axis label.
                          std::string loc_data_legend,                                              // Data legend.
                          std::string loc_error_legend                                              // Error legend.
                         )
{
  if(scrollplot_time.size () < (loc_ID + 1))
  {
    scrollplot_time.push_back (0.0f);                                                               // Adding scroll time buffer...
    scrollplot_data.push_back (ScrollingBuffer ());                                                 // Adding scroll data buffer...
    scrollplot_up_error.push_back (ScrollingBuffer ());                                             // Adding scroll up-errorbar buffer...
    scrollplot_down_error.push_back (ScrollingBuffer ());                                           // Adding scroll down-errorbar buffer...
  }

  if(history_time.size () < (loc_ID + 1))
  {
    history_time.push_back (10.0f);                                                                 // Adding history time [s]...
  }

  std::string     history_name = "History##_" + std::to_string (loc_ID);                            // History slider unique name.
  std::string     plot_name    = loc_title + "##_Timeplot_" + std::to_string (loc_ID);              // Timeplot unique name...

  ImGui::SliderFloat (history_name.c_str (), &history_time[loc_ID], 1, 30, "%.1f s");               // Setting history slider...
  ImPlotAxisFlags flags        = ImPlotAxisFlags_AutoFit;

  scrollplot_time[loc_ID] += dt;
  scrollplot_data[loc_ID].AddPoint (scrollplot_time[loc_ID], loc_data);                             // Adding point to data buffer...
  scrollplot_up_error[loc_ID].AddPoint (scrollplot_time[loc_ID], loc_data + loc_error);             // Adding point to up-errorbar buffer...
  scrollplot_down_error[loc_ID].AddPoint (scrollplot_time[loc_ID], loc_data - loc_error);           // Adding point to down-errorbar buffer...

  if(ImPlot::BeginPlot (plot_name.c_str (), ImVec2 (-1, 150)))
  {
    ImPlot::SetupAxes ("time [s]", loc_data_axis.c_str (), flags, flags);
    ImPlot::SetupAxisLimits (
                             ImAxis_X1,
                             scrollplot_time[loc_ID] - history_time[loc_ID],
                             scrollplot_time[loc_ID],
                             ImGuiCond_Always
                            );
    ImPlot::SetupAxisLimits (ImAxis_Y1, -1, 1);
    ImPlot::SetNextFillStyle (IMPLOT_AUTO_COL, 0.5f);
    ImPlot::PlotShaded (
                        loc_error_legend.c_str (),
                        &scrollplot_data[loc_ID].Data[0].x,
                        &scrollplot_up_error[loc_ID].Data[0].y,
                        &scrollplot_down_error[loc_ID].Data[0].y,
                        scrollplot_data[loc_ID].Data.size (),
                        scrollplot_data[loc_ID].Offset,
                        2*sizeof(float)
                       );
    ImPlot::PlotLine (
                      loc_data_legend.c_str (),
                      &scrollplot_data[loc_ID].Data[0].x,
                      &scrollplot_data[loc_ID].Data[0].y,
                      scrollplot_data[loc_ID].Data.size (),
                      scrollplot_data[loc_ID].Offset,
                      2*sizeof(float)
                     );

    ImPlot::EndPlot ();
  }
}

void nu::imgui::lineplot (
                          int                loc_ID,                                                // Plot unique ID.
                          std::vector<float> loc_x_data,                                            // x-data values.
                          std::vector<float> loc_y_data,                                            // y-data values.
                          std::string        loc_title,                                             // Plot title.
                          std::string        loc_x_axis,                                            // x-axis label.
                          std::string        loc_y_axis,                                            // y-axis label.
                          std::string        loc_data_legend                                        // Data legend.
                         )
{
  ImPlotAxisFlags flags     = ImPlotAxisFlags_AutoFit;
  std::string     plot_name = loc_title + "##_Lineplot_" + std::to_string (loc_ID);                 // Lineplot unique name...

  if(ImPlot::BeginPlot (plot_name.c_str (), ImVec2 (-1, 150)))
  {
    ImPlot::SetupAxes (loc_x_axis.c_str (), loc_y_axis.c_str (), flags, flags);
    ImPlot::SetupAxisLimits (
                             ImAxis_X1,
                             loc_x_data[0],
                             loc_x_data[loc_x_data.size () - 1],
                             ImGuiCond_Always
                            );
    ImPlot::SetupAxisLimits (ImAxis_Y1, -1, 1);
    ImPlot::SetNextFillStyle (IMPLOT_AUTO_COL, 0.5f);

    ImPlot::PlotLine (
                      loc_data_legend.c_str (),
                      &loc_x_data[0],
                      &loc_y_data[0],
                      (int)loc_x_data.size ()
                     );

    ImPlot::EndPlot ();
  }
}

bool nu::imgui::button (
                        std::string loc_name,                                                       // Button name.
                        int         loc_width                                                       // Button width.
                       )
{
  return ImGui::Button (loc_name.c_str (), ImVec2 ((float)loc_width, ImGui::GetFrameHeight ()));    // Adding button...
}

void nu::imgui::space (
                       int loc_space                                                                // Horizontal space [px].
                      )
{
  ImGui::SameLine (0.0f,  (float)loc_space);
}

void nu::imgui::newline ()
{
  ImGui::NewLine ();                                                                                // Adding new line...
}

void nu::imgui::finish ()
{
  ImGui::End ();                                                                                    // Finishing window...
}

void nu::imgui::end ()
{
  ImGui::Render ();                                                                                 // Rendering windows...
  ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());                                         // Rendering windows...
}

nu::imgui::~imgui()
{
  // Doing nothing!
}