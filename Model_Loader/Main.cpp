#include "GUI.h"
#include <GLFW/glfw3native.h>
int MainLoop(HWND ParentWindow, GLFWwindow*);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{

	HWND ParentWindow = GUIinit(hInst, hPrevInst, args, ncmdshow);

	
	//Initialises GLFW once the file is opened.
	GLFWwindow* window = GLFWInit();
	HWND OpenGLWindow = glfwGetWin32Window(window);
	SetParent(OpenGLWindow, ParentWindow);
	//SetWindowLongA(hWnd, GWL_STYLE, WS_BORDER);
	//SetWindowLong(hWnd, GWL_STYLE, WS_BORDER | WS_THICKFRAME);
	ShowWindow(OpenGLWindow, SW_SHOWMAXIMIZED);
	UpdateWindow(OpenGLWindow);
	MainLoop(ParentWindow, window);
}


//Main program loop
int MainLoop(HWND ParentWindow, GLFWwindow* openglWindow) 
{
	MSG msg = { 0 };
	GLfloat timer = 0.0f;
	while (GetMessage(&msg, NULL, NULL, NULL) || (!glfwWindowShouldClose(openglWindow)))
	{
		//=======GUI Functions==========
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//=======openGL functions=======
		Display();
		glfwSwapBuffers(openglWindow);
		glfwPollEvents();
	

	
	}

	//Otherwise close the opengl window
	glfwDestroyWindow(openglWindow);
	glfwTerminate();
	DestroyWindow(ParentWindow);
	return 0;
}