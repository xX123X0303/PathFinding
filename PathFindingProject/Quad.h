#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "Grid.h"

class Quad
{
public:
	Quad(int r, int c);
	~Quad();

	void Update(int instanceIndex, float x, float y);
	void SetColor(int instanceIndex, glm::vec3 color);
	void Draw(const Grid& grid);

private:
	GLuint VAO, quadVBO, instanceVBO, colorVBO, EBO;

	int rows;
	int cols;

	std::vector<glm::vec2> translations;
	std::vector<glm::vec3> colors;

	float gap = 0.005f;
	float quadW, quadH;
};