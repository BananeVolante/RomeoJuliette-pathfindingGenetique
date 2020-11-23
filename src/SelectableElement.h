#ifndef SelectableElement_HEADER
#define SelectableElement_HEADER
#include <SFML/Graphics.hpp>



class SelectableElement
{
protected:
    sf::Vector2f position;
    sf::Vector2f size{250,100};
    float contourWidth=15;
    bool isSelected = false;
    sf::RectangleShape elementSelectedContour{size};
    sf::RectangleShape elementBg{sf::Vector2f(size.x-(contourWidth*2), size.y-(contourWidth*2))};


    sf::Text title;
    sf::Font& font;
public:
    SelectableElement(sf::Vector2f position, std::string title, sf::Font& font);
    virtual void select();
    virtual void unselect();
    virtual void handleInput(sf::Event&) = 0;
    virtual void draw(sf::RenderTarget& target);
};
#endif

