#include "effector.h"
#include "sensor.h"

effector::effector()
{

}

void effector::movex(int a)
{
  position->x+=a;
}

void effector::movey(int a)
{
    position->y+=a;
}

void effector::vaccum(Box* env, int position)
{
    env[position].deleteDust();
    env[position].deleteJewel();
}

