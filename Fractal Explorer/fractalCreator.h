#ifndef FRACTAL_CREATOR_H
#define FRACTAL_CREATOR_H

#include "globals.h"
#include "fractal_constants.h"


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
	virtual void calculateSet(int sliceStart, float zoomLevel, float xOffset, float yOffset, int itrCheck) = 0;

protected:
	colourPallette colourPallette[PALLETTE_ENTRIES];
	void writeTexture(int xPos, int yPos, int iterations);
};

#endif