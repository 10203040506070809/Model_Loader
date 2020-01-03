#ifndef GUI_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GUI_H

#include <Windows.h>
#include "Model_Loader.h"
HWND GUIinit(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow);
#endif