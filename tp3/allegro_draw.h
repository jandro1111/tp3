#ifndef ALLEGRO_DRAW_H
#define ALLEGRO_DRAW_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

typedef struct {
	long base;
	long altura;
	long robots;
	int modo;
}MyData_t;

#define BUFFER_SIZE 230.0
#define DISP_SCALE 4
#define SCREEN_W (BUFFER_SIZE * DISP_SCALE)
#define SCREEN_H (BUFFER_SIZE * DISP_SCALE)


#define ROBOT_RADIO 250
#define DOT_RADIO 100
#define SEPARACIONES_Y 21
#define SEPARACIONES_X 10
#define VELOCIDAD 300.0
#define REST (1/VELOCIDAD)
#define TIEMPO_DE_GRAFICO 600.0


//Inicia todo lo referente a allegro
int allegro_start(drawingData* draw);

void draw_all(simulation* sim, drawingData* draw);

#endif /* ALLEGRO_DRAW_H */

