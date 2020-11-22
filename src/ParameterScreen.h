#ifndef ParameterScreen_H
#define ParameterScreen_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "PathManager.h"
#include "SFMLDrawer.h"
#include "TextBox.h"

class ParameterScreen
{
private:
    sf::RenderWindow& window;
public:
    ParameterScreen(sf::RenderWindow& window);
    ~ParameterScreen();

    typedef struct geneticAlgorithmObjects
    {
        PathManager& manager;
        Map& map;
        SFMLDrawer& drawer;
    } geneticAlgorithmObjects;



    void display();
};



#endif
