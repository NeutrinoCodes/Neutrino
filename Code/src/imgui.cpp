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

void nu::imgui::plot (
                      std::string loc_value_description,                                            // Value description.
                      std::string loc_value_name,                                                   // Value name.
                      std::string loc_error_name,                                                   // Error name.
                      float       loc_value,                                                        // Value.
                      float       loc_error,                                                        // Error.
                      float       loc_dt                                                            // Time delta [s].
                     )
{
  static ScrollingBuffer data_avg;
  static ScrollingBuffer data_std_up;
  static ScrollingBuffer data_std_down;
  static float           t       = 0;
  static float           history = 10.0f;
  ImGui::SliderFloat ("History", &history, 1, 30, "%.1f s");
  static ImPlotAxisFlags flags   = ImPlotAxisFlags_AutoFit;

  t += loc_dt;
  data_avg.AddPoint (t, loc_value);
  data_std_up.AddPoint (t, loc_value + loc_error);
  data_std_down.AddPoint (t, loc_value - loc_error);

  if(ImPlot::BeginPlot ("##Scrolling", ImVec2 (-1, 150)))
  {
    ImPlot::SetupAxes ("time [s]", loc_value_description.c_str (), flags, flags);
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