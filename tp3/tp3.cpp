// tp3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"backend.h"



using namespace std;
int main(int argc, char** argv)
{
    int cant, blobcant, ticks, b, blobcantini, modo;
    srand(time(NULL));
    pCallback p = parseCallback;

    printf(" El primer daro es la cantidad inicial de blobs, y el segundo  el modo, mandar solo parametros \n");
    printf("El modo es 1 para ... , y 2 para....\n");

    if ((cant = parseCmdLine(argc, argv, p)) != 2) {//si pase una cantidad incorrecta de datos
        printf("Parametros incorrectos o insuficientes. \n");
        return (EXIT_FAILURE);  //Se revisa que el ingreso de datos sea válido
    }
    else {//pase una cantidad correcta de datos, veo que estos sean correctos

        blobcantini = atoi(argv[1]);
        modo = atoi(argv[2]);

        printf(" blobs iniciales:%d modo:%d \n", blobcantini, modo);
        if (blobcantini <= 0) {//cant de robot no valido
            printf("Cantidad de robots no valida\n");
            return (EXIT_FAILURE);
        }
        if (modo < 1 || modo>2) {//si es un modo no valido
            printf("Modo no valido\n");
            return (EXIT_FAILURE);
        }
    }


    //Floor* f;
    //Blob* blob_p;
    //b = 0;
    //f = createfloor(LARGOMAX,ANCHOMAX);
    //blob_p = (Blob*)createblob(LARGOMAX, ANCHOMAX, blobcantini);

    ///*   for (int i = 0; i < LARGOMAX; ++i) {
    //       for (int j = 0; j < ANCHOMAX; ++j) {
    //           cout<< *((f->tiles) + j + i * ANCHOMAX) ;
    //       }
    //       cout << endl;
    //   }*/
    //for (b = 0; b < blobcantini; ++b) {
    //    printf("x:%lf y:%lf angulo en radianes:%lf  x:%d  y:%d\n", ((blob_p + b)->x), ((blob_p + b)->y), ((blob_p + b)->angle), (int)((blob_p + b)->x), (int)((blob_p + b)->y));
    //}
    //  

    //    deleteRobot(blob_p);
    //    deletefloor(f);

        return(EXIT_SUCCESS);
}


