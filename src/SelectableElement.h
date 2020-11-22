#include <SFML/Graphics.hpp>

class SelectableElement
{
private:
    sf::Vector2f position;
    sf::Vector2f size{300,100};
    bool isSelected = true;
    sf::RectangleShape elementSelectedContour{size};
    sf::RectangleShape elementBg{sf::Vector2f(size.x-30.0f, size.y-30.0f)};
public:
    SelectableElement( sf::Vector2f position);
    virtual void select();
    virtual void unselect();
    virtual void handleInput() = 0;
    virtual void draw(sf::RenderTarget& target);
};