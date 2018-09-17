#pragma once
#include <Windows.h>

class CustomRectangle
{
public:
	CustomRectangle();

	void SetLeftRight(int nleft, int nright);
	void SetTopBottom(int ntop, int nbottom);
	void SetBrush(HBRUSH nbrush);
	void SetPen(HPEN npen);

	HBRUSH GetBrush();
	HPEN GetPen();

	int DrawRectangle(HDC hdc);
	int DrawRectangle(HDC hdc, int left, int top, int right, int bottom);
	int DrawRectangle(HWND hwnd, int addleft, int addtop, int addright, int addbottom);

	~CustomRectangle();
protected:
	int left;
	int right;
	int top;
	int bottom;
	HBRUSH brush;
	HPEN pen;
};

