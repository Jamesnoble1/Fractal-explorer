#include "display.h"

//definitions of global variables
complex<double> k(-0.7, 0.27015);
sf::Uint8 computedImage[WIDTH * HEIGHT * 4];
int maxIterations = 200;
bool isRunning = true;
bool newJob;
condition_variable waitOnJob;
mutex jobCreator;
mutex iterationLock;//ensures itterations dont change until calculation copmplete

int main()
{
	windowDisplay testWindow;

	testWindow.startProgram();

	return 0;
}

