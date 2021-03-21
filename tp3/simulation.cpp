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

    foodShown = 0;
    Food comid[MAXFOOD];
    
    for (int i = 0; i < MAXFOOD; ++i) {
        comid[i].shown = false;//empizo sin mostrar ninguna comida
        //despues cuando spawneo la comida le inicializo el resto de los datos
    }
    comida = comid;
}

void simulation::runSim(void) {

    int crashCheck = -1;

    for (int i = 0; i < MAXBLOB; ++i) {

        if ((blob[i].getdead()) == false) {     //si no esta muerto, hace todo lo de un blob vivo

            blob[i].moveblob();                 //muevo el blob ANDA
            blob[i].blobdeath(deathChance);     //veo si se muere ANDA
            blob[i].setvel(velPorc);            //seteo velocidad ANDA
            blob[i].blobfeed(smellRadius, comida);//hace que se muevan hacia la comida mas cercana ANDA a veces

            crashCheck = blob[i].foodCrash(comida);   
            if (crashCheck != -1) {
                foodShown--;
                //if (blob[i].blobEats(comida, crashCheck)) { //En el caso de que se produzca un blobBirth

                //    blob[i].blobBirth(blob);
                //}
                crashCheck = -1;
            }
            
            //crashCheck = blob[i].blobCrash(blob, i); // no anda
            //if (crashCheck != -1) {

            //    blob[i].blobMerge(blob, crashCheck, randomJiggleLimit);
            //    crashCheck = -1;
            //}

            cout << i << " posicion x: " << blob[i].getposx() << " posicion y: " << blob[i].getposy() << " angulo: " << blob[i].getangle() << " muerto: " << blob[i].getdead() << endl;
        }
    }
    foodShown = foodspawn(foodCount, comida, foodShown);                   //genera de a una comida x vez
    cout << foodShown << endl;
    cout << "\n" << endl;
}

