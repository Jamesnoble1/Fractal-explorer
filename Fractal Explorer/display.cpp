#include "display.h"

windowDisplay::windowDisplay()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE); //creates window and sets title bar
	
	window.setActive(false); //deactivates window to allow new thread to controll window
	
	currentSet = NONE;

	//loads in fonts
	if (!displayFont.loadFromFile(FONT))
	{
		std::cout << FONT_ERROR_MESSAGE << std::endl;
	}

	itrInput = DEFAULT_ITERATIONS;
	juliaInput[0] = JULIA_LINE_ONE
	juliaInput[1] = JULIA_LINE_TWO;

	menuString[0] = MENU_LINE_ONE;
	menuString[1] = MENU_LINE_TWO;
	menuString[2] = MENU_LINE_THREE;
	menuString[3] = MENU_LINE_FOUR;
	menuString[4] = MENU_LINE_FIVE;
	menuString[5] = MENU_LINE_SIX;

	//loads temp texture for sprite to initialise it
	sf::Image temp;
	temp.create(WIDTH, HEIGHT, computedImage);
	
	//set up sprite
	if (!displayTex.loadFromImage(temp))
	{
		std::cout << SPRITE_ERROR_MESSAGE;
	}
	displaySprite.setTexture(displayTex);
	displaySprite.setPosition(SPRITE_X, SPRITE_Y);

	//set up text used in program
	for (int setMenu = 0; setMenu < MENU_OPTIONS; setMenu++)
	{
		menuText[setMenu].setFont(displayFont);
		menuText[setMenu].setCharacterSize(FONT_SIZE);
		menuText[setMenu].setStyle(sf::Text::Regular);
		menuText[setMenu].setPosition(MENU_TEXT_X, MENU_TEXT_SPACING * setMenu);
		menuText[setMenu].setString(menuString[setMenu]);
	}


	currentInput.setFont(displayFont);
	currentInput.setCharacterSize(FONT_SIZE);
	currentInput.setStyle(sf::Text::Regular);
	currentInput.setPosition(TEXT_CENTRE_X, TEXT_OTHER_Y);


	itrTitle.setFont(displayFont);
	itrTitle.setCharacterSize(FONT_SIZE);
	itrTitle.setStyle(sf::Text::Regular);
	itrTitle.setPosition(TEXT_CENTRE_X, TEXT_CENTRE_Y);
	itrTitle.setString(ITERATION_TITLE_TEXT);
	
	juliaTitle.setFont(displayFont);
	juliaTitle.setCharacterSize(FONT_SIZE);
	juliaTitle.setStyle(sf::Text::Regular);
	juliaTitle.setPosition(TEXT_CENTRE_X, TEXT_CENTRE_Y);
	juliaTitle.setString(JULIA_TITLE);

	exitText[0].setString(EXIT_TEXT_ONE);
	exitText[1].setString(EXIT_TEXT_TWO);

	waitText.setString(WAIT_TEXT);
	waitText.setFont(displayFont);
	waitText.setCharacterSize(FONT_SIZE);
	waitText.setStyle(sf::Text::Regular);
	waitText.setPosition(TEXT_OTHER_X, TEXT_OTHER_Y);

	for (int setupIndex = 0; setupIndex < 2; setupIndex++)
	{
		exitText[setupIndex].setFont(displayFont);
		exitText[setupIndex].setCharacterSize(FONT_SIZE);
		exitText[setupIndex].setStyle(sf::Text::Regular);
		exitText[setupIndex].setPosition(TEXT_EXIT_X, TEXT_CENTRE_Y + TEXT_EXIT_OFFSET * setupIndex);
	}
	
	//initialises thread manager
	threadManager.init(&generationBarrier);

	//starts threads
	generateSet = new thread(std::bind(&generationManager::startJobCreator, &threadManager));

	for (int threadCreate = 0; threadCreate < MAX_THREADS; threadCreate++)
	{
		generationThreads.push_back(thread(std::bind(&generationManager::fractalGeneration, &threadManager, threadCreate)));
	}
	
	//bools to control program flow
	newJob = false;
	showMenu = true;
	confirmExit = false;
	changeIterations = false;
	changeJuliaConstant = false;
	juliaInputStage = REAL;
}

