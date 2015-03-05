#include "display.h"
#include <thread>


using std::thread;

int main()
{
	windowDisplay testWindow;

	testWindow.startThread();

	return 0;
}