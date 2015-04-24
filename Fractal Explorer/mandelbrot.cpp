#include "mandelbrot.h"

void mandelbrot::calculateSet(int sliceStart, float zoomLevel, float xOffset, float yOffset, int itrCheck)
{
	
	
	//Complex C to represent pixel location
	complex<double> c(0.0, 0.0);

	c.imag((sliceStart - HEIGHT / 2) / (0.5 * zoomLevel * HEIGHT) + yOffset);

	for (int xPos = 0; xPos < WIDTH; xPos++)
	{
		c.real(1.5 * (xPos - WIDTH / 2) / (0.5 * zoomLevel * WIDTH) + xOffset + CENTER_OFFSET);

		//Complex Z to represent each iterations result
		complex<double> z(0.0, 0.0);
		int iterations = 0;

		//calculates one iteration to see if c lies in the set. Avoids sqrt in z.abs() for optimisation
		while (iterations < itrCheck && (z.real() * z.real() + z.imag() * z.imag()) < 4.0)
		{
			z = (z * z) + c;
			iterations++;
		}

	
		//inserts pixel colour in array based on how many iterations passed
		writeTexture(xPos, sliceStart, iterations);	
	}
	
}