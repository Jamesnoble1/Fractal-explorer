#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractalCreator.h"



class mandelbrot : public fractalCreator
{
public:
	void startGeneration();

private:
	

	void calculateSet(int sliceStart, int sliceEnd);
};

#endif