#include "Map.h"
#include "GeometricForms.h"
#include "SFMLDrawer.h"
#include <SFML/Graphics.hpp>
#include "PathManager.h"
#include "Path.h"
#include "Test.h"

#include <unistd.h>
#include <sstream>

#define USE_REDUCE 0
#define EXTEND_ON_CONVERGE 1



int testMain()
{
    Test t;
    std::cout << t.testPathMatrix() << std::endl;
    return 0;
}

int normalMain(int argc, char* argv[])
{

    point screenSize;
    point mapSize;
    point startPoint; point endPoint;
    int pathLen;int pathNumber;
    float baseElement;
    float lineWidth;
    int mutationChance;
    if(argc == 1)
    {
        screenSize = {1920,1080};
        mapSize = {1920,1080};
        startPoint ={0,0}; endPoint ={800,800};
        pathLen = 3000; pathNumber = 10;
        baseElement = 5;
        lineWidth = baseElement+0.001;
        mutationChance = 4;
        
    }else if (argc <13)
    {
        std::cout << "usage : " << argv[0] << " screenSizeX screenSizeY" 
        "mapSizeX mapSizeY startPointX startPointY pathLength NumberOfPaths baseElement mutationChance" << std::endl;
        exit(EXIT_FAILURE);
    } else
    {
        std::istringstream(argv[1]) >>screenSize.x;
        std::istringstream(argv[2]) >>screenSize.y;
        std::istringstream(argv[3]) >>mapSize.x;
        std::istringstream(argv[4]) >>mapSize.y;
        std::istringstream(argv[5]) >>startPoint.x;
        std::istringstream(argv[6]) >>startPoint.y;
        std::istringstream(argv[7]) >>endPoint.x;
        std::istringstream(argv[8]) >>endPoint.y;
        std::istringstream(argv[9]) >>pathLen;
        std::istringstream(argv[10]) >>pathNumber;
        std::istringstream(argv[11]) >>baseElement;
        std::istringstream(argv[12]) >>mutationChance;
    }
    

    

    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Genetic pathfinding!");


    Map map(mapSize.x, mapSize.y, startPoint, endPoint, lineWidth);
    PathManager manager(map, pathLen, pathNumber, baseElement, mutationChance, 100);

    SFMLDrawer drawer(map, manager, window);
    drawer.addRectangle(point{500,500}, 400,200);
    drawer.addLine(point{200,200}, 200);
    drawer.addLine(point{400,600}, 400);
    drawer.addCircle(point{300,100}, 90);
    drawer.addCircle(point{800,0}, 350);


    manager.fillRandomPaths();

    manager.orderByScoreRandomed(); 


    int frameNumber=0;
    bool stop = false;
    while (!stop && window.isOpen())
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

        bool converge = manager.testIfConverge();
        if(converge)
        {
            #if EXTEND_ON_CONVERGE == 1
                if(manager.findValidPath() == -1) // if the path isn't good for now, extend it
                    manager.extend();
                else 
                    stop = true;
            #else 
                stop = true; // stop if the algorithm converge
            #endif
        }

        #if USE_REDUCE == 1
        manager.reduce();
        #endif

        
        

        window.clear();
        drawer.drawAll();
        window.display();
        std::cout << "drawn frame : " << frameNumber  << " current pathLen = " << manager.getPathLength() << std::endl;
        frameNumber++;
    }
    



    return 0;
}


int main(int argc, char* argv[])
{
    #ifdef TESTING
        return testMain();
    #else
        return normalMain(argc, argv);
    #endif
}