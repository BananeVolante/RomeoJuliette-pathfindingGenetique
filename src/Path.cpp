#include "Path.h"

Path::Path(size_t pathLenP, float baseElementP) : baseElement(baseElementP), pathLen(pathLenP)
{
    path =(point*) malloc(pathLenP * sizeof(point));
}

Path::~Path()
{
    free(path);
}

point Path::evaluateEndPoint(point start)
{
    point end;
    for (size_t i = 0; i < pathLen; i++)
    {
        end.x += path[i].x;
        end.y += path[i].y;
    }
    end.x *= baseElement;
    end.y *= baseElement;
    end.x += start.x;
    end.y += start.y;

    return end;    
}