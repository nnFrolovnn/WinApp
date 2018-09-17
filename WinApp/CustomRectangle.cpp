#include "CustomRectangle.h"



CustomRectangle::CustomRectangle()
{
	SetLeftRight(100, 150);
	SetTopBottom(100, 150);
	brush = CreateSolidBrush(0x0000FF00);
	pen = CreatePen(PS_SOLID, 1, 0x000000FF);
}

void CustomRectangle::SetLeftRight(int nleft, int nright)
{
	left = (nleft < 0)? 0: nleft;
	right = (nright < 0)? 0: nright;
}

void CustomRectangle::SetTopBottom(int ntop, int nbottom)
{
	top = (ntop < 0)? 0: ntop;
	bottom = (nbottom < 0)? 0: nbottom;
}

void CustomRectangle::SetBrush(HBRUSH nbrush)
{
	brush = nbrush;
}

void CustomRectangle::SetPen(HPEN npen)
{
	pen = npen;
}

HBRUSH CustomRectangle::GetBrush()
{
	return brush;
}

HPEN CustomRectangle::GetPen()
{
	return pen;
}


int CustomRectangle::DrawRectangle(HDC hdc)
{
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);
	Rectangle(hdc, left, top, right, bottom);
	return 0;
}

int CustomRectangle::DrawRectangle(HDC hdc, int nleft, int ntop, int nright, int nbottom)
{
	SetLeftRight(nleft, nright);
	SetTopBottom(ntop, nbottom);
	DrawRectangle(hdc);
	return 0;
}

int CustomRectangle::DrawRectangle(HWND hwnd, int addleft, int addtop, int addright, int addbottom)
{
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

	DrawRectangle(GetWindowDC(hwnd));

	return 0;
}

CustomRectangle::~CustomRectangle()
{
	pen = NULL;
	brush = NULL;
}