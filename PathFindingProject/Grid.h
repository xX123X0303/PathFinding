#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Cell {
	bool isObstacle = false;
	bool isStart = false;
	bool isGoal = false;
	bool isPath = false;
};

class Grid
{
public:
	Grid(int r, int c);

	// Set Cell types
	void SetObstacle(int row, int col, bool value);
	void SetStart(int row, int col);
	void SetGoal(int row, int col);
	void ClearPath();
	
	// Query
	bool IsObstacle(int row, int col) const;
	bool IsValidCell(int row, int col) const;

	// Getter
	int GetRows() const;
	int GetCols() const;
	Cell GetCell(int row, int col) const;

	// Setter
	void SetPath(int row, int col, bool value);

private:
	int rows, cols;
	std::vector<std::vector<Cell>> grid;
	glm::ivec2 startPos;
	glm::ivec2 goalPos;
};