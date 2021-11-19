#include "PathManager.h"
#include <algorithm>
#include <time.h>


PathManager::PathManager(Map &mapP, size_t pathLenP, size_t pathNumberP, float baseElementP, float mutationChanceP, int maxConsecutiveScoresP)
:    pathNumber(pathNumberP),pathLen(pathLenP), baseElement(baseElementP), mutationChance(mutationChanceP),
    map(mapP), pathMatrix({map.mapHitbox.height, map.mapHitbox.width}, pathNumberP), maxConsecutiveScores(maxConsecutiveScoresP), generator(time(NULL)),  crossDistrib(0,pathLen)
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
        replacePath(0, dnaList[i], i);
    }
}

void PathManager::replacePath(size_t startIndex, Path& path, size_t pathId)
{
    point currentPos = map.start;
    point tmpPos;
    for (size_t j = startIndex; j < pathLen; j++)
    {
        do
        {
            path[j] = getBiasedMovement(currentPos);
            tmpPos = currentPos + path[j];
            if(j>0)
                std::cout << tmpPos << currentPos << currentPos -path[j-1] << std::endl;
            //if the current path already passed by the tmpPos, if accessing an element outside of the matrix, do as if it was already taken
            if( j>0 && pathMatrix.getElementDefault(tmpPos.x, tmpPos.y, pathId, true) )
            //if( j >0 && tmpPos.approximatelyEqual(currentPos - path[j-1], 0.1))
            {
                std::cout << "skipped" << std::endl;
                continue;
            }
        } while (map.isInObstacle(tmpPos));

        pathMatrix.setElement(currentPos.x, currentPos.y, pathId, false);
        currentPos = tmpPos;
        pathMatrix.setElement(currentPos.x, currentPos.y, pathId, true);
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
        
//        scoreArray[i].score = map.getSquaredDistance(path.getEndPoint(map.start));
      //  scoreArray[i].score *= scoreModulatorDistrib(generator);
        scoreArray[i].score = computeScore(path);
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
        arePathsValid = true;
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
        for (i=crossoverPoint; i < pathLen; i++)
        {
            worsePath[i] = b[i];
            secondWorsePath[i] = a[i];
            currentPos1 += worsePath[i];
            currentPos2 += secondWorsePath[i];
             if(map.isInObstacle(currentPos1) || map.isInObstacle(currentPos2))
            {
                arePathsValid = false;
                break;
            } 

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
            if(mutationDistrib(generator) < mutationChance)
            {
                // here to replace the elements that have been picked before
                randomMovementReplace();
                do
                {
                    
                    currentPath[i] = getRandomMovementNoReplacement();
                    //gives less interesting results
                    //currentPath[i] = getBiasedMovement(currentPos);

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
    // the initial position
    if(map.isInObstacle(posAtOffset))
        return false;
    
    for (size_t i = offset+1; i < pathLen; i++)
    {
        posAtOffset += (point)path[i];
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
        return Path::UP*baseElement;
        break;
    case 2:
        return Path::DOWN*baseElement;
        break;
    case 3:
        return Path::LEFT*baseElement;
        break;
    case 4:
        return Path::RIGHT*baseElement;
        break;
    default:
        return Path::NONE;
    }
}




// return a random movement with more chances to go toward the end point
point PathManager::getBiasedMovement(point p)
{
    //https://stackoverflow.com/a/1761646
    
    int weights[4] = {1,1,1,1};
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
    
    std::uniform_int_distribution<int> biasedDistrib(0, sumOfWeight-1);
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
        return Path::LEFT*baseElement;
        break;
    case 1:

        return Path::RIGHT*baseElement;
        break;
    case 2:
        return Path::UP*baseElement;
        break;
    case 3:
        return Path::DOWN*baseElement;
        break;
    default : 
        throw new std::runtime_error("weird outcome of getBiasedMovemet");
        return Path::NONE;
        break;
    }
    

    
}

point PathManager::getRandomMovementNoReplacement()
{
    if(replacementIndex>4)
    {
        std::cout<<"error"<<std::endl;

        return Path::NONE;
    }
    return replacementArray[replacementIndex++]*baseElement;
}


void PathManager::randomMovementReplace()
{
    std::shuffle(replacementArray, replacementArray+4, generator);
    replacementIndex=0;
}


void PathManager::reduce()
{
    size_t smallestPath = pathLen;
    for (auto &&path : dnaList)
    {
        //its a copy
        point currentPos = map.start;
        // start from the end point and go back to the start
        for (size_t i = 0; i <pathLen; i++)
        {
            currentPos += path[i];
            if(currentPos.approximatelyEqual(map.end, baseElement))
            {
                std::cout<<"HOLA"<<std::endl;
                if(i+1 < smallestPath)
                    smallestPath = i+1;
                break;
            }
        }
    }

    for (auto &&path : dnaList)
        path.setLength(smallestPath);
    pathLen = smallestPath;

    //update the generator for the crossing
    crossDistrib = std::uniform_int_distribution<int>(0,pathLen);

    
}


void PathManager::printAllPaths()
{
    int i=0;
    for (auto &&path : dnaList)
    {
        std:: cout << "-----------PATH-"<<i<<" --------\n";
        path.printPath();
        i++;
    }
    
}


/*
check the paths are converging, returns true if there is convergence

*/
bool PathManager::testIfConverge()
{
    
    //calculate the sum of scores
    float sumOfScores;
    //it should be fast, so theres no need to compute the score in orderByScoreRandomed
    for (size_t i = 2; i < pathNumber-2; i++)
    {
        sumOfScores+=map.getSquaredDistance(dnaList[i].getEndPoint(map.start));
    }
    
    //if the sum is similar to the precedent sum, increment a variable, else reset it
    //if this variable is higher that max consecutiveScores, there is convergence
    if (lastTotalScore < sumOfScores*1.1 && lastTotalScore > sumOfScores*0.9)
    {
        consecutiveSimilarScores++;
        if(consecutiveSimilarScores > maxConsecutiveScores)
        {
            std::cout << "convergence!!" << std::endl;  
            return true;  
        }
    }
    else
        consecutiveSimilarScores=0;
    
    lastTotalScore = sumOfScores;
    return false;
}


float PathManager::computeScore(Path& path)
{
    
    //go from the end of the path, and find the closest point
    point currentPos = path.getEndPoint(map.start);
    float score = INFINITY;

    for (size_t i = pathLen-1; i!=(size_t)(0-1); i--) //(0-1) for the highest size_t value
    {
        float tmpScore = map.getSquaredDistance(currentPos);
        if(tmpScore == 0) // if the distance is null, it's useless to continue
            return 0;
        if(tmpScore < score)
            score = tmpScore;
        currentPos -= path[i];
    }
    
    score *= scoreModulatorDistrib(generator);
    return score;

}

int PathManager::findValidPath()
{
    for (size_t i = 0; i < pathNumber; i++)
    {
        if(dnaList[i].getEndPoint(map.start).approximatelyEqual(map.end, baseElement))
        {
            return i;
        }
    }
    return -1;
}

void PathManager::extend()
{
    //update path sizes and fill the new paths
    size_t newPathLen = pathLen *= extendPercentage;
    for(auto&& path : dnaList)
    {
        path.changeSize(newPathLen);
        replacePath(pathLen, path, 0);
    }
    //reset the counter to check if there is a convergence
    consecutiveSimilarScores = 0;
}



std::vector<Path> PathManager::getDnaList()
{
    return dnaList;
}

size_t PathManager::getPathLength()
 {
     return pathLen;
 }