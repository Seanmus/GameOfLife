#include "classyButton.h"


/// <summary>
/// Initializes a button class
/// </summary>
/// <param name="coord">The position of the button.</param>
///	<param name="restingImagePath">The file path of the resting image.</param>
///	<param name="hoverImagePath">The file path of the hover image state.</param>
ClassyButton::ClassyButton(const Coordinate2D coord, std::string restingImagePath, std::string hoverImagePath)
{
	this->coord = coord;
	restingImage.load(restingImagePath);
	hoverImage.load(hoverImagePath);
	currentImage = restingImage;
	currentImage.setAnchorPoint(currentImage.getWidth() / 2, currentImage.getHeight() / 2);
}

/// <summary>
/// Checks if the mouse is hovering above and changes the image to a hover state if so.
/// </summary>
/// <param name="mouseCoords">The current position of the mouse.</param>
void ClassyButton::checkHover(Coordinate2D mouseCoords)
{
	if (checkClick(mouseCoords))
	{
		currentImage = hoverImage;
	}
	else
	{
		currentImage = restingImage;
	}
}
/// <summary>
/// Draws the button using the current image.
/// </summary>
void ClassyButton::draw()
{
	currentImage.draw(coord.x, coord.y);
}

/// <summary>
/// Checks collision against the provided coordinates
/// </summary>
/// <param name="mouseCoords">The current position of the mouse.</param>
bool ClassyButton::checkClick(Coordinate2D mouseCoords) const
{
	if (mouseCoords.x >= coord.x - currentImage.getWidth() / 2 && mouseCoords.x <= coord.x + currentImage.getWidth() / 2
		&& mouseCoords.y >= coord.y - currentImage.getHeight() / 2 && mouseCoords.y <= coord.y + currentImage.getHeight() / 2)
	{
		return true;
	}
	return false;
}



