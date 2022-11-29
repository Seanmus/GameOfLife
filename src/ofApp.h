#pragma once

#include "classyButton.h"
#include "coord.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mouseReleased(int x, int y, int button);

		void processCells();
		bool mouseClicked;
		bool playing = false;
		int generation = 0;
		ofTrueTypeFont uiFont;

		ClassyButton playButton{ Coordinate2D{static_cast<float>(ofGetWidth() / 1.2), 100}, "pauseButtonStatic.png", "pauseButtonHover.png" };
};
