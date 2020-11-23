#ifndef Map_HEADER
#define Map_HEADER



#include <vector>
#include "GeometricForms.h"

class Map
{
private:
    std::vector<GeometricForm*> obstacleList;
    void addForm(GeometricForm* form);

    //used to modelize the map's hitbox
    // the left bottom corner have the 0,0 coordinates
public:
    const Rectangle mapHitbox;

    Map(float width, float height, point start, point end, float lineWidth);
    ~Map();
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void addCircle(float x, float y, float radius);
    void addRectangle(float x, float y, float width, float height);
    void addLine(float x, float y, float size);

    // return distance from point to end
    float getSquaredDistance(point p);
    bool isInObstacle(point p);


    const float lineWidth;
    const point start;
    const point end;
    

    //DBG
    void printAllForms();
    std::vector<GeometricForm*> getList();
};


#endif
