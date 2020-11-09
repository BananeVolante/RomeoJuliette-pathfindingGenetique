#include "Map.h"

#include "stdio.h"
Map::Map(float width, float height) : mapHitbox(point{.x=width/2, .y=height/2}, width, height)
{
    //if i want the bottom left corner's coordinates to be 0,0, the rectangle's
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
    if(!mapHitbox.isInHitbox(form->getCenter()))
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
    addForm(new Line(center, size));
}

void Map::addCircle(float x, float y, float radius)
{
    point center;
    center.x = x; center.y=y;
    addForm(new Circle(center, radius));
}

void Map::addRectangle(float x, float y, float width, float height)
{
    point center;
    center.x = x; center.y=y;
    addForm(new Rectangle(center, width, height));
}

void Map::addLine(float x, float y, float size)
{
    point center;
    center.x = x; center.y=y;
    addForm(new Line(center, size));
}

void Map::printAllForms()
{
    for (auto &&i : obstacleList)
    {
        std::cout << *i << std::endl;
    }
    
}