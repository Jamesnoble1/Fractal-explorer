#ifndef JULIA_H
#define JULIA_H

#include "fractalCreator.h"

class julia : public fractalCreator
{
public:
	void calculateSet(int sliceStart, float zoomLevel, float xOffset, float yOffset, int itrCheck);
};

#endif
