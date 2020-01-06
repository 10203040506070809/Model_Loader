#pragma once;

#include <glm/glm.hpp> //includes GLM
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace glm;




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
		#define BUFFER_OFFSET(a) ((void*)(a))

	///Vertex Buffer Objects are a method of uploading vertex data for rendering
	vector<vec3> vertices;
	vector<vec2> texture_coords;
	vector<vec3> normals;
	vector<vec3> faces;
	string texturePath;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint texture1;
	GLuint textureID;

	//Sets up the mesh
	void SetupMesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<vec3> faces, GLuint shader)
	{
		LoadTexture(texture1, texturePath);
		glUniform1i(glGetUniformLocation(shader, "texture1"), 0);


		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	}

	void DrawMesh(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<vec3> faces , int counter)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		//// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(textureID, 0);



		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		
	}

	void LoadTexture(GLuint &texture, string texturepath)
	{

	}
};

vector<string> SplitString(const string &s, char delimiter);

Colour RGBtoFloat(float r, float g, float b, float a);