//main program loop
void windowDisplay::updateWindow()
{

	while (isRunning)
	{
		processEvent();

		if (threadManager.getGenerationStatus() == true)
		{
			updateSpirte();
		}

		window.draw(displaySprite);

		if (showMenu)
		{
			for (int displayMenu = 0; displayMenu < MENU_OPTIONS; displayMenu++)
			{
				window.draw(menuText[displayMenu]);
			}
		}

		//displays messages based on user input
		if (confirmExit)
		{
			window.draw(exitText[0]);
			window.draw(exitText[1]);
		}
		else if (changeIterations)
		{
			currentInput.setString(itrInput);
			window.draw(currentInput);
			window.draw(itrTitle);
		}
		else if (changeJuliaConstant)
		{
			currentInput.setString(juliaInput[juliaInputStage]);
			window.draw(currentInput);
			window.draw(juliaTitle);
		}

		window.display(); //displays updated window

		window.clear(); //clears for next frame

	}
}
//sets the window active in the new thread then enters main window loop
void windowDisplay::startProgram()
{
	window.setActive(true);
	updateWindow();
	generateSet->join();

	for (int threadEnd = 0; threadEnd < MAX_THREADS; threadEnd++)
	{
		generationThreads.at(threadEnd).join();
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

		//handles exit and exit confirmations
		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Escape)
		{
			confirmExit = true;
		}

		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Y && confirmExit)
		{
			newJob = true;
			waitOnJob.notify_all();
			isRunning = false;
		}

		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::N && confirmExit)
		{
			confirmExit = false;
		}

		//show menu
		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::M)
		{
			if (showMenu)
			{
				showMenu = false;
			}
			else
			{
				showMenu = true;
			}
		}
	
		//menu controls
		
		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Num1 && !changeIterations && !changeJuliaConstant)
			{
				threadManager.resetXOffset();
				threadManager.resetYOffset();
				threadManager.resetZoom();
				currentSet = MANDELBROT;
				setUpdate();
			
			}

		if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Num2 && !changeIterations && !changeJuliaConstant)
			{
				
				threadManager.resetXOffset();
				threadManager.resetYOffset();
				threadManager.resetZoom();
				currentSet = JULIA;
				setUpdate();
			}


			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::F1)
			{
				changeIterations = true;
				
			}

			if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::F2)
			{
				changeJuliaConstant = true;
				
			}

		//manages moving around the image
	
		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::Up || eventHandler.key.code == sf::Keyboard::W))
		{
			threadManager.updateYOffset(-MOVE_STEP);
			setUpdate();
		}

		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::Down || eventHandler.key.code == sf::Keyboard::S))
		{
			threadManager.updateYOffset(MOVE_STEP);
			setUpdate();		
		}

		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::Left || eventHandler.key.code == sf::Keyboard::A))
		{
			threadManager.updateXOffset(-MOVE_STEP);
			setUpdate();
		}
		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::Right|| eventHandler.key.code == sf::Keyboard::D))
		{
			threadManager.updateXOffset(MOVE_STEP);
			setUpdate();
		}

		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::PageUp || eventHandler.key.code == sf::Keyboard::E))
		{
			threadManager.updateZoom(MOVE_STEP);
			setUpdate();
		}

		if (eventHandler.type == sf::Event::KeyPressed && (eventHandler.key.code == sf::Keyboard::PageDown || eventHandler.key.code == sf::Keyboard::Q))
		{
			threadManager.updateZoom(-MOVE_STEP);
			setUpdate();
		}
		

		//handles user text input
		if (eventHandler.type == sf::Event::TextEntered)
		{
			//updates iterations
			if (changeIterations)
			{
				if (eventHandler.text.unicode >= UNICODE_ZERO && eventHandler.text.unicode <= UNICODE_NINE)
				{
					itrInput.insert(itrInput.getSize(), eventHandler.text.unicode);
				}
				else if (eventHandler.text.unicode == UNICODE_BACKSPACE && itrInput.getSize() > ITERATION_INPUT_START)
				{
					itrInput.erase(itrInput.getSize() - 1);
				}
				else if (eventHandler.text.unicode == UNICODE_RETURN) //on pressing return take updated iteration value
				{
					std::istringstream tempstr(itrInput.substring(ITERATION_INPUT_START));
					iterationLock.lock();
					tempstr >> maxIterations;
					iterationLock.unlock();
					changeIterations = false;
				}
				
			}
			else if (changeJuliaConstant) //updates julia constant, waits until iterations have been changed if needed
			{
				//enters numbers if between 0-9 or -, .
				if (eventHandler.text.unicode >= UNICODE_ZERO && eventHandler.text.unicode <= UNICODE_NINE || eventHandler.text.unicode == UNICODE_DECIMAL || eventHandler.text.unicode == UNICODE_MINUS)
				{
					juliaInput[juliaInputStage].insert(juliaInput[juliaInputStage].getSize(), eventHandler.text.unicode);
				} 
				else if (eventHandler.text.unicode == UNICODE_BACKSPACE && itrInput.getSize() > JULIA_INPUT_START)
				{
					juliaInput[juliaInputStage].erase(juliaInput[juliaInputStage].getSize() - 1);
				}
				else if (eventHandler.text.unicode == UNICODE_RETURN) //on pressing return take updated  value
				{
					std::istringstream tempstr(juliaInput[juliaInputStage].substring(JULIA_INPUT_START));

					double tempDouble;
					
					iterationLock.lock();
					tempstr >> tempDouble;
					iterationLock.unlock();
					
					//updates correct entry
					if (juliaInputStage == REAL)
					{
						juliaInputStage = IMAG;
						k.real(tempDouble);
					}
					else
					{
						changeJuliaConstant = false;
						juliaInputStage = REAL;
						k.imag(tempDouble);
					}
				}
				currentInput.setString(juliaInput[REAL]);
			}
		}
	}
}

//updates texture on sprite from calculated image
void windowDisplay::updateSpirte()
{
					   //Loads set from memory to an sf::image to use as a texture.
					   sf::Image temp;
					   temp.create(WIDTH, HEIGHT, computedImage);
					 
					   //set up sprite
					   if (!displayTex.loadFromImage(temp))
					   {
						   std::cout << SPRITE_ERROR_MESSAGE;
					   }
				
					   displaySprite.setTexture(displayTex);
}

//orders creation of new job list wehn ever set veiw is changed
void windowDisplay::setUpdate()
{
	switch (currentSet)
	{
	case MANDELBROT:
	{
		 threadManager.setCurrentSet(&mandelbrotSet);
		 newJob = true;
		 waitOnJob.notify_all();
		 break;
	}
	case JULIA:
	{
		threadManager.setCurrentSet(&juliaSet);
		newJob = true;
		waitOnJob.notify_all();
		break;
	}

	default:
		break;
	}	
}


windowDisplay::~windowDisplay()
{
	delete generateSet;
}

