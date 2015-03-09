#include "julia.h"

const int SECTIONS = 6;

void julia::startGeneration()
{
	int sectionHeight = HEIGHT / SECTIONS;

	vector<thread> calculationThreads;
	iterationLock.lock(); //ensures itterations dont change until calculation copmplete
	for (int threadCreate = 1; threadCreate < SECTIONS + 1; threadCreate++)
	{
		calculationThreads.push_back(thread(&julia::calculateSet, this, threadCreate * sectionHeight - sectionHeight, threadCreate * sectionHeight));
	}

	for (int threadCreate = 0; threadCreate < SECTIONS; threadCreate++)
	{
		calculationThreads.at(threadCreate).join();
	}
	iterationLock.unlock();
}

void julia::calculateSet(int sliceStart, int sliceEnd)
{
	
	complex<double> k(-0.5, -0.50);



	for (int yPos = sliceStart; yPos < sliceEnd; yPos++)
	{
		
		for (int xPos = 0; xPos < WIDTH; xPos++)
		{

			//set z on complex plane based on pixel location.
			complex<double> z(1.5 * (xPos - WIDTH / 2) / (0.5 * WIDTH),
							(yPos - HEIGHT / 2) / (0.5 * HEIGHT));
			int iterations = 0;

			//calculates one iteration to see if c lies in the set
			while (iterations < maxIterations && abs(z) < 2.0)
			{
				z = (z * z) + k;
				iterations++;
			}


			//inserts pixel colour in array based on how many iterations passed
			writeTexture(xPos, yPos, iterations);
			
		}
	}

}