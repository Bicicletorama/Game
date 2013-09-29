#include "mask.h"

//================================================================
// VARIAVEIS ESTATICAS
//================================================================
int Mask::width = 200;
int Mask::height = 100;
ofImage Mask::mask;
unsigned char * Mask::pixel;
bool Mask::bActivePaint = false;
bool Mask::bIsShiftDown = false;

//================================================================
// SETUP
//================================================================
void Mask::setup(int width, int height)
{
	if (Mask::mask.loadImage("mask.png"))
	{
		Mask::pixel = Mask::mask.getPixels();
	}
	else
	{
		Mask::mask.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	
		Mask::pixel = new unsigned char[width * height * 4];

		memset(Mask::pixel, 0, width * height * 4);

		Mask::mask.setFromPixels(Mask::pixel, width, height, OF_IMAGE_COLOR_ALPHA);
	}
}

//================================================================
// DRAW
//================================================================
void Mask::draw(int x, int y)
{
	//ofSetColor(0xffffff);
	ofSetColor( 255,255,255 );

	ofEnableAlphaBlending();
	Mask::mask.draw(0, 0);
	ofDisableAlphaBlending();

	if (Mask::bActivePaint)
	{
		if (Mask::width < 0) Mask::width = 0;
		if (Mask::height < 0) Mask::height = 0; 
		
		
		ofNoFill();
		ofRect(x, y, Mask::width, Mask::height);
		ofFill();
	}
}

//================================================================
// PAINT
//================================================================
void Mask::paint(int x, int y, int button)
{	
	if (button == 0 && !Mask::bIsShiftDown)
	{
		if (Mask::bActivePaint)
		{
			
			for (int i = 0; i < Mask::width; i++)
			{
				for (int j = 0; j < Mask::height; j++)
				{
					if (y + j < 0 || y + j >= Mask::mask.height)
						continue;

					if (x + i < 0 || x + i >= Mask::mask.width)
						continue;
					
					Mask::pixel[(y + j) * Mask::mask.width * 4 + (x + i) * 4 + 0] = 0;
					Mask::pixel[(y + j) * Mask::mask.width * 4 + (x + i) * 4 + 1] = 0;
					Mask::pixel[(y + j) * Mask::mask.width * 4 + (x + i) * 4 + 2] = 0;
					Mask::pixel[(y + j) * Mask::mask.width * 4 + (x + i) * 4 + 3] = 255;
				}
			}
			Mask::mask.setFromPixels(Mask::pixel, Mask::mask.width, Mask::mask.height, OF_IMAGE_COLOR_ALPHA);
		}
	}
	else if (button == 0 && Mask::bIsShiftDown)
	{
		if (Mask::bActivePaint)
		{
			cout << "remove paint" << endl;
			for (int i = 0; i < Mask::width; i++)
			{
				for (int j = 0; j < Mask::height; j++)
				{
					if (y + j < 0 || y + j >= Mask::mask.height)
						continue;

					if (x + i < 0 || x + i >= Mask::mask.width)
						continue;

					Mask::pixel[(y + j) * Mask::mask.width * 4 + (x + i) * 4 + 3] = 0;
				}
			}
			Mask::mask.setFromPixels(Mask::pixel, Mask::mask.width, Mask::mask.height, OF_IMAGE_COLOR_ALPHA);
		}
	}
}

//================================================================
// SAVE MASK
//================================================================
void Mask::saveMask(void)
{
	cout << "save mask" << endl;
	if (Mask::bActivePaint)
		Mask::mask.saveImage("mask.png");
}