#include "Test.h"

Test::Test(/* args */)
{
}

Test::~Test()
{
}

bool Test::testPathMatrix()
{
    bool res = true;

    point mapSize = {100,100};
    size_t pathNumber = 10;
    PathMatrix p(mapSize, pathNumber);
    
    for (size_t pathId = 0; pathId < pathNumber; pathId++)
    {
        for (size_t x = 0; x < mapSize.x; x++)
        {
            for (size_t y = 0; y < mapSize.y; y++)
            {
                if(p.getElement(x,y,pathId) != 0) res = false;
            }
        }
    }

    p.setElement(33,37,2,true);

    for (size_t pathId = 0; pathId < pathNumber; pathId++)
    {
        for (size_t x = 0; x < mapSize.x; x++)
        {
            for (size_t y = 0; y < mapSize.y; y++)
            {
                if(p.getElement(x,y,pathId) != 0 && !(x==33 && y==37 && pathId==2)) res = false;
            }
        }
    }

    if(p.getElement(33,37,2) != true) res = false;

    p.setElement(34,37,2,true);
    p.setElement(34,37,3,true);
    if(p.getElement(34,37,2) != true) res = false;
    if(p.getElement(34,37,3) != true) res = false;
    p.setElement(34,37,2,false);
    if(p.getElement(34,37,2) != false) res = false;



    

    return res;
}
