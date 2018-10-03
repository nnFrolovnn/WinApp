#include "CustomRectangle.h"
#include <math.h>
#include "WinAppLib.h"

CustomRectangle::CustomRectangle():CustomRectangle(HIDE)
{
}

CustomRectangle::CustomRectangle(int nhide)
{
	x = 100;
	y = 100;
	width = 50;
	height = 50;

	hide = nhide;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = CreateSolidBrush(WA_COLOR_BRUSH);
	pen = CreatePen(PS_SOLID, 1, WA_COLOR_PEN);
}

CustomRectangle::CustomRectangle(int x, int y, int width, int height):CustomRectangle(HIDE)
{
}

CustomRectangle::CustomRectangle(int x, int y, int width, int height, HBRUSH nbrush, HPEN npen)
{
	x = x;
	y = y;
	width = width;
	height = height;

	hide = HIDE;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = nbrush;
	pen = npen;
}

void CustomRectangle::Draw(HDC hdc)
{
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);
	Rotate(hdc, 0);
}

void CustomRectangle::Move(HWND hwnd, HDC hdc, int addx, int addy)
{
	LPRECT lpRect = (LPRECT)malloc(sizeof(RECT));;
	GetClientRect(hwnd, lpRect);
	if (x + addx >= 0 && x + width + addx <= lpRect->right)
	{
		x += addx;
	}
	if (y + addy >= 0 && y + height + addy <= lpRect->bottom)
	{
		y += addy;
	}

	CustomRectangle::Draw(hdc);
}

void CustomRectangle::Rotate(HDC hdc, double nangle)
{
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

	Rectangle(hdc, x, y, x + width, y + height);
}

CustomRectangle::~CustomRectangle()
{
}
