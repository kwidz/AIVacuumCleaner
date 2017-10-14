#include "ai.h"
#include "environment.h"
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

int timeBetweenResearch = 5000;
int timeBetweenActions = 1000;

int currentEnergy=50;
int TotalEnergy=50;

AI::AI() : timer(new QTimer(this))
{
    pos_aspi.x=10;
    pos_aspi.y=5;
}

void AI::run(){

}


void AI::justDoIt()
{
    if(pos_aspi.x<pos_cible.x) {
        pos_aspi.x++;
    } else if (pos_aspi.x>pos_cible.x) {
       pos_aspi.x--;
    } else if (pos_aspi.y>pos_cible.y){
        pos_aspi.y--;
    } else if (pos_aspi.y<pos_cible.y){
        pos_aspi.y++;
    } else /*Sur la cible*/ {
        //Aspire / récupère selon le type de la case sur laquelle il se trouve
        //Sinon si la case est vide / do nothing. L'aspirateur n'a plus de but et attends une nouvelle cible
    }
}

void AI::timerHit()
{
    timerGhetto ++;
    timerGhetto=timerGhetto%3;
    if(timerGhetto==0) {
        timerHit2();
    }
    //tous les timeBetweenActions, dirige de 1 l'aspirateur vers sa cible
    srand (time(NULL));

    //INTENTION
    //Trouver le plus court chemin pour aller a x1,y1 et effectuer l'action à part. dans le Run.
    justDoIt();



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
    Point choixDestination = ChooseAnAction(v);
    machineLearning();

   //Résultat : tous les timeBetweenResearch, on effectue une remise en question. Mais sinon, on se dirige vers l'objectif courrant.


}

void AI::machineLearning(){

//Cette fonction va adapter le temps entre deux recherches de l'environnement selon ses dernières expériences

if (pos_aspi.x != pos_cible.x || pos_aspi.y != pos_cible.y)
{
   timeBetweenResearch += 500;
} else {
   timeBetweenResearch -= 500;
}
}

Box* AI::ObserveEnvironmentWithAllMySensors(){
    Box* m;
    m = Sensor();
}


Box* AI::Sensor(){
    return universe;
}

 std::vector<Point> AI::UpdateMyState(){
     //Pour chaque boite de la matrice, on regarde si elle est vide et on renvoie une liste de position de boites non vides.
     std::vector<Point> list;
     for(int k = 1; k <= *universeSize; k++) {
         for(int j = 1; j <= *universeSize; j++) {
             if(universe[k*(*universeSize) + j].getDust() == Dust) {
                 Point *point = new Point();
                 point->x = k;
                 point->y = j;
                 list.push_back(*point);
             }
         }
     }
    return list;
 }

Point AI::ChooseAnAction(std::vector<Point> v){
    int distanceMin = 10000;
    Point pointMin;
    pointMin.x = 0;
    pointMin.y = 0;
    for (Point &p : v){
        if (!v.empty()){
            //Calcul de distance et renvoie du point le plus près..
            if (distanceMin > (abs(p.x - pos_aspi.x) + abs(p.y - pos_aspi.y))){
            distanceMin = (abs(p.x - pos_aspi.x) + abs(p.y - pos_aspi.y));
            pointMin = p;
            }
        }
    }
    return pointMin;
}
