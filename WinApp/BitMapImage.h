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

	virtual void SetHide(int nhide) override;
	virtual void SetWidth(int nwidth) override;
	virtual void SetHeight(int nheight) override;
	virtual void SetTop(int ntop) override;
	virtual void SetLeft(int nleft) override;

	virtual int GetHide() override;
	virtual int GetWidth() override;
	virtual int GetHeight() override;
	virtual int GetTop() override;
	virtual int GetLeft() override;

	virtual void Draw(HDC hdc) override;
	virtual void Move(HWND hwnd, HDC hdc, int addx, int addy) override;
	virtual void Rotate(HDC hdc, double nangle) override;

private:
	int width;
	int height;
	int x, y;
	int hide;
	HBITMAP hbitmap;
	HDC source;
	HDC hdcMem;
	double angle;
	

	void MakeTransparent(HDC hdc);
	void LoadBitMapImage(HWND hwnd, HDC hdc);
};

