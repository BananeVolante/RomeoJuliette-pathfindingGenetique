#include <vector>
#include "GeometricForms.h"
class Map
{
private:
    std::vector<GeometricForm*> obstacleList;
    void addForm(GeometricForm* form);
public:
    Map();
    ~Map();
    void addCircle(point center, float radius);
    void addRectangle(point center, float width, float height);
    void addLine(point center, float size);
    void addCircle(float x, float y, float radius);
    void addRectangle(float x, float y, float width, float height);
    void addLine(float x, float y, float size);

    

    //DBG
    void printAllForms();
};

