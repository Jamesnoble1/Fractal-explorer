#ifndef GENERATION_MANAGER
#define GENERATION_MANAGER

#include "globals.h"
#include "barrier.h"
#include "fractalCreator.h"
#include <fstream>
#include <chrono>


const int TOTAL_SECTIONS = HEIGHT;


class generationManager
{

public:

	void init(barrier* usedBarrier);
	void startJobCreator();
	bool getGenerationStatus();
	void fractalGeneration(int threadID);
	void setCurrentSet(fractalCreator* newSet);
	void resetXOffset();
	void resetYOffset();
	void resetZoom();
	void updateXOffset(float offsetChange);
	void updateYOffset(float offsetChange);
	void updateZoom(float zoomChange);

private:
	struct jobDetails
	{
		int horizontalPosition;
		float xOffset;
		float yOffset;
		float zoom;
	};

	int currentSection;
	int jobIterations;
	float xOffset, yOffset, zoom;
	bool finishedGeneration;
	mutex sectionLock, offsetLock;
	
	jobDetails jobList[TOTAL_SECTIONS];
	fractalCreator* currentSet;
	barrier* jobBarrier;

	

	

};

#endif
