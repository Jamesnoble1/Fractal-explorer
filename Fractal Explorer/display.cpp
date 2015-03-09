#include "display.h"

std::mutex test;

windowDisplay::windowDisplay()
{
	window.create(sf::VideoMode(800, 600), "Fractal Explorer"); //creates window and sets title bar
	
	window.setActive(false); //deactivates window to allow new thread to controll window
	
	//loads in fonts
	if (!displayFont.loadFromFile("arial.ttf"))
	{
		std::cout << "Font loading failed" << std::endl;
	}
	
	itrInput = "Iterations: 200";

	menuString[0] = "Menu = M";
	menuString[1] = "Display = D";
	menuString[2] = "Exit = ESC";
	menuString[3] = "Set Maximum Iterations = F1";
	menuString[4] = "Generate Mandelbrot = 1";
	menuString[5] = "Generate Julia set = 2";


	//set up text
	for (int setMenu = 0; setMenu < MENU_OPTIONS; setMenu++)
	{
		menuText[setMenu].setFont(displayFont);
		menuText[setMenu].setCharacterSize(20);
		menuText[setMenu].setStyle(sf::Text::Regular);
		menuText[setMenu].setPosition(0, 20 * setMenu);
		menuText[setMenu].setString(menuString[setMenu]);
	}


	currentInput.setFont(displayFont);
	currentInput.setCharacterSize(20);
	currentInput.setStyle(sf::Text::Regular);
	currentInput.setPosition(150.0f, 300.0f);
	currentInput.setString(itrInput);

	itrTitle.setFont(displayFont);
	itrTitle.setCharacterSize(20);
	itrTitle.setStyle(sf::Text::Regular);
	itrTitle.setPosition(150.0f, 250.0f);
	itrTitle.setString("Please enter maximum iterations to perform.");
	

	for (int setupIndex = 0; setupIndex < 2; setupIndex++)
	{
		exitText[setupIndex].setFont(displayFont);
		exitText[setupIndex].setCharacterSize(20);
		exitText[setupIndex].setStyle(sf::Text::Regular);
		exitText[setupIndex].setPosition(200.0f, 250.0f + 100 * setupIndex);
	}
	
	exitText[0].setString("Are you sure you want to quit?");
	exitText[1].setString("ESC to exit or M to return to main menu");

	waitText.setString("No set generated");
	waitText.setFont(displayFont);
	waitText.setCharacterSize(20);
	waitText.setStyle(sf::Text::Regular);
	waitText.setPosition(300.0f, 300.0f);
	
	
	sf::Image temp;
	temp.create(WIDTH, HEIGHT, computedImage);
	//set up sprite
	if (!testTex.loadFromImage(temp))
	{
		std::cout << "borked";
	}
	test.lock();
	testSprite.setTexture(testTex);
	test.unlock();
	testSprite.setPosition(0.0f, 0.0f);
	currentState = MENU; //initial state for state machine
	generateSet = new thread(&windowDisplay::updateSpirte, this);


}

void windowDisplay::updateWindow()
{
	while (isRunning)
	{
		processEvent();
		switch (currentState)
		{
			case MENU: //User in menu
			{
				for (int displayMenu = 0; displayMenu < MENU_OPTIONS; displayMenu++)
				{
					window.draw(menuText[displayMenu]);
				}
				
				 break;
			}
			case DRAWING: //user veiwing fractal
			{
				if (!setGenerated)
				{
					window.draw(waitText);
				}
							  
				window.draw(testSprite);
					
				break;
			}
			case EXIT:
			{
				window.draw(exitText[0]);
				window.draw(exitText[1]);
				break;
			}
			case IT_CHANGE:
			{
					currentInput.setString(itrInput);
					window.draw(currentInput);
					window.draw(itrTitle);
							  break;
			}
			default:
			{
				break;
			}
		}

		window.display(); //displays updated window
		
		window.clear(); //clears for next frame
	}
}
	
//sets the window active in the new thread then enters main window loop
void windowDisplay::startThread()
{
	window.setActive(true);
	updateWindow();
	generateSet->join();
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
			if (currentState == EXIT)
			{
				isRunning = false;
			}
			else
			{
				currentState = EXIT;
			}
		}

		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::M)
		{
			currentState = MENU;
		}
	
		if (currentState == MENU)
		{
			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Num1)
			{
				currentSet = MANDELBROT;
			}

			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Num2)
			{
				currentSet = JULIA;
			}

			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::D)
			{
				currentState = DRAWING;
			}

			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::F1)
			{
				currentState = IT_CHANGE;
			}
		}

		//handles user text input
		if (eventHandler.type == sf::Event::TextEntered)
		{
			if (currentState == IT_CHANGE)
			{
				if (eventHandler.text.unicode >= 0x30 && eventHandler.text.unicode <= 0x39)
				{
					itrInput.insert(itrInput.getSize(), eventHandler.text.unicode);
				}
				else if (eventHandler.text.unicode == 0x08 && itrInput.getSize() > 12)
				{
					itrInput.erase(itrInput.getSize() - 1);
				}
				else if (eventHandler.text.unicode == 0x0D) //on pressing return take updated iteration value
				{
					std::istringstream tempstr(itrInput.substring(12));
					iterationLock.lock();
					tempstr >> maxIterations;
					iterationLock.unlock();
					std::cout << maxIterations;
				}
			}
		}
	}
}

void windowDisplay::updateSpirte()
{
	while (isRunning)
	{
	
		switch (currentSet)
		{
		case MANDELBROT:
		{
						   currentSet = UPDATE;
						   mandelbrotSet.startGeneration();
						

						   break;
		}
		case JULIA:
		{
						   currentSet = UPDATE;
						   juliaSet.startGeneration();
						  

						   break;
		}
		case UPDATE:
		{
					   setGenerated = true;
					   //Loads set from memory to an sf::image to use as a texture.
					   sf::Image temp;
					   temp.create(WIDTH, HEIGHT, computedImage);
					   //set up sprite
					   if (!testTex.loadFromImage(temp))
					   {
						   std::cout << "failed to load texture";
					   }
					   test.lock();
					   testSprite.setTexture(testTex);
					   test.unlock(); 
					   currentSet = NONE;
						   break;
		}
		default:
		{
				   break;
		}
		}
	}
}

	



windowDisplay::~windowDisplay()
{
	delete generateSet;
}