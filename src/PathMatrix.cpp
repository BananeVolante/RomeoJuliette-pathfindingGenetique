#include "PathMatrix.h"
#include <iostream>

PathMatrix::PathMatrix(point mapSize, size_t pathNumberP) : pathNumber(pathNumberP), matrix(std::vector<bool>(mapSize.x * mapSize.y * pathNumber, false))
{
    elementSize = pathNumber/8 + (pathNumber%8 !=0);
    //matrix = (char*) malloc(mapSize.x * mapSize.y * elementSize);
    //making a copy is voluntary : modifying the size would completely break the class
    matrixSizeX = mapSize.x;
    matrixSizeY = mapSize.y;
}

PathMatrix::~PathMatrix()
{
}

bool PathMatrix::getElement(size_t x, size_t y, size_t pathId)
{
    
    if(x > matrixSizeX || y > matrixSizeY || pathId > pathNumber-1) throw new std::invalid_argument("trying to access elements outside of the matrix");
    return matrix[matrixSizeX * matrixSizeY * pathId + x*matrixSizeX + y];
    //return (matrix[ (x*matrixSizeX +y) * elementSize + pathId/BITS_IN_BYTES] >> pathId%BITS_IN_BYTES) & ONE;
}

bool PathMatrix::getElementDefault(size_t x, size_t y, size_t pathId, bool defaultValue)
{
    if(x > matrixSizeX || y > matrixSizeY || pathId > pathNumber-1) return defaultValue;
    return matrix[matrixSizeX * matrixSizeY * pathId + x*matrixSizeX + y];
}

void PathMatrix::setElement(size_t x, size_t y, size_t pathId, bool value)
{
    if(x > matrixSizeX || y > matrixSizeY ) throw new std::invalid_argument("trying to access elements outside of the matrix");
    matrix[matrixSizeX * matrixSizeY * pathId + x*matrixSizeX + y] = value;

}
