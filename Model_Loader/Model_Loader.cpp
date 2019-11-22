// Model_Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp> //includes GLM
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitString(const string &s, char delimiter) 
{
	vector<string> words;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delimiter)) {
		words.push_back(item);
	}

	return words;
}

void LoadObj()
{

}
void ParseObj(ifstream& myFile)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_textures;
	std::vector< glm::vec3 > temp_normals;

	string line;
	
	if (myFile.is_open())
	{
		while (!myFile.eof())
		{

			

			getline(myFile, line);
			string firstWord = line.substr(0, line.find(" "));

			///Vertex of models start with V in OBJ files - If the line starts with V, we know the following three values are vertex positions
			if (firstWord == "v")
			{
				glm::vec3 vertex;
				vector<string> words = SplitString(line, ' ');
				///Can ignore the first point since it's v
				///string 1 is the first point
				///string 2 is the second point
				///string 3 is the third point
				///Make vertex vector

				vertex.x = stof(words[1]);
				vertex.y = stof(words[2]);
				vertex.z = stof(words[3]);
				
				temp_vertices.push_back(vertex);


			}
			///Texture coordinates of models start with vt in OBJ files - If the line starts with vt, we know the following two values are texture coordinates
			else if (firstWord == "vt")
			{
				glm::vec2 texture;

				vector<string> words = SplitString(line, ' ');
				///Can ignore the first point since it's v
				///string 1 is the first point
				///string 2 is the second point
				///string 3 is the third point

				texture.x = stof(words[1]);
				texture.y = stof(words[2]);

				temp_textures.push_back(texture);
				///Make texture vector
			}
			///Normal of one vertex - If the line starts with vn, we know the following three values are normals for each vertex
			else if (firstWord == "vn")
			{
				glm::vec3 normal;
				vector<string> words = SplitString(line, ' ');
				///Can ignore the first point since it's v
				///string 1 is the first point
				///string 2 is the second point
				///string 3 is the third point
				///Make vertex vector

				normal.x = stof(words[1]);
				normal.y = stof(words[2]);
				normal.z = stof(words[3]);

				///Make normal vector
				temp_normals.push_back(normal);
			}
			///Face of the model - If the line starts with f, we know the following values are faces. 
			else if(firstWord == "f")
			{
				//vector<string> words = SplitString(line, ' ');

				//for (int i = 1; i < words.size; i++)
				//{
				//	words[i];
				//}
			}
			///If the first word is mtllib, we know the part after this is the material file.
			else if (firstWord == "mtllib")
			{   ///Splits the string at each whitespace
				vector<string> words = SplitString(line, ' ');
				///Gets the second element in the vector
				string textureName = words[1];
				
			}
		}
		///Close the filestream
		myFile.close();
	}


}

void ParseDAE(ifstream& myFile)
{
	cout << "DAE found";
}

///Opens a file by calling the relevant method, based on file extension
void OpenFile(string path)
{
	if (path == "debug") {
		path = "media/Creeper.obj";
		cout << "debug mode activated : Creeper.obj loading...";
	}
	ifstream myFile(path, std::ios::binary);
	///Get everything after the last . which should give the filetype
	string fileType = path.substr(path.find_last_of(".") + 1);
	///If input is an obj file, call this method
	if (fileType == "obj")
	{
		ParseObj(myFile);
	}
	///Else if input is a dae file, call this method
	else if (fileType == "dae")
	{
		ParseDAE(myFile);
	}
	else
	{
		cout << "File format unknown.";
		cout << "Paste the path to your model here, including the name. \n  Type 'debug' to open a default file. \n";
		cin >> path;
		OpenFile(path);
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
	///Displays a pure white background
	static const float background[] = { 125.0f, 125.0f, 125.0f, 255.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	


}
///Passing void as a parameter makes certain the compiler knows NOTHING can be passed as a parameter. In default C, not having this means anything can be passed.
void init(void) {


	///Deal with shaders here
}
///
void GLFWInit() {

		///Initialises glfw
		glfwInit();
		///Creates a window of a determined size with a title
		GLFWwindow* window = glfwCreateWindow(800, 600, "Scene View", NULL, NULL);
		///Make the window the currently highlighted window
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
int main(void)
{
	string path;
	cout << "Paste the path to your model here, including the name. \n  Type 'debug' to open a default file. \n";
	cin >> path;
	///Test method call
	OpenFile(path);

	///Initialise GLFW Window
	GLFWInit();
	
}


