#include "PathManager.h"


PathManager::PathManager(Map mapP, size_t pathLenP, size_t pathNumberP, float baseElementP)
 : pathLen(pathLenP), pathNumber(pathNumberP), baseElement(baseElementP), map(mapP), distrib(1,5)
{
}

PathManager::~PathManager()
{
    for (auto &&i : dnaList)
    {
        free(i);
    }
    
}

void PathManager::fillRandomPaths()
{
    dnaList.clear();
    for (size_t i = 0; i < pathNumber; i++)
    {
        point* currentPath = (point*)malloc(pathLen*sizeof(point));
        dnaList.push_back(currentPath);
        // that's a copy
        point currentPos = map.start;
        for (size_t j = 0; j < pathLen; j++)
        {
            do
            {
                int roll = distrib(generator);
                switch (roll)
                {
                case 1:
                    currentPath[j] = point{0,0};
                    break;
                case 2:
                    currentPath[j] = point{baseElement,0};
                    break;
                case 3:
                    currentPath[j] = point{-baseElement,0};
                    break;
                case 4:
                    currentPath[j] = point{0,baseElement};
                    break;
                case 5:
                    currentPath[j] = point{0,-baseElement};
                    break;

                }
                currentPos.x =+ currentPath[j].x;
                currentPos.y =+ currentPath[j].y;
            } while (map.isInObstacle(currentPos));
            
        }
        
    }
    
}


void PathManager::printAllPaths()
{
    for (auto &&path : dnaList)
    {
        std:: cout << "-----------PATH---------";
        for (size_t i = 0; i < pathLen; i++)
        {
            std::cout << "(" << path[i].x << "," << path[i].y<<")" << std::endl;
        }
        
    }
    
}

std::vector<point*> PathManager::getDnaList()
{
    return dnaList;
}