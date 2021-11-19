#ifndef PathMatrix_HEADER
#define PathMatrix_HEADER
#include "point.h"
#include <vector>

class PathMatrix
{
private:
    const char BITS_IN_BYTES = 8;
    const size_t pathNumber;
    size_t elementSize;
  //  char* matrix;
    std::vector<bool> matrix;
    size_t matrixSizeX;
    size_t matrixSizeY;
    
public:

    PathMatrix(point mapSize, size_t pathNumberP);
    ~PathMatrix();

    bool getElement(size_t x, size_t y, size_t pathId);
    //get element, but returns a default value when accessing elements outside of the matrix
    bool getElementDefault(size_t x, size_t y, size_t pathId, bool defaultValue);
    void setElement(size_t x, size_t y, size_t pathId, bool value);
};


#endif