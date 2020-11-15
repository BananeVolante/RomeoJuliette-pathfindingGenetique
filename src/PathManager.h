#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <vector>
#include <random>


#include "GeometricForms.h"
#include "Map.h"


class PathManager
{
public: 
    const size_t pathLen;
    const size_t pathNumber;



private:


    

    // the distance (in x, y or both) of the elementary movement
    float baseElement;

    Map &map;

    //vector of arrays
    std::vector<point*> dnaList;
    //can't e static since the pathManager stores the path length
    point evaluateEndPoint(point* path);

    //here to keep old id after sorting
    struct scoreWithId
    {
        float score;
        int id;
    };
    static bool scoreComparer(scoreWithId const& lhs, scoreWithId const& rhs);
    point getRandomMovement();
    point getBiasedMovement(point p);
    // determine if the rest of the path does not go in obstacles or outside the map
    //takes a path, an offset, and the position corresponding to the offset
    bool isRestOfPathValid(point* path, size_t offset, point posAtOffset);

    

    std::default_random_engine generator;
    std::uniform_int_distribution<int> directionDistrib{1,5};
    std::uniform_real_distribution<float> scoreModulatorDistrib{0.95, 1.05};
    std::uniform_int_distribution<int> crossDistrib;
    std::uniform_real_distribution<float> mutationDistrib{0,100};



public:

    PathManager(Map &map, size_t pathLen, size_t pathNumer, float baseElement);
    ~PathManager();

    //Must be called after adding obstacles
    void fillRandomPaths();
    void orderByScoreRandomed();
    void crossing();
    void mutate();



    std::vector<point*> getDnaList();



    //DBG
    //DO NOT USE WITH A BIG PATHS
    void printAllPaths();
};
#endif