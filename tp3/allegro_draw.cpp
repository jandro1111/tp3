#include "allegro_draw.h"

drawingData::drawingData(void) {
	background = NULL;
	food = NULL;
	blob1 = NULL;
	blob2 = NULL;
	blob3 = NULL;
	display = NULL;
	font1 = NULL;
	font2 = NULL;
}

int allegro_start(drawingData* draw)
{

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	draw->display = al_create_display(ANCHOMAX, LARGOMAX);

	if (!draw->display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}


	if (!al_init_image_addon()) {
		fprintf(stderr, "Unable to start image addon \n");
		return -1;
	}

	if (!(draw->blob1 = al_load_bitmap("babyblob.png"))) {
		fprintf(stderr, "Unable to load png1\n");
		return -1;
	}

	if (!(draw->blob2 = al_load_bitmap("grownblob.png"))) {
		fprintf(stderr, "Unable to load png2\n");
		return -1;
	}

	if (!(draw->blob3 = al_load_bitmap("goodoldblob.png"))) {
		fprintf(stderr, "Unable to load png3\n");
		return -1;
	}

	if (!(draw->background = al_load_bitmap("background.jpg"))) {
		fprintf(stderr, "Unable to load png4\n");
		return -1;
	}

	if (!(draw->food = al_load_bitmap("food.png"))) {
		fprintf(stderr, "Unable to load png5\n");
		return -1;
	}

	al_set_window_title(draw->display, "BLOB evolution");
	al_set_display_icon(draw->display, draw->blob1);


	/*al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
	draw->font1 = al_load_ttf_font("Sans.ttf", DISP_SCALE * 7, 0);
	if (!draw->font1) {
		fprintf(stderr, "Could not load 'Sans.ttf'.\n");
		return -1;
	}
	draw->font2 = al_load_ttf_font("Sans.ttf", DISP_SCALE * 4, 0);
	if (!draw->font2) {
		fprintf(stderr, "Could not load 'Sans.ttf'.\n");
		return -1;
	}*/

	al_set_target_backbuffer(draw->display);

	return 0;
}



void draw_all(simulation* sim, drawingData* draw)
{
	al_draw_bitmap(draw->background, 0, 0, 0);//se dibuja el fondo

	int flag = 0;
	float angulo[MAXBLOB];
	int n;

	//Dibujo de blobs
	for (n = 0; n < MAXBLOB; n++)
	{
		if ( !(sim->blob[n].dead))
		{
			angulo[n] = -(sim->blob[n].angle);

			if (sim->blob[n].angle <= (PI / 2) || sim->blob[n].angle >= ((3 / 2) * PI))
			{
				flag = ALLEGRO_FLIP_HORIZONTAL;
				angulo[n] = PI - sim->blob[n].angle;
			}

			if (sim->blob[n].tipo == 1)
				al_draw_rotated_bitmap(draw->blob1, (sim->blob[n].hitbox.arribader.x) - (BLOB1_SIZE / 2), (sim->blob[n].hitbox.arribader.y) + (BLOB1_SIZE / 2), sim->blob[n].p.x, sim->blob[n].p.y, angulo[n], flag);
			else if (sim->blob[n].tipo == 2)
				al_draw_rotated_bitmap(draw->blob2, (sim->blob[n].hitbox.arribader.x) - (BLOB2_SIZE / 2), (sim->blob[n].hitbox.arribader.y) + (BLOB1_SIZE / 2), sim->blob[n].p.x, sim->blob[n].p.y, angulo[n], flag);
			else if (sim->blob[n].tipo == 3)
				al_draw_rotated_bitmap(draw->blob3, (sim->blob[n].hitbox.arribader.x) - (BLOB3_SIZE / 2), (sim->blob[n].hitbox.arribader.y) + (BLOB1_SIZE / 2), sim->blob[n].p.x, sim->blob[n].p.y, angulo[n], flag);
		}
	}

	//Dibujo de la comida
	/*for (n = 0; n < MAXFOOD; n++)
	{
		if (sim->comida[n].shown == true)
			al_draw_bitmap(draw->food, (sim->comida[n].hitbox.arribader.x) - (FOOD_SIZE), (sim->comida[n].hitbox.arribader.y) , 0);
	}*/

	al_flip_display();
}