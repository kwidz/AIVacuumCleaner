#include "ai.h"
#include "environment.h"
#include<iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
#include <stdlib.h>

//position de l'aspirateur
int x, y;
//position de la cible
int x1, y1;

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

   // BELIEF - Récupérer ce qu'on sait sur la carte. Supposé ici : on connaît la carte en son ensemble, a ajouter un filtre si besoin/envie
   //Matrix m = Environment::getGrid();      -----  A appeler quand la matrice sera effective


   int matrixDeRemplacement [10][10];

   //DESIRE
   //Regarder ce qui est rentable de faire - ce qu'on veux faire au final. Exemple : exterminer la tache en X1,Y1

   //TODO TT Parse la grille et, par rapport au gain, faire un choix de cible
   //x1= choix.x;
   //y1 = choix.y;


   //INTENTION
   //Trouver le plus court chemin pour aller a x1,y1 et effectuer l'action à part. dans le Run.

   //Résultat : tous les timeBetweenResearch, on effectue une remise en question. Mais sinon, on se dirige vers l'objectif courrant.


}

