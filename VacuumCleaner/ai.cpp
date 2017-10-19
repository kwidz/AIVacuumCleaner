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

//position de l'aspirateur
//position de la cible
Point pos_cible;
Point whatToDo;
int timerGhetto;
Box* env;

Point AI::getPos_aspi() const
{
    return pos_aspi;
}

void AI::setPos_aspi(const Point &value)
{
    pos_aspi = value;
}

AI::AI() : timer(new QTimer(this))
{
    pos_aspi.x=10;
    pos_aspi.y=5;
    pos_cible.x=1;
    pos_cible.y=1;
    effecteur.position = &pos_aspi;
    energy = 0;
}

void AI::run(){

}


void AI::justDoIt()
{
    if(pos_aspi.x<pos_cible.x) {
      effecteur.movex(1);
    } else if (pos_aspi.x>pos_cible.x) {
      effecteur.movex(-1);
    } else if (pos_aspi.y<pos_cible.y){
      effecteur.movey(1);
    } else if (pos_aspi.y>pos_cible.y){
      effecteur.movey(-1);
    } else /*Sur la cible*/ {
        if ( env[pos_aspi.y*(*senseur.getUniverseSize()) + pos_aspi.x].getDust() && env[pos_aspi.y*(*senseur.getUniverseSize()) + pos_aspi.x].getJewel()) {
            overallPoints-=1;
            jewelRemoved++;
            dustRemoved++;
        }else if (env[pos_aspi.y*(*senseur.getUniverseSize()) + pos_aspi.x].getDust()){
            overallPoints+=2;
            dustRemoved+=1;
        }else if (env[pos_aspi.y*(*senseur.getUniverseSize()) + pos_aspi.x].getJewel()){
            overallPoints+=1;
            jewelPicked++;
        }
        effecteur.vaccum(env, pos_aspi.y*(*senseur.getUniverseSize()) + pos_aspi.x);
        }
        energy++;
}

void AI::timerHit()
{
    timerGhetto++;
    timerGhetto=timerGhetto%timeBetweenResearch;
    if(timerGhetto==0) {
        timerHit2();
    }

    //INTENTION
    justDoIt();
    srand (time(NULL));
}




void AI::timerHit2()
{
    srand (time(NULL));
   //Reparser la carte et regarder si l'objectif fixé avant est toujours le plus optimal

   // BELIEF - Récupérer ce qu'on sait sur la carte. Supposé ici : on connaît la carte en son ensemble, a ajouter un filtre si besoin/envie
   env = ObserveEnvironmentWithAllMySensors();

   //DESIRE
   //Regarder ce qui est rentable de faire - ce qu'on veux faire au final. Exemple : exterminer la tache en X1,Y1
    std::vector<Point> v;
    v = UpdateMyState();
    pos_cible = ChooseAnAction(v);
   //Résultat : tous les timeBetweenResearch, on effectue une remise en question. Mais sinon, on se dirige vers l'objectif courrant.


}

void AI::machineLearning(Point pointMin){

//Cette fonction va adapter le temps entre deux recherches de l'environnement selon ses dernières expériences
    if(pointMin.x == pos_cible.x && pointMin.y == pos_cible.y){
        timeBetweenResearch++;
    } else if (timeBetweenResearch != 1){
        timeBetweenResearch --;
    }
}

Box* AI::ObserveEnvironmentWithAllMySensors(){
    Box* m;
    m = senseur.getUniverse();
    return m;
}

 std::vector<Point> AI::UpdateMyState(){
     //Pour chaque boite de la matrice, on regarde si elle est vide et on renvoie une liste de position de boites non vides.
     std::vector<Point> list;
     for(int k = 1; k <= *senseur.getUniverseSize(); k++) {
         for(int j = 1; j <= *senseur.getUniverseSize(); j++) {
             if(env[k*(*senseur.getUniverseSize()) + j].getDust() == true) {
                 Point *point = new Point();
                 point->x = j;
                 point->y = k;
                 list.push_back(*point);
             }
         }
     }
     //Le but est de ramasser la poussiere, il cherche les bijoux uniquement si il n'y a pas de poussiere
     if(list.size() == 0) {
         for(int k = 1; k <= *senseur.getUniverseSize(); k++) {
             for(int j = 1; j <= *senseur.getUniverseSize(); j++) {
                 if(env[k*(*senseur.getUniverseSize()) + j].getJewel() == true) {
                     Point *point = new Point();
                     point->x = j;
                     point->y = k;
                     list.push_back(*point);
                 }
             }
         }
     }
    return list;
 }

Point AI::ChooseAnAction(std::vector<Point> v){
    int distanceMin = 10000;
    Point pointMin;
    pointMin.x = 1;
    pointMin.y = 1;
   if (!v.empty()){
    for (Point &p : v){
            //Calcul de distance et renvoie du point le plus près..
            if (distanceMin > (abs(p.x - pos_aspi.x) + abs(p.y - pos_aspi.y))){
            distanceMin = (abs(p.x - pos_aspi.x) + abs(p.y - pos_aspi.y));
            pointMin = p;
            }
            machineLearning(pointMin);
            }
        } else {
            pointMin = pos_aspi;
    }
   return pointMin;
}
