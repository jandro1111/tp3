// tp3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"backend.h"



using namespace std;
int main(int argc,char**argv)
{
    int cant,blobcant, ticks,b, ancho, largo, blobcantini, modo;
    srand(time(NULL));
    pCallback p = parseCallback;

    printf("El primer dato es el ancho, el segundo el largo, el tercero la cantidad inicial de blobs, y el cuarto el modo, mandar solo parametros \n");
    printf("El modo es 1 para ... , y 2 para....\n");

    if (((cant = parseCmdLine(argc, argv, p)) > 4) || ((cant = parseCmdLine(argc, argv, p)) < 3)) {//si pase una cantidad incorrecta de datos
        printf("Parametros incorrectos o insuficientes. \n");
        return (EXIT_FAILURE);  //Se revisa que el ingreso de datos sea válido
    }
    else {//pase una cantidad correcta de datos, veo que estos sean correctos

         ancho = atoi(argv[1]);
         largo = atoi(argv[2]);//casteo a int
         blobcantini = atoi(argv[3]);
         modo = atoi(argv[4]);

        printf("ancho:%d largo:%d blobs:%d modo:%d \n", ancho, largo, blobcantini, modo);

        if (ancho <= 0 || ancho > ANCHOMAX) {//si es un ancho no valido
            printf("Ancho no valido\n");
            return (EXIT_FAILURE);
        }
        if (largo <= 0 || largo > LARGOMAX) {//si es un largo no valido
            printf("Largo no valido\n");
            return (EXIT_FAILURE);
        }
        if (blobcantini <= 0) {//cant de robot no valido
            printf("Cantidad de robots no valida\n");
            return (EXIT_FAILURE);
        }
        if (modo < 1 || modo>2) {//si es un modo no valido
            printf("Modo no valido\n");
            return (EXIT_FAILURE);
        }
    }


    Floor* f;
    Blob* blob_p;
    b = 0;
        f = createfloor(largo, ancho);
        blob_p = (Blob*)createblob(largo, ancho, blobcantini);

    for (int i = 0; i < largo; ++i) {
        for (int j = 0; j < ancho; ++j) {
            cout<< *((f->tiles) + j + i * ancho) ;
        }
        cout << endl;
    }
    printf("x:%lf y:%lf angulo en radianes:%lf  x:%d  y:%d\n", ((blob_p+b)->x), ((blob_p+b)->y), ((blob_p+b)->angle), (int)((blob_p+b)->x), (int)((blob_p+b)->y));
    
      

        deleteRobot(blob_p);
        deletefloor(f);

        return(EXIT_SUCCESS);
}


