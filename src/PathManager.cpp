#include "PathManager.h"
#include <algorithm>
#include <time.h>


PathManager::PathManager(Map &mapP, size_t pathLenP, size_t pathNumberP, float baseElementP)
:   pathLen(pathLenP), pathNumber(pathNumberP), baseElement(baseElementP), 
    map(mapP),generator(time(NULL)),  crossDistrib(0,pathLen) 
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
    point end = map.start;
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
                currentPath[j] = getRandomMovement();


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
    struct scoreWithId scoreArray[pathNumber];
    int i = 0;
    for (auto &&path : dnaList)
    {
        
        scoreArray[i].score = map.getSquaredDistance(evaluateEndPoint(path));
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
    dnaList = newPathVector;
}

// create 
void PathManager::crossing()
{
    //get 2 best paths
    point* worsePath = dnaList.at(0);
    point* secondWorsePath = dnaList.at(1);

    // get the 2 worse paths
    point* a = dnaList.at(dnaList.size()-1);
    point* b = dnaList.at(dnaList.size()-2);


    size_t crossoverPoint;
    size_t i=0; //crossIndex

    bool arePathsValid;

    do
    {

        point currentPos1 = map.start;
        point currentPos2 = map.start;
        crossoverPoint = crossDistrib(generator);
        //cross elements
        for (i = 0; i < crossoverPoint; i++)
        {
            worsePath[i] = a[i];
            secondWorsePath[i] = b[i];

            currentPos1.x += worsePath[i].x;
            currentPos1.y += worsePath[i].y;
            currentPos2.x += secondWorsePath[i].x;
            currentPos2.y += secondWorsePath[i].y;
        }
        //and check if the new paths does not collide with the terrain
        arePathsValid = true;
        for (i=i; i < pathLen; i++)
        {
            worsePath[i] = b[i];
            secondWorsePath[i] = a[i];
            if(map.isInObstacle(currentPos1) || map.isInObstacle(currentPos2))
            {
                arePathsValid = false;
                break;
            }
            currentPos1.x += worsePath[i].x;
            currentPos1.y += worsePath[i].y;
            currentPos2.x += secondWorsePath[i].x;
            currentPos2.y += secondWorsePath[i].y;
        }
        
    } while (!arePathsValid);
}


void PathManager::mutate()
{
    // only mutate the last 2 elements, which are the results of crossing
    for (size_t pathIndex = 0; pathIndex < 2; pathIndex++)
    {
        
        point* currentPath = dnaList.at(pathIndex);
        point currentPos = map.start;
        point tmpPos;

        for (size_t i = 0; i < pathLen; i++)
        {    
            if(mutationDistrib(generator) < 4)
            {
                do
                {
                    currentPath[i] = getRandomMovement();

                    tmpPos.x = currentPos.x + currentPath[i].x;
                    tmpPos.y = currentPos.y + currentPath[i].y;

                } while (!isRestOfPathValid(currentPath, i, tmpPos));
                currentPos = tmpPos;
            }
            else
            {
                currentPos.x += currentPath[i].x;
                currentPos.y += currentPath[i].y;
            }
            
        }

    }
}
    
bool PathManager::isRestOfPathValid(point* path, size_t offset, point posAtOffset)
{
    // the the initial position
    if(map.isInObstacle(posAtOffset))
        return false;
    
    for (size_t i = offset+1; i < pathLen; i++)
    {
        //set t
        posAtOffset.x += path[i].x;
        posAtOffset.y += path[i].y;
       // std::cout << i << std::endl;
        if(map.isInObstacle(posAtOffset))
            return false;
    }
    return true;  
}

point PathManager::getRandomMovement()
{
    int roll = directionDistrib(generator);
    switch (roll)
    {
    case 1:
        return point{0,0};
        break;
    case 2:
        return point{baseElement,0};
        break;
    case 3:
        return point{-baseElement,0};
        break;
    case 4:
        return point{0,baseElement};
        break;
    default:
        return point{0,-baseElement};
        break;
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