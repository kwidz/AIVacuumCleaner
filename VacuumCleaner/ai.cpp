#include "ai.h"
#include "environment.h"
#include<iostream>
#define WIDTH 10
#define HEIGHT 10
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <math.h>

//position de l'aspirateur
Point pos_aspi;
//position de la cible
Point pos_cible;

int timeBetweenResearch = 5000;
int timeBetweenActions = 1000;

int currentEnergy=50;
int TotalEnergy=50;


Matrix<Box, WIDTH, HEIGHT> env;

AI::AI()
{

}

void AI::run(){

    QTimer timer;
    QTimer timer2;
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    connect(&timer2, SIGNAL(timeout()), this, SLOT(timerHit2()), Qt::DirectConnection);
    timer.setInterval(timeBetweenResearch);
    timer2.setInterval(timeBetweenActions);
    timer.start();   // puts one event in the threads event queue
    timer2.start();
    exec();
    timer.stop();
    timer2.stop();
}


void AI::timerHit2()
{
    //tous les timeBetweenActions, dirige de 1 l'aspirateur vers sa cible
    srand (time(NULL));

    //algo rapide
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
    srand (time(NULL));

   //Reparser la carte et regarder si l'objectif fixé avant est toujours le plus optimal

   // BELIEF - Récupérer ce qu'on sait sur la carte. Supposé ici : on connaît la carte en son ensemble, a ajouter un filtre si besoin/envie
   env = ObserveEnvironmentWithAllMySensors();

   //DESIRE
   //Regarder ce qui est rentable de faire - ce qu'on veux faire au final. Exemple : exterminer la tache en X1,Y1
    std::vector<Point> v;
    v = UpdateMyState();
    Point choixDestination = ChooseAnAction(v);

   //TODO TT Parse la grille et, par rapport au gain, faire un choix de cible
   //x_cible= choix.x;
   //y_cible = choix.y;

   machineLearning();


   //INTENTION
   //Trouver le plus court chemin pour aller a x1,y1 et effectuer l'action à part. dans le Run.

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

Matrix<Box, WIDTH, HEIGHT> AI::ObserveEnvironmentWithAllMySensors(){
    Matrix<Box, WIDTH, HEIGHT> m;
    m = Sensor();
}


Matrix<Box, WIDTH, HEIGHT> AI::Sensor(){
    //Todo Geoffrey - récuperer depuis l'environnment
    Matrix<Box, WIDTH, HEIGHT> *m = new Matrix<Box, WIDTH, HEIGHT>;
}

 std::vector<Point> AI::UpdateMyState(){
    for (Box &bobox : env.m_Data){
        //Pour chaque boite de la matrice, on regarde si elle est vide et on renvoie une liste de position de boites non vides.

        //Obstacle o = bobox.getContent();
        //if (o == dynamic_cast<Box*>(o)){
        //}
    }
    std::vector<Point> v;
    return v;
 }

Point AI::ChooseAnAction(std::vector<Point> v){

}
