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
                          float       loc_data,                                                     // Data value.
                          float       loc_error,                                                    // Data error.
                          std::string loc_title,                                                    // Plot title.
                          std::string loc_label,                                                    // Axis label.
                          std::string loc_y_name,                                                   // Value name.
                          std::string loc_y_error_name                                              // Error name.
                         )
{
  if(scrollplot_x.size () < (loc_ID + 1))
  {
    scrollplot_x.push_back (ScrollingBuffer ());                                                    // Adding scroll x-axis data buffer...
    scrollplot_y.push_back (ScrollingBuffer ());                                                    // Adding scroll y-axis data buffer...
    scrollplot_up_error.push_back (ScrollingBuffer ());                                             // Adding scroll plot up errorbar buffer...
    scrollplot_down_error.push_back (ScrollingBuffer ());                                           // Adding scroll plot down errorbar buffer...
  }

  float           t        = 0;
  float           history  = 10.0f;
  std::string     loc_name = "History##_";                                                          // Writing data to file...

  ImGui::SliderFloat ((loc_name + loc_title).c_str (), &history, 1, 30, "%.1f s");                  // Setting unique ID for History widget...
  ImPlotAxisFlags flags    = ImPlotAxisFlags_AutoFit;

  t += loc_dt;
  scrollplot_y[loc_ID].AddPoint (t, loc_y_data);                                                    // Adding point to y-axis buffer...
  scrollplot_up_error[loc_ID].AddPoint (t, loc_y_data + loc_y_error);                               // Adding point to y-axis up errorbar buffer...
  scrollplot_up_error[loc_ID].AddPoint (t, loc_y_data - loc_y_error);                               // Adding point to y-axis down errorbar buffer...

  if(ImPlot::BeginPlot (loc_title.c_str (), ImVec2 (-1, 150)))
  {
    ImPlot::SetupAxes ("time [s]", loc_value_unit.c_str (), flags, flags);
    ImPlot::SetupAxisLimits (ImAxis_X1, t - history, t, ImGuiCond_Always);
    ImPlot::SetupAxisLimits (ImAxis_Y1, -1, 1);
    ImPlot::SetNextFillStyle (IMPLOT_AUTO_COL, 0.5f);
    ImPlot::PlotShaded (
                        loc_error_name.c_str (),
                        &data_avg.Data[0].x,
                        &data_std_up.Data[0].y,
                        &data_std_down.Data[0].y,
                        data_avg.Data.size (),
                        data_avg.Offset,
                        2*sizeof(float)
                       );
    ImPlot::PlotLine (
                      loc_value_name.c_str (),
                      &data_avg.Data[0].x,
                      &data_avg.Data[0].y,
                      data_avg.Data.size (),
                      data_avg.Offset,
                      2*sizeof(float)
                     );

    ImPlot::EndPlot ();
  }
}

void nu::imgui::lineplot (
                          std::string        loc_title,                                             // Plot title.
                          std::string        loc_x_label,                                           // Value description.
                          std::string        loc_y_label,                                           // Value name.
                          std::vector<float> loc_x,                                                 // x-values.
                          std::vector<float> loc_y                                                  // y-values.
                         )
{
  ImPlotAxisFlags flags = ImPlotAxisFlags_AutoFit;

  if(ImPlot::BeginPlot (loc_title.c_str (), ImVec2 (-1, 150)))
  {
    ImPlot::SetupAxes (loc_x_label.c_str (), loc_y_label.c_str (), flags, flags);
    ImPlot::SetupAxisLimits (ImAxis_X1, loc_x[0], loc_x[loc_x.size () - 1], ImGuiCond_Always);
    ImPlot::SetupAxisLimits (ImAxis_Y1, -1, 1);
    ImPlot::SetNextFillStyle (IMPLOT_AUTO_COL, 0.5f);

    ImPlot::PlotLine (
                      loc_title.c_str (),
                      &loc_x[0],
                      &loc_y[0],
                      (int)loc_x.size ()
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