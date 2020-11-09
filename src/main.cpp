#include "Map.h"
#include "GeometricForms.h"


int main(int argc, char const *argv[])
{
    Map map(100,100);
    map.addCircle(0,0,5);
    map.addLine(0,5,4.2);
    point center;
    center.x=4;center.y=2;
    map.addRectangle(center, 4.3,2.1);

    map.printAllForms();

    



    return 0;
}

