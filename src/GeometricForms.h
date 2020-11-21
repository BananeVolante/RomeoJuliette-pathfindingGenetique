#ifndef GeometricForms_HEADER
#define GeometricForms_HEADER

#include <iostream>
#include "point.h"

#define SQUARE(a) ((a)*(a))



class GeometricForm
{
protected:
    virtual std::ostream& handleCoutPrint(std::ostream& os) const ;
public:
    GeometricForm(point center);
    virtual ~GeometricForm();
    virtual bool isInHitbox(const point point) const =0;
    const point center;


    friend std::ostream& operator<<(std::ostream& os, const GeometricForm& form);
};



class Circle : public GeometricForm
{
protected:
    std::ostream& handleCoutPrint(std::ostream& os) const;
public:
    Circle(point center, float radius);
    bool isInHitbox(const point point) const;

    const float radius;
};

class Rectangle : public GeometricForm
{
protected:
    
    std::ostream& handleCoutPrint(std::ostream& os) const;
public : 
    Rectangle(point center, float width, float height);
    virtual bool isInHitbox(const point point) const;

    const float width;
    const float height;
};

#endif  