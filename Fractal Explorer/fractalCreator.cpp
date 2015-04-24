#include "fractalCreator.h"


fractalCreator::fractalCreator()
{
	//fills colour pallette used to colourise set image. 
	for (int palletteFill = 0; palletteFill < PALLETTE_ENTRIES; palletteFill++)
	{
		if (palletteFill < RED_CHECK)
		{
			colourPallette[palletteFill].red = HALF - 1 - palletteFill * COLOUR_STEP;
		}
		else if (palletteFill < GREEN_CHECK)
		{
			colourPallette[palletteFill].red = 0;
			colourPallette[palletteFill].green = HALF - 1 - (palletteFill - RED_CHECK) * COLOUR_STEP;
		}
		else
		{
			colourPallette[palletteFill].red = 0;
			colourPallette[palletteFill].green = 0;
			colourPallette[palletteFill].blue = HALF - 1 - (palletteFill - GREEN_CHECK) * COLOUR_STEP;
		}
	}
}

//writes image data to memory for use as texture. May expand this to ba able to write to arbritrary image array.
void fractalCreator::writeTexture(int xPos, int yPos, int iterations)
{
	if (iterations == maxIterations)
	{
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET] = BLACK; //r
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 1] = BLACK; //g
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 2] = BLACK; //b
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 3] = OPAQUE; //a
	}
	else
	{
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET] = colourPallette[iterations % PALLETTE_ENTRIES].red; //r
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 1] = colourPallette[iterations % PALLETTE_ENTRIES].green; //g
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 2] = colourPallette[iterations % PALLETTE_ENTRIES].blue; //b
		computedImage[yPos * WIDTH * IMAGE_ARRAY_OFFSET + xPos * IMAGE_ARRAY_OFFSET + 3] = OPAQUE; //a
	}
}

