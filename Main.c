#include "Paint.h"

PENCIL Pencil;
ERASER Eraser;
MyLINE line;
int Tools = 0;
int Click = 0;
int k = 0;
BOOL FileCreated;
char FileName[200];

BUTTONS Buttons;
HWND hWnd;
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
		if (lParam == (LPARAM)Buttons.hBtnNew)
		{
			GetWindowText(Buttons.hEditFileName, FileName, 200);
			FileCreated = Created;
			break;
		}
		if (lParam == (LPARAM)Buttons.hBtnOpen)
		{
			GetWindowText(Buttons.hEditFileName, FileName, 200);
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
			if (lParam == (LPARAM)Buttons.hBtnPencil)
			{
				Pencil = PencilDescription(Pencil, Buttons.hEditThicknessPencil, Buttons.hEditColor);
				Tools = PencilTool;
			}
			if (lParam == (LPARAM)Buttons.hBtnLine)
			{
				line.Click = 0;
				line = LineDescription(line, Buttons.hEditThicknessLine, Buttons.hEditColor);
				Tools = Line;
			}
			if (lParam == (LPARAM)Buttons.hBtnEraser)
			{
				Eraser = EraserDescription(Eraser, Buttons.hEditThicknessEraser);
				Tools = EraserTool;
			}
			if (lParam == (LPARAM)Buttons.hBtnSave)
			{
				k = 1;
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		break;
	}
	case WM_CREATE:
	{
		Buttons = CreateButtons(Buttons, hWnd, hInstance);
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
		if (Tools == Line)
		{
			line.Click++;
			if (line.Click == 1)
			{
				line.StartPosition.x = LOWORD(lParam);
				line.StartPosition.y = HIWORD(lParam);
			}
			if (line.Click == 2)
			{
				line.EndPosition.x = LOWORD(lParam);
				line.EndPosition.y = HIWORD(lParam);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			line.State = TRUE;
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
		if (Tools == Line && line.Click == 2)
		{
			line.Click = 0;
			line.State = FALSE;
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
			PencilDraw(Pencil, hdc);
		}
		if (Tools == EraserTool && Eraser.State == TRUE)
		{
			EraserDraw(Eraser, hdc);
		}
		if (Tools == Line && line.Click == 2)
		{
			LineDraw(line, hdc);
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
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
