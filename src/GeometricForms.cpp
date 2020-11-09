#include "GeometricForms.h"
#include <math.h>
#include <stdexcept>


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

point GeometricForm::getCenter()
{
    return center;
}

//Circle

Circle::Circle(point centerP, float radiusP) : GeometricForm(centerP), radius(radiusP)
{
    if(radiusP<=0)
        throw new std::invalid_argument("radius must be >= 0");
}
bool Circle::isInHitbox(point point)
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

bool Rectangle::isInHitbox(point point)
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

    
    return abs((point.x-center.x)/width + (point.y-center.y)/height) 
            + abs((point.x-center.x)/width - (point.y-center.y)/height) <=1;

}

std::ostream& Rectangle::handleCoutPrint(std::ostream& os) const
{
    GeometricForm::handleCoutPrint(os) <<" width : " << width << " height : " << height;

    return os;
}


//Line
    //the 1.01
    //must be at least as wide as the path's elementary element
    //later, must be directly fixed using a constant somewhere else
Line::Line(point centerP, float size) : Rectangle(centerP, 1.01,size)
{

}

std::ostream& Line::handleCoutPrint(std::ostream& os) const
{
    GeometricForm::handleCoutPrint(os) <<" size : " << height;

    return os;
}