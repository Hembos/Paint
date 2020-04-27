#include "Paint.h"

PENCIL Pencil;
ERASER Eraser;
int Tools = 0;
int Click = 0;
int k = 0;
BOOL FileCreated;
char FileName[200];
PENSILCOLOR hEditColor;

HWND hWnd;
HWND hBtnPencil;
HWND hBtnEraser;
HWND hEditThicknessPencil;
HWND hEditThicknessEraser;
HWND hBtnSave;
HWND hBtnNew;
HWND hBtnOpen;
HWND hEditFileName;

HINSTANCE hInstance;
HDC hdc;
PAINTSTRUCT ps;

LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	WNDCLASS wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Paint";

	RegisterClass(&wc);

	hWnd = CreateWindow("Paint", "Paint", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd) { return 0; }
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_COMMAND:
	{
		if (lParam == (LPARAM)hBtnNew)
		{
			GetWindowText(hEditFileName, FileName, 200);
			FileCreated = Created;
			break;
		}
		if (lParam == (LPARAM)hBtnOpen)
		{
			GetWindowText(hEditFileName, FileName, 200);
			FileCreated = Opened;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		if (FileCreated == 0)
		{
			break;
		}
		if (FileCreated != 0)
		{
			if (lParam == (LPARAM)hBtnPencil)
			{
				Pencil = PencilDraw(Pencil, hEditThicknessPencil, hEditColor);
				Tools = PencilTool;
			}
			if (lParam == (LPARAM)hBtnEraser)
			{
				char Er[10];
				GetWindowText(hEditThicknessEraser, Er, 5);
				Tools = EraserTool;
				Eraser.Thickness = atoi(Er);
			}
			if (lParam == (LPARAM)hBtnSave)
			{
				k = 1;
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		
		
		break;
	}
	case WM_CREATE:
	{
		///////////////////////Pencil
		hBtnPencil = CreateWindow("button", "Pencil",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 120, 30, hWnd, 0, hInstance, NULL);
		hEditThicknessPencil = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 10, 50, 50, 20, hWnd, NULL, hInstance, 0);
		ShowWindow(hBtnPencil, SW_SHOWNORMAL);
		////////////////////////////////////

		///////////////////////Eraser
		hBtnEraser = CreateWindow("button", "Eraser",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			130, 10, 120, 30, hWnd, 0, hInstance, NULL);
		hEditThicknessEraser = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 130, 50, 50, 20, hWnd, NULL, hInstance, 0);
		ShowWindow(hBtnEraser, SW_SHOWNORMAL);
		///////////////////////////////////

		//////////////////////Color
		hEditColor.hEditR = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 270, 20, 50, 20, hWnd, NULL, hInstance, 0);
		ShowWindow(hEditColor.hEditR, SW_SHOWNORMAL);
		hEditColor.hEditG = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 320, 20, 50, 20, hWnd, NULL, hInstance, 0);
		ShowWindow(hEditColor.hEditG, SW_SHOWNORMAL);
		hEditColor.hEditB = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 370, 20, 50, 20, hWnd, NULL, hInstance, 0);
		ShowWindow(hEditColor.hEditB, SW_SHOWNORMAL);
		//////////////////////////////////

		/////////////////////Save Open New
		hBtnSave = CreateWindow("button", "Save",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			450, 10, 120, 30, hWnd, 0, hInstance, NULL);
		hBtnOpen = CreateWindow("button", "Open",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			570, 10, 120, 30, hWnd, 0, hInstance, NULL);
		hBtnNew = CreateWindow("button", "New",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			690, 10, 120, 30, hWnd, 0, hInstance, NULL);
		hEditFileName = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE, 450, 50, 420, 20, hWnd, NULL, hInstance, 0);
		////////////////////////////////////

		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (Tools == PencilTool)
		{
			Pencil.Position.x = LOWORD(lParam);
			Pencil.Position.y = HIWORD(lParam);
			Pencil.State = TRUE;
		}
		if (Tools == EraserTool)
		{
			Eraser.Position.x = LOWORD(lParam);
			Eraser.Position.y = HIWORD(lParam);
			Eraser.State = TRUE;
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		if (Tools == PencilTool)
		{
			Pencil.State = FALSE;
		}
		if (Tools == EraserTool)
		{
			Eraser.State = FALSE;
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (Tools == PencilTool && Pencil.State == TRUE)
		{
			Pencil.OldPosition.x = Pencil.Position.x;
			Pencil.OldPosition.y = Pencil.Position.y;
			Pencil.Position.x = LOWORD(lParam);
			Pencil.Position.y = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		if (Tools == EraserTool && Eraser.State == TRUE)
		{
			Eraser.OldPosition.x = Eraser.Position.x;
			Eraser.OldPosition.y = Eraser.Position.y;
			Eraser.Position.x = LOWORD(lParam);
			Eraser.Position.y = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		HPEN hPen;

		if (Tools == PencilTool && Pencil.State == TRUE)
		{
			hPen = CreatePen(PS_SOLID, Pencil.Thickness, RGB(Pencil.Color.R, Pencil.Color.G, Pencil.Color.B));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, Pencil.OldPosition.x, Pencil.OldPosition.y, NULL);
			LineTo(hdc, Pencil.Position.x, Pencil.Position.y);
			DeleteObject(hPen);
		}
		if (Tools == EraserTool && Eraser.State == TRUE)
		{
			hPen = CreatePen(PS_SOLID, Eraser.Thickness, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, Eraser.OldPosition.x, Eraser.OldPosition.y, NULL);
			LineTo(hdc, Eraser.Position.x, Eraser.Position.y);
			DeleteObject(hPen);
		}

		if (k == 1)
		{
			Save(hdc, FileName);
			k = 0;
		}
		if (FileCreated == Opened)
		{
			Open(hdc, FileName);
			FileCreated = Created;
		}

		EndPaint(hWnd, &ps);
		
		
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
