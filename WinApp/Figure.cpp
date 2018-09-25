#include "Figure.h"


Figure::~Figure()
{
}

void Figure::Draw(HDC hdc, int nx, int ny, int nwidth, int nheight)
{
}

void Figure::Draw(HDC hdc)
{
}

void Figure::Move(HWND hwnd, HDC hdc, int addx, int addy)
{
}

void Figure::Rotate(HDC hdc, int angle)
{
}

void Figure::SetWidth(int nwidth)
{
}

void Figure::SetHeight(int nheight)
{
}

void Figure::SetHide(int nhide)
{
}

int Figure::GetHide()
{
	return 0;
}

int Figure::GetWidth()
{
	return 0;
}

int Figure::GetHeight()
{
	return 0;
}