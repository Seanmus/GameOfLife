#include "ofApp.h"

const int rows = 65;
const int columns = 50;

//Cannot be declared in header like this must be made global
std::vector<std::vector<bool> > cellGrid(
	rows,
	std::vector<bool>(columns, false));


void ofApp::setup() {
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {
	if(playing)
	{
		processCells();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	int gridWidth = screenWidth / columns;
	int gridHeight = screenHeight / rows;


	ofSetColor(0);
	//if (!mouseInScreen) { return; }
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (cellGrid[i][j] == true)
			{
				//Draws the pixels
				ofDrawRectangle(j * gridWidth, i * gridHeight, gridWidth, gridHeight);
			}
			if (mouseX > gridWidth * j && mouseX < gridWidth * (j + 1) && mouseY > gridHeight * i && mouseY < gridHeight * (i + 1)) {
				if (ofGetMousePressed() && mouseClicked == false)
				{
					mouseClicked = true;
					if (cellGrid[i][j] == false)
					{
						cellGrid[i][j] = true;
					}
					else
					{
						cellGrid[i][j] = false;
					}
				}
				else if (!ofGetMousePressed())
				{
					mouseClicked = false;
				}
			}
		}
	}
	//Draws the grid
	ofSetColor(128);
	for (int i = 1; i <= rows; i++) {
		ofDrawLine(0, i * gridHeight, screenWidth, i * gridHeight);
	}
	for (int i = 1; i <= columns; i++) {
		ofDrawLine(i * gridWidth, 0, i * gridWidth, screenHeight);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 32)
	{
		ofSetFrameRate(1);
		playing = !playing;
	}
}

void ofApp::processCells()
{
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	int gridWidth = screenWidth / columns;
	int gridHeight = screenHeight / rows;

	std::vector<std::vector<bool> > cellGridCopy = cellGrid;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int aliveInRadius = 0;
			bool aboveCell = i - 1 >= 0;
			bool belowCell = i + 1 < rows;
			bool leftCell = j - 1 >= 0;
			bool rightCell = j + 1 < columns;
			bool aboveLeftCell = i - 1 >= 0 && j - 1 >= 0;
			bool aboveRightCell = i - 1 >= 0 && j + 1 < columns;
			bool belowLeftCell = i + 1 < rows && j - 1 >= 0;
			bool belowRightCell = i + 1 < rows && j + 1 < columns;


			//Above
			if(aboveCell)
			{
				if(cellGrid[i-1][j] == true)
				{
					aliveInRadius++;
				} 
			}

			//Below
			if(belowCell)
			{
				if (cellGrid[i + 1][j] == true)
				{
					aliveInRadius++;
				}
			}

			//Left
			if(leftCell)
			{
				if (cellGrid[i][j - 1] == true)
				{
					aliveInRadius++;
				}
			}

			//Right
			if(rightCell)
			{
				if (cellGrid[i][j + 1] == true)
				{
					aliveInRadius++;
				}
			}

			//AboveLeft
			if (aboveLeftCell)
			{
				if (cellGrid[i - 1][j-1] == true)
				{
					aliveInRadius++;
				}
			}
			//AboveRight
			if (aboveRightCell)
			{
				if (cellGrid[i - 1][j + 1] == true)
				{
					aliveInRadius++;
				}
			}

			//BelowLeft
			if (belowLeftCell)
			{
				if (cellGrid[i + 1][j - 1] == true)
				{
					aliveInRadius++;
				}
			}

			//BelowRight
			if (belowRightCell)
			{
				if (cellGrid[i + 1][j + 1] == true)
				{
					aliveInRadius++;
				}
			}

			if (aliveInRadius < 2)
			{
				cellGridCopy[i][j] = false;

			}
			if(aliveInRadius == 3)
			{
				cellGridCopy[i][j] = true;
			}
			if(aliveInRadius > 3)
			{
				cellGridCopy[i][j] = false;
			}
		}
	}
	cellGrid = cellGridCopy;
}



