#ifndef JULIA_H
#define JULIA_H

#include "fractalCreator.h"

class julia : public fractalCreator
{
public:
	void startGeneration();

private:


	void calculateSet(int sliceStart, int sliceEnd);
};

#endif
