#include "Map.h"

#include <stdio.h>
#include <math.h>

Map::Map(float width, float height) : mapHitbox(point{.x=width/2, .y=height/2}, width, height),
 start(point{0,0}), end(point{1000, 1000})
{
    //if i want the top left corner's coordinates to be 0,0, the rectangle's
    //center must have these coordinates

    obstacleList = std::vector<GeometricForm*>();
}

Map::~Map()
{
    for (auto &&i : obstacleList)
    {
        delete i;
    }
    
}

// obstacles does not have to be completely inside the map, but their center
//must be in the map
void Map::addForm(GeometricForm* form) 
{
    if(!mapHitbox.isInHitbox(form->center))
        throw new std::invalid_argument("The forms' center must be inside the map");
    obstacleList.push_back(form);
}

void Map::addCircle(point center, float radius)
{
    addForm(new Circle(center,radius));
}

void Map::addRectangle(point center, float width, float height)
{
    addForm(new Rectangle(center, width, height));
}

void Map::addLine(point center, float size)
{
    addForm(new Rectangle(center,lineWidth,size));
}



float Map::getSquaredDistance(point p)
{
    //return (p.x - end.x)*(p.x - end.x) + (p.y-end.y)*(p.y-end.y);
    return SQUARE(p.x - end.x) + SQUARE(p.y-end.y);
}


bool Map::isInObstacle(point p)
{

    for (auto &&i : obstacleList)
    {
        if(i->isInHitbox(p))
            return true;
    }

    if(!mapHitbox.isInHitbox(p))
        return true;
    return false;
    
}



void Map::printAllForms()
{
    for (auto &&i : obstacleList)
    {
        std::cout << *i << std::endl;
    }
    
}

std::vector<GeometricForm*> Map::getList()
{
    return obstacleList;
}