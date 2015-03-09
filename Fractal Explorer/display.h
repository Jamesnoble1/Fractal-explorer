#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "globals.h"
#include "mandelbrot.h"
#include "julia.h"
#include <SFML/Graphics.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <sstream>

const int MENU_OPTIONS = 6;

enum programState {MENU, DRAWING, EXIT, IT_CHANGE};
enum setToProcess {NONE, UPDATE, MANDELBROT, JULIA}; //can be expanded for additional sets

class windowDisplay
{
public:
	windowDisplay();
	~windowDisplay();
	void startThread();

private:
	sf::RenderWindow window;
	sf::Event eventHandler;
	sf::Font displayFont;
	sf::Text waitText, currentInput, itrTitle;
	sf::Text menuText[MENU_OPTIONS];
	sf::Text exitText[2];
	sf::String itrInput;
	sf::String menuString[MENU_OPTIONS];
	sf::Sprite testSprite;
	sf::Texture testTex;
	julia juliaSet;
	mandelbrot mandelbrotSet;
	programState currentState;
	setToProcess currentSet;
	thread * generateSet;

	bool isRunning = true;
	bool setGenerated = false;
	void updateWindow();
	void processEvent(); //processes window and input events
	void updateSpirte(); //updates sprite texture once new image has been generated
};

#endif