#include "display.h"

windowDisplay::windowDisplay()
{
	window.create(sf::VideoMode(800, 600), "Fractal Explorer");
	window.setActive(false);
}

void windowDisplay::updateWindow()
{
	
	window.display();
}

void windowDisplay::startThread()
{
	window.setActive(true);

	while (isRunning)
	{
		processEvent();
		updateWindow();
	}
}

void windowDisplay::processEvent()
{
	//process events until none left
	while (window.pollEvent(eventHandler))
	{	
		//closes window upon request
		if (eventHandler.type == sf::Event::Closed)
		{
			isRunning = false;
		}

		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Escape)
		{
			isRunning = false;
		}
	}
}