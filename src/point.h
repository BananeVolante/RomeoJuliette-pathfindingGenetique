#ifndef point_HEADER
#define point_HEADER
#include <ostream>

typedef struct point
{
    float x;
    float y;
    point operator+(const point& p) const;
    point& operator+=(const point& p);
    point operator-(const point& p) const;
    point& operator-=(const point& p);

    //multiplication by a scalar
    point operator*(const float& s) const;
    point& operator*=(const float& s);

    bool operator==(const point& p) const;

    // useless, but it's still interesting to say that point have <<
    friend std::ostream& operator<<(std::ostream& os, const point& p);

} point;
#endif

