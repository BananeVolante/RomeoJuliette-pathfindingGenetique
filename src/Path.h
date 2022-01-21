
#ifndef Path_HEADER
#define Path_HEADER
#include "stdlib.h"
#include "GeometricForms.h"



// used to give different rules when using []
//probably overkill and makes me repeat point's operators, 
//but i wanted to do it anyway
//in a case outside learning, i would use get and set instead, much cleaner

struct PathProxy
{
    PathProxy(point& currentPoint, point& endPoint);


    PathProxy& operator=(point newPoint);
    //to solve the a[x] = b[y] case
    PathProxy& operator=(PathProxy& newPoint);

    point operator+(const point& p) const;
    point& operator+=(const point& p);
    point operator-(const point& p) const;
    point& operator-=(const point& p);

    friend std::ostream& operator<<(std::ostream& os, const PathProxy& p);


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
    Path(const Path&);

    //see pathProxy
    PathProxy operator[](int index);
    Path& operator=(const Path&);

    size_t getLength() const;
    void setLength(size_t l);
    point getEndPoint(point startPoint) const;

    //recherche si le point demandé se trouve dans le path, retourne l'index trouvé +1, -1 si rien trouvé
    int findIfInPath(point startPoint, point pointToSearch, float precision) const;


    /*
    change the size of the path using reallocate
    newSize can't be null
    if the size of the path is increased, fill the added points with {0,0}
    make sure that the endPoint is still valid
    //should be OK
    */
    void changeSize(size_t newSize);

    void printPath();

    //must be multiplied by the base distance
    static constexpr point LEFT{-1,0};
    static constexpr point RIGHT{1,0};
    static constexpr point UP{0,-1};
    static constexpr point DOWN{0,1};
    static constexpr point NONE{0,0};

};
#endif







