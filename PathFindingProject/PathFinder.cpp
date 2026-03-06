#include "PathFinder.h"

PathFinder::PathFinder() {}

void PathFinder::FindPath(Grid& grid)
{
	grid.ClearPath();

	int rows = grid.GetRows();
	int cols = grid.GetCols();

	std::queue<glm::ivec2> q;

	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
	std::vector<std::vector<glm::ivec2>> parents(rows, std::vector<glm::ivec2>(cols, {-1, -1}));

	glm::ivec2 start, goal;

	for (int r = 0; r < rows; r++)
	for (int c = 0; c < cols; c++)
	{
		Cell cell = grid.GetCell(r, c);
		if (cell.isStart) start = glm::ivec2(r, c);
		else if (cell.isGoal) goal = glm::ivec2(r, c);
	}

	q.push(start);
	visited[start.x][start.y] = true;

	while (!q.empty())
	{
		glm::ivec2 current = q.front();
		q.pop();

		if (current == goal) break;

		for (const auto& n : GetNeighbour(current, grid))
		{
			if (!visited[n.x][n.y])
			{
				visited[n.x][n.y] = true;
				parents[n.x][n.y] = current;
				q.push(n);
			}
		}
	}

	glm::ivec2 p = goal;

	while (p != start)
	{
		grid.SetPath(p.x, p.y, true);
		p = parents[p.x][p.y];

		if (p.x == -1) break;
	}
}

std::vector<glm::ivec2> PathFinder::GetNeighbour(glm::ivec2 pos, Grid& grid)
{
	std::vector<glm::ivec2> neighbours;

	int r = pos.x;
	int c = pos.y;

	glm::ivec2 dirs[4] = {
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0}
	};

	for (const auto& d : dirs)
	{
		int nr = r + d.x;
		int nc = c + d.y;

		if (grid.IsValidCell(nr, nc) && !grid.IsObstacle(nr, nc))
		{
			neighbours.push_back({nr, nc});
		}
	}

	return neighbours;
}
