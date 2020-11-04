#include "GeometricForms.h"
#include <math.h>


//GeometricForm
GeometricForm::GeometricForm(point centerP) : center(centerP)
{
}

GeometricForm::~GeometricForm() = default;
//Circle

Circle::Circle(point centerP, float radiusP) : GeometricForm(centerP), radius(radiusP)
{
    
}
bool Circle::isInHitbox(point point)
{
    return ( SQUARE(center.x - point.x)+ SQUARE(center.y - point.y) ) <= SQUARE(radius); 
}

//Rectangle

Rectangle::Rectangle(point centerP, float widthP, float heightP) : GeometricForm(centerP), width(widthP), height(heightP)
{

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
    
    return abs(center.x/width + center.y/height) 
            + abs(center.x/width - center.y/height) <=1;

}

//Line

Line::Line(point centerP, float size) : Rectangle(centerP, WIDTH,size)
{

}
