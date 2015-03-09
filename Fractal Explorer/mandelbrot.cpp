#include "mandelbrot.h"


const int SECTIONS = 8;

void mandelbrot::startGeneration()
{

	int sectionHeight = HEIGHT / SECTIONS;

	vector<thread> calculationThreads;

	iterationLock.lock(); //ensures itterations dont change until calculation copmplete
	for (int threadCreate = 1; threadCreate < SECTIONS + 1; threadCreate++)
	{
		calculationThreads.push_back(thread(&mandelbrot::calculateSet, this, threadCreate * sectionHeight - sectionHeight, threadCreate * sectionHeight));
	}
	
	for (int threadCreate = 0; threadCreate < SECTIONS; threadCreate++)
	{
		calculationThreads.at(threadCreate).join();
	}
	iterationLock.unlock();
}

void mandelbrot::calculateSet(int sliceStart, int sliceEnd)
{
	
	
	complex<double> minComplex(-0.751085, 0.118378);
	complex<double> maxComplex(-0.734975, 0.134488);
	complex<double> c(0.0, 0.0);



	for (int yPos = sliceStart; yPos < sliceEnd; yPos++)
	{
		c.imag(maxComplex.imag() + (yPos  * (minComplex.imag() - maxComplex.imag()) / HEIGHT));
		for (int xPos = 0; xPos < WIDTH; xPos++)
		{
			
			c.real(minComplex.real() + (xPos * (maxComplex.real() - minComplex.real()) / WIDTH ));

			complex<double> z(0.0, 0.0);
			int iterations = 0;

			//calculates one iteration to see if c lies in the set
			while (iterations < maxIterations && abs(z) < 2.0)
			{
				z = (z * z) + c;
				iterations++;
			}

			
			//inserts pixel colour in array based on how many iterations passed
			writeTexture(xPos, yPos, iterations);
			
		}
	}
	
	
}