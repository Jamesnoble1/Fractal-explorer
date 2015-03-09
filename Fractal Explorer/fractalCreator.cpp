#include "fractalCreator.h"

fractalCreator::fractalCreator()
{
	//fills colour pallette used to colourise set image. 
	for (int palletteFill = 0; palletteFill < palletteEntries; palletteFill++)
	{
		if (palletteFill < redCheck)
		{
			colourPallette[palletteFill].red = 255 - palletteFill * colourStep;
		}
		else if (palletteFill < greenCheck)
		{
			colourPallette[palletteFill].red = 0;
			colourPallette[palletteFill].green = 255 - (palletteFill - 255) * colourStep;
		}
		else
		{
			colourPallette[palletteFill].red = 0;
			colourPallette[palletteFill].green = 0;
			colourPallette[palletteFill].blue = 255 - (palletteFill - 510) * colourStep;
		}
	}
}

//writes image data to memory for use as texture. May expand this to ba able to write to arbritrary image array.
void fractalCreator::writeTexture(int xPos, int yPos, int iterations)
{
	if (iterations == maxIterations)
	{
		computedImage[yPos * WIDTH * 4 + xPos * 4] = 0x00; //r
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 1] = 0x00; //g
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 2] = 0x00; //b
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 3] = 0x00; //a
	}
	else
	{
		computedImage[yPos * WIDTH * 4 + xPos * 4] = colourPallette[iterations % palletteEntries].red; //r
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 1] = colourPallette[iterations % palletteEntries].green; //g
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 2] = colourPallette[iterations % palletteEntries].blue; //b
		computedImage[yPos * WIDTH * 4 + xPos * 4 + 3] = 0xff; //a
	}
}