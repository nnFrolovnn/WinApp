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

	virtual void Draw(HDC hdc) override;
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy) override;
	virtual void Rotate(HDC hdc, double nangle) override;
	
	~CustomRectangle();

protected:
	HBRUSH brush;
	HPEN pen;
	HDC hdcMem;
};

