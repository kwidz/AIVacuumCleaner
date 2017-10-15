#include "environment.h"
#include<iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <time.h>
#include <stdlib.h>
#include <iostream>


Box::Box(){
    this->dust=false;
    this->jewel=false;

}
bool Box::getDust(){
    return this->dust;
}
bool Box::getJewel(){
    return this->jewel;
}
bool Box::addDust(){

    if(this->getDust())
        return false;
    else
        this->dust=true;
    return true;
}
bool Box::addJewel(){
    if(this->getJewel())
        return false;
    else
        this->jewel=true;
    return true;
}
void Box::deleteDust(){
    this->dust=false;
}
void Box::deleteJewel(){
    this->jewel=false;
}

