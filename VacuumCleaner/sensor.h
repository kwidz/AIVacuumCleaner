#ifndef SENSOR_H
#define SENSOR_H
#include "environment.h"

class sensor

{
public:
    Box* universe;
    int* universeSize;
    sensor();
    int *getUniverseSize() const;
    Box *getUniverse() const;
};

#endif // SENSOR_H
