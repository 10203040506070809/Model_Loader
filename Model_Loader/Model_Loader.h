#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32

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
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <GLFW/glfw3native.h>

using namespace std;
using namespace glm;

#ifndef ML_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ML_H
 

void OpenModel(std::string path);
GLFWwindow* GLFWInit();
void Display(GLfloat delta);
#endif