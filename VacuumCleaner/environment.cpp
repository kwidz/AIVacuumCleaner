#include "environment.h"
#include<iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

Environment::Environment()
{

}
Box::Box(){

}
std::vector<Obstacle> Box::getContent(){
    return this->content;
}
std::string Box::display(){
    std::string s;
    if(this->getContent().size()==0){
        s+=" ";
    }
    else{
        for(int i=0; i<this->getContent().size();i++){
            if(this->getContent()[i]==Obstacle::Dust){
                s+="D";
            }
            if(this->getContent()[i]==Obstacle::Dust){
                s+="J";
            }
        }

    }
    return s;
}
Matrix<Box, WIDTH, HEIGHT> Environment::getGrid(){

    return grid;
}
//toutes les 3 secondes l'environnement place une poussière quelquepart
void Environment::run(){
    while(1){
        for(int i =0; i<HEIGHT;i++){
            for(int j=0;i<WIDTH;i++){
                std::cout<<grid(i,j).display()<<"|";
            }
            std::cout<<"\n______________________________________\n";
        }

    }
}

