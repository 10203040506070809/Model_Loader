#include <glm/glm.hpp> //includes GLM
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

#ifndef Utilities    // To make sure you don't declare the function more than once by including the header multiple times.
#define Utilities

//A colour struct following RGBA 
struct Colour
{
	float r;
	float g;
	float b;
	float a;
};

//A struct denoting a mesh to be loaded. Can be Drawn taking in vertices, uvs and normals.
struct Mesh
{
	enum VAO_IDs { Triangles, Indices, Colours, Tex, NumVAOs = 1 };
	///Vertex Buffer Objects are a method of uploading vertex data for rendering
	enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
	enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;
	GLuint VAO_ID;
	GLuint vertexBuffer;
	//Draws the mesh
	void DrawMesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals)
	{
		glGenVertexArrays(1, &VAO_ID);
		glBindVertexArray(VAO_ID);

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	}
	//Loads the texture of the mesh
	void LoadTexture()
	{

	}
};

vector<string> SplitString(const string &s, char delimiter);

Colour RGBtoFloat(float r, float g, float b, float a);

#endif