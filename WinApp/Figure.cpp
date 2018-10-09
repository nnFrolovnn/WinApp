#include "Figure.h"


Figure::~Figure()
{

}

void Figure::SetWidth(int nwidth)
{
	width = nwidth;
}

void Figure::SetHeight(int nheight)
{
	height = nheight;
}

void Figure::Rotate(double nangle)
{
	angle += nangle;
}

void Figure::SetHide(int nhide)
{
	hide = nhide;
}

void Figure::SetTop(int ntop)
{
	y = ntop;
}

void Figure::SetLeft(int nleft)
{
	x = nleft;
}

int Figure::GetHide()
{
	return hide;
}

int Figure::GetWidth()
{
	return width;
}

int Figure::GetHeight()
{
	return height;
}

int Figure::GetTop()
{
	return y;
}

int Figure::GetLeft()
{
	return x;
}
