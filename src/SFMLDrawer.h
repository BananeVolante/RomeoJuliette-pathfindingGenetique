#ifndef SFMLDrawer_HEADER
#define SFMLDrawer_HEADER

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "GeometricForms.h"
#include "Map.h"
#include "PathManager.h"


/*
coordinates used are
origin is top left
x/first component is width
y/second component is height
*/


class SFMLDrawer
{
private:
    // static because why not


    std::vector<sf::Shape*> cachedObstacles;
    const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
    Map &map;
    PathManager &pathManager;

    const float startAndEndPointSize;



public:
    SFMLDrawer(Map &map, PathManager &pahManager);
    ~SFMLDrawer();
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void drawAll(sf::RenderWindow &window);
    //UNIMPLEMENTED
    //void addRandomObstacles(int n);

    std::vector<Path> getList();
};

#endif

