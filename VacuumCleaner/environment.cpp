#include "environment.h"
#include<iostream>
#include <vector>

Environment::Environment()
{

}
Box::Box(){

}
Matrix<Box, WIDTH, HEIGHT> Environment::getGrid(){

    return grid;
}
void Environment::run(){
    while(true){
        std::cout<< " coucou ";
    }
}

