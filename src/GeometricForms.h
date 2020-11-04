#ifndef GeometricForms_HEADER
#define GeometricForms_HEADER

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
public:
    GeometricForm(point center);
    virtual ~GeometricForm();
    virtual bool isInHitbox(point point) =0 ;
};



class Circle : public GeometricForm
{
protected:
    float radius;
public:
    Circle(point center, float radius);
    bool isInHitbox(point point);
};

class Rectangle : public GeometricForm
{
protected:
    float width;
    float height;
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
    const float WIDTH = 1.01;
public:
    Line(point center, float size);
};
#endif  