#include "SFMLDrawer.h"
#include <math.h>


SFMLDrawer::SFMLDrawer(Map &mapP, PathManager &pathManagerP, sf::RenderWindow& windowP) : 
map(mapP), pathManager(pathManagerP), window(windowP),
startAndEndPointSize(std::min(map.mapHitbox.height, map.mapHitbox.width)/100), 
startPointShape(startAndEndPointSize), endPointShape(startAndEndPointSize)
{

    mapToWindowConversion.x =  window.getSize().x / map.mapHitbox.width; 
    mapToWindowConversion.y =   window.getSize().y / map.mapHitbox.height;

    staticTextures.create(map.mapHitbox.width,map.mapHitbox.height);
    //must intialise obstacleSprite after calling create on the texture
    obstacleSprite = sf::Sprite(staticTextures.getTexture());

    pathTexture.create(map.mapHitbox.width,map.mapHitbox.height);
    pathSprite = sf::Sprite(pathTexture.getTexture());

    pathSprite.setScale(mapToWindowConversion.x, mapToWindowConversion.y);
    obstacleSprite.setScale(mapToWindowConversion.x, mapToWindowConversion.y);


    startPointShape.setOrigin(startAndEndPointSize, startAndEndPointSize);
    startPointShape.setPosition(map.start.x, map.start.y);
    startPointShape.setFillColor(sf::Color::Red);
    staticTextures.draw(startPointShape);


    endPointShape.setOrigin(startAndEndPointSize, startAndEndPointSize);
    endPointShape.setPosition(map.end.x, map.end.y);
    endPointShape.setFillColor(sf::Color::Red);
    staticTextures.draw(endPointShape);

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
    staticTextures.draw(shape);
    staticTextures.display();

    map.addCircle(center, radius);
}

void SFMLDrawer::addRectangle(point center, float width, float height)
{


    sf::RectangleShape shape(sf::Vector2f(width, height));
    //base origin is the top left corner by default, i have to change it to its center
    shape.setOrigin(width/2, height/2);
    shape.setPosition(center.x, center.y);
    shape.setFillColor(DEFAULT_COLOR);
    staticTextures.draw(shape);
    staticTextures.display();

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
        for (size_t i = 0; i < pathManager.getPathLength(); i++)
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



    
}


std::vector<Path> SFMLDrawer::getList()
{
    return pathManager.getDnaList();
}


//TODO ---- IMPLEMENT
/*void SFMLDrawer::addRandomObstacles(int n)
{

}*/
