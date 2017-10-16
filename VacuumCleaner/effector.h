#ifndef EFFECTOR_H
#define EFFECTOR_H
#include "ai.h"
#include "environment.h"
#include "sensor.h"
#include "effector.h"
#include<iostream>
#include <QTimer>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <math.h>


class effector
{
public:
    effector();
    Point* position;
};

#endif // EFFECTOR_H
