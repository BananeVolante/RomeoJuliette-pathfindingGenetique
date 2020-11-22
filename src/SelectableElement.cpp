#include "SelectableElement.h"


SelectableElement::SelectableElement(sf::Vector2f positionP) : position(positionP)
{
    elementSelectedContour.setFillColor(sf::Color::Red);
    elementSelectedContour.setPosition(position);
  //  elementBg.setPosition(sf::Vector2f(position.x-15.0f, position.y-15.0f));
  elementBg.setPosition(position);
  elementBg.move(sf::Vector2f(contourWidth, contourWidth));

}

void SelectableElement::select()
{
    isSelected = true;
}

void SelectableElement::unselect()
{
    isSelected = false;
}

void SelectableElement::draw(sf::RenderTarget& target)
{
    // instead of making a real contour, i draw a red rectangle then draw
    //the background a bit smaller on top of the contour
    if(isSelected)
        target.draw(elementSelectedContour);
    target.draw(elementBg);
}
