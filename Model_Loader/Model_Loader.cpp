// Model_Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <glm/glm.hpp> //includes GLM
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

//TODO Remove these from global
///Vertex Array Objects are objects which contain one or more vertex buffer objects and is designed to store the
///information for a complete rendered object
enum VAO_IDs {Model, NumVAOs = 1 };
///Vertex Buffer Objects are a method of uploading vertex data for rendering
enum Buffer_IDs { Triangles, Colours, Normals, Textures, Indices, ArrayBuffer, NumBuffers = 6 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
GLuint texture1;
GLuint shader;

#define BUFFER_OFFSET(a) ((void*)(a))

vector<vec3> out_vertices;
vector<vec2> out_uvs;
vector<vec3> out_normals;
vector<GLuint> vertexIndices, uvIndices, normalIndices;
vector<vec3> vertices;
vector<vec2> texture_coords;
vector<vec3> normals;
vector<vec3> indices;
//Splits strings into a vector of strings and returns it.
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
void ParseObj(ifstream& myFile, string path)
{
	string line;
	
	if (myFile.is_open())
	{
		//clear all vectors here
		while (!myFile.eof())
		{
			getline(myFile, line);
			//First word in any given line.
			string firstWord = line.substr(0, line.find(" "));

			//# is a comment - Ignore
			if (firstWord == "#") {

			}
			//Geometric vertices of models start with V in OBJ files - If the line starts with V, we know the following three values are vertex positions
			else if (firstWord == "v")
			{
				glm::vec3 vertex;
				vector<string> words = SplitString(line, ' ');
				//Can ignore the first point since it's v
				//string 1 is the first data point
				//string 2 is the second data point
				//string 3 is the third data point
				//Make vertex vector
				//Adds the three float values to a vector, e.g in the creeper.obj, the first vertex is 0.5, -0.5, -0.5. 
				//x = 0.5, y = - 0.5 z = -0.5
				//It would push back 0.5, then -0.5, then -0.5.
				vertex.x = stof(words[1]);
				vertex.y = stof(words[2]);
				vertex.z = stof(words[3]);
				//This is then added to a vector
				vertices.push_back(vertex);		

			}
			//Texture vertices of models start with vt in OBJ files - If the line starts with vt, we know the following two values are texture coordinates
			else if (firstWord == "vt")
			{
				glm::vec2 texture;

				vector<string> words = SplitString(line, ' ');
				//Can ignore the first point since it's v
				//string 1(i=0) is the first point
				//string 2(i=1) is the second point
				//string 3(i=2) is the third point
				texture.x = stof(words[1]);
				texture.y = stof(words[2]);
				texture_coords.push_back(texture);
				//Make texture vector

			
			}
			//Vertex normals - If the line starts with vn, we know the following three values are normals for each vertex
			else if (firstWord == "vn")
			{
				glm::vec3 normal;
				vector<string> words = SplitString(line, ' ');
				//Can ignore the first point since it's vn
				//string 1 is the first point
				//string 2 is the second point
				//string 3 is the third point
				//Make vertex vector
				normal.x = stof(words[1]);
				normal.y = stof(words[2]);
				normal.z = stof(words[3]);
				//Make normal vector
				normals.push_back(normal);
			}
			//Gets the name of the object - Not currently used.
			else if (firstWord == "o")
			{

			}
			//Material name - ignore 
			else if (firstWord == "usemtl") 
			{

			}
			//Smoothing group - ignore
			else if (firstWord == "s")
			{

			}
			//Face of the model - If the line starts with f, we know the following values are faces. 
			//The first three values,
			//f V1 / VT1 / VN1 V2 / VT2 / VN2 V3 / VT3 / VN3 V4 / VT4 / VN4
			//i.e x/x/x describe a vertex of a triangle. I.E, for the creeper, the first value is 1/1/1 
			//The first number is which vertex to use, since this is 1 it's the first vertex
			//The second number is which texture coordinate to use, which since it's 1, it's the first vt
			//The third number is which normal to use, since this is 1, it's the first vn
			//Since obj's are usually shown as quads, 
			//vertices are going to be at index 0, 1 and 2 then 0,2,3 because the quad is split into two tri's
			//3------ - 2     0 1 2 3 as quad
			//|      /|		  0 1 2 as first tri
			//|    /  |		  0 2 3 as second tri
			//|  /    |
			//|/      |
			//0------ - 1
			
			else if(firstWord == "f")
			{
				//We can check if the face is split into quads or if it's been exported as a tri by checking how many elements are inside of words. 
				//If there's a quad there should be 4 elements, however as the firstWord 'f' hasn't been omitted, there will be 5 for a quad.
				vector<string> words = SplitString(line, ' ');

				//if obj uses tris and has three face vectors. //TODO
				if (words.size() == 4) {
					
					for (size_t i = 1; i < words.size(); i++)
					{
						//vector<string> faces = SplitString(words[i], '/');
						//vertexIndices.push_back(stoul(faces[0]));
						//uvIndices.push_back(stoul(faces[1]));
						//normalIndices.push_back(stoul(faces[2]));
					}
	
				}
				//If obj uses quads
				else if (words.size() == 5) {
				
					for (size_t i = 1; i < words.size(); i++)
					{
						
						//Splits the value of each part of words(x/x/x) by /, giving you three values of v, vt and vn
						vector<string> faces = SplitString(words[i], '/');

					}
				}
				else {
					cout << "This model loader doesn't support this n-gon. You have " << words.size() << " number of vertexes within this face.";
					break;
				} 
			}
			//If the first word is mtllib, we know the part after this is the material library.
			else if (firstWord == "mtllib")
			{   //Splits the string at each whitespace
				vector<string> words = SplitString(line, ' ');
				//Gets the second element in the vector
				string textureName = words[1];	

				//
				string texPath = path.substr(0, path.find_last_of("/")) + "/" + textureName;
				
				ifstream texFile(texPath, std::ios::binary);
			
				if (texFile.is_open()) 
				{
					while (!texFile.eof()) 
					{
						getline(texFile, line);
						if (line.substr(0, line.find(" ")) == "map_Kd") {
							vector<string> words = SplitString(line, ' ');
							//Got the name of the texture within the address of the model
							string texName = words[1];
						}
					}
					
				}
			}
		}

		myFile.close();
	}
}
//Parses a DAE file //TODO
void ParseDAE(ifstream& myFile)
{
	cout << "DAE found";
}

void OpenFile(string path)
{
	if (path == "debug") {
		path = "Media/Models/Creeper.obj";
		cout << "debug mode activated : Creeper.obj loading...";
	}
	ifstream myFile(path, std::ios::binary);
	//Get everything after the last . which should give the filetype
	string fileType = path.substr(path.find_last_of(".") + 1);
	//If input is an obj file, call this method
	if (fileType == "obj")
	{
		ParseObj(myFile, path);
	}
	//Else if input is a dae file, call this method
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

//Checks for user input, like quitting and moving inside the scene.
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

// Displaying models is handled here.
void Display(GLfloat delta)
{
	//Displays a pure white background
	static const float background[] = { 255.0f, 255.0f, 255.0f, 255.0f };
	//Displays a pure black background
	static const float black[] = { 0.0f, 0.0f, 0.f, 0.0f };

	//Sets the clear colour
	glClearBufferfv(GL_COLOR, 0, background);
	//Fills all colours with the above colour
	glClear(GL_COLOR_BUFFER_BIT);
	// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

}
void init(void) {

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Model]);

	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "Media/Triangles/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "Media/Triangles/triangles.frag" },
		{ GL_NONE, NULL }
	};

	shader = LoadShaders(shaders);
	//Sets the given object as the shader program to use.
	//Parameters:
	//GLuint Program - The shader program to use.
	glUseProgram(shader);

}
//Initialises GLFW and opens the GLFW window. Sets the callback for user input.
void GLFWInit() {
		//Initialises glfw
		glfwInit();
		//Creates a window of a determined size with a title
		GLFWwindow* window = glfwCreateWindow(800, 600, "Scene View", NULL, NULL);
		//Make the window the currently highlighted window
		glfwMakeContextCurrent(window);
		//Initialises glew
		glewInit();
		init();
		//Sets the window that receives key callback and the method that is called
		glfwSetKeyCallback(window, checkForInput);

		//While the window is open, repeat these functions
		GLfloat timer = 0.0f;
		while (!glfwWindowShouldClose(window))
		{			
			Display(timer);
			glfwSwapBuffers(window);
			glfwPollEvents();		
			timer += 0.1f;
		}
		//Otherwise close the window
		glfwDestroyWindow(window);
		glfwTerminate();
}

//Main function
int main(int argc, char** argv)
{
	string path;
	cout << "Paste the path to your model here, including the name. \n  Type 'debug' to open a default file. \n";
	cin >> path;
	//Calls the OpenFile method
	OpenFile(path);

	//Initialises GLFW once the file is opened.
	GLFWInit();
	
}




