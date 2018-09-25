#pragma once
#include <Windows.h>
#include "Figure.h"

class CustomRectangle : public Figure
{
public:
	CustomRectangle();
	CustomRectangle(int nhide);
	CustomRectangle(int x, int y, int width, int height);
	CustomRectangle(int x, int y, int width, int height, HBRUSH nbrush, HPEN npen);

	virtual void SetHide(int nhide) override;
	virtual void SetWidth(int nwidth) override;
	virtual void SetHeight(int nheight) override;
	virtual void SetTop(int ntop) override;
	virtual void SetLeft(int nxleft) override;

	virtual int GetHide() override;
	virtual int GetWidth() override;
	virtual int GetHeight() override;
	virtual int GetTop() override;
	virtual int GetLeft() override;

	virtual void Draw(HDC hdc) override;
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy) override;
	virtual void Rotate(HDC hdc, double nangle) override;


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

