#include "display.h"
#include "mandelbrot.h"
#include "julia.h"




sf::Uint8 computedImage[WIDTH * HEIGHT * 4];
mutex iterationLock;//ensures itterations dont change until calculation copmplete
int maxIterations = 200;

int main()
{
	windowDisplay testWindow;

	testWindow.startThread();

	//windowThread.join();

	return 0;
}

