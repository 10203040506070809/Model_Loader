#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "Utilities.h"
#include "LoadShaders.h"
#include "stb_image.h"
#include "Obj_Loader.h"
#define STB_IMAGE_IMPLEMENTATION



#ifndef ML_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ML_H


 

void OpenModel(string path);
GLFWwindow* GLFWInit();
void Display();
#endif