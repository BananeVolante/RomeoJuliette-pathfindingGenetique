#ifndef GeometricForms_HEADER
#define GeometricForms_HEADER

#include <iostream>

#define SQUARE(a) ((a)*(a))

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

    // useless, but it's still interesting to say that point have <<
    friend std::ostream& operator<<(std::ostream& os, const point& p);

} point;

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