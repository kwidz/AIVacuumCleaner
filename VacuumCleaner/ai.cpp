#include "ai.h"
#include "environment.h"
#include<iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <stdlib.h>

//position de l'aspirateur
int x;
int y;
//position de la cible
int x_cible;
int y_cible;

AI::AI()
{

}

void AI::run(){

    std::cout << "aiRun";
    int timeBetweenResearch = 5000;
    int timeBetweenActions = 1000;
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
    std::cout << "timer1";
    srand (time(NULL));

    //algo rapide
    if(x<x_cible) {
        x++;
    } else if (x>x_cible) {
        x--;
    } else if (y>y_cible){
        y--;
    } else if (y<y_cible){
        y++;
    } else /*Sur la cible*/ {
        //Aspire / récupère selon le type de la case sur laquelle il se trouve
        //Sinon si la case est vide / do nothing. L'aspirateur n'a plus de but et attends une nouvelle cible
    }


}




void AI::timerHit()
{
    int choix_x;
    int choix_y;

    srand (time(NULL));
    std::cout << "timer2";

   //Reparser la carte et regarder si l'objectif fixé avant est toujours le plus optimal

   // BELIEF - Récupérer ce qu'on sait sur la carte. Supposé ici : on connaît la carte en son ensemble, a ajouter un filtre si besoin/envie
   //Matrix m = Environment::getGrid();      -----  A appeler quand la matrice sera effective


   int matrixDeRemplacement [10][10];

   //DESIRE
   //Regarder ce qui est rentable de faire - ce qu'on veux faire au final. Exemple : exterminer la tache en X1,Y1

   //TODO TT Parse la grille et, par rapport au gain, faire un choix de cible
   //x_cible= choix.x;
   //y_cible = choix.y;

   machineLearning(choix_x, choix_y);


   //INTENTION
   //Trouver le plus court chemin pour aller a x1,y1 et effectuer l'action à part. dans le Run.

   //Résultat : tous les timeBetweenResearch, on effectue une remise en question. Mais sinon, on se dirige vers l'objectif courrant.


}

void AI::machineLearning(int x,int y){

//Cette fonction va adapter le temps entre deux recherches de l'environnement selon ses dernières expériences

if (x != x_cible || y != y_cible)
{
   timeBetweenResearch += 500;
} else {
    timeBetweenResearch -= 500;
}
}

