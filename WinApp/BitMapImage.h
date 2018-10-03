#pragma once
#include <Windows.h>
#include "Figure.h"
class BitMapImage: public Figure
{
public:
	BitMapImage(HWND hwnd, HDC hdc);
	BitMapImage(HWND hwnd, HDC hdc, int nx, int ny);
	BitMapImage(int nhide);
	BitMapImage();
	~BitMapImage();

	virtual void Draw(HDC hdc) override;
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy) override;
	virtual void Rotate(HDC hdc, double nangle) override;

private:
	HBITMAP hbitmap;
	HDC source;
	HDC hdcMem;	

	void MakeTransparent(HDC hdc);
	void LoadBitMapImage(HWND hwnd, HDC hdc);
};

