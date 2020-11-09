#ifndef SFMLDrawer_HEADER
#define SFMLDrawer_HEADER

#include <SFML/Graphics.hpp>
#include <vector>
#include "GeometricForms.h"
#include "Map.h"


class SFMLDrawer
{
private:
    std::vector<sf::Shape*> cachedObstacles;
    const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
    Map map;

    void fillObstacleCache(std::vector<GeometricForm*> obstacleList);


public:
    SFMLDrawer(Map map);
    ~SFMLDrawer();
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void drawAll(sf::RenderWindow &window);
};

#endif

