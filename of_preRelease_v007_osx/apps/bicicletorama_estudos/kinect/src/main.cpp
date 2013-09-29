#include "kinectBox2d.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_FULLSCREEN);
	ofRunApp(new kinectBox2d());
}
