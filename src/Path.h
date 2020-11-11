#include "GeometricForms.h"



class Path
{
private:
    point * path;
    size_t pathLen;
    float baseElement;
public:
    static constexpr point MV_DOWN{1,0};
    static constexpr point MV_UP{-1,0};
    static constexpr point MV_RIGHT{0,1};
    static constexpr point MV_LEFT{0,-1};
    static constexpr point MV_NONE{0,0};



    Path(size_t pathLen, float);
    ~Path();

    point evaluateEndPoint(point start);
};

