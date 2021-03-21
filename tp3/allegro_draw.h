#ifndef ALLEGRO_DRAW_H
#define ALLEGRO_DRAW_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>*/

#include "simulation.h"

#define SCREEN_SIZE 1
#define SCREEN_W (ANCHOMAX*SCREEN_SIZE)
#define SCREEN_H (LARGOMAX*SCREEN_SIZE)
#define FPS 10.0

#define BUTTON1X 0
#define BUTTON1Y 50

#define BUTTON2X 300
#define BUTTON2Y 50

#define BUTTON3X 40
#define BUTTON3Y 150

#define BUTTON4X 40
#define BUTTON4Y 300

#define BUTTON_SIZE 50


class drawingData
{
public:
	drawingData(void);

	ALLEGRO_BITMAP* buffer;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* blob1;
	ALLEGRO_BITMAP* blob2;
	ALLEGRO_BITMAP* blob3;

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
};


//Inicia todo lo referente a allegro
int allegro_start(drawingData* draw);

void draw_all(simulation* sim, drawingData* draw);

void post_draw(drawingData* draw);

void allegro_events(simulation* sim, drawingData* draw);

bool isButtonPress(drawingData* draw, float abajoizqx, float abajoizqy);

#endif /* ALLEGRO_DRAW_H */

