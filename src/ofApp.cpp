#include "ofApp.h"

const int rows = 65;
const int columns = 50;

//Cannot be declared in header like this must be made global
std::vector<std::vector<bool> > image(
	rows,
	std::vector<bool>(columns, false));


void ofApp::setup() {
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {

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
			if (image[i][j] == true)
			{
				//Draws the pixels
				ofDrawRectangle(j * gridWidth, i * gridHeight, gridWidth, gridHeight);
			}
			if (mouseX > gridWidth * j && mouseX < gridWidth * (j + 1) && mouseY > gridHeight * i && mouseY < gridHeight * (i + 1)) {
				if (ofGetMousePressed() && mouseClicked == false)
				{
					mouseClicked = true;
					if (image[i][j] == false)
					{
						image[i][j] = true;
					}
					else
					{
						image[i][j] = false;
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

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
