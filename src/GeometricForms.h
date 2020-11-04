#ifndef GeometricForms_HEADER
#define GeometricForms_HEADER

#include <iostream>

#define SQUARE(a) (a*a)

typedef struct point
{
    float x;
    float y;
} point;

class GeometricForm
{
protected:
    point center;
    virtual std::ostream& handleCoutPrint(std::ostream& os) const ;
public:
    GeometricForm(point center);
    virtual ~GeometricForm();
    virtual bool isInHitbox(point point) =0 ;
    friend std::ostream& operator<<(std::ostream& os, const GeometricForm& form);
};



class Circle : public GeometricForm
{
protected:
    float radius;
    std::ostream& handleCoutPrint(std::ostream& os) const;
public:
    Circle(point center, float radius);
    bool isInHitbox(point point);
};

class Rectangle : public GeometricForm
{
protected:
    float width;
    float height;
    std::ostream& handleCoutPrint(std::ostream& os) const;
public : 
    Rectangle(point center, float width, float height);
    virtual bool isInHitbox(point point);
};

class Line : public Rectangle
{
protected:
//for now i'll only add vertical lines
    //angle
    //must be at least as wide as the path's elementary element
    //later, must be directly fixed using a constant somewhere else
    std::ostream& handleCoutPrint(std::ostream& os) const;
public:
    Line(point center, float size);
};
#endif  