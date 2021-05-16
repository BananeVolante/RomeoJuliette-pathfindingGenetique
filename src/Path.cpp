#include "Path.h"
#include "string.h"
#include "point.h"


Path::Path(size_t lengthP) : length(lengthP), 
    cachedEndPoint{0,0}
    
{
  //  std::cout << "Path \tCONSTRUCT" << std::endl;
    path = (point*)calloc(length, sizeof(point));
}
Path::~Path()
{
   // std::cout<<"Path \tDESTRUCT" <<std::endl; 
    free(path);
}

Path::Path(const Path& oldPath)
{
  //  std::cout << "Path \tCOPY" << std::endl;
    length = oldPath.length;
    path = (point*) malloc(length * sizeof(point));
    //memcpy(path, oldPath.path, length);
    for (size_t i = 0; i < length; i++)
    {
        path[i] = oldPath.path[i];
    }
    
    cachedEndPoint = oldPath.cachedEndPoint;
    

}

PathProxy Path::operator[](int index)
{
    if((size_t)index >= length || index<0)
        throw new std::out_of_range("Tried to access an element out of bounds");
    return PathProxy(path[index], cachedEndPoint);
}

Path& Path::operator=(const Path& p)
{
    //std::cout << "Path OPERATOR=" << std::endl;
    if(this == &p)
        return *this;

    length = p.length;
    cachedEndPoint = p.cachedEndPoint;

    path = (point*)realloc(path, length*sizeof(point));
    memcpy(path, p.path, length*sizeof(point));
    return *this;
}



size_t Path::getLength() const
{
    return length;
}

void Path::setLength(size_t lengthP)
{
    length = lengthP;
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


PathProxy& PathProxy::operator=(PathProxy& newPoint)
{
    return *this = newPoint.currentPoint;
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


std::ostream& operator<<(std::ostream& os, const PathProxy& p)
{
    return os << p.currentPoint; 
}