/*****************************************************************************
  @file     simulation.cpp
  @author   Grupo 1
 ******************************************************************************/

#include "simulation.h"

void simulation::initSim(void){

    //inicializo los blobs
    deathChance = 0;
    foodCount = 10;            // entre 0 y 100, empiza seteada en 10
    smellRadius = 100;         //el minimo deberia ser 40, que es el tamaño de la hitbox del blob chiquito
    randomJiggleLimit = 180;
    velPorc = 0.5;

    blob = static_cast<Blob*>(::operator new[](MAXBLOB * sizeof(Blob)));
    for (size_t i = 0; i < MAXBLOB; i++) {              //creo el arreglo con todos los blobs que voy a poder usar
        ::new (blob + i) Blob(BabyBlob, modo, velPorc, velMax);
    }

    for (int i = blobsCantIni; i < MAXBLOB; ++i) {      //mato todos los que no estoy usando segun la cantidad de blobs iniciales
        blob[i].kill();
    }
    //inicializo la comida

    foodShown = 0;
    comida = static_cast<Food*>(::operator new[](MAXFOOD * sizeof(Food)));
    
    for (int i = 0; i < MAXFOOD; ++i) {
        comida[i].shown = false;     //empizo sin mostrar ninguna comida
                                    //despues cuando spawneo la comida le inicializo el resto de los datos
    }
}

void simulation::runSim(void) {

    int crashCheck = -1;

    for (int i = 0; i < MAXBLOB; ++i) {

        if ((blob[i].getdead()) == false) {     //si no esta muerto, hace todo lo de un blob vivo

            blob[i].moveblob();                 //muevo el blob ANDA
            blob[i].blobdeath(deathChance);     //veo si se muere ANDA
            blob[i].setvel(velPorc);            //seteo velocidad ANDA
            blob[i].blobfeed(smellRadius, comida);//hace que se muevan hacia la comida mas cercana ANDA a veces

            if (foodShown > 0) {
                crashCheck = blob[i].foodCrash(comida);
                if (crashCheck != -1) {
                    foodShown--;
                    if (blob[i].blobEats()) { //En el caso de que se produzca un blobBirth

                        blob[i].blobBirth(blob);
                    }
                    crashCheck = -1;
                }
            }
            if (blob[i].CantMerge == 0) {
                crashCheck = blob[i].blobCrash(blob, i);
                if (crashCheck != -1) {

                    blob[i].blobMerge(blob, crashCheck, randomJiggleLimit);
                    crashCheck = -1;
                }
            }

            if (blob[i].CantMerge > 0 && blob[i].CantMerge <= UNMERGEABLETICKS) {
                (blob[i].CantMerge)--;
            }

            //cout << i << " posicion x: " << blob[i].getposx() << " posicion y: " << blob[i].getposy() << " angulo: " << blob[i].getangle() << " muerto: " << blob[i].getdead() << endl;
        }
    }
    foodShown = foodspawn(foodCount, comida, foodShown);                   //genera de a una comida x vez

}

