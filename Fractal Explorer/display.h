#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <SFML\Window\Event.hpp>

class windowDisplay
{
public:
	windowDisplay();
	void startThread();

private:
	sf::RenderWindow window;
	sf::Event eventHandler;
	bool isRunning = true;
	void updateWindow();
	void processEvent(); //processes window and input events
};

#endif