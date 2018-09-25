#include "BitMapImage.h"
#include <math.h>
#include "WinAppLib.h"

BitMapImage::BitMapImage(HWND hwnd, HDC hdc)
{
	width = 50;
	height = 50;
	x = 10;
	y = 10;
	hide = 1;
	hbitmap = NULL;
	hdcMem = NULL;
	angle = 0;

	LoadBitMapImage(hwnd, hdc);
	MakeTransparent(hdc);
}

BitMapImage::BitMapImage(HWND hwnd, HDC hdc, int nx, int ny)
{
	x = nx;
	y = ny;
	width = 50;
	height = 50;
	hide = 1;
	hbitmap = NULL;
	hdcMem = NULL;
	angle = 0;

	LoadBitMapImage(hwnd, hdc);
	MakeTransparent(hdc);
}

BitMapImage::BitMapImage(int nhide)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	hide = nhide;
	hbitmap = NULL;
	hdcMem = NULL;
	angle = 0;
}

BitMapImage::BitMapImage()
{
}

BitMapImage::~BitMapImage()
{
}

void BitMapImage::Rotate(HDC hdc, double nangle)
{
	/*POINT *lpPoint = (POINT *)calloc(3, sizeof(POINT));

	angle += nangle;

	double b = asin(width / sqrt(height*height + width * width));
	double g = (PI - angle) / 2;

	double d2 = g - b;
	double d1 = g - PI / 2 + b;
	double s = 2 * sin(angle / 2.0)*sqrt(height*height + width * width)/2.0;

	lpPoint[0].x = x  +s * cos(d1);
	lpPoint[0].y = y - s * sin(d1);

	lpPoint[1].x = x  +width + s * sin(d1);
	lpPoint[1].y = y + s * cos(d1);

	lpPoint[2].x = x  -s * sin(d2);
	lpPoint[2].y = y + height - s * cos(d2);

	PlgBlt(hdc, lpPoint, hdcMem, 0, 0, width, height, NULL, 0, 0);*/
	XFORM xForm;
	float m = x + width / 2.0;
	float n = y + height / 2.0;

	angle += nangle;
	xForm.eM11 = cos(angle);
	xForm.eM12 = sin(angle);
	xForm.eM21 = -sin(angle);
	xForm.eM22 = cos(angle);

	xForm.eDx = -m * (cos(angle) - 1) + n * sin(angle);
	xForm.eDy = -n * (cos(angle) - 1) - m * sin(angle);


	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xForm);

	BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
}

void BitMapImage::SetWidth(int nwidth)
{
	width = nwidth;
}

void BitMapImage::SetHeight(int nheight)
{
	height = nheight;
}

void BitMapImage::SetTop(int ntop)
{
	y = ntop;
}

void BitMapImage::SetLeft(int nleft)
{
	x = nleft;
}

void BitMapImage::SetHide(int nhide)
{
	hide = nhide;
}

int BitMapImage::GetHide()
{
	return hide;
}

int BitMapImage::GetWidth()
{
	return width;
}

int BitMapImage::GetHeight()
{
	return height;
}

int BitMapImage::GetTop()
{
	return y;
}

int BitMapImage::GetLeft()
{
	return x;
}

void BitMapImage::Draw(HDC hdc)
{
	if ((long)round(angle) == 0)
	{
		BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
	}
	else
	{
		//TODO
		Rotate(hdc, 0);
	}
}

void BitMapImage::Move(HWND hwnd, HDC hdc, int addx, int addy)
{
	LPRECT lpRect = (LPRECT)malloc(sizeof(RECT));;
	GetClientRect(hwnd, lpRect);

	if (x + addx >= 0 && x + addx + width <= lpRect->right)
	{
		x += addx;
	}
	if (y + addy >= 0 && y + addy + height <= lpRect->bottom)
	{
		y += addy;
	}
	Draw(hdc);
}

void BitMapImage::MakeTransparent(HDC hdc)
{
	BITMAP     bm;
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HDC        hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT      ptSize;

	hdcTemp = source;

	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hdcTemp);
	hdcObject = CreateCompatibleDC(hdcTemp);
	hdcMem = CreateCompatibleDC(hdcTemp);
	hdcSave = CreateCompatibleDC(hdcTemp);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem = CreateCompatibleBitmap(hdcTemp, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdcTemp, ptSize.x, ptSize.y);

	SelectObject(hdcBack, bmAndBack);
	SelectObject(hdcObject, bmAndObject);
	SelectObject(hdcMem, bmAndMem);
	SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, source, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, 0x00FFFFFF);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);

	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, 0, 0, SRCCOPY);

	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	//BitBlt(hdc, x, y, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);

	hbitmap = CreateCompatibleBitmap(hdcMem, ptSize.x, ptSize.y);

	DeleteDC(source);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

void BitMapImage::LoadBitMapImage(HWND hwnd, HDC hdc)
{

	OPENFILENAME image;
	char szDirect[260];
	char szFileName[260];
	BITMAP bm;

	memset(&image, 0, sizeof(OPENFILENAME));
	image.hwndOwner = hwnd;
	image.Flags = OFN_EXPLORER;
	image.hInstance = NULL;
	image.lpstrFilter = NULL;
	image.lpstrCustomFilter = NULL;
	image.nFilterIndex = 1;
	image.lpstrFile = szDirect;
	*(image.lpstrFile) = 0;
	image.lpstrInitialDir = NULL;
	image.lStructSize = sizeof(image);
	image.nMaxFile = sizeof(szDirect);
	image.lpstrFileTitle = szFileName;
	*(image.lpstrFileTitle) = 0;
	image.nMaxFileTitle = sizeof(szFileName);
	image.Flags = OFN_EXPLORER;

	int load = GetOpenFileNameA(&image);
	if (load == 0)
	{
		return;
	}
	hbitmap = (HBITMAP)LoadImageA(NULL, image.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObjectA(hbitmap, sizeof(BITMAP), &bm);

	source = CreateCompatibleDC(NULL);
	SelectObject(source, hbitmap);

	width = bm.bmWidth;
	height = bm.bmHeight;
}
