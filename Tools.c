#include "Paint.h"

HDC memDC;
HBITMAP memBM;
HBITMAP hbOpen;

void Save(HDC hdc, char* FileName)
{
	memDC = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, 900, 600);
	HGDIOBJ oldBMP = SelectObject(memDC, memBM);
	BITMAP Bitmap;
	GetObject(memBM, sizeof(Bitmap), (LPVOID)&Bitmap);
	StretchBlt(memDC, 0, 0, 900, 600, hdc, 0, 70, Bitmap.bmWidth - 10, Bitmap.bmHeight - 115, SRCCOPY);


	long Size = (Bitmap.bmWidth * ((Bitmap.bmHeight * 3 + 3) / 4 * 4) + 3) / 4 * 4;
	BITMAPFILEHEADER bitfileh;
	memset(&bitfileh, 0, sizeof(BITMAPFILEHEADER));
	bitfileh.bfType = 0x4D42;
	bitfileh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + Size;
	bitfileh.bfReserved1 = 0;
	bitfileh.bfReserved2 = 0;
	bitfileh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER bitinfoh;
	memset(&bitinfoh, 0, sizeof(BITMAPINFOHEADER));
	bitinfoh.biSize = sizeof(BITMAPINFOHEADER);
	bitinfoh.biWidth = Bitmap.bmWidth;
	bitinfoh.biHeight = Bitmap.bmHeight;
	bitinfoh.biPlanes = 1;
	bitinfoh.biBitCount = 24;

	BYTE* mBits = malloc(Size);

	GetDIBits(memDC, memBM, 0, Bitmap.bmHeight, mBits, (BITMAPINFO*)&bitinfoh, DIB_RGB_COLORS);

	FILE* File;
	File = fopen(FileName, "w");
	fwrite(&bitfileh, sizeof(bitfileh), 1, File);
	fwrite(&bitinfoh, sizeof(bitinfoh), 1, File);
	fwrite(mBits, Size, 1, File);
	fclose(File);

	free(mBits);
	SelectObject(memDC, oldBMP);
	DeleteObject(memBM);
	DeleteDC(memDC);
}

void Open(HDC hdc, char* FileName)
{
	memDC = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, 900, 600);
	HGDIOBJ oldBMP = SelectObject(memDC, memBM);
	hbOpen = (HBITMAP)LoadImage(NULL, TEXT(FileName), IMAGE_BITMAP, 900, 530, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbOpen);
	BitBlt(hdc, 0, 70, 900, 600, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBMP);
	DeleteObject(memBM);
	DeleteDC(memDC);
}

PENCIL PencilDraw(PENCIL Pencil, HWND hEditThicknessPencil, PENSILCOLOR hEditColor)
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
