#ifndef SelectableElement_HEADER
#define SelectableElement_HEADER
#include <SFML/Graphics.hpp>



class SelectableElement
{
protected:
    sf::Vector2f position;
    sf::Vector2f size{300,100};
    float contourWidth=15;
    bool isSelected = false;
    sf::RectangleShape elementSelectedContour{size};
    sf::RectangleShape elementBg{sf::Vector2f(size.x-(contourWidth*2), size.y-(contourWidth*2))};
public:
    SelectableElement( sf::Vector2f position);
    virtual void select();
    virtual void unselect();
    virtual void handleInput(sf::Event&) = 0;
    virtual void draw(sf::RenderTarget& target);
};
#endif

