#include "ofApp.h"

const int rows = 65;
const int columns = 65;

//Cell state enum
enum class CellState { alive, dead };
//The cell grid
std::vector<std::vector<CellState> > cellGrid(
	rows,
	std::vector<CellState>(columns, CellState::dead));

/// <summary>
/// Sets the background colour and loads the UI font.
/// </summary>
void ofApp::setup() {
	ofBackground(255);
	uiFont.loadFont("Sigmar.ttf", 30);
}

/// <summary>
/// Proccesses cells if the game is being played currently
/// </summary>
void ofApp::update() {
	if(playing)
	{
		processCells();
	}
}

/// <summary>
/// Draws the ui, cells and grid to the screen.
/// </summary>
void ofApp::draw() {
	drawCells();
	drawGrid();
	ofSetColor(128);
	playButton.draw();
	stepButton.draw();
	randomButton.draw();
	clearButton.draw();
	const std::string generationString = "Generation: " + std::to_string(generation);
	uiFont.drawString(generationString, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

/// <summary>
/// Checks if the mouse is hovering any of the buttons when it is moved.
/// </summary>
/// <param name="x">The x position of the mouse.</param>
/// <param name="y">The y position of the mouse.</param>
void ofApp::mouseMoved(int x, int y) {
	playButton.checkHover(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) });
	stepButton.checkHover(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) });
	randomButton.checkHover(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) });
	clearButton.checkHover(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) });
}

/// <summary>
/// Checks if any of the buttons are cells are being hovered by the mouse when it is released if so their individual functionality is played.
/// </summary>
/// <param name="x">The x position of the mouse.</param>
/// <param name="y">The y position of the mouse.</param>
/// <param name="button">The mouse button.</param>
void ofApp::mouseReleased(int x, int y, int button) {
	if (playButton.checkClick(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) }))
	{
		ofSetFrameRate(1);
		playing = !playing;
		if (!playing) {
			ofSetFrameRate(60);
		}
	}
	else if(stepButton.checkClick(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) }))
	{
		processCells();
	}
	else if (randomButton.checkClick(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) }))
	{
		randomizeCells();
	}
	else if (clearButton.checkClick(Coordinate2D{ static_cast<float>(x), static_cast<float>(y) }))
	{
		clearGrid();
	}
	else {
		int screenWidth = ofGetWidth();
		int screenHeight = ofGetHeight();
		int mouseX = ofGetMouseX();
		int mouseY = ofGetMouseY();

		int gridWidth = screenWidth / columns;
		int gridHeight = screenHeight / rows;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (mouseX > gridWidth * j && mouseX < gridWidth * (j + 1) && mouseY > gridHeight * i && mouseY < gridHeight * (i + 1)) {
					{
						mouseClicked = true;
						if (cellGrid[i][j] == CellState::dead)
						{
							cellGrid[i][j] = CellState::alive;
						}
						else
						{
							cellGrid[i][j] = CellState::dead;
						}
					}
				}
			}
		}
	}

}

/// <summary>
/// Checks the status of the surronding cells to see how many alive neighbor each cell has
/// </summary>
void ofApp::processCells()
{
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	int gridWidth = screenWidth / columns;
	int gridHeight = screenHeight / rows;

	std::vector<std::vector<CellState> > cellGridCopy = cellGrid;

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
				if(cellGrid[i-1][j] == CellState::alive)
				{
					aliveInRadius++;
				} 
			}
			//Below
			if(belowCell)
			{
				if (cellGrid[i + 1][j] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			//Left
			if(leftCell)
			{
				if (cellGrid[i][j - 1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			//Right
			if(rightCell)
			{
				if (cellGrid[i][j + 1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			//AboveLeft
			if (aboveLeftCell)
			{
				if (cellGrid[i - 1][j-1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}
			//AboveRight
			if (aboveRightCell)
			{
				if (cellGrid[i - 1][j + 1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			//BelowLeft
			if (belowLeftCell)
			{
				if (cellGrid[i + 1][j - 1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			//BelowRight
			if (belowRightCell)
			{
				if (cellGrid[i + 1][j + 1] == CellState::alive)
				{
					aliveInRadius++;
				}
			}

			if (aliveInRadius < 2)
			{
				cellGridCopy[i][j] = CellState::dead;

			}
			if(aliveInRadius == 3)
			{
				cellGridCopy[i][j] = CellState::alive;
			}
			if(aliveInRadius > 3)
			{
				cellGridCopy[i][j] = CellState::dead;
			}
		}
	}
	generation++;
	cellGrid = cellGridCopy;
}

/// <summary>
/// Has a 35% chance of making each cell alive.
/// </summary>
void ofApp::randomizeCells()
{
	srand(time(NULL));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int randomNum = rand() % 100 + 1;
			if (randomNum <= 35) {
				cellGrid[i][j] = CellState::alive;
			}
			else {
				cellGrid[i][j] = CellState::dead;
			}

		}
	}
}
/// <summary>
/// Clears all of the alive cells from the grid
/// </summary>
void ofApp::clearGrid()
{
	generation = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cellGrid[i][j] = CellState::dead;
		}
	}
}

/// <summary>
/// Draws the cells to the grid
/// </summary>
void ofApp::drawCells()
{
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	int gridWidth = screenWidth / columns;
	int gridHeight = screenHeight / rows;
	ofSetColor(0, 255, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (cellGrid[i][j] == CellState::alive)
			{
				ofDrawRectangle(j * gridWidth, i * gridHeight, gridWidth, gridHeight);
			}
		}
	}
}

/// <summary>
/// Draws the grid lines
/// </summary>
void ofApp::drawGrid()
{
	ofSetColor(128);
	int screenWidth = ofGetWidth();
	int screenHeight = ofGetHeight();
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	int gridWidth = screenWidth / columns;
	int gridHeight = screenHeight / rows;
	for (int i = 1; i <= rows; i++) {
		ofDrawLine(0, i * gridHeight, screenWidth, i * gridHeight);
	}
	for (int i = 1; i <= columns; i++) {
		ofDrawLine(i * gridWidth, 0, i * gridWidth, screenHeight);
	}
}





