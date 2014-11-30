
#include "includes.h"

CRect::CRect(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

CRect::CRect(void)
{
	CRect(0, 0, 0, 0);
}
