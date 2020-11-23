#include "SelectableElement.h"


SelectableElement::SelectableElement(sf::Vector2f positionP, std::string titleP, sf::Font& fontP) :
 position(positionP), font(fontP)
{
    elementSelectedContour.setFillColor(sf::Color::Red);
    elementSelectedContour.setPosition(position);
    //  elementBg.setPosition(sf::Vector2f(position.x-15.0f, position.y-15.0f));
    elementBg.setPosition(position);
    elementBg.move(sf::Vector2f(contourWidth, contourWidth));


    title.setFont(font);
    title.setCharacterSize(15);
    title.setPosition(position);
    title.setFillColor(sf::Color::Magenta); 
    title.setString(titleP);

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
    target.draw(title);
}
