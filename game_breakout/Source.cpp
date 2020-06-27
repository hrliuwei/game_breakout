
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <GLFW/glfw3.h>
#include <iostream>
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);


	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", NULL, NULL);
	if (window == NULL )
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetKeyCallback(window, key_callback);

	Breakout.Init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	Breakout.State = GAME_ACTIVE;
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//manage user input
		Breakout.ProcessInput(deltaTime);

		//update game stata
		Breakout.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();


		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Breakout.Keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE)
		{
			Breakout.Keys[key] = GL_FALSE;
		}
		
	}
}