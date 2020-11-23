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


    const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
    Map &map;
    PathManager &pathManager;
    sf::RenderWindow& window;

    // the obstacles shapes and the stat and end point shapes
    sf::RenderTexture staticTextures;
    sf::Sprite obstacleSprite;


    sf::Sprite pathSprite;
    sf::RenderTexture pathTexture;

    const float startAndEndPointSize;
    sf::CircleShape startPointShape;
    sf::CircleShape endPointShape;

    point mapToWindowConversion;
    point mapToWindow(const point p) const;



public:
    SFMLDrawer(Map &map, PathManager &pathManager, sf::RenderWindow& window);
    ~SFMLDrawer() = default;
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void drawAll();
    //UNIMPLEMENTED
    //void addRandomObstacles(int n);

    std::vector<Path> getList();
};

#endif

