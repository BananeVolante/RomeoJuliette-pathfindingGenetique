#include "PathManager.h"
#include <algorithm>

PathManager::PathManager(Map &mapP, size_t pathLenP, size_t pathNumberP, float baseElementP)
 : pathLen(pathLenP), pathNumber(pathNumberP), baseElement(baseElementP), map(mapP), directionDistrib(1,5), 
 scoreModulatorDistrib(0.9,1.1)
{
}

PathManager::~PathManager()
{
    for (auto &&i : dnaList)
    {
        free(i);
    }
    
}


point PathManager::evaluateEndPoint(point* path)
{
    point end{0,0};
    for (size_t i = 0; i < pathLen; i++)
    {
        end.x += path[i].x;
        end.y += path[i].y;
    }
    return end;
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
        point tmpPos;
        for (size_t j = 0; j < pathLen; j++)
        {
            do
            {
                int roll = directionDistrib(generator);
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

                tmpPos.x = currentPos.x + currentPath[j].x;
                tmpPos.y = currentPos.y + currentPath[j].y;
            } while (map.isInObstacle(tmpPos));

            currentPos = tmpPos;
        }
        
    }
    
}

bool PathManager::scoreComparer(scoreWithId const& lhs, scoreWithId const& rhs)
{
    return lhs.score>rhs.score;
}

void PathManager::orderByScoreRandomed()
{
    //score is the distance * [0.9,1.1]
    struct scoreWithId scoreArray[pathNumber];
    int i = 0;
    for (auto &&path : dnaList)
    {
        
        scoreArray[i].score = map.getDistance(evaluateEndPoint(path));
        scoreArray[i].score *= scoreModulatorDistrib(generator);
        scoreArray[i].id = i;
        i++;
    }
        
    std::sort(scoreArray, scoreArray+pathNumber,PathManager::scoreComparer);
    
    std::vector<point*> newPathVector;
    for (size_t i = 0; i < pathNumber; i++)
    {
        newPathVector.push_back(dnaList.at(scoreArray[i].id));    
    }
    
}



void PathManager::printAllPaths()
{
    for (auto &&path : dnaList)
    {
        std:: cout << "-----------PATH---------\n";
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