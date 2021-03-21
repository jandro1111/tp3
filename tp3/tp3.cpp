// tp3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "backend.h"
#include "Blob.h"
#include "allegro_draw.h"

#include <Windows.h>

int main(int argc, char** argv)
{
    simulation Simu;

    drawingData drawing;

    if (allegro_start(&drawing))
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    srand(time(NULL));          //para randomizar

    /*

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

    */

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


    Simu.deathChance = 0;       //sacar TODO LO SIGUIENTE cuando este la gui
    Simu.velPorc = 0.5;         //entre 0 y 1 empieza en 0.5
    Simu.foodCount = 10;        // entre 0 y 100, empiza seteada en 10
    Simu.smellRadius = 100;     //el minimo deberia ser 40, que es el tamaño de la hitbox del blob chiquito
    Simu.modo = 1;
    Simu.blobsCantIni = 10;
    Simu.velMax = 10;
    Simu.randomJiggleLimit = 180;

    Simu.initSim();

    while (!drawing.do_exit) // idem anterior
    {
        allegro_events(&drawing);

        if (drawing.redraw && al_is_event_queue_empty(drawing.event_queue))
        {
            drawing.redraw = false;

            Simu.runSim();

            draw_all(&Simu, &drawing);

        }
    }

    return(EXIT_SUCCESS);

}
void Blob::blobBirth(Blob* blobs) {

    bool encontrado = false;    

    for (int i = 0; (i < MAXBLOB) && (encontrado == false); i++) { //Busco un blob que este muerto

        if ((blobs[i]).dead == true) {   //Cuando encuentro un blob muerto, lo revivo e inicializo

            (blobs[i]).dead = false;
            (blobs[i]).tipo = BabyBlob;
            (blobs[i]).p.x = p.x;
            (blobs[i]).p.y = p.y;

            encontrado = true;
        }
    }
}

