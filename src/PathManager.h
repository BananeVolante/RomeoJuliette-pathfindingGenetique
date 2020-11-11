#include <vector>
#include <array>

#include "GeometricForms.h"


class PathManager
{
private:
size_t pathLen;
size_t pathNumber;

// the distance (in x, y or both) of the elementary movement
float baseElement;

std::vector<point*> adnList;

point evaluateEndPoint(point* path);

public:
    PathManager(size_t pathLen, size_t pathNumer, float baseElement);
    ~PathManager();

};
