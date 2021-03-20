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


class drawingData
{
public:
	drawingData(void);

	ALLEGRO_BITMAP* background;

	ALLEGRO_BITMAP* blob1;
	ALLEGRO_BITMAP* blob2;
	ALLEGRO_BITMAP* blob3;

	ALLEGRO_BITMAP* food;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font1;
	ALLEGRO_FONT* font2;
};



//Inicia todo lo referente a allegro
int allegro_start(drawingData* draw);

void draw_all(simulation* sim, drawingData* draw);

#endif /* ALLEGRO_DRAW_H */

