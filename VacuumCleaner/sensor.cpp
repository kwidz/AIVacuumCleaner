#include "sensor.h"
#include "environment.h"

int *sensor::getUniverseSize() const
{
    return universeSize;
}

Box *sensor::getUniverse() const
{
    return universe;
}

sensor::sensor()
{

}

