#include "julia.h"

void julia::calculateSet(int sliceStart, float zoomLevel, float xOffset, float yOffset, int itrCheck)
{
	
	
	//Z complex number to represent current pixel while calculating set


		
		for (int xPos = 0; xPos < WIDTH; xPos++)
		{
			//set z on complex plane based on pixel location.
			complex<double> z(1.5 * (xPos - WIDTH / 2) / (0.5 * zoomLevel * WIDTH) + xOffset,
				(sliceStart - HEIGHT / 2) / (0.5 * zoomLevel* HEIGHT) + yOffset);

			int iterations = 0;

			//calculates one iteration to see if c lies in the set. Avoids sqrt in z.abs() for optimisation
			while (iterations < itrCheck && (z.real() * z.real() + z.imag() * z.imag()) < 4.0)
			{
				z = (z * z) + k;
				iterations++;
			}

			//inserts pixel colour in array based on how many iterations passed
			writeTexture(xPos, sliceStart, iterations);

		}
	
	
}