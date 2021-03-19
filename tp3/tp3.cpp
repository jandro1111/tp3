// tp3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include"backend.h"
#include"Blob.h"



int main(int argc, char** argv)
{
    int cant, blobcant, ticks, b, blobcantini, modo,velmax;
    srand(time(NULL));//para randomizar
    pCallback p = parseCallback;

    printf(" El primer dato es la cantidad inicial de blobs, y el segundo  el modo, y el trecero para velmax,mandar solo parametros \n");
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
        if (blobcantini <= 0) {//cant de robot no valido
            printf("Cantidad de robots no valida\n");
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
    /// modo 1 vmax es seteada por terminal
    /// v porcentual, por gui, todos los blobs comparten la misma vel
    //modo 2
    // cada blob tiene una vmax, es random entre un valor puesto por terminal
    //v porcentual random, todos los blobs comparten la misma vel
    //
    //GUIpara ambos modosI
    //randomjigglelimit(num entre 0 y 360)
    //foodcount
    // prob de muerte entre 0y1
    //radio de deteccion de comida
    blobcant = blobcantini;
    double prob = 0.05;//sacar cuando este la gui
    double velpor = 0.5;//
    Blob blob1(1,modo,velpor,velmax);
    cout << "vel: " << (velmax * velpor) << " vel: %"<< (velpor*100)<< endl;
    cout << "posicion x: " << blob1.getposx() << " posicion y: " << blob1.getposy() << " angulo: " << blob1.getangle() << endl;
    for (ticks = 0; ticks < 20; ++ticks) {
        blob1.moveblob();
        blob1.blobdeath(prob);
    cout << "posicion x: " << blob1.getposx() << " posicion y: " << blob1.getposy() << " angulo: " << blob1.getangle() << " muerto: "<<blob1.getdead()<< endl;
}
    return(EXIT_SUCCESS);
}


