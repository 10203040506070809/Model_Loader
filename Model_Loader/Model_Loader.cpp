#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

vector<Mesh> objectsToRender;
mat4 model;
mat4 view;
mat4 projection;
GLuint shader;
GLfloat scrollDistance = -300;
GLfloat posX = 0;
GLfloat posY = 0;
Colour col = RGBtoFloat(224, 224, 224, 255);
vec3 modelScale = { 1.0f, 1.0f, 1.0f };
GLfloat rotSpeed = 1;
GLfloat rot = 0;
vec3 rotDir = { 1.0f,1.0f,1.0f };
//vec3 
#define BUFFER_OFFSET(a) ((void*)(a))

void ShowFPS();

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
		MessageBox(NULL, "An error occured while trying to load the file.", "Error", MB_OK);
		OpenModel(path);
	}
	//Get everything after the last . which should give the filetype
	string fileType = path.substr(path.find_last_of(".") + 1);

	//If input is an obj file, call this method
	if (fileType == "obj")
	{
		Mesh mesh = ParseObj(path);
		mesh.SetupMesh(mesh.vertices, mesh.texture_coords, mesh.normals, mesh.faces, shader);
		objectsToRender.push_back(mesh);
	
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
void CheckForKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
	///87 = w
	///68 = d 
	///83 = s
	///65 = a
	///Use GLFW_PRESS to capture a single event
	switch (key) {

	case GLFW_KEY_W:
		//if (action == GLFW_PRESS)
			scrollDistance += 1;
		break;
	case GLFW_KEY_D:
		posX += 1;
		break;
	case GLFW_KEY_S:
			scrollDistance -= 1;
		break;
	case GLFW_KEY_A:
		posX -= 1;
		break;
	case GLFW_KEY_Q:
		exit(0);
		break;

	case GLFW_KEY_SPACE:
			posY += 1;
			break;
	case GLFW_KEY_BACKSPACE:
		posY -= 1;
		break;
	case GLFW_KEY_1:
		modelScale = { 1.0f, 1.0f, 1.0f };
		break;
	case GLFW_KEY_2:
		modelScale = { 2.0f, 2.0f, 2.0f };
		break;
	case GLFW_KEY_3:
		modelScale = { 3.0f, 3.0f, 3.0f };
		break;
	case GLFW_KEY_4:
		modelScale = { 4.0f, 4.0f, 4.0f };
		break;
	case GLFW_KEY_UP:

		rotDir.x = 1;
		rotDir.y = 0;

		rot = rot + (rotSpeed * -5);
		break;
	case GLFW_KEY_DOWN:
		rotDir.x = 1;
		rotDir.y = 0;
		rot = rot + (rotSpeed * 5);

		break;
	case GLFW_KEY_LEFT:
		rotDir.y = 1;
		rotDir.x = 0;

		rot = rot + (rotSpeed * -5);
		break;
	case GLFW_KEY_RIGHT:
		rotDir.y = 1;
		rotDir.x = 0;
		rot = rot + (rotSpeed * 5);

		break;
	default:

		break;
	}
}

void CheckForMouseInput(GLFWwindow *window, int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		
		
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
	
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_REPEAT)
	{

	}
}

void CheckForMouseWheel(GLFWwindow* window, double xOffset, double yOffset)
{
	if (yOffset > 0)
		scrollDistance += 5;
	else 
		scrollDistance -= 5;
}

// Displaying models is handled here.
void Display(GLfloat delta)
{
	
	 float background[4] = { col.r, col.g, col.b, col.a };
	//Sets the background colour - Requires the colour as a value between 0 and 1 as a float, RGBtoFloat is used to simplify that process
	glClearBufferfv(GL_COLOR, 0, background);

	glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	int counter = 0;
	//draw all meshes in scene
	for (Mesh x : objectsToRender)
	{
		glPushMatrix();
		x.DrawMesh(x.vertices,x.texture_coords,x.normals, x.faces, counter);
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(1.0f, 0.0f, 0.0f);
		
		counter++;
		glPopMatrix();
	}

	// creating the model matrix - Note to self: opengl camera doesn't move, the world moves around it

	// creating the model matrix
	mat4 model = mat4(1.0f);
	model = scale(model, vec3(modelScale));
	model = rotate(model, radians(rot), vec3(rotDir.x, rotDir.y, 0.0f));
	//model = translate(model, vec3(0.0f, 0.0f, 0.0f));
	// creating the view matrix
	mat4 view = mat4(1.0f);
	view = translate(view, glm::vec3(posX, posY, scrollDistance));

	// creating the projection matrix (fov, screen ratio of 4:3, camera view range 0.1-500)
	mat4 projection = perspective(45.0f, 4.0f / 3, 0.1f, 500.0f);

	// Adding all matrices up to create combined matrix
	mat4 mvp = projection * view * model;


	//adding the Uniform to the shader
	int mvpLoc = glGetUniformLocation(shader, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}

void init(void) {

	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "Media/Triangles/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "Media/Triangles/triangles.frag" },
		{ GL_NONE, NULL }
	};
	//error here
	shader = LoadShaders(shaders);
	//Sets the given object as the shader program to use.
	//Parameters:
	//GLuint Program - The shader program to use.
	glUseProgram(shader);

}

//Initialises GLFW and opens the GLFW window. Sets the callback for user input.
GLFWwindow* GLFWInit(RECT rect) {
		//Initialises glfw
		glfwInit();

		//Creates a window of a determined size with a title
		GLFWwindow* window = glfwCreateWindow(rect.right, rect.bottom, "Scene View", NULL, NULL);
		//Make the window the currently highlighted window
		glfwMakeContextCurrent(window);
		//Initialises glew
		glewExperimental = GL_TRUE;
		GLenum initOkay = glewInit();
		if (GLEW_OK != initOkay)
		{
			MessageBox(NULL, "Glew has encountered an error and must close.", "Fatal Error", MB_OK);
			exit(0);
		}
		init();
		//Sets the window that receives key callback and the method that is called
		glfwSetKeyCallback(window, CheckForKeyboardInput);
		glfwSetScrollCallback(window, CheckForMouseWheel);
		glfwSetMouseButtonCallback(window, CheckForMouseInput);
		return window;
}

void SetBackgroundColour(float r, float g, float b, float a)
{
	col = RGBtoFloat(r, g, b, a);
}
