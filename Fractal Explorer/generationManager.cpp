#include "generationManager.h"


void generationManager::init(barrier* usedBarrier)
{
	currentSet = NULL;
	jobBarrier = usedBarrier;
	currentSection = 0;
	xOffset = 0.0f;
	yOffset = 0.0f;

}

//sets up individual jobs
void generationManager::startJobCreator()
{
	unique_lock<mutex> lock(jobCreator);
	
	while (isRunning)
	{
	
			waitOnJob.wait(lock, []{return newJob; }); //waits until a job is needed
			//set up job
		
			iterationLock.lock();
			jobIterations = maxIterations;
			iterationLock.unlock();
			offsetLock.lock();
			for (int jobIndex = 0; jobIndex < TOTAL_SECTIONS; jobIndex++)
			{
				jobList[jobIndex].horizontalPosition = jobIndex;
				jobList[jobIndex].xOffset = xOffset;
				jobList[jobIndex].yOffset = yOffset;
				jobList[jobIndex].zoom = zoom;
			
			}
			
			offsetLock.unlock();
			newJob = false;
			jobBarrier->wait();
			jobBarrier->wait();
	}
}

void generationManager::fractalGeneration(int threadID)
{
	
	while (isRunning)
	{
		
		
			jobBarrier->wait();
			//make sure slices available
			if (currentSet != NULL)
			{
				finishedGeneration = false;
			}
			currentSection = 0;
			//loops through sections until generation finished
			while (currentSection < TOTAL_SECTIONS && currentSet != NULL)
			{
				currentSet->calculateSet(jobList[currentSection].horizontalPosition,
					jobList[currentSection].zoom,
					jobList[currentSection].xOffset,
					jobList[currentSection].yOffset, jobIterations);

				currentSection++;
			}


			finishedGeneration = true;
			jobBarrier->wait();
			currentSection = 0;


			currentSet = NULL;
	}

}

void generationManager::setCurrentSet(fractalCreator* newSet)
{
	currentSet = newSet;
}

bool generationManager::getGenerationStatus()
{
	return finishedGeneration;
}


//functions for manipulating the calculated portion of the fractal
void generationManager::resetXOffset()
{
	offsetLock.lock();
	xOffset = 0.0f;
	offsetLock.unlock();
}

void generationManager::resetYOffset()
{
	offsetLock.lock();
	yOffset = 0.0f;
	offsetLock.unlock();
}
void generationManager::resetZoom()
{
	offsetLock.lock();
	zoom = 1.0f;
	offsetLock.unlock();
}
void generationManager::updateXOffset(float offsetChange)
{
	offsetLock.lock();
	xOffset += offsetChange * abs(1 / zoom);
	offsetLock.unlock();
}
void generationManager::updateYOffset(float offsetChange)
{
	offsetLock.lock();
	yOffset += offsetChange * abs(1 / zoom);
	offsetLock.unlock();
}
void generationManager::updateZoom(float zoomChange)
{
	offsetLock.lock();
	zoom += zoomChange;
	offsetLock.unlock();
}