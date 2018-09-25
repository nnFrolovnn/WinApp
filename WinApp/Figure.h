#pragma once
#include <Windows.h>

class Figure
{
public:
	virtual ~Figure();

	virtual void Draw(HDC hdc);
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy);
	virtual void Rotate(HDC hdc, double nangle);


	virtual void SetHide(int nhide);
	virtual void SetWidth(int nwidth);
	virtual void SetHeight(int nheight);
	virtual void SetTop(int ntop);
	virtual void SetLeft(int nxleft);

	virtual int GetHide();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual int GetTop();
	virtual int GetLeft();
};

