// tp3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "backend.h"
#include "Blob.h"
#include "simulation.h"



int main(int argc, char** argv)
{
    simulation Simu;

    srand(time(NULL));//para randomizar

    int cant, blobcant, ticks, b, blobcantini, modo,velmax;
    pCallback p = parseCallback;

    printf(" El primer dato es la cantidad inicial de blobs, y el segundo el modo, y el tercero para velmax,mandar solo parametros \n");
    printf("El modo es 1 para ... , y 2 para....\n");

    if ((cant = parseCmdLine(argc, argv, p)) != 3) {//si pase una cantidad incorrecta de datos
        printf("Parametros incorrectos o insuficientes. \n");
        return (EXIT_FAILURE);  //Se revisa que el ingreso de datos sea válido
    }
    else {//pase una cantidad correcta de datos, veo que estos sean correctos

        blobcantini = atoi(argv[1]);
        modo = atoi(argv[2]);
        velmax = atoi(argv[3]);//en pixeles x tick
        printf(" blobs iniciales:%d modo:%d vel max:%d \n", blobcantini, modo,velmax);
        if (blobcantini <= 0||blobcantini>MAXBLOB) {//cant de robot no valido
            printf("Cantidad de blobs no valida\n");
            return (EXIT_FAILURE);
        }
        if (modo < 1 || modo>2) {//si es un modo no valido
            printf("Modo no valido\n");
            return (EXIT_FAILURE);
        }
        if (velmax <= 0) {
            cout << "velocidad maxima no valida" << endl;
            return(EXIT_FAILURE);
        }
    }
    /// modo 1 vmax es seteada por terminal ESTA
    /// v porcentual, por gui, todos los blobs comparten la misma vel ESTA
    //modo 2
    // cada blob tiene una vmax, es random entre un valor puesto por terminal ESTA
    //v porcentual random, todos los blobs comparten la misma vel ESTA
    //
    // funciones de blobs
    // blobbirth
    // blobdeath ESTA
    // blobfood
    // blobmerge
    // blob
    //GUIpara ambos modosI
    //randomjigglelimit(num entre 0 y 360)
    //foodcount ESTA
    // prob de muerte entre 0y1 ESTA
    //radio de deteccion de comida
    blobcant = blobcantini;
    double prob = 0.05;//sacar cuando este la gui
    double velpor = 0.5;//entre 0 y 1 empieza en 0.5
    int foodcount = 10;// entre 0 y 100, empiza seteada en 10
    int smellradio = 100;//el minimo deberia ser 40, que es el tamaño de la hitbox del blob chiquito
    int i;

    //inicializo los blobs
    Blob* blob = static_cast<Blob*>(::operator new[](MAXBLOB * sizeof(Blob)));
    for (size_t i = 0; i < MAXBLOB; i++) {//creo el arreglo con todos los blobs que voy a poder usar
        ::new (blob + i) Blob(1, modo, velpor, velmax);
    }
    for (i = blobcantini; i < MAXBLOB;++i) {//mato todos los que no estoy usando segun la cantidad de blobs iniciales
        blob[i].kill();
    }
    //inicializo la comida
    int foodshown = 0;
    Food comida[MAXFOOD];
    Food* f = comida;
    for (i = 0; i < MAXFOOD; ++i) {
        comida[i].shown = false;//empizo sin mostrar ninguna comida
        //despues cuando spawneo la comida le inicializo el resto de los datos
    }

    //

    cout << "vel: " << (velmax * velpor) << " vel: %"<< (velpor*100)<< endl;
    for (ticks = 0; ticks < 20; ++ticks) {
        for (i = 0; i < MAXBLOB; ++i) {
            if ((blob[i].getdead())==false){//si no esta muerto, hace todo lo de un blob vivo
                blob[i].moveblob();//muevo el blob
                blob[i].blobdeath(prob);//veo si se muere
                blob[i].setvel(velpor);
                //blob[i].blobfeed(smellradio, foodshown, f);
                cout << i <<" posicion x: " << blob[i].getposx() << " posicion y: " << blob[i].getposy() << " angulo: " << blob[i].getangle() << " muerto: " << blob[i].getdead() << endl;
            }
        }
        foodshown=foodspawn(foodcount,f,foodshown);//genera de a una comida x vez
        cout << foodshown << endl;
        cout << "\n" << endl;
    }
    return(EXIT_SUCCESS);
}


