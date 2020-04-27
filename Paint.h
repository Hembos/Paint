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

typedef enum
{
	PencilTool = 1,
	EraserTool
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

PENCIL PencilDraw(PENCIL Pencil, HWND hEditThicknessPencil, PENSILCOLOR hEditColor);
void Open(HDC hdc, char* FileName);
void Save(HDC hdc, char* FileName);
