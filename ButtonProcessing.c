#include "Paint.h"

BUTTONS CreateButtons(BUTTONS Buttons, HWND hWnd, HINSTANCE hInstance)
{
	///////////////////////Pencil
	Buttons.hBtnPencil = CreateWindow("button", "Pencil",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 10, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hEditThicknessPencil = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 10, 50, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hBtnPencil, SW_SHOWNORMAL);
	////////////////////////////////////

	///////////////////////Eraser
	Buttons.hBtnEraser = CreateWindow("button", "Eraser",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		130, 10, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hEditThicknessEraser = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 130, 50, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hBtnEraser, SW_SHOWNORMAL);
	///////////////////////////////////

	//////////////////////Color
	Buttons.hEditColor.hEditR = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 270, 20, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hEditColor.hEditR, SW_SHOWNORMAL);
	Buttons.hEditColor.hEditG = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 320, 20, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hEditColor.hEditG, SW_SHOWNORMAL);
	Buttons.hEditColor.hEditB = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 370, 20, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hEditColor.hEditB, SW_SHOWNORMAL);
	//////////////////////////////////

	/////////////////////Save Open New
	Buttons.hBtnSave = CreateWindow("button", "Save",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		450, 10, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hBtnOpen = CreateWindow("button", "Open",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		570, 10, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hBtnNew = CreateWindow("button", "New",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		690, 10, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hEditFileName = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 450, 50, 420, 20, hWnd, NULL, hInstance, 0);
	////////////////////////////////////

	///////////////////Line
	Buttons.hBtnLine = CreateWindow("button", "Line",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 70, 120, 30, hWnd, 0, hInstance, NULL);
	Buttons.hEditThicknessLine = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 10, 110, 50, 20, hWnd, NULL, hInstance, 0);
	ShowWindow(Buttons.hBtnLine, SW_SHOWNORMAL);
	///////////////////////////////////
	return Buttons;
}
