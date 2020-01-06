#include "Obj_Loader.h"

Mesh ParseObj(string path)
{
	Mesh mesh;

	vector<vec3> out_vertices;
	vector<vec2> out_texture_coords;
	vector<vec3> out_faces;
	vector<vec3> out_normals;


	vector<vec3> temp_vertices;
	vector<vec2> temp_textures;
	vector<vec3> temp_faces;
	vector<vec3> temp_normals;


	vector<unsigned int> vertexIndices, texIndices, normalIndices;

	//vertices, texture_coords, normals, indices.size = 0;
	ifstream myFile;
	myFile.open(path);
	string line;
	//myFile.open(path);
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
				
				//==========new implementation======

				vec3 vertex;

				vector<string> words = SplitString(line, ' ');

				vertex.x = stof(words[1]);
				vertex.y = stof(words[2]);
				vertex.z = stof(words[3]);

				temp_vertices.push_back(vertex);
			}
			//Texture vertices of models start with vt in OBJ files - If the line starts with vt, we know the following two values are texture coordinates
			else if (firstWord == "vt")
			{

			   //======new implementation======

				vec2 tex;

				vector<string> words = SplitString(line, ' ');
				tex.x = stof(words[1]);
				tex.y = stof(words[2]);

				temp_textures.push_back(tex);

			}
			//Vertex normals - If the line starts with vn, we know the following three values are normals for each vertex
			else if (firstWord == "vn")
			{

				//======new implementation========

				vec3 normals;

				vector<string> words = SplitString(line, ' ');

				normals.x = stof(words[1]);
				normals.y = stof(words[2]);
				normals.z = stof(words[3]);

				temp_normals.push_back(normals);
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

			else if (firstWord == "f")
			{
				//We can check if the face is split into quads or if it's been exported as a tri by checking how many elements are inside of words. 
				//If there's a quad there should be 4 elements, however as the firstWord 'f' hasn't been omitted, there will be 5 for a quad.
				vector<string> words = SplitString(line, ' ');

				//======new implementation==============
				if (words.size() == 4)
				{
					unsigned int vertexIndex[3], texIndex[3], normalIndex[3];
					vector<string> faces;
					for (size_t i = 1; i < words.size(); i++)
					{
						//Splits the value of each part of words(x/x/x) by /, giving you three values of v, vt and vn
						faces = SplitString(words[i], '/');
						vertexIndex[i-1] = stoul(faces[0]);
						texIndex[i-1] = stoul(faces[1]);
						normalIndex[i-1] = stoul(faces[2]);
					}

					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					texIndices.push_back(texIndex[0]);
					texIndices.push_back(texIndex[1]);
					texIndices.push_back(texIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}


				//========new implementation========
				else if(words.size() == 5)
				{
					unsigned int vertexIndex[4], texIndex[4], normalIndex[4];
					vector<string> faces;
					for (size_t i = 1; i < words.size(); i++)
					{
						//Splits the value of each part of words(x/x/x) by /, giving you three values of v, vt and vn
						faces = SplitString(words[i], '/');
						//0 based indexing whereas i starts at 1 because of the f at the beginning of words
						vertexIndex[i - 1] = stoul(faces[0]);
						texIndex[i - 1] = stoul(faces[1]);
						normalIndex[i - 1] = stoul(faces[2]);
					}

					//First 'face' of 012 then second of 023
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					texIndices.push_back(texIndex[0]);
					texIndices.push_back(texIndex[1]);
					texIndices.push_back(texIndex[2]);
					texIndices.push_back(texIndex[0]);
					texIndices.push_back(texIndex[2]);
					texIndices.push_back(texIndex[3]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
				}
			}
			//If the first word is mtllib, we know the part after this is the material library.
			else if (firstWord == "mtllib")
			{

				//Splits the string at each whitespaces
				vector<string> words = SplitString(line, ' ');
				//Gets the second element in the vector
				string textureName = words[1];	
				string test = path;
				string texPath = path.substr(0, path.find_last_of("\\")) + "/" + textureName;
				
				ifstream texFile;
				texFile.open(texPath);
				if (texFile.is_open()) 
				{
					while (!texFile.eof()) 
					{
						getline(texFile, line);
						if (line.substr(0, line.find(" ")) == "map_Kd") {
							vector<string> words = SplitString(line, ' ');
							//Got the name of the texture within the address of the model
							string texName = words[1];
							mesh.texturePath = texName;
						}
					}
					
				}

				texFile.close();
			}
		}
		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int texIndex = texIndices[i];
			unsigned int normalIndex = normalIndices[i];

			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec2 tex = temp_textures[texIndex - 1];
			glm::vec3 normal = temp_normals[normalIndex - 1];
		
			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_texture_coords.push_back(tex);
			out_normals.push_back(normal);

		}

		mesh.vertices = out_vertices;
		mesh.texture_coords = out_texture_coords;
		mesh.normals = out_normals;
		myFile.close();

		return mesh;
	}

}


