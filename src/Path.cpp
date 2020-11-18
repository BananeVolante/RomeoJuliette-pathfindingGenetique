#include "Path.h"

Path::Path(size_t lengthP) : length(lengthP)
{
    path = (point*) malloc(length * sizeof(point));
}

Path::~Path()
{
    free(path);
}

point& Path::operator[](int index)
{
    if(index >= length || index<0)
        throw new std::out_of_range("Tried to access an element out of bounds");
    return path[index];
}

size_t Path::getLength() const
{
    return length;
}