#include "SFMLDrawer.h"
#include <math.h>


SFMLDrawer::SFMLDrawer(Map &mapP, PathManager &pathManagerP, sf::RenderWindow& windowP) : 
map(mapP), pathManager(pathManagerP), window(windowP),
startAndEndPointSize(std::min(map.mapHitbox.height, map.mapHitbox.width)/100)
{

    mapToWindowConversion.x = map.mapHitbox.width / window.getSize().x;
    mapToWindowConversion.y = map.mapHitbox.height / window.getSize().y;

    obstacleTexture.create(window.getSize().x, window.getSize().y);
    //must intialise obstacleSprite after calling create on the texture
    obstacleSprite = sf::Sprite(obstacleTexture.getTexture());

    pathTexture.create(window.getSize().x, window.getSize().y);
    pathSprite = sf::Sprite(pathTexture.getTexture());

}



point SFMLDrawer::mapToWindow(const point p) const
{
    return point
    {
        mapToWindowConversion.x * p.x,
        mapToWindowConversion.y * p.y,
    };
}

void SFMLDrawer::addCircle(point center, float radius)
{

    sf::CircleShape shape(radius);
    //base origin is the top left corner by default, i have to change it to its center
    shape.setOrigin(radius, radius);
    shape.setPosition(center.x, center.y);
    shape.setFillColor(DEFAULT_COLOR);
    obstacleTexture.draw(shape);
    obstacleTexture.display();

    map.addCircle(center, radius);
}

void SFMLDrawer::addRectangle(point center, float width, float height)
{


    sf::RectangleShape shape(sf::Vector2f(width, height));
    //base origin is the top left corner by default, i have to change it to its center
    shape.setOrigin(width/2, height/2);
    shape.setPosition(center.x, center.y);
    shape.setFillColor(DEFAULT_COLOR);
    obstacleTexture.draw(shape);
    obstacleTexture.display();

    map.addRectangle(center, width, height);
}

void SFMLDrawer::addLine(point center, float size)
{
    addRectangle(center, map.lineWidth, size);
}

void SFMLDrawer::drawAll()
{
    pathTexture.clear();

    for (auto &&path : pathManager.getDnaList())
    {
        point lastPos = map.start;
        for (size_t i = 0; i < pathManager.pathLen; i++)
        {
            sf::Vertex line[2] = 
            {
                sf::Vertex(sf::Vector2f(lastPos.x, lastPos.y)),
            };
            lastPos += path[i];
            line[1] = sf::Vertex(sf::Vector2f(lastPos.x, lastPos.y));

            pathTexture.draw(line, 2, sf::Lines);
        }
        
    }
    pathTexture.display();
    window.draw(pathSprite);
    window.draw(obstacleSprite);


    sf::CircleShape startPoint(startAndEndPointSize);
    startPoint.setOrigin(startAndEndPointSize, startAndEndPointSize);
    startPoint.setPosition(map.start.x, map.start.y);
    startPoint.setFillColor(sf::Color::Red);
    window.draw(startPoint);

    sf::CircleShape endPoint(startAndEndPointSize);
    endPoint.setOrigin(startAndEndPointSize, startAndEndPointSize);
    endPoint.setPosition(map.end.x, map.end.y);
    endPoint.setFillColor(sf::Color::Red);
    window.draw(endPoint);
    
}


std::vector<Path> SFMLDrawer::getList()
{
    return pathManager.getDnaList();
}


//TODO ---- IMPLEMENT
/*void SFMLDrawer::addRandomObstacles(int n)
{

}*/
