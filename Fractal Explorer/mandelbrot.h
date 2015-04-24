#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractalCreator.h"

class mandelbrot : public fractalCreator
{
public:
	void calculateSet(int sliceStart, float zoomLevel, float xOffset, float yOffset, int itrCheck);

private:
	const float CENTER_OFFSET = -0.5f;
	
};

#endif