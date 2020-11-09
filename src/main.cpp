#include "Map.h"
#include "GeometricForms.h"
#include "SFMLDrawer.h"
#include <SFML/Graphics.hpp>


int main(int argc, char const *argv[])
{
    Map map(1000,1000);
   SFMLDrawer drawer(map);
   drawer.addCircle(point{500,500}, 200);
   drawer.addRectangle(point{100,100}, 50,50);
   drawer.addLine(point{700,900}, 1000);
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        drawer.drawAll(window);
        window.display();
    }



    return 0;
}

