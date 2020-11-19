#include "GeometricForms.h"
#include <math.h>
#include <stdexcept>
//point

point point::operator+(const point& p)
{
    return point{x+p.x , y+p.y};
}
point& point::operator+=(const point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

point point::operator-(const point& p)
{
    return point{x-p.x , y-p.y};
}
point& point::operator-=(const point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}




//GeometricForm
GeometricForm::GeometricForm(point centerP) : center(centerP)
{
}

GeometricForm::~GeometricForm() = default;

std::ostream& GeometricForm::handleCoutPrint(std::ostream& os) const
{
    os << "center : (" << center.x << "," << center.y <<") ";
    return os;
}

//make the << operator call handleCoutPrint, since i can't use polymorphism and everything with this
std::ostream& operator<<(std::ostream& os, const GeometricForm& form)
{
    return form.handleCoutPrint(os); 
}



//Circle

Circle::Circle(point centerP, float radiusP) : GeometricForm(centerP), radius(radiusP)
{
    if(radiusP<=0)
        throw new std::invalid_argument("radius must be >= 0");
}
bool Circle::isInHitbox(const point point) const
{
    return ( SQUARE(center.x - point.x)+ SQUARE(center.y - point.y) ) <= SQUARE(radius); 
}


std::ostream& Circle::handleCoutPrint(std::ostream& os) const
{
    GeometricForm::handleCoutPrint(os) <<" radius : " << radius;

    return os;
}


//Rectangle

Rectangle::Rectangle(point centerP, float widthP, float heightP) : GeometricForm(centerP), width(widthP), height(heightP)
{
    if(widthP <= 0 || heightP <= 0)
        throw new std::invalid_argument("width and height must be >0");
}

bool Rectangle::isInHitbox(const point point) const
{
    /*
    parametric equation of a rectangle : 
    p = width and q = height
    abs(x/p + y/q) + abs(x/p - y/q) = 1
    or 
    abs(x/p + y/q) + abs(x/p - y/q) <= 1 
    to have a filled rectangle
    i found a lot of other equations but this one does not have arctans, sinuses or
    other things like that, so i think that it'll be easy to compute
    */

    
    return abs((point.x-center.x)/(width/2) + (point.y-center.y)/(height/2)) 
            + abs((point.x-center.x)/(width/2) - (point.y-center.y)/(height/2)) <=2;

}

std::ostream& Rectangle::handleCoutPrint(std::ostream& os) const
{
    GeometricForm::handleCoutPrint(os) <<" width : " << width << " height : " << height;

    return os;
}


