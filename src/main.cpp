// Standard Libary
#include <thread>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <filesystem>
// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// Shaders
#include "Headers/Shaders.h"
#include "Headers/FindDirs.h"
// Buffers
#include "Buffers/VAO.h"
#include "Buffers/VBO.h"
#include "Buffers/EBO.h"
#include "Buffers/VAO.h"
#include "glm/gtc/type_ptr.hpp"
#include "Headers/FindDirs.h"
#include "Headers/shapes.h"






static int currentShape = 0;
float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
bool debugOn = false;
std::vector<int> keyInputs = {};

void debug() {
	if (debugOn == false) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		debugOn = true;
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		debugOn = false;
	}
}



void movement() {


	if (std::find(keyInputs.begin(), keyInputs.end(), GLFW_KEY_W) != keyInputs.end()) {
		posY += 0.001f;
	}
	if ((std::find(keyInputs.begin(), keyInputs.end(), GLFW_KEY_S) != keyInputs.end())) {
		posY -= 0.001f;

	}
	if ((std::find(keyInputs.begin(), keyInputs.end(), GLFW_KEY_A) != keyInputs.end())) {
		posX -= 0.001f;
	}
	if (((std::find(keyInputs.begin(), keyInputs.end(), GLFW_KEY_D) != keyInputs.end()))) {
		posX += 0.001f;
	}

}





void inputManager(int key) {
	if (key == GLFW_KEY_GRAVE_ACCENT and std::find(keyInputs.begin(), keyInputs.end(), key) == keyInputs.end()) {
		keyInputs.insert(keyInputs.begin(), key);

		debug();
	}
	if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D)) {
		keyInputs.insert(keyInputs.begin(), key);

		movement();
	}
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);


	std::string vertPath = findDirectory("Shaders", "default.vert");
	std::string fragPath = findDirectory("Shaders", "default.frag");

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram((vertPath.c_str()), (fragPath.c_str()));



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(Kotlin::vertices, sizeof(Kotlin::vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(Kotlin::indices, sizeof(Kotlin::indices));


	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	auto shapeChange = []()  {
		ShapeData& shape = shapeMap[shapes[currentShape]];
		VBO VBO1(shape.vertices, shape.vertSize);
		// Generates Element Buffer Object and links it to indices
		EBO EBO1(shape.indices, shape.indecieSize);

	};



	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	int fragLocation = glGetUniformLocation(shaderProgram.ID, "fragColor");
	static float colors[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	int objLocation = glGetUniformLocation(shaderProgram.ID, "object");
	float slideValue = 1.0f;
	std::thread moveThread(movement);
	moveThread.detach();




	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// uses glmath libaries to create 4x4 matrix to alter the scale of object
		glm::mat4 objectMatrix = glm::mat4(slideValue);
		objectMatrix = glm::translate(objectMatrix, glm::vec3(posX, posY, posZ));
		objectMatrix = glm::scale(objectMatrix, glm::vec3(slideValue,slideValue,slideValue));

		// Applies new matrix to object based on sliderValue
		glUniform4f(fragLocation, colors[0], colors[1], colors[2], colors[3]);
		glUniformMatrix4fv(objLocation, 1,GL_FALSE, glm::value_ptr(objectMatrix));

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		// ImGui Stuff
		if (debugOn == true) {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();

			ImGui::NewFrame();
			ImGui::Begin("DegubMenu");

			ImGui::Text("Color Picker");
			ImGui::ColorPicker4("Color", colors);

			ImGui::Text("Properties");
			ImGui::SliderFloat("Scale", &slideValue, 0.0f, 99.0f);
			if (ImGui::Combo("Shapes", &currentShape, shapes, IM_ARRAYSIZE(shapes))) {
				shapeChange();
			}


			ImGui::End();
			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}





		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		int keys[] = {
			GLFW_KEY_GRAVE_ACCENT,
			GLFW_KEY_W,
			GLFW_KEY_A,
			GLFW_KEY_S,
			GLFW_KEY_D
		};

		for (int key : keys) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				inputManager(key);
			}
			if (glfwGetKey(window, key) == GLFW_RELEASE) {
				keyInputs.erase(std::remove(keyInputs.begin(), keyInputs.end(), key), keyInputs.end());


			}
		}


		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
