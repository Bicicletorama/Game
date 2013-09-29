#ifndef _PIXEL_MASK_
#define _PIXEL_MASK_

#include "ofMain.h"

class Mask
{
private:
	Mask(void){};
	~Mask(void);

	static ofImage mask;
	static unsigned char * pixel;
	
public:
	static void setup(int width, int height);
	static void draw(int x, int y);
	static void paint(int x, int y, int button);
	static void saveMask(void);
	static void gui(void);

	static int width;
	static int height;
	static bool bActivePaint;
	static bool bIsShiftDown;
};

#endif