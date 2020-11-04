#include "Map.h"

#include "stdio.h"
Map::Map()
{
    obstacleList = std::vector<GeometricForm*>();
}

Map::~Map()
{
    for (auto &&i : obstacleList)
    {
        delete i;
    }
    
}

void Map::addForm(GeometricForm* form) 
{
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
        printf("c \n");
    }
    
}