#ifndef FRACTAL_CREATOR_H
#define FRACTAL_CREATOR_H

#include "globals.h"
#include <complex>
#include <vector>

using std::complex;
using std::vector;

const int palletteEntries = 500;
const int colourStep = 10;
const int redCheck = 256 / colourStep;
const int greenCheck = 512 / colourStep;

//struct to hold colour values
struct colourPallette
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

class fractalCreator
{

public:
	fractalCreator();
	//virtual void startGeneration();

protected:
	colourPallette colourPallette[palletteEntries];
	void writeTexture(int xPos, int yPos, int iterations);
private:

};

#endif