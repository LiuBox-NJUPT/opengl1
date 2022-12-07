// This code is to draw a triangle within the window. The code is using opengl programmable
// pipeline with Shader class. 
// Copyright by Rui @njupt.
// 2022.9

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<cmath>
#include "Shader.h"

#define ERROR_LOG(ErrorMessage) std::cout << ErrorMessage << std::endl;glfwTerminate();return -1;
#define PI 3.14159265
const int WIDTH = 800;
const int HEIGHT = 600;



GLuint VAO, VBO;
static void RenderScreen(GLFWwindow* window)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 15);
	glBindVertexArray(0);
	glfwSwapBuffers(window);
}

static void CreateVertexBuffer()
{
	double t = (1 + tan (18*PI/180)* tan(18 * PI / 180)) / (3 - tan (18*PI/180)* tan(18 * PI / 180));
	GLfloat vertices[] = { 
		//-1.0f, -1.0f, 0.0f, 
		//0.0f, 1.0f, 0.0f, 
		//1.0f, -1.0f, 0.0f
		0.0f,1.0f,0.0f,
		-t * cos(18*PI/180),-t* sin(18*PI/180),0.0f,
		t* cos(18*PI/180),-t* sin(18*PI/180),0.0f,

		cos(18*PI/180),sin(18*PI/180),0.0f,
		0.0f,-t,0.0f,
		-t* cos(54 * PI / 180),t * sin(54 * PI / 180),0.0f,

		cos(54*PI/180),-sin(54*PI/180),0.0f,
		-t* cos(18 * PI / 180),-t * sin(18 * PI / 180),0.0f,
		t * cos(54 * PI / 180),t* sin(54 * PI / 180),0.0f,

		-cos(54 * PI / 180),-sin(54 * PI / 180),0.0f,
		-t* cos(54 * PI / 180),t* sin(54 * PI / 180),0.0f,
		t* cos(18 * PI / 180),-t * sin(18 * PI / 180),0.0f,

		-cos(18 * PI / 180),sin(18 * PI / 180),0.0f,
		0.0f,-t,0.0f,
		t * cos(54 * PI / 180),t* sin(54 * PI / 180),0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

static void SetViewport(GLFWwindow* window)
{
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
#endif // __APPLE__
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLTutorial3", NULL, NULL);
	if (window == NULL) { ERROR_LOG("Failed to create Window!") }

	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit()) { ERROR_LOG("Failed to init glew") }

	CreateVertexBuffer();
	Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	while (!glfwWindowShouldClose(window))
	{
		SetViewport(window);
		glfwPollEvents();
		shader.UseProgram();
		RenderScreen(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	return 0;
}