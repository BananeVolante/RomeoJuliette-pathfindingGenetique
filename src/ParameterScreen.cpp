#include "ParameterScreen.h"

ParameterScreen::ParameterScreen(sf::RenderWindow& windowP) : window(windowP) 
{
    
}

ParameterScreen::~ParameterScreen()
{
}


void ParameterScreen::display()
{
    std::vector<TextBox> textBoxes;
    unsigned int selectedId = 0;
    sf::Font font;
    if(!font.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr<<"error while loading font" << std::endl;
    }
    for (size_t i = 0; i < 10; i++)
    {
        textBoxes.push_back(TextBox(sf::Vector2f(300*(i%3), 200*(i/3)), font));  
    }
    textBoxes[selectedId].select();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased :
                case sf::Event::TextEntered : 
                    textBoxes[selectedId].handleInput(event);
                    break;
                case sf::Event::KeyPressed : 
                    if(event.key.code == sf::Keyboard::Left)
                    {
                        if(selectedId !=0)
                        {
                            textBoxes[selectedId].unselect();
                            selectedId--;
                            textBoxes[selectedId].select();
                        }
                    }
                    if(event.key.code == sf::Keyboard::Right)
                    {
                        if(selectedId != textBoxes.size()-1)
                        {
                            textBoxes[selectedId].unselect();
                            selectedId++;
                            textBoxes[selectedId].select();
                        }
                    }
                    break;
                default:
                    break;
            }
            
        }
        window.clear();
        for (auto &&i : textBoxes)
        {
            i.draw(window);
        }
        
        
        window.display();
        
    }


    
}