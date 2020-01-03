
#include "Model_Loader.h"

//TODO Remove these from global REMINDER: THESE ARE NOT CLEARED WHENEVER A NEW MODEL IS LOADED. THIS NEEDS TO CHANGE
///Vertex Array Objects are objects which contain one or more vertex buffer objects and is designed to store the
///information for a complete rendered object
//enum VAO_IDs { Triangles, Indices, Colours, Tex, NumVAOs = 1 };
/////Vertex Buffer Objects are a method of uploading vertex data for rendering
//enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };
//GLuint  VAOs[NumVAOs];
//GLuint  Buffers[NumBuffers];
//GLuint texture1;

#define BUFFER_OFFSET(a) ((void*)(a))

//Parses a DAE file //TODO
void ParseDAE(ifstream& myFile)
{
	MessageBox(NULL, "DAE file found but not yet supported", "Error", MB_OK);
}
//Parses an FBX file //TODO
void ParseFBX(ifstream& myFile)
{
	MessageBox(NULL, "FBX file found but not yet supported", "Error", MB_OK);
}
//Parses a 3ds file //TODO
void Parse3DS(ifstream& myFile)
{
	MessageBox(NULL, "3DS file found but not yet supported", "Error", MB_OK);
}

//Opens a file by calling the relevant method, based on file extension. //TODO  DAE support
void OpenModel(string path)
{
	ifstream myFile;
	myFile.open(path);
	if (myFile.fail())
	{
		MessageBox(NULL, "An error occured.", "Error", MB_OK);
		cin >> path;
		OpenModel(path);
	}
	//Get everything after the last . which should give the filetype
	string fileType = path.substr(path.find_last_of(".") + 1);

	//If input is an obj file, call this method
	if (fileType == "obj")
	{
		Mesh mesh = ParseObj(path);
		mesh.DrawMesh(mesh.vertices,mesh.uvs,mesh.normals);
	}
	//Else if input is a dae file, call this method
	else if (fileType == "dae")
	{
		ParseDAE(myFile);
	}
	//Else if input is an fbx file, call this method
	else if (fileType == "fbx")
	{
		ParseFBX(myFile);
	}
	//Else if input is a 3ds file, call this method
	else if (fileType == "3ds")
	{
		Parse3DS(myFile);
	}
	//Else assume the file was mistakenly added
	else
	{
		MessageBox(NULL, "File format unknown.", "Error", MB_OK);
	}
	myFile.close();
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
		
	}
}

//Loads a texture
void loadTexture(GLuint &texture, std::string texturepath)
{
	// load and create a texture 
// -------------------------

//// texture 1
//// ---------
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	GLint width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
}

// Displaying models is handled here.
void Display()
{
	Colour col = RGBtoFloat(185, 60, 60, 255);
	static const float background[4] = { col.r, col.g, col.b, col.a };
	//Sets the clear colour - Requires the colour as a value between 0 and 1 as a float, RGBtoFloat is used to simplify that process
	//glClearBufferfv(GL_COLOR, 0, background);
	//Clears all colour
	//glClear(GL_COLOR_BUFFER_BIT);
	//// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//glBindVertexArray(VAOs[Triangles]);
	////glBindTexture(GL_TEXTURE_2D, texture1);
	//glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
}
void init(void) {


	//glGenVertexArrays(NumVAOs, VAOs);
	//glBindVertexArray(VAOs[Triangles]);

	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "Media/Triangles/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "Media/Triangles/triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint shader;
	shader = LoadShaders(shaders);
	//Sets the given object as the shader program to use.
	//Parameters:
	//GLuint Program - The shader program to use.
	glUseProgram(shader);



	//glGenBuffers(NumBuffers, Buffers);
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vector<GLfloat>) * vertices.size(), &vertices[0][0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vector<GLuint>) * indices.size(), &indices[0][0], GL_STATIC_DRAW);

	//glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	////Texture Binding
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[Tex]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vector<GLfloat>) * texture_coords.size(), &texture_coords, GL_STATIC_DRAW);
	//glVertexAttribPointer(tPosition, 2, GL_FLOAT,
	//	GL_FALSE, 0, BUFFER_OFFSET(0));

	// creating the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));

	// creating the view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

	// creating the projection matrix
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 0.0f);

	// Adding all matrices up to create combined matrix
	glm::mat4 mvp = projection * view * model;

	//adding the Uniform to the shader
	int mvpLoc = glGetUniformLocation(shader, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	//glEnableVertexAttribArray(vPosition);
	//glEnableVertexAttribArray(cPosition);
	//glEnableVertexAttribArray(tPosition);
}

//Initialises GLFW and opens the GLFW window. Sets the callback for user input.
GLFWwindow* GLFWInit() {
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

		return window;
}



