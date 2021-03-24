/*****************************************************************************
  @file     tp3.cpp (main)
  @author   Grupo 1
 ******************************************************************************/
/**************************************
   _____                          __ 
  / ____|                        /_ |
 | |  __ _ __ _   _ _ __   ___    | |
 | | |_ | '__| | | | '_ \ / _ \   | |
 | |__| | |  | |_| | |_) | (_) |  | |
  \_____|_|   \__,_| .__/ \___/   |_|
                   | |               
                   |_|               
***************************************/

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

    //Escribi en consola por ej:
    //                         -modo 1 -blobscantini 10 -velmax 20 
    if (parseCmdLine(argc, argv, parseCallback, &Simu) != 3 ) {
        
        cout << "Ingrese solo los datos pre-simulacion" << endl;
    }

    printf("modo: %d, velMax: %d, blobsCantIni: %d\n", Simu.modo, Simu.velMax, Simu.blobsCantIni);

    Simu.deathChance = 0;           //sacar TODO LO SIGUIENTE cuando este la gui
    Simu.foodCount = 10;            // entre 0 y 100, empiza seteada en 10
    Simu.smellRadius = 100;         //el minimo deberia ser 40, que es el tama�o de la hitbox del blob chiquito
    Simu.randomJiggleLimit = 180;

    Simu.initSim();

    while (!drawing.do_exit) // idem anterior
    {
        allegro_events(&Simu, &drawing);

        if (drawing.redraw && al_is_event_queue_empty(drawing.event_queue))
        {
            drawing.redraw = false;

            Simu.runSim();

            draw_all(&Simu, &drawing);

        }
    }

    return(EXIT_SUCCESS);

}

