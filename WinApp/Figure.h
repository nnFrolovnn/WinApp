#pragma once
#include <Windows.h>
#include "WinAppLib.h"

class Figure
{
public:
	virtual ~Figure();

	virtual void Draw(HDC hdc) = 0;
	virtual void Move(HWND hwnd, int addx, int addy) = 0;
	virtual void Rotate(double nangle);

	virtual void SetHide(int nhide);
	virtual void SetWidth(int nwidth);
	virtual void SetHeight(int nheight);
	virtual void SetTop(int ntop);
	virtual void SetLeft(int nleft);

	virtual int GetHide();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual int GetTop();
	virtual int GetLeft();

protected:

	int width;
	int height;
	int x, y;
	int hide;
	double angle;

};