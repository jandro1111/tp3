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

    //Escribi en consola tipo -modo 1 -blobscantini 10 -velmax 20 
    parseCmdLine(argc, argv, parseCallback, &Simu);

    printf("modo: %d, velMax: %d, blobsCantIni: %d\n", Simu.modo, Simu.velMax, Simu.blobsCantIni);

    Simu.deathChance = 0;       //sacar TODO LO SIGUIENTE cuando este la gui
    Simu.velPorc = 0.5;         //entre 0 y 1 empieza en 0.5
    Simu.foodCount = 10;        // entre 0 y 100, empiza seteada en 10
    Simu.smellRadius = 100;     //el minimo deberia ser 40, que es el tama�o de la hitbox del blob chiquito
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

