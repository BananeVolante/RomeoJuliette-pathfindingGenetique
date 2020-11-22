#include <string>
#include "point.h"
#include <SFML/Graphics.hpp>
#include "SelectableElement.h"

class TextBox : public SelectableElement
{
private:
    std::string text;
public:
    TextBox(sf::Vector2f position);
    virtual void handleInput();
    ~TextBox();
};

TextBox::TextBox(sf::Vector2f positionP) : SelectableElement(positionP) 
{
}
TextBox::~TextBox()
{
}

void TextBox::handleInput()
{

}

