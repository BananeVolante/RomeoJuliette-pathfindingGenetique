#ifndef TextBox_HEADER
#define TextBox_HEADER
#include <string>
#include "point.h"
#include <SFML/Graphics.hpp>
#include "SelectableElement.h"

class TextBox : public SelectableElement
{
private:
    std::string text;
    bool keyReleased = true;
    
    sf::Font& font;
    sf::Text displayedText;

    unsigned int maxLength = 6;
public:
    TextBox(sf::Vector2f position, sf::Font& font);
    virtual void handleInput(sf::Event&);
    virtual void draw(sf::RenderTarget& target);
};



#endif


