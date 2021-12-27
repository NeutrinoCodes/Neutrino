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

void nu::imgui::parameter (
                           std::string loc_description,                                             // Parameter description.
                           std::string loc_unit,                                                    // Parameter dimensional unit.
                           std::string loc_name,                                                    // Parameter name.
                           float*      loc_value                                                    // Parameter value.
                          )
{
  ImGui::PushStyleColor (ImGuiCol_Text, IM_COL32 (0, 255, 0, 255));                                 // Setting text color...
  ImGui::Text (loc_description.c_str ());                                                           // Writing text...
  ImGui::PopStyleColor ();                                                                          // Restoring text color...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::Text (loc_unit.c_str ());                                                                  // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::InputFloat (loc_name.c_str (), loc_value);                                                 // Adding input field...
}

void nu::imgui::slider (
                        std::string loc_description,                                                // Parameter description.
                        std::string loc_unit,                                                       // Parameter dimensional unit.
                        std::string loc_name,                                                       // Parameter name.
                        float*      loc_value,                                                      // Parameter value.
                        float       loc_min_value,                                                  // Parameter minimum value.
                        float       loc_max_value                                                   // Parameter maximum value.
                       )
{
  ImGui::PushStyleColor (ImGuiCol_Text, IM_COL32 (0, 255, 0, 255));                                 // Setting text color...
  ImGui::Text (loc_description.c_str ());                                                           // Writing text...
  ImGui::PopStyleColor ();                                                                          // Restoring text color...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::Text (loc_unit.c_str ());                                                                  // Writing text...
  ImGui::SameLine ();                                                                               // Staying on same line...
  ImGui::SliderFloat (loc_name.c_str (), loc_value, loc_min_value, loc_max_value);                  // Adding input field...
}

void nu::imgui::plot (
                      std::string loc_value_description,                                            // Value description.
                      std::string loc_value_name,                                                   // Value name.
                      std::string loc_error_name,                                                   // Error name.
                      float       loc_value,                                                        // Value.
                      float       loc_error                                                         // Error.
                     )
{

}

void nu::imgui::button (
                        std::string loc_name                                                        // Button name.
                       )
{
  ImGui::Button (loc_name.c_str ());                                                                // Adding button...
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