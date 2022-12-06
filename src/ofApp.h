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
		void randomizeCells();
		void clearGrid();
		void drawCells();
		void drawGrid();
		bool mouseClicked;
		bool playing = false;
		int generation = 0;
		ofTrueTypeFont uiFont;

		ClassyButton playButton{ Coordinate2D{900, 100}, "pauseButtonStatic.png", "pauseButtonHover.png" };
		ClassyButton stepButton{ Coordinate2D{100, 900}, "nextFrameButtonStatic.png","nextFrameButtonHover.png" };
		ClassyButton randomButton{ Coordinate2D{900, 900}, "randomButtonStatic.png", "randomButtonHover.png" };
		ClassyButton clearButton{ Coordinate2D{100,100}, "clearButtonStatic.png" , "clearButtonHover.png" };

};
