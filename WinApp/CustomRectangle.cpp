#include "CustomRectangle.h"
#include <math.h>
#include "WinAppLib.h"

CustomRectangle::CustomRectangle():CustomRectangle(HIDE)
{
}

CustomRectangle::CustomRectangle(int nhide)
{
	left = 100;
	top = 100;
	right = 150;
	bottom = 150;

	hide = nhide;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = CreateSolidBrush(WA_COLOR_BRUSH);
	pen = CreatePen(PS_SOLID, 1, WA_COLOR_PEN);
}

CustomRectangle::CustomRectangle(int x, int y, int width, int height)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

	hide = HIDE;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = CreateSolidBrush(WA_COLOR_BRUSH);
	pen = CreatePen(PS_SOLID, 1, WA_COLOR_PEN);
}

CustomRectangle::CustomRectangle(int x, int y, int width, int height, HBRUSH nbrush, HPEN npen)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

	hide = HIDE;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = nbrush;
	pen = npen;
}

void CustomRectangle::SetLeft(int nleft)
{
	left = (nleft < 0) ? 0 : nleft;
}

void CustomRectangle::SetTop(int ntop)
{
	top = (ntop < 0) ? 0 : ntop;
}

void CustomRectangle::SetHeight(int nheight)
{
	bottom = left + nheight;
}

void CustomRectangle::SetWidth(int nwidth)
{
	right = left + nwidth;
}

void CustomRectangle::SetHide(int nhide)
{
	hide = nhide;
}

int CustomRectangle::GetLeft()
{
	return left;
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
	if (left + addx >= 0 && right + addx <= lpRect->right)
	{
		left += addx;
		right += addx;
	}
	if (top + addy >= 0 && bottom + addy <= lpRect->bottom)
	{
		top += addy;
		bottom += addy;
	}

	CustomRectangle::Draw(hdc);
}

void CustomRectangle::Rotate(HDC hdc, double nangle)
{
	XFORM xForm;
	float m = (left + right) / 2.0;
	float n = (top + bottom) / 2.0;

	angle += nangle;
	xForm.eM11 = cos(angle);
	xForm.eM12 = sin(angle);
	xForm.eM21 = -sin(angle);
	xForm.eM22 = cos(angle);

	xForm.eDx = -m * (cos(angle) - 1) + n * sin(angle);
	xForm.eDy = -n * (cos(angle) - 1) - m * sin(angle);


	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xForm);

	Rectangle(hdc, left, top, right, bottom);
}

int CustomRectangle::GetHeight()
{
	return (bottom - top);
}

int CustomRectangle::GetTop()
{
	return top;
}

int CustomRectangle::GetHide()
{
	return hide;
}

int CustomRectangle::GetWidth()
{
	return (right - left);
}

CustomRectangle::~CustomRectangle()
{
}
