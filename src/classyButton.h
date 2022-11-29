#pragma once
#pragma once
#include "ofImage.h"
#include "coord.h"
class ClassyButton
{
public:
	ClassyButton(const Coordinate2D coord, std::string restingImagePath, std::string hoverImagePath);
	void checkHover(Coordinate2D mouseCoords);
	void draw();
	bool checkClick(Coordinate2D mouseCoords) const;
private:
	Coordinate2D coord;
	ofImage hoverImage;
	ofImage restingImage;
	ofImage currentImage;
};