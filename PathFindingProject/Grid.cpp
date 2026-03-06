#include "Grid.h"

Grid::Grid(int r, int c) : rows(r), cols(c)
{
	grid.resize(rows, std::vector<Cell>(cols));
	startPos = glm::ivec2(1, 1);
	goalPos = glm::ivec2(cols-1, rows-2);
	grid[startPos.x][startPos.y].isStart = true;
	grid[goalPos.x][goalPos.y].isGoal = true;
}

void Grid::SetObstacle(int row, int col, bool value)
{
	if (!IsValidCell(row, col)) return;

	grid[row][col].isObstacle = value;
	grid[row][col].isStart = false;
	grid[row][col].isGoal = false;
}

void Grid::SetStart(int row, int col)
{
	if (!IsValidCell(row, col)) return;

	grid[startPos.x][startPos.y].isStart = false;
	startPos = glm::ivec2(row, col);
	grid[row][col].isStart = true;
	grid[row][col].isObstacle = false;
}

void Grid::SetGoal(int row, int col)
{
	if (!IsValidCell(col, row)) return;

	grid[goalPos.y][goalPos.x].isGoal = false;
	goalPos = glm::ivec2(col, row);
	grid[row][col].isGoal = true;
	grid[row][col].isObstacle = false;
}

void Grid::ClearPath()
{
	for (int r = 0; r < rows; r++)
	for (int c = 0; c < cols; c++)
	{
		grid[r][c].isPath = false;
	}
}

bool Grid::IsObstacle(int row, int col) const
{
	if (!IsValidCell(col, row)) return true;
	return grid[row][col].isObstacle;
}

bool Grid::IsValidCell(int row, int col)  const
{
	return (row >= 0 && row < rows && col >= 0 && col < cols);
}

Cell Grid::GetCell(int row, int col) const
{
	if (!IsValidCell(col, row)) return Cell{};
	return grid[row][col];
}

int Grid::GetRows() const
{
	return rows;
}

int Grid::GetCols() const
{
	return cols;
}

void Grid::SetPath(int row, int col, bool value)
{
	if (!IsValidCell(row, col)) return;
	grid[row][col].isPath = value;
}
