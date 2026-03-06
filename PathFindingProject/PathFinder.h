#pragma once
#include <queue>
#include <vector>
#include "Grid.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class PathFinder
{
public:
	PathFinder();

	void FindPath(Grid& grid);

private:
	std::vector<glm::ivec2> GetNeighbour(glm::ivec2 pos, Grid& grid);
};
