#include "GUI.h"
#include "Model_Loader.h"

int MainLoop(GLFWwindow*);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{

	//Calls the OpenFile method


	HWND ParentWindow = GUIinit(hInst, hPrevInst, args, ncmdshow);

	
	//Initialises GLFW once the file is opened.
	GLFWwindow* window = GLFWInit();
	HWND hWnd = glfwGetWin32Window(window);
	SetWindowLongA(hWnd, GWL_STYLE, WS_BORDER);

	SetParent(hWnd, ParentWindow);
	UpdateWindow(hWnd);
	MainLoop(window);
}


//Main program loop
int MainLoop(GLFWwindow* window) 

{
	MSG msg = { 0 };
	GLfloat timer = 0.0f;
	while (GetMessage(&msg, NULL, NULL, NULL) || (!glfwWindowShouldClose(window)))
	{
		//=======GUI Functions==========
		TranslateMessage(&msg);
		DispatchMessage(&msg);


		//=======openGL functions=======
		Display(timer);
		glfwSwapBuffers(window);
		glfwPollEvents();
		timer += 0.1f;
	}

	//Otherwise close the window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}