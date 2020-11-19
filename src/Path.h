#include "stdlib.h"
#include "GeometricForms.h"


// used to give different rules when using []
//probably overkill and makes me repeat point's operators, 
//but i wanted to do it anyway
//in a case outside learning, i would use get and set instead, much cleaner
// ignore it
struct PathProxy
{
    PathProxy(point& currentPoint, point& endPoint);


    PathProxy& operator=(point newPoint);
    point operator+(const point& p) const;
    point& operator+=(const point& p);
    point operator-(const point& p) const;
    point& operator-=(const point& p);

    operator  point ();


    private: 

        point& currentPoint;
        point& endPoint;
};



class Path
{
private:
    size_t length;
    point* path;
    
    //care, it's the relative end point
    point cachedEndPoint;
public:
    Path(size_t pathLength);
    ~Path();

    //see pathProxy
    PathProxy operator[](int index);

    size_t getLength() const;
    point getEndPoint(point startPoint) const;

    void printPath();

};






