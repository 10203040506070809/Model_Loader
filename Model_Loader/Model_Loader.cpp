// Model_Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

///Opens a file
void OpenFile(string path) {
	string line;
	ifstream myFile(path, std::ios::binary);
	string content;
	if (myFile.is_open())
	{
		GLubyte byte; // is 8bit and maps to char
		while (!myFile.eof())
		{

			GLfloat vertices; 

			getline(myFile, line);
			cout << line + "\n";
			string firstWord = line.substr(0, line.find(" "));

			
			//cout << firstWord;
			///Vertex of models start with V in OBJ files - If the line starts with V, we know the following three values are vertex positions
			if (firstWord == "v")
			{
					///Make vertex vector

				vector<float> vertices;
				//vertices.push_back(stof(line.substr(stof(firstWord), line.find(" "))));
				

			}
			///Texture coordinates of models start with vt in OBJ files - If the line starts with vt, we know the following two values are texture coordinates
			else if (firstWord == "vt")
			{
				cout << "line starting with VT";

				///Make texture vector
			}
			///Normal of one vertex - If the line starts with vn, we know the following three values are normals for each vertex
			else if (firstWord == "vn") 
			{
				cout << "line starting with VN";

				///Make normal vector
			}
			///Debug variable - Holds the entire file line by line
			//content += line + "\n";
			
			//check and map each byte
			// only read strings if file is in plaintext encoding
		}
		//Read content line-by-line
		//cout << content;
		myFile.close();
	}	
}

///Checks for user input, like quitting and moving inside the scene
void checkForInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
	///87 = w
	///68 = d 
	///83 = s
	///65 = a


	///If key = q
	if (key == 81) {
		exit(0);
	}
	///If W is pressed - Move the camera forward
	else  if (key == 87) {

	}
	///If D is pressed - Move the camera right
	else if (key == 68) {

	}
	///If S is pressed - Move the camera back
	else if (key == 83) {

	}
	///If A is pressed - Move the camera left
	else if (key == 65) {

	}
	///Debug method used to check what keycode input is
	else {
		std::cout << key << std::endl;
	}
}

///
void Display() 
{
	static const float background[] = { 125.0f, 125.0f, 125.0f, 255.0f };	glClearBufferfv(GL_COLOR, 0, background);


}

void init() {

}
///
void GLFWInit() {

		///Initialises glfw
		glfwInit();
		///Creates a window of a determined size with a title
		GLFWwindow* window = glfwCreateWindow(800, 600, "Scene View", NULL, NULL);

		glfwMakeContextCurrent(window);
		///Initialises glew
		glewInit();
		init();

		///Sets the window that receives key callback and the method that is called
		glfwSetKeyCallback(window, checkForInput);

		while (!glfwWindowShouldClose(window))
		{			
			Display();
			glfwSwapBuffers(window);
			glfwPollEvents();			
		}

		glfwDestroyWindow(window);
		glfwTerminate();
}

///Main function
int main()
{

	std::cout << "Hello World!\n";

	///Test method call
	OpenFile("media/Creeper.obj");

	///Initialise GLFW Window
	GLFWInit();
	
}


