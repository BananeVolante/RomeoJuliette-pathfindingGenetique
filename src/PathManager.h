#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <vector>
#include <random>


#include "GeometricForms.h"
#include "Map.h"
#include "Path.h"
#include "cassert"



class PathManager
{
public: 
    const size_t pathNumber;



private:

    
    size_t pathLen;

    // the distance (in x, y or both) of the elementary movement
    float baseElement;

    float mutationChance; 

    Map &map;

    point replacementArray[4] = {Path::UP, Path::DOWN, Path::LEFT, Path::RIGHT};
    size_t replacementIndex;


    //vector of arrays
    std::vector<Path> dnaList;


    // used to determine if there is a convergence
    float lastTotalScore = -1;
    //number of consecutive scores that look similar
    int consecutiveSimilarScores = 0;
    //when consecutiveSimilarScores > maxConsecutiveScores, it means that our paths converged
    int maxConsecutiveScores;


    //here to keep old id after sorting
    struct scoreWithId
    {
        float score;
        size_t id;
    };
    static bool scoreComparer(scoreWithId const& lhs, scoreWithId const& rhs);
    //compute a path's score
    float computeScore(Path& path);
    point getRandomMovement();
    point getBiasedMovement(point p);
    // determine if the rest of the path does not go in obstacles or outside the map
    //takes a path, an offset, and the position corresponding to the offset
    bool isRestOfPathValid(Path& path, size_t offset, point posAtOffset);

    point getRandomMovementNoReplacement();
    void randomMovementReplace();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> directionDistrib{1,4};
    std::uniform_real_distribution<float> scoreModulatorDistrib{0.95, 1.05};
    std::uniform_int_distribution<int> crossDistrib;
    std::uniform_real_distribution<float> mutationDistrib{0,100};



public:

    PathManager(Map &map, size_t pathLen, size_t pathNumer, float baseElement, float mutationChance, int maxConsecutiveScoresP);
    ~PathManager();

    //Must be called after adding obstacles
    void fillRandomPaths();
    void orderByScoreRandomed();
    void crossing();
    void mutate();

    /* find the fist point in all paths that reach the endpoint, and 
    reduce the path length according to its index
    does not give good results, unused*/
    void reduce();

    /* test if the "middle" paths are not changing a lot */
    bool testIfConverge();

    std::vector<Path> getDnaList();
    size_t getPathLength();



    //DBG
    //DO NOT USE WITH A BIG PATHS
    void printAllPaths();
};
#endif