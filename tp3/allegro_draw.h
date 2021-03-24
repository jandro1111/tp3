/*****************************************************************************
  @file     allegro_draw.h
  @author   Grupo 1
 ******************************************************************************/

#ifndef ALLEGRO_DRAW_H
#define ALLEGRO_DRAW_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#include "simulation.h"

//Tamaño de la pantalla t fps
#define SCREEN_SIZE 2
#define SCREEN_W (ANCHOMAX*SCREEN_SIZE)
#define SCREEN_H (LARGOMAX*SCREEN_SIZE)
#define FPS 10.0

//ancho del menu
#define OFFSET 420

//tamaño de los botones
#define BUTTON_SIZE 50

//COORDENADAS DE LOS BOTONES
 
//Cerrar y abrir menu
#define BUTTON1X 0
#define BUTTON1Y 50

#define BUTTON2X  OFFSET
#define BUTTON2Y 50

//Regulador de velocidad
#define VELX 60
#define VELY (LARGOMAX/5)

#define BUTTON3X (VELX -20)
#define BUTTON3Y (VELY -5)

#define BUTTON4X (VELX -20)
#define BUTTON4Y (VELY +10+40+BUTTON_SIZE)

//Regulador de probabilidad de muerte
#define MUEX 190
#define MUEY (LARGOMAX/5)

#define BUTTON5X (MUEX -20)
#define BUTTON5Y (MUEY -5)

#define BUTTON6X (MUEX -20)
#define BUTTON6Y (MUEY +10+40+BUTTON_SIZE)

//Regulador de cantidad de alimento
#define ALX 60
#define ALY (13*(LARGOMAX/20))

#define BUTTON7X (ALX -20)
#define BUTTON7Y (ALY -5)

#define BUTTON8X (ALX -20)
#define BUTTON8Y (ALY +10+40+BUTTON_SIZE)

//Regulador de deteccion de comida
#define DETX 190
#define DETY (13*(LARGOMAX/20))

#define BUTTON9X (DETX -20)
#define BUTTON9Y (DETY -5)

#define BUTTON10X (DETX -20)
#define BUTTON10Y (DETY +10+40+BUTTON_SIZE)

//Regulador de aleatoriedad de giro
#define GIRX 330
#define GIRY (LARGOMAX/5)

#define BUTTON11X (GIRX -20)
#define BUTTON11Y (GIRY -5)

#define BUTTON12X (GIRX -20)
#define BUTTON12Y (GIRY +10+40+BUTTON_SIZE)

//Info extra
#define BUTTON13X -18
#define BUTTON13Y 445

#define INFO_X 270
#define INFO_Y 210

class drawingData
{
public:
	drawingData(void);

	ALLEGRO_BITMAP* buffer;
	ALLEGRO_BITMAP* buffer2;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* blob1;
	ALLEGRO_BITMAP* blob2;
	ALLEGRO_BITMAP* blob3;
	ALLEGRO_BITMAP* flecha;
	ALLEGRO_BITMAP* bmenu;
	ALLEGRO_BITMAP* moreinfo;

	ALLEGRO_BITMAP* food;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font1;
	ALLEGRO_FONT* font2;

	bool redraw ;
	bool do_exit;

	float pointer_x;
	float pointer_y;

	float offset;
	bool menu;
	bool info;
};


//Inicia todo lo referente a allegro
int allegro_start(drawingData* draw);

//Dibuja la simulacion
void draw_all(simulation* sim, drawingData* draw);

//Detecta si se presiono algun boton en pantalla
void allegro_events(simulation* sim, drawingData* draw);


#endif /* ALLEGRO_DRAW_H */

