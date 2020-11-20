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
    
}


void PathManager::fillRandomPaths()
{
    //dnaList.clear();
    dnaList.assign(pathNumber, Path(pathLen));
    for (size_t i = 0; i < pathNumber; i++)
    {
        Path& currentPath = dnaList.at(i);

        // that's a copy
        point currentPos = map.start;
        point tmpPos;
        for (size_t j = 0; j < pathLen; j++)
        {
            do
            {
                currentPath[j] = getBiasedMovement(currentPos);

                tmpPos = currentPos + currentPath[j];
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
        
        scoreArray[i].score = map.getSquaredDistance(path.getEndPoint(map.start));
        scoreArray[i].score *= scoreModulatorDistrib(generator);
        scoreArray[i].id = i;
        i++;
    }

    std::sort(scoreArray, scoreArray+pathNumber,PathManager::scoreComparer);
    
    //https://devblogs.microsoft.com/oldnewthing/20170102-00/?p=95095
    for (size_t i = 0; i < pathNumber; i++)
    {
        auto current = i;
        while (i != scoreArray[current].id)
        {
            auto next = scoreArray[current].id;
            std::swap(dnaList[current], dnaList[next]);
            scoreArray[current].id = current;
            current = next;
        }
        scoreArray[current].id = current; 
    }

    
    
}

// create 
void PathManager::crossing()
{
    //get 2 best paths
    Path& worsePath = dnaList.at(0);
    Path& secondWorsePath = dnaList.at(1);

    // get the 2 worse paths
    Path& a = dnaList.at(dnaList.size()-1);
    Path& b = dnaList.at(dnaList.size()-2);


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

            currentPos1 += worsePath[i];
            currentPos2 += secondWorsePath[i];
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
            currentPos1 += worsePath[i];
            currentPos2 += secondWorsePath[i];
        }
        
    } while (!arePathsValid);
}


void PathManager::mutate()
{
    // only mutate the last 2 elements, which are the results of crossing
    for (size_t pathIndex = 0; pathIndex < 2; pathIndex++)
    {
        
        Path& currentPath = dnaList.at(pathIndex);
        point currentPos = map.start;
        point tmpPos;

        for (size_t i = 0; i < pathLen; i++)
        {    
            if(mutationDistrib(generator) < 4)
            {
                do
               {
                    currentPath[i] = getRandomMovement();

                    tmpPos = currentPos + currentPath[i];

                } while (!isRestOfPathValid(currentPath, i, tmpPos));
                currentPos = tmpPos;
            }
            else
            {
                currentPos += currentPath[i];
            }
            
        }

    }
}
    
bool PathManager::isRestOfPathValid(Path& path, size_t offset, point posAtOffset)
{
    // the the initial position
    if(map.isInObstacle(posAtOffset))
        return false;
    
    for (size_t i = offset+1; i < pathLen; i++)
    {
        //set t
        posAtOffset += path[i];
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


// return a random movement with more chances to go toward the end point
point PathManager::getBiasedMovement(point p)
{
    //https://stackoverflow.com/a/1761646
    
    int weights[4] = {1};
    int sumOfWeight = 4; //4*1


    if(p.x - map.end.x > 0) // p is at the right of the endpoint
    {
        weights[0] = 2;
        sumOfWeight++;
    }
    else if(p.x - map.end.x < 0) // at the left
    {
        weights[1] = 2;
        sumOfWeight++;
    }

    if(p.y - map.end.y > 0) // p is lower
    {
        weights[2] = 2;
        sumOfWeight++;
    }
    else if(p.y - map.end.y < 0) // p is higher
    {
        weights[3] = 2;
        sumOfWeight++;
    }
    
    std::uniform_int_distribution<int> biasedDistrib(0, sumOfWeight);
    int random = biasedDistrib(generator);
    int movementID = 0;

    for (size_t i = 0; i < 4; i++)
    {
        if(random < weights[i])
        {
            movementID = i;
            break;
        }
        random -= weights[i];
    }

    switch (movementID)
    {
    case 0:
        return point{-baseElement, 0};
        break;
    case 1:
        return point{baseElement, 0};
        break;
    case 2:
        return point{0, -baseElement};
        break;
    default:
        return point{0, baseElement};
        break;
    }
    

    
}



void PathManager::printAllPaths()
{
    for (auto &&path : dnaList)
    {
        std:: cout << "-----------PATH---------\n";
        path.printPath();
        
    }
    
}

std::vector<Path> PathManager::getDnaList()
{
    return dnaList;
}