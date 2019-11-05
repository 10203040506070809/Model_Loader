// Model_Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <fstream>

using namespace std;
///Opens a file
void OpenFile(string path) {
	std::string line;
	std::ifstream myFile(path, std::ios::binary);
	if (myFile.is_open())
	{
		GLubyte byte; // is 8bit and maps to char
		while (myFile >> byte)
		{

			std::cout << byte;
			//check and map each byte
			// only read strings if file is in plaintext encoding
		}
		myFile.close();
	}	
}

///Checks for user input, like quitting and moving between files
void checkForInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
	

	if (key == 81) {
		exit(0);
	}
	///Debug method used to check what keycode input is
	else {
		std::cout << key << std::endl;
	}
}

///
void GLFWInit() {
	
		glfwInit();
		GLFWwindow* window = glfwCreateWindow(800, 600, "Scene View", NULL, NULL);
		glfwMakeContextCurrent(window);
		glewInit();
		glfwSetKeyCallback(window, checkForInput);

		while (!glfwWindowShouldClose(window))
		{			
			glfwSwapBuffers(window);
			glfwPollEvents();			
		}
}

///Main function
int main()
{

	std::cout << "Hello World!\n";

	///Initialise GLFW Window
	GLFWInit();

	///Test method call
	OpenFile("media/Creeper.obj");
	
}


