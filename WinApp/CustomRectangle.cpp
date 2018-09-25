#include "CustomRectangle.h"
#include <math.h>
#define PI 3.14159265 

CustomRectangle::CustomRectangle()
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
	brush = CreateSolidBrush(0x0000FF00);
	pen = CreatePen(PS_SOLID, 1, 0x000000FF);
}

CustomRectangle::CustomRectangle(int x, int y, int width, int height)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;

	hide = 0;
	angle = 0;
	hdcMem = CreateCompatibleDC(NULL);
	brush = CreateSolidBrush(0x0000FF00);
	pen = CreatePen(PS_SOLID, 1, 0x000000FF);

	SelectObject(hdcMem, brush);
	SelectObject(hdcMem, pen);
	Rectangle(hdcMem, 0, 0, 50, 50);
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

void CustomRectangle::SetBrush(HBRUSH nbrush)
{
	brush = nbrush;
}

void CustomRectangle::SetPen(HPEN npen)
{
	pen = npen;
}

void CustomRectangle::SetHide(int nhide)
{
	hide = nhide;
}

HBRUSH CustomRectangle::GetBrush()
{
	return brush;
}

HPEN CustomRectangle::GetPen()
{
	return pen;
}

int CustomRectangle::GetLeft()
{
	return left;
}

int CustomRectangle::GetTop()
{
	return top;
}


int CustomRectangle::GetBottom()
{
	return bottom;
}

int CustomRectangle::GetRight()
{
	return right;
}

int CustomRectangle::GetHide()
{
	return hide;
}

int CustomRectangle::DrawRectangle(HDC hdc)
{
	if (hide == 0)
	{
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
		Rotate(hdc, 0);
	}
	return 0;
}

int CustomRectangle::MoveRectangle(HWND hwnd, HDC hdc, int addleft, int addtop, int addright, int addbottom)
{
	if (hide != 0)
	{
		exit(0);
	}
	LPRECT lpRect = (LPRECT)malloc(sizeof(RECT));;
	GetClientRect(hwnd, lpRect);
	if (left + addleft >= 0 && right + addright <= lpRect->right)
	{
		left += addleft;
		right += addright;
	}
	if (top + addtop >= 0 && bottom + addbottom <= lpRect->bottom)
	{
		top += addtop;
		bottom += addbottom;
	}

	DrawRectangle(hdc);

	return 0;
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

CustomRectangle::~CustomRectangle()
{
	pen = NULL;
	brush = NULL;
}
