#include "Paint.h"

MyLINE LineDescription(MyLINE line, HWND hEditThicknessLine, PENSILCOLOR hEditColor)
{
	char Line[10];
	char r[10], g[10], b[10];
	GetWindowText(hEditThicknessLine, Line, 5);
	GetWindowText(hEditColor.hEditR, r, 5);
	GetWindowText(hEditColor.hEditG, g, 5);
	GetWindowText(hEditColor.hEditB, b, 5);
	line.Color.R = atoi(r);
	line.Color.G = atoi(g);
	line.Color.B = atoi(b);
	line.Thickness = atoi(Line);
	return line;
}

PENCIL PencilDescription(PENCIL Pencil, HWND hEditThicknessPencil, PENSILCOLOR hEditColor)
{
	char Pen[10];
	char r[10], g[10], b[10];
	GetWindowText(hEditThicknessPencil, Pen, 5);
	GetWindowText(hEditColor.hEditR, r, 5);
	GetWindowText(hEditColor.hEditG, g, 5);
	GetWindowText(hEditColor.hEditB, b, 5);
	Pencil.Color.R = atoi(r);
	Pencil.Color.G = atoi(g);
	Pencil.Color.B = atoi(b);
	Pencil.Thickness = atoi(Pen);
	return Pencil;
}

ERASER EraserDescription(ERASER Eraser, HWND hEditThicknessEraser)
{
	char Er[10];
	GetWindowText(hEditThicknessEraser, Er, 5);
	Eraser.Thickness = atoi(Er);
	return Eraser;
}

void PencilDraw(PENCIL Pencil, HDC hdc)
{
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, Pencil.Thickness, RGB(Pencil.Color.R, Pencil.Color.G, Pencil.Color.B));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, Pencil.OldPosition.x, Pencil.OldPosition.y, NULL);
	LineTo(hdc, Pencil.Position.x, Pencil.Position.y);
	DeleteObject(hPen);
}

void EraserDraw(ERASER Eraser, HDC hdc)
{
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, Eraser.Thickness, RGB(255, 255, 255));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, Eraser.OldPosition.x, Eraser.OldPosition.y, NULL);
	LineTo(hdc, Eraser.Position.x, Eraser.Position.y);
	DeleteObject(hPen);
}

void LineDraw(MyLINE line, HDC hdc)
{
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, line.Thickness, RGB(line.Color.R, line.Color.G, line.Color.B));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, line.StartPosition.x, line.StartPosition.y, NULL);
	LineTo(hdc, line.EndPosition.x, line.EndPosition.y);
	DeleteObject(hPen);
}
