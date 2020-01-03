#include "Obj_Loader.h"

Mesh ParseObj(string path)
{
	Mesh mesh;
	vector<vec3> temp_vertices;
	vector<vec2> temp_uvs;
	vector<vec3> temp_normals;

	vector<unsigned int> vertexIndices, uvIndices, normalIndices;

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

				//========original implementation=========

				//vector<GLfloat> vertex;
				//vector<string> words = SplitString(line, ' ');
				////Can ignore the first point since it's v
				////string 1 is the first data point
				////string 2 is the second data point
				////string 3 is the third data point
				////Make vertex vector
				////Adds the three float values to a vector, e.g in the creeper.obj, the first vertex is 0.5, -0.5, -0.5. 
				////x = 0.5, y = - 0.5 z = -0.5
				////It would push back 0.5, then -0.5, then -0.5.
				//vertex.push_back(stof(words[1]));
				//vertex.push_back(stof(words[2]));
				//vertex.push_back(stof(words[3]));
				////This is then added to a vector
				//vertices.push_back(vertex);		

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

				//=======original implementation=========

			   //vector<GLfloat> texture;

			   //vector<string> words = SplitString(line, ' ');
			   ////Can ignore the first point since it's v
			   ////string 1(i=0) is the first point
			   ////string 2(i=1) is the second point
			   ////string 3(i=2) is the third point
			   //texture.push_back(stof(words[1]));
			   //texture.push_back(stof(words[2]));
			   ////Make texture vector

			   //texture_coords.push_back(texture);

			   //======new implementation======

				vec2 uv;

				vector<string> words = SplitString(line, ' ');
				uv.x = stof(words[1]);
				uv.y = stof(words[2]);

				temp_uvs.push_back(uv);

			}
			//Vertex normals - If the line starts with vn, we know the following three values are normals for each vertex
			else if (firstWord == "vn")
			{
				//=======original implementation======

				//vector<GLfloat> normal;
				//vector<string> words = SplitString(line, ' ');
				////Can ignore the first point since it's vn
				////string 1 is the first point
				////string 2 is the second point
				////string 3 is the third point
				////Make vertex vector
				//normal.push_back(stof(words[1]));
				//normal.push_back(stof(words[2]));
				//normal.push_back(stof(words[3]));
				////Make normal vector
				//normals.push_back(normal);

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

				//=======old implementation========

				//if obj uses tris and has three face vectors. //TODO
				//if (words.size() == 4) {
				//	
				//	vector<GLfloat> vIndices;
				//	vector<GLuint> tIndices;
				//	vector<GLfloat> nIndices;

				//	for (size_t i = 1; i < words.size(); i++)
				//	{
				//		//Splits the value of each part of words(x/x/x) by /, giving you three values of v, vt and vn
				//		vector<string> faces = SplitString(words[i], '/');

				//		
				//		for (size_t j = 0; j < faces.size(); j++)
				//		{
				//			vIndices.push_back(stof(faces[0]));
				//			tIndices.push_back(stoul(faces[1]));
				//			nIndices.push_back(stof(faces[2]));
				//		}

				//	}

				//}
				////If obj uses quads
				//else if (words.size() == 5) {

				//	vector<vector<string>> faceValues;
				//	vector<vector<GLuint>> faceV;
				//	for (size_t i = 1; i < words.size(); i++)
				//	{
				//		//Splits the value of each part of words(x/x/x) by /, giving you three values of v, vt and vn
				//		vector<string> faces = SplitString(words[i], '/');
				//		//After the line has been read, this should have vectors of all faces
				//		faceValues.push_back(faces);
				//	}
				//	//Convert each value to a float
				//	for(vector<string> x : faceValues)
				//	{
				//		vector<GLuint> fv;
				//		for (size_t i = 0; i < x.size(); i++)
				//		{
				//			//0 based index
				//			
				//			fv.push_back(stoul(x[i]) - 1);
				//		}
				//		//this is the face, indexed to 0 and converted to GLuint
				//		faceV.push_back(fv);
				//	}
				//	//Push the faces in the order: 0,1,2 0,2,3 - Converts polys to tris.
				//	vector <GLuint> vertIndex;
				//	vector <GLfloat> texIndex;
				//	vector <GLfloat> normIndex;

				//	//Get every vertices point from the face and add it to vertIndex
				//	for (size_t i = 0; i < faceV.size(); i++)
				//	{
				//		vertIndex.push_back(faceV[i][0]);
				//		texIndex.push_back(faceV[i][1]);
				//		normIndex.push_back(faceV[i][2]);
				//	}
				//	vector <GLuint> temp;
				//	temp.push_back(vertIndex[0]);
				//	temp.push_back(vertIndex[1]);
				//	temp.push_back(vertIndex[2]);
				//	indices.push_back(temp);
				//	temp.clear();
				//	temp.push_back(vertIndex[0]);
				//	temp.push_back(vertIndex[2]);
				//	temp.push_back(vertIndex[3]);
				//	indices.push_back(temp);
				//	temp.clear();
				//}
				//else {
				//	cout << "This model loader doesn't support this n-gon. You have " << words.size() << " number of vertexes within this face.";
				//	break;
				//} 

				//========new implementation========

			}
			//If the first word is mtllib, we know the part after this is the material library.
			else if (firstWord == "mtllib")
			{
				//========old implementation========

				//Splits the string at each whitespaces
				//vector<string> words = SplitString(line, ' ');
				////Gets the second element in the vector
				//string textureName = words[1];	
				//string texPath = path.substr(0, path.find_last_of("/")) + "/" + textureName;
				//
				//ifstream texFile(texPath, std::ios::binary);

				//if (texFile.is_open()) 
				//{
				//	while (!texFile.eof()) 
				//	{
				//		getline(texFile, line);
				//		if (line.substr(0, line.find(" ")) == "map_Kd") {
				//			vector<string> words = SplitString(line, ' ');
				//			//Got the name of the texture within the address of the model
				//			string texName = words[1];
				//		}
				//	}
				//	
				//}

				//========new implementation========

			}
		}
		mesh.vertices = temp_vertices;
		mesh.uvs = temp_uvs;
		mesh.normals = temp_normals;
		myFile.close();

		return mesh;
	}
}

