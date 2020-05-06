#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	int R,
		G,
		B;
} COLOR;

typedef struct
{
	int Thickness;
	COLOR Color;
	BOOL State;
	POINT Position;
	POINT OldPosition;
} PENCIL;

typedef struct
{
	int Thickness;
	BOOL State;
	POINT Position;
	POINT OldPosition;
} ERASER;

typedef struct
{
	int Thickness;
	int Click;
	POINT StartPosition;
	POINT EndPosition;
	COLOR Color;
	BOOL State;
} MyLINE;

typedef enum
{
	PencilTool = 1,
	EraserTool,
	Line
} TOOL;

typedef struct
{
	HWND hEditR;
	HWND hEditG;
	HWND hEditB;
} PENSILCOLOR;

typedef enum
{
	Created = 1,
	Opened
};

typedef struct
{
	HWND hBtnPencil;
	HWND hBtnEraser;
	HWND hBtnLine;
	HWND hBtnSave;
	HWND hBtnNew;
	HWND hBtnOpen;
	HWND hEditThicknessPencil;
	HWND hEditThicknessEraser;
	HWND hEditFileName;
	HWND hEditThicknessLine;
	PENSILCOLOR hEditColor;
} BUTTONS;

PENCIL PencilDescription(PENCIL Pencil, HWND hEditThicknessPencil, PENSILCOLOR hEditColor);
void Open(HDC hdc, char* FileName);
void Save(HDC hdc, char* FileName);
MyLINE LineDescription(MyLINE line, HWND hEditThicknessLine, PENSILCOLOR hEditColor);
ERASER EraserDescription(ERASER Eraser, HWND hEditThicknessEraser);
void PencilDraw(PENCIL Pencil, HDC hdc);
void EraserDraw(ERASER Eraser, HDC hdc);
void LineDraw(MyLINE line, HDC hdc);
BUTTONS CreateButtons(BUTTONS Buttons, HWND hWnd, HINSTANCE hInstance);
