#include "TextBox.h"
#include <iostream>




TextBox::TextBox(sf::Vector2f positionP, sf::Font& fontP) : SelectableElement(positionP), font(fontP)
{
    displayedText.setFont(font);
    displayedText.setCharacterSize(36);
    displayedText.setFillColor(sf::Color::Green); 
    displayedText.setPosition(position.x+contourWidth, position.y+contourWidth);
}


void TextBox::handleInput(sf::Event& event)
{
    if(event.type == sf::Event::TextEntered && keyReleased == true)
    {
        //check if the character is printable
        if(event.text.unicode == '\b')
        {
            if(!text.empty())
                text.pop_back();
        }
            
        else if(event.text.unicode< 0x80)//normal ascii char
        {
            if(text.length() < maxLength)
                text.append(1,(char)event.text.unicode);
        }
        keyReleased = false;
     } 
    if(event.type == sf::Event::KeyReleased)
    {
        keyReleased = true;
        
    }
    displayedText.setString(text);
}

void TextBox::draw(sf::RenderTarget& target)
{
    SelectableElement::draw(target);
    target.draw(displayedText);
}