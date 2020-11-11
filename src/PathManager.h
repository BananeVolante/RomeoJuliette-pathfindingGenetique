#include <vector>
#include <random>


#include "GeometricForms.h"
#include "Map.h"


class PathManager
{
private:
    size_t pathLen;
    size_t pathNumber;

    // the distance (in x, y or both) of the elementary movement
    float baseElement;

    Map map;

    //vector of arrays
    std::vector<point*> dnaList;
    static point evaluateEndPoint(point* path);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distrib;


public:
    PathManager(Map map, size_t pathLen, size_t pathNumer, float baseElement);
    ~PathManager();

    void fillRandomPaths();
    std::vector<point*> getDnaList();

    //DBG
    //DO NOT USE WITH A USABLE PATHS
    void printAllPaths();
};
