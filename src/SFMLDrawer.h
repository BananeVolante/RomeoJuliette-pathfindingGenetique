#ifndef SFMLDrawer_HEADER
#define SFMLDrawer_HEADER

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "GeometricForms.h"
#include "Map.h"



class SFMLDrawer
{
private:
    // static because why not
    static std::default_random_engine generator;
    
    //these depends on the map size, it's not static
    std::uniform_real_distribution<float> xPlacementDistrib;
    std::uniform_real_distribution<float> yPlacementDistrib;
    //no differences for x and y in the size since 
    //not all forms have 2 size parameters
    std::uniform_real_distribution<float> sizeDistrib;


    std::vector<sf::Shape*> cachedObstacles;
    const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
    Map map;



public:
    SFMLDrawer(Map map);
    ~SFMLDrawer();
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void drawAll(sf::RenderWindow &window);
    //UNIMPLEMENTED
    void addRandomObstacles(int n);
};

#endif

