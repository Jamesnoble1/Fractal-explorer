#ifndef DISPLAY_H
#define DISPLAY_H


#include "globals.h"
#include "display_defines.h"
#include "generationManager.h"
#include "mandelbrot.h"
#include "julia.h"
#include "barrier.h"
#include <SFML/Graphics.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <sstream>
#include <iostream>
#include <vector>

using std::vector;




enum currentSet {NONE, MANDELBROT, JULIA};


class windowDisplay
{
public:
	windowDisplay();
	~windowDisplay();
	void startProgram();

private:
	sf::RenderWindow window;
	sf::Event eventHandler;
	sf::Font displayFont;
	sf::Text waitText, currentInput, itrTitle, juliaTitle;
	sf::Text menuText[MENU_OPTIONS];
	sf::Text exitText[EXIT_LINES];
	sf::String itrInput, juliaInput[JULIA_LINES];
	sf::String menuString[MENU_OPTIONS];
	sf::Sprite displaySprite;
	sf::Texture displayTex;
	julia juliaSet;
	mandelbrot mandelbrotSet;
	currentSet currentSet;
	thread * generateSet;
	vector<thread> generationThreads;
	generationManager threadManager;
	barrier generationBarrier;
	void setUpdate();
	int juliaInputStage;
	bool showMenu, confirmExit, changeIterations, changeJuliaConstant;
	bool setGenerated = false;
	void updateWindow();
	void processEvent(); //processes window and input events
	void updateSpirte(); //updates sprite texture once new image has been generated

};

#endif