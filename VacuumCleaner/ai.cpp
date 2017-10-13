#include "ai.h"
#include<iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <stdlib.h>

AI::AI()
{
}

void AI::run(){
    int timeBetweenResearch = 3000;
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer.setInterval(timeBetweenResearch);
    timer.start();   // puts one event in the threads event queue
    exec();
    timer.stop();
}

void AI::timerHit()
{
    srand (time(NULL));
   //Reparser la carte et regarder si l'objectif fixé avant est toujours le plus optimal

}

