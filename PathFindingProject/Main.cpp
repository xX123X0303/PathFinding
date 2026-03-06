#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Shader.h"
#include "Quad.h"
#include "PathFinder.h"
#include "UI.h"

const int width = 1200;
const int height = 900;

const int rows = 25;
const int cols = 25;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Grid& grid);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Path Finding", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD loader" << std::endl;
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); 

	UI gameUI;
	if (!gameUI.Init()) return -1;

	{
		Shader shader("default.vert", "default.frag");
		Grid grid(rows, cols);
		Quad quad(rows, cols);
		PathFinder pathfinder;


		while (!glfwWindowShouldClose(window))
		{
			processInput(window, grid);

			glClearColor(0.956f, 0.941f, 0.894f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			shader.Use();
			quad.Draw(grid);

			gameUI.Render(grid, pathfinder);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Grid& grid)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	

	bool leftMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	bool rightMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	
	if (!leftMousePressed && !rightMousePressed) return;

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	int cellX = static_cast<int>(mouseX / (width / grid.GetCols()));
	int cellY = static_cast<int>(mouseY / (height / grid.GetRows()));

	if (grid.GetCell(cellX, cellY).isStart || grid.GetCell(cellX, cellY).isGoal) return;

	if (leftMousePressed) grid.SetObstacle(cellX, cellY, true);
	if (rightMousePressed) grid.SetObstacle(cellX, cellY, false);
}