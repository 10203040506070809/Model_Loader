#pragma once

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include "Utilities.h"
#include "LoadShaders.h"
#include "Obj_Loader.h"
#include "Controls.h"





 

void OpenModel(string path);
GLFWwindow* GLFWInit(RECT rect);
void Display(GLfloat delta);
void SetBackgroundColour(float r, float g, float b, float a);