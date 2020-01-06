#include "GUI.h"
#include <GLFW/glfw3native.h>
int MainLoop(HWND ParentWindow, GLFWwindow*);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{

	HWND ParentWindow = GUIinit(hInst, hPrevInst, args, ncmdshow);

	ShowWindow(ParentWindow, SW_SHOWMAXIMIZED);
	//Initialises GLFW once the file is opened.
	RECT rect;
	if (GetWindowRect(ParentWindow, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
	}
	

	GLFWwindow* window = GLFWInit(rect);
	HWND OpenGLWindow = glfwGetWin32Window(window);
	SetParent(OpenGLWindow, ParentWindow);
	//SetWindowLongA(hWnd, GWL_STYLE, WS_BORDER);
	SetWindowLong(OpenGLWindow, GWL_STYLE, WS_BORDER);
	ShowWindow(OpenGLWindow, SW_SHOWMAXIMIZED);
	UpdateWindow(OpenGLWindow);
	MainLoop(ParentWindow, window);
}


//Main program loop
int MainLoop(HWND ParentWindow, GLFWwindow* openglWindow) 
{
	MSG msg = { 0 };
	GLfloat timer = 0.0f;
	///Had to switch this around - For some reason, having GetMessage first made the cube only rotate when the mouse was moving.
	///I'm guessing this is due to mouse movement being a message and it being something to do with evaluating that operand first
	///And ignoring the second
	while ((!glfwWindowShouldClose(openglWindow)) || GetMessage(&msg, NULL, NULL, NULL))
	{
		//=======GUI Functions==========
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//=======openGL functions=======
		Display(timer);
		glfwSwapBuffers(openglWindow);
		glfwPollEvents();
	
		timer = timer + 0.1;
	
	}

	//Otherwise close the opengl window
	glfwDestroyWindow(openglWindow);
	glfwTerminate();
	DestroyWindow(ParentWindow);
	return 0;
}