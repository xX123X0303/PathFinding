#pragma once
#include "PathFinder.h"
#include "Grid.h"

#include <imgui/imgui.h>

class UI
{
public:
	bool Init();

	void Render(Grid& grid, PathFinder& pathfinder);

private:
	ImFont* titleFont = nullptr;
};