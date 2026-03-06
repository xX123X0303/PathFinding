#include "Quad.h"

Quad::Quad(int r, int c) : rows(r), cols(c)
{
	translations.resize(rows * cols);
	colors.resize(rows * cols);

	// Quad shape (VBO)
	quadW = (2.0f - gap * (cols + 1)) / cols;
	quadH = (2.0f - gap * (rows + 1)) / rows;

	float quadVertices[] = {
		0.0f,  0.0f, 
		quadW, 0.0f, 
		quadW, quadH, 
		0.0f,  quadH
	};

	// Indices (EBO)
	int indices[] = {0, 1, 2, 2, 3, 0};

	// Prepare translations for instances
	int transIndex = 0;
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	{ 
		float x = -1.0f + gap + i * (quadW + gap);
		float y =  1.0f - gap - j * (quadH + gap) - quadH;
		translations[transIndex++] = glm::vec2(x, y);
	}

	// Prepare colors for instances
	int colorsIndex = 0;
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	{
		colors[colorsIndex++] = glm::vec3(1.f, 0.f, 0.f);
	}

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Quad VBO
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Instance VBO
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

	glBufferData(GL_ARRAY_BUFFER, translations.size() * sizeof(glm::vec2), translations.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	// Color VBO
	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &quadVBO);
	glDeleteBuffers(1, &instanceVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
}

void Quad::Update(int instanceIndex, float x, float y)
{
	translations[instanceIndex] = glm::vec2(x, y);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, instanceIndex * sizeof(glm::vec2), sizeof(glm::vec2), &translations[instanceIndex]);
}

void Quad::SetColor(int instanceIndex, glm::vec3 color)
{
	colors[instanceIndex] = color;
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, instanceIndex * sizeof(glm::vec3), sizeof(glm::vec3), &colors[instanceIndex]);
}

void Quad::Draw(const Grid& grid)
{
	for (int r = 0; r < rows; r++)
	for (int c = 0; c < cols; c++)
	{
		Cell cell = grid.GetCell(r, c);
		int index = r * cols + c;

		if (cell.isGoal) SetColor(index, glm::vec3(1.f, 0.f, 0.f));
		else if (cell.isStart) SetColor(index, glm::vec3(0.f, 1.f, 0.f));
		else if (cell.isObstacle) SetColor(index, glm::vec3(1.f, 1.f, 1.f));
		else if (cell.isPath) SetColor(index, glm::vec3(1.f, 0.f, 1.f));
		else SetColor(index, glm::vec3(0.f, 0.f, 0.f));
	}

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, translations.size());
	glBindVertexArray(0);
}