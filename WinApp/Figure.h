#pragma once
#include <Windows.h>
class Figure
{
public:
	virtual ~Figure();

	virtual void Draw(HDC hdc, int nx, int ny, int nwidth, int nheight);
	virtual void Draw(HDC hdc);
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy);
	virtual void Rotate(HDC hdc, int angle);


	virtual void SetWidth(int nwidth);
	virtual void SetHeight(int nheight);
	virtual void SetHide(int nhide);

	virtual int GetHide();
	virtual int GetWidth();
	virtual int GetHeight();

private:
	int width;
	int height;
	int x, y;
	int hide;
};

