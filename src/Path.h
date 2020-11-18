#include "stdlib.h"
#include "GeometricForms.h"

class Path
{
private:
    size_t length;
    point* path;
    
    point cachedEndPoint;
public:
    Path(size_t pathLength);
    ~Path();

    point& operator[](int index);
    size_t getLength() const;

};


