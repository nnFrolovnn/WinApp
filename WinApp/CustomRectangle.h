#pragma once
#include <Windows.h>
#include "Figure.h"

class CustomRectangle: public Figure
{
public:
	CustomRectangle();

	void SetLeftRight(int nleft, int nright);
	void SetTopBottom(int ntop, int nbottom);
	void SetBrush(HBRUSH nbrush);
	void SetPen(HPEN npen);
	void SetHide(int nhide);

	HBRUSH GetBrush();
	HPEN GetPen();

	int GetLeft();
	int GetTop();
	int GetBottom();
	int GetRight();
	int GetHide();

	int DrawRectangle(HDC hdc);
	int MoveRectangle(HWND hwnd, HDC hdc, int addleft, int addtop, int addright, int addbottom);
	void Rotate(HDC hdc, double nangle);


	~CustomRectangle();
protected:
	int left;
	int right;
	int top;
	int bottom;
	HBRUSH brush;
	HPEN pen;
	HDC hdcMem;
	int hide;
	double angle;
};

