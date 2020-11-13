#include "SFMLDrawer.h"

SFMLDrawer::SFMLDrawer(Map &mapP, PathManager &pathManagerP) : map(mapP), pathManager(pathManagerP)
{

}

SFMLDrawer::~SFMLDrawer()
{
    for (auto &&i : cachedObstacles)
    {
        delete i;   
    }
    
}


void SFMLDrawer::addCircle(point center, float radius)
{
    sf::CircleShape* shape = new sf::CircleShape(radius);
    //base origin is the top left corner by default, i have to change it to its center
    shape->setOrigin(radius, radius);
    shape->setPosition(center.x, center.y);
    shape->setFillColor(DEFAULT_COLOR);
    cachedObstacles.push_back(shape);
    map.addCircle(center, radius);
}

void SFMLDrawer::addRectangle(point center, float width, float height)
{
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));
    //base origin is the top left corner by default, i have to change it to its center
    shape->setOrigin(width/2, height/2);
    shape->setPosition(center.x, center.y);
    shape->setFillColor(DEFAULT_COLOR);
    cachedObstacles.push_back(shape);
    map.addRectangle(center, width, height);
}

void SFMLDrawer::addLine(point center, float size)
{
    addRectangle(center, map.lineWidth, size);
}

void SFMLDrawer::drawAll(sf::RenderWindow &window)
{
    for (auto &&i : cachedObstacles)
    {
        window.draw(*i);
    }

    for (auto &&path : pathManager.getDnaList())
    {
        point lastPos = map.start;
        for (size_t i = 0; i < pathManager.pathLen; i++)
        {
            sf::Vertex line[] = 
            {
                sf::Vertex(sf::Vector2f(lastPos.x, lastPos.y)),
                sf::Vertex(sf::Vector2f(lastPos.x+path[i].x, lastPos.y + path[i].y))
            };
            window.draw(line, 2, sf::Lines);
            lastPos.x += path[i].x;
            lastPos.y += path[i].y;
        }
        
    }
    
}


std::vector<point*> SFMLDrawer::getList()
{
    return pathManager.getDnaList();
}


//TODO ---- IMPLEMENT
/*void SFMLDrawer::addRandomObstacles(int n)
{

}*/
