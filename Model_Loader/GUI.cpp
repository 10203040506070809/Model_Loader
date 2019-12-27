#include "GUI.h"
#include "Model_Loader.h"
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_SAVE 3
#define FILE_MENU_EXIT 4
#define FILE_MENU_EXPORT 10
#define OPTIONS_MENU_SOLID 5
#define OPTIONS_MENU_WIRE 6
#define HELP_MENU_ABOUT 7
#define HELP_MENU_HELP 8
#define HELP_MENU_GITHUB 9
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
char* OpenFileDialog(HWND);
HMENU hMenu;


HWND GUIinit(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	

	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	//If you don't define this, the window will have no cursor
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hInstance = hInst;

	wc.lpszClassName = L"WindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc)) {
		return NULL;
	}
	HWND ParentWindow = CreateWindowW(L"WindowClass", L"Model Loader", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1200, 800, NULL, NULL, NULL, NULL);

	return ParentWindow;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{
		case FILE_MENU_NEW:

			break;

		case FILE_MENU_OPEN:
			OpenFileDialog(hWnd);
			break;

		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;

		case  OPTIONS_MENU_SOLID:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case OPTIONS_MENU_WIRE:
			// uncomment to draw only wireframe 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case HELP_MENU_ABOUT:

			break;
		case HELP_MENU_HELP:

			break;
		case HELP_MENU_GITHUB:
			ShellExecute(NULL, "open", "https://github.com/10203040506070809/Model_Loader", NULL, NULL, SW_SHOWNORMAL);
			break;
		case FILE_MENU_EXPORT:

			break;
		default:

			break;
		}

		break;

	case WM_CREATE:
		AddMenus(hWnd);
		break;

		//return false and quit application
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);

	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	HMENU hOptionsMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING || MF_CHECKED, FILE_MENU_NEW, "New");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, "Save");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXPORT, "Export");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Quit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	
	AppendMenu(hOptionsMenu, MF_STRING, OPTIONS_MENU_SOLID, "Solid");
	AppendMenu(hOptionsMenu, MF_STRING, OPTIONS_MENU_WIRE, "Wireframe");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptionsMenu, "Options");

	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_ABOUT, "About");
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_HELP, "Help");
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_GITHUB, "Github");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");
	SetMenu(hWnd, hMenu);
}

char* OpenFileDialog(HWND hWnd)
{
	OPENFILENAME ofn;

	char file[100];
	char* path;
	//sets all elements of ofn to 0 
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All Files\0*.*\0Wavefront (.obj)\0*.obj\0Colla (.dae)\0*.dae\0Filmbox (.fbx)\0*.fbx";
	ofn.nFilterIndex = 1;

	 bool isFound = GetOpenFileName(&ofn);

	
	 if (isFound)
	 {
		 path = ofn.lpstrFile;
		 //MessageBox(NULL, path, "Debug", MB_OK);
		 OpenModel(path);

		 return path;
	 }
	 else
	 {
		 MessageBox(NULL, "An error occured. Did you cancel?", "Error", MB_OK);
		 return NULL;
	 }

	 return path;
	 
}