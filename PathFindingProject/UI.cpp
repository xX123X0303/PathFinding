#include "UI.h"
#include <iostream>

bool UI::Init()
{
	ImGuiIO& io = ImGui::GetIO();

	titleFont = io.Fonts->AddFontFromFileTTF(
		"Roboto-Bold.ttf",
		35.0f
	);
	if (!titleFont)
	{
		std::cerr << "Failed to load font!" << std::endl;
		return false;
	}
	return true;
}

void UI::Render(Grid& grid, PathFinder& pathfinder)
{
	ImGui::Begin("Demo Window");

	if (titleFont) ImGui::PushFont(titleFont);
	ImGui::Text("PATHFINDING VISUALIZER");
	if (titleFont) ImGui::PopFont();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.3, 0.8, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3, 0.4, 0.9, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1, 0.2, 0.7, 1));

	if (ImGui::Button("Find Path", ImVec2(200, 60))) pathfinder.FindPath(grid);
	if (ImGui::Button("Clear Path", ImVec2(200, 60))) grid.ClearPath();

	ImGui::PopStyleColor(3);

	ImGui::End();
}