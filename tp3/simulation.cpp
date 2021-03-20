
#include "simulation.h"

void simulation::initSim(void){

    //inicializo los blobs

    blob = static_cast<Blob*>(::operator new[](MAXBLOB * sizeof(Blob)));
    for (size_t i = 0; i < MAXBLOB; i++) {              //creo el arreglo con todos los blobs que voy a poder usar
        ::new (blob + i) Blob(1, modo, velPorc, velMax);
    }

    for (int i = blobsCantIni; i < MAXBLOB; ++i) {      //mato todos los que no estoy usando segun la cantidad de blobs iniciales
        blob[i].kill();
    }
    //inicializo la comida

    int foodshown = 0;
    Food comida[MAXFOOD];
    for (int i = 0; i < MAXFOOD; ++i) {
        comida[i].shown = false;//empizo sin mostrar ninguna comida
        //despues cuando spawneo la comida le inicializo el resto de los datos
    }
}

void simulation::runSim(void) {

    Food* f = comida;

    for (int i = 0; i < MAXBLOB; ++i) {
        if ((blob[i].getdead()) == false) {     //si no esta muerto, hace todo lo de un blob vivo

            blob[i].moveblob();                 //muevo el blob
            blob[i].blobdeath(deathChance);     //veo si se muere
            blob[i].setvel(velPorc);
            blob[i].blobfeed(smellRadius, foodShown, f);
            cout << i << " posicion x: " << blob[i].getposx() << " posicion y: " << blob[i].getposy() << " angulo: " << blob[i].getangle() << " muerto: " << blob[i].getdead() << endl;
        }
    }
    foodShown = foodspawn(foodCount, f, foodShown);//genera de a una comida x vez
    cout << foodShown << endl;
    cout << "\n" << endl;
}