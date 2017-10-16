#ifndef EFFECTOR_H
#define EFFECTOR_H
#include "point.h"
#include "environment.h"

class effector
{
public:
    effector();
    void movex(int a);
    void movey(int a);
    void vaccum(Box* environment, int position);
    Point* position;
};

#endif // EFFECTOR_H
