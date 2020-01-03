
#include "GUI.h"

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_SAVE 3
#define FILE_MENU_EXIT 4
#define FILE_MENU_EXPORT 10
#define OPTIONS_MENU_SOLID 5
#define OPTIONS_MENU_WIRE 6
#define OPTIONS_MENU_DARK 11
#define OPTIONS_MENU_LIGHT 12
#define HELP_MENU_ABOUT 7
#define HELP_MENU_HELP 8
#define HELP_MENU_GITHUB 9

//Max path length for file i/o
#define MAX_PATH_LENGTH 100

//http://tedfelix.com/software/c++-callbacks.html
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void OpenFileDialog(HWND);
HMENU hMenu;

//Creates parent window and initialises message processes
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
	HWND ParentWindow = CreateWindowW(L"WindowClass", L"Model Loader", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 250, 250, 1200, 800, NULL, NULL, NULL, NULL);

	return ParentWindow;
}

//https://docs.microsoft.com/en-gb/previous-versions/windows/desktop/legacy/ms633573(v=vs.85)
//CallWindowProc function - Processes button clicks/events
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		///Button commands
	case WM_COMMAND:

		switch (wp)
		{
			///Occurs when new button is pressed
		case FILE_MENU_NEW:

			break;
			///Occurs when open button is pressed - Opens a new file
		case FILE_MENU_OPEN:
			OpenFileDialog(hWnd);
			break;
			///Occurs when exit button is pressed - Quits application
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
			///Occurs when Solid button is pressed - Renders objects as solid objects
		case  OPTIONS_MENU_SOLID:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
			///Occurs when wire option is pressed - Renders objects as wireframe
		case OPTIONS_MENU_WIRE:
			// uncomment to draw only wireframe 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
			///Occurs when about option is pressed - Shows an about message prompt
		case HELP_MENU_ABOUT:
			MessageBox(NULL, "Created by Jack Fletcher", "About", MB_OK);
			break;
			///Occurs when help option is pressed - Opens the readme for the project
		case HELP_MENU_HELP:
			ShellExecute(NULL, "open", "https://github.com/10203040506070809/Model_Loader/blob/master/README.md", NULL, NULL, SW_SHOWNORMAL);
			break;
			///Occurs when github option is pressed - Opens the github page for source code
		case HELP_MENU_GITHUB:
			ShellExecute(NULL, "open", "https://github.com/10203040506070809/Model_Loader", NULL, NULL, SW_SHOWNORMAL);
			break;
			///Occurs when export button is pressed - 
		case FILE_MENU_EXPORT:

			break;
			///Occurs when Dark button is pressed - puts application in dark mode
		case OPTIONS_MENU_DARK:

			break;
			///Occurs when export button is pressed - puts application in light mode
		case OPTIONS_MENU_LIGHT:

			break;
		default:

			break;
		}

		break;
		///Adds the menus 
	case WM_CREATE:
		AddMenus(hWnd);
		break;

		///return false and quit application
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);

	}
}
///Adds menus to the window
void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	HMENU hOptionsMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();
	HMENU hFillMenu = CreateMenu();
	HMENU hPreferencesMenu = CreateMenu();

	///TODO - Add uxtheme and check registry file to see whether user has dark mode enabled, if so, enable this
	//SetWindowTheme(hWnd, L"DarkMode_Explorer", NULL);

	AppendMenu(hFileMenu, MF_STRING || MF_UNCHECKED, FILE_MENU_NEW, "New");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, "Save");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXPORT, "Export");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Quit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	
	AppendMenu(hFillMenu, MF_STRING, OPTIONS_MENU_SOLID, "Solid");
	AppendMenu(hFillMenu, MF_STRING, OPTIONS_MENU_WIRE, "Wireframe");

	AppendMenu(hPreferencesMenu, MF_STRING, OPTIONS_MENU_DARK, "Dark Mode");
	AppendMenu(hPreferencesMenu, MF_STRING, OPTIONS_MENU_LIGHT, "Light Mode");

	AppendMenu(hOptionsMenu, MF_POPUP, (UINT_PTR)hFillMenu, "Fill");
	AppendMenu(hOptionsMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hOptionsMenu, MF_POPUP, (UINT_PTR)hPreferencesMenu, "Preferences");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptionsMenu, "Options");
	
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_ABOUT, "About");
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_HELP, "Help");
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_GITHUB, "Github");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

	SetMenu(hWnd, hMenu);
}
///Opens the file dialog and handles file input
void OpenFileDialog(HWND hWnd)
{
	//https://docs.microsoft.com/en-gb/windows/win32/api/commdlg/ns-commdlg-openfilenamea
	OPENFILENAME ofn;

	char file[MAX_PATH_LENGTH];
	char* path;
	//sets all elements of ofn to 0 
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All Files\0*.*\0Wavefront (.obj)\0*.obj\0Colla (.dae)\0*.dae\0Filmbox (.fbx)\0*.fbx";
	//default to obj
	ofn.nFilterIndex = 2;

	
	bool isFound = GetOpenFileName(&ofn);
	
	 if (isFound)
	 {
		 path = ofn.lpstrFile;
		 OpenModel(path);		 
	 }
	 else
	 {
	 //https://docs.microsoft.com/en-us/windows/win32/api/commdlg/nf-commdlg-commdlgextendederror

		 ///Extended error handling - If none of these return true, user most likely cancelled.
		 ///Unlikely most of these errors would occur, but for the sake of robustness during testing they've been added.
		 switch (CommDlgExtendedError()) 
		 {
		 case CDERR_DIALOGFAILURE:
			 MessageBox(NULL, "The dialog box could not be created. The common dialog box function's call to the DialogBox function failed. For example, this error occurs if the common dialog box call specifies an invalid window handle.", "CDERR_DIALOGFAILURE", MB_OK);
			 break;
		 case CDERR_FINDRESFAILURE:
			 MessageBox(NULL, "The common dialog box function failed to find a specified resource.", "CDERR_FINDRESFAILURE", MB_OK);
			 break;
		 case CDERR_INITIALIZATION:
			 MessageBox(NULL, "The common dialog box function failed during initialization. This error often occurs when sufficient memory is not available.", "CDERR_INITIALIZATION", MB_OK);
			 break;
		 case CDERR_LOADRESFAILURE:
			 MessageBox(NULL, "The common dialog box function failed to load a specified resource.", "CDERR_LOADRESFAILURE", MB_OK);
			 break;
		 case CDERR_LOADSTRFAILURE:
			 MessageBox(NULL, "The common dialog box function failed to load a specified string.", "CDERR_LOADSTRFAILURE", MB_OK);
			 break;
		 case CDERR_LOCKRESFAILURE:
			 MessageBox(NULL, "The common dialog box function failed to lock a specified resource.", "CDERR_LOCKRESFAILURE", MB_OK);
			 break;
		 case CDERR_MEMALLOCFAILURE:
			 MessageBox(NULL, "The common dialog box function was unable to allocate memory for internal structures.", "CDERR_MEMALLOCFAILURE", MB_OK);
			 break;
		 case CDERR_MEMLOCKFAILURE:
			 MessageBox(NULL, "The common dialog box function was unable to lock the memory associated with a handle.", "CDERR_MEMLOCKFAILURE", MB_OK);
			 break;
		 case CDERR_NOHINSTANCE:
			 MessageBox(NULL, "The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle.", "CDERR_NOHINSTANCE", MB_OK);
			 break;
		 case CDERR_NOHOOK:
			 MessageBox(NULL, "The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure.", "CDERR_NOHOOK", MB_OK);
			 break;
		 case CDERR_NOTEMPLATE:
			 MessageBox(NULL, "The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template.", "CDERR_NOTEMPLATE", MB_OK);
			 break;
		 case CDERR_REGISTERMSGFAIL:
			 MessageBox(NULL, "The RegisterWindowMessage function returned an error code when it was called by the common dialog box function.", "CDERR_REGISTERMSGFAIL", MB_OK);
			 break;
		 case CDERR_STRUCTSIZE:
			 MessageBox(NULL, "	The lStructSize member of the initialization structure for the corresponding common dialog box is invalid.", "CDERR_STRUCTSIZE", MB_OK);
			 break;

		 default:
			 //User probably cancelled

			 break;
		 }
	 }


	 
}