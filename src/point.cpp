#include "point.h"

//point

point point::operator+(const point& p) const
{
    return point{x+p.x , y+p.y};
}
point& point::operator+=(const point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

point point::operator-(const point& p) const
{
    return point{x-p.x , y-p.y};
}
point& point::operator-=(const point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}



point point::operator*(const float& s) const
{

    return point{x*s, y*s};
}

point& point::operator*=(const float& s)
{
    x*=s;
    y*=s;
    return *this;
}


bool point::operator==(const point& p) const
{
    return (x==p.x && y==p.y);
}


bool point::approximatelyEqual(const point& p, const float precision)
{

    return p.x<x+precision && p.x>x-precision &&  p.y<y+precision && p.y>y-precision;
}


std::ostream& operator<<(std::ostream& os, const point& p)
{
    return os << "(" << p.x << "," << p.y << ")"; 
}
