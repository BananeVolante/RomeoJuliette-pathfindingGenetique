#ifndef test_HEADER
#define test_HEADER

#include "PathMatrix.h"

/*
A class with a bunch of tests that returns 0 if they fail
*/
class Test
{
private:

public:
    Test();
    ~Test();
    //test the PathMatrix class
    bool testPathMatrix();
};


#endif