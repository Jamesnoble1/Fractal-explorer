#ifndef DISPLAY_DEFINES_H
#define DISPLAY_DEFINES_H

//Program text 
#define WINDOW_TITLE "Fractal Explorer"

#define FONT "arial.ttf"
#define FONT_ERROR_MESSAGE "Font loading failed"

#define DEFAULT_ITERATIONS "Iterations: 200"


#define JULIA_LINE_ONE "Real: 0.0";
#define JULIA_LINE_TWO "Imag: 0.0"

#define MENU_LINE_ONE "Menu = M"
#define MENU_LINE_TWO "Exit = ESC"
#define MENU_LINE_THREE "Set Maximum Iterations = F1"
#define MENU_LINE_FOUR "Set Julia set constant = F2"
#define MENU_LINE_FIVE "Generate Mandelbrot = 1"
#define MENU_LINE_SIX "Generate Julia set = 2"

#define SPRITE_ERROR_MESSAGE "Failed to load image"

#define ITERATION_TITLE_TEXT "Please enter maximum iterations to perform."
#define JULIA_TITLE "Please enter real and imaginary part."

#define EXIT_TEXT_ONE "Are you sure you want to quit?"
#define EXIT_TEXT_TWO "Y to exit or N to cancel"

#define WAIT_TEXT "No set generated"

//constants 
#define FONT_SIZE 20
#define SPRITE_X 0.0f
#define SPRITE_Y 0.0f

#define MENU_TEXT_X 0.0f
#define MENU_TEXT_SPACING 20.0f

#define TEXT_CENTRE_X 150.0f
#define TEXT_CENTRE_Y 250.0f

#define TEXT_OTHER_X 300.0f
#define TEXT_OTHER_Y 300.0f

#define TEXT_EXIT_X 200.0f
#define TEXT_EXIT_OFFSET 100

#define ITERATION_INPUT_START 12

#define JULIA_INPUT_START 6

#define MOVE_STEP  0.2f
#define MENU_OPTIONS  6
#define JULIA_LINES 2
#define EXIT_LINES 2
#define REAL  0
#define IMAG 1
#define	UNICODE_ZERO  0x30
#define	UNICODE_NINE  0x39
#define UNICODE_BACKSPACE  0x08
#define UNICODE_RETURN  0x0D
#define UNICODE_MINUS  0x2D
#define UNICODE_DECIMAL  0x2E

#endif