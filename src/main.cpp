#include "Map.h"
#include "GeometricForms.h"
#include "SFMLDrawer.h"
#include <SFML/Graphics.hpp>
#include "PathManager.h"
#include "Path.h"

#include <unistd.h>

int main()
{

    Map map(1000,1000);
    PathManager manager(map, 2000, 10, 5);

    SFMLDrawer drawer(map, manager);
    drawer.addRectangle(point{500,500}, 400,200);
    drawer.addLine(point{200,200}, 200);
    drawer.addLine(point{400,600}, 400);
    drawer.addCircle(point{300,100}, 90);
    //drawer.addCircle(point{800,0}, 350);


    manager.fillRandomPaths();

    std::cout << "\npathsFilled\n" << std::endl;
    manager.orderByScoreRandomed(); 


    //exit(0);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    int frameNumber=0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        manager.orderByScoreRandomed();
        manager.crossing();
        manager.mutate();

        window.clear();
        drawer.drawAll(window);
        window.display();
        std::cout << "\n\n\ndrawn frame : " << frameNumber << std::endl;
        frameNumber++;


    }



    return 0;
}

