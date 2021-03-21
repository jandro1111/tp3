#include "allegro_draw.h"

drawingData::drawingData(void) {
	background = NULL;
	event_queue = NULL;
	timer = NULL;
	buffer = NULL;
	food = NULL;
	blob1 = NULL;
	blob2 = NULL;
	blob3 = NULL;
	display = NULL;
	font1 = NULL;
	font2 = NULL;
	redraw = false;
	do_exit = false;
	pointer_x = 0;
	pointer_y = 0;
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

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	draw->event_queue = al_create_event_queue();
	if (!draw->event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		return -1;
	}

	draw->timer = al_create_timer(1.0 / FPS);
	if (!draw->timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	draw->display = al_create_display(SCREEN_W, SCREEN_H);

	if (!draw->display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}


	if (!al_init_image_addon()) {
		fprintf(stderr, "Unable to start image addon \n");
		return -1;
	}

	draw->buffer = al_create_bitmap(ANCHOMAX, LARGOMAX);
	if (!draw->buffer) {
		fprintf(stderr, "failed to create buffer!\n");
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

	al_set_target_bitmap(draw->buffer);
	

	al_register_event_source(draw->event_queue, al_get_display_event_source(draw->display));
	al_register_event_source(draw->event_queue, al_get_timer_event_source(draw->timer));
	al_register_event_source(draw->event_queue, al_get_mouse_event_source());

	al_start_timer(draw->timer);

	return 0;
}



void draw_all(simulation* sim, drawingData* draw)
{
	al_set_target_bitmap(draw->buffer);
	al_draw_bitmap(draw->background, 0, 0, 0);//se dibuja el fondo

	int flag = ALLEGRO_FLIP_HORIZONTAL;
	float angulo[MAXBLOB];
	int n;

	//Dibujo de blobs
	for (n = 0; n < MAXBLOB; n++)
	{
		if ( !(sim->blob[n].dead))
		{
			angulo[n] = -(sim->blob[n].angle);

			flag = ALLEGRO_FLIP_HORIZONTAL;

			if (sim->blob[n].angle <= (PI / 2) || sim->blob[n].angle >= ((3 / 2) * PI))
			{
				flag = 0;
				angulo[n] = PI - sim->blob[n].angle;
			}

			if (sim->blob[n].tipo == 1)
				//al_draw_rotated_bitmap(draw->blob1, sim->blob[n].p.x, sim->blob[n].p.y, (sim->blob[n].hitbox.arribader.x) - BLOB1_SIZE, (sim->blob[n].hitbox.arribader.y), angulo[n], flag);
				al_draw_bitmap(draw->blob1, sim->blob[n].p.x, sim->blob[n].p.y, flag);
			else if (sim->blob[n].tipo == 2)
				al_draw_bitmap(draw->blob2, sim->blob[n].p.x, sim->blob[n].p.y, flag);
				//al_draw_rotated_bitmap(draw->blob2, sim->blob[n].p.x, sim->blob[n].p.y, (sim->blob[n].hitbox.arribader.x) - BLOB2_SIZE, (sim->blob[n].hitbox.arribader.y), angulo[n], flag);
			else if (sim->blob[n].tipo == 3)
				al_draw_bitmap(draw->blob3, sim->blob[n].p.x, sim->blob[n].p.y, flag);
				//al_draw_rotated_bitmap(draw->blob3, sim->blob[n].p.x, sim->blob[n].p.y, (sim->blob[n].hitbox.arribader.x) - BLOB3_SIZE, (sim->blob[n].hitbox.arribader.y), angulo[n], flag);
		}
	}

	//Dibujo de la comida
	for (n = 0; n < MAXFOOD; n++)
	{
		if (sim->comida[n].shown == true)
			al_draw_bitmap(draw->food, (sim->comida[n].hitbox.arribader.x) - (FOOD_SIZE), (sim->comida[n].hitbox.arribader.y) , 0);
	}

	//Dibujo del mouse
	al_draw_bitmap(draw->food, draw->pointer_x, draw->pointer_y, 0);

	post_draw(draw);
}

void post_draw(drawingData* draw)
{
	al_set_target_backbuffer(draw->display);

	al_draw_scaled_bitmap(draw->buffer,0,0,ANCHOMAX,LARGOMAX,0,0,SCREEN_W,SCREEN_H,0);
	al_flip_display();
}

void allegro_events(drawingData* draw)
{
	ALLEGRO_EVENT ev;
	if (al_get_next_event(draw->event_queue, &ev)) //Toma un evento de la cola
	{
		if (ev.type == ALLEGRO_EVENT_TIMER)
			draw->redraw = true;

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)//Si se cierra el display o click de mouse cerrar
			draw->do_exit = true;

		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			draw->pointer_y = ev.mouse.y;
			draw->pointer_x = ev.mouse.x;
		}
	}
}
