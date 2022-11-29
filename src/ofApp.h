#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);


		void processCells();
		bool mouseClicked;
		bool playing = false;
};
