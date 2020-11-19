#include "Path.h"

Path::Path(size_t lengthP) : length(lengthP), cachedEndPoint{0,0}
{
    // need to be calloc to make sure that the path is 0
    path = (point*) calloc(length, sizeof(point));
}

Path::~Path()
{
    free(path);
}

PathProxy Path::operator[](int index)
{
    if((size_t)index >= length || index<0)
        throw new std::out_of_range("Tried to access an element out of bounds");
    return PathProxy(path[index], cachedEndPoint);
}

size_t Path::getLength() const
{
    return length;
}


void Path::printPath()
{
    for (size_t i = 0; i < length; i++)
    {
        std::cout<< "("<< path[i].x << "," << path[i].y << ")" << std::endl;
    }
}

point Path::getEndPoint(const point start) const
{
    return cachedEndPoint + start;
}





PathProxy::PathProxy(point& currentPointP, point& endPointP) : 
    currentPoint(currentPointP), endPoint(endPointP)
{

}

PathProxy& PathProxy::operator=(point newPoint)
{

    endPoint -= currentPoint;
    endPoint += newPoint;

    currentPoint = newPoint;
    return *this;
}

PathProxy::operator point ()
{

    return currentPoint;
}

point PathProxy::operator+(const point& p) const
{
    return currentPoint + p;
}

point& PathProxy::operator+=(const point& p)
{
    endPoint+=p;
    return (currentPoint+=p);
}

point PathProxy::operator-(const point& p) const
{
    return currentPoint-p;
}
point& PathProxy::operator-=(const point& p)
{
    endPoint-=p;
    return currentPoint-=p;
}