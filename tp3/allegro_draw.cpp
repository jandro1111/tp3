/*****************************************************************************
  @file     allegro_draw.cpp
  @author   Grupo 1
 ******************************************************************************/

#include "allegro_draw.h"

//Dibuja el menu y y los buffers
void post_draw(simulation* sim, drawingData* draw);

//Revisa si se presiono el boton indicado
bool isButtonPress(drawingData* draw, float abajoizqx, float abajoizqy);

//Cuanto los blobs con vida
int countLiveBlobs(simulation* sim);


drawingData::drawingData(void) {
	background = NULL;
	event_queue = NULL;
	timer = NULL;
	buffer = NULL;
	buffer2 = NULL;
	flecha = NULL;
	bmenu = NULL;
	moreinfo = NULL;
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
	offset= 0;
	menu = false;
	info = false;
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

	draw->buffer2 = al_create_bitmap(OFFSET *SCREEN_SIZE, LARGOMAX);
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

	if (!(draw->flecha = al_load_bitmap("flecha.png"))) {
		fprintf(stderr, "Unable to load png6\n");
		return -1;
	}

	if (!(draw->bmenu = al_load_bitmap("menu.png"))) {
		fprintf(stderr, "Unable to load png7\n");
		return -1;
	}

	if (!(draw->moreinfo = al_load_bitmap("info.png"))) {
		fprintf(stderr, "Unable to load png8\n");
		return -1;
	}

	al_set_window_title(draw->display, "BLOB evolution");
	al_set_display_icon(draw->display, draw->blob1);


	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
	draw->font1 = al_load_ttf_font("Sans.ttf", 15, 0);
	if (!draw->font1) {
		fprintf(stderr, "Could not load 'Sans.ttf'.\n");
		return -1;
	}
	draw->font2 = al_load_ttf_font("Sans.ttf", 10, 0);
	if (!draw->font2) {
		fprintf(stderr, "Could not load 'Sans.ttf'.\n");
		return -1;
	}

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
	int n;

	//Dibujo de blobs
	for (n = 0; n < MAXBLOB; n++)
	{
		if ( !(sim->blob[n].dead))
		{


			flag = ALLEGRO_FLIP_HORIZONTAL;

			if ( (sim->blob[n].angle <= (PI / 2)) || (sim->blob[n].angle >= ((3.0 / 2.0) * PI)))
			{
				flag = 0;
			}

			if (sim->blob[n].tipo == BabyBlob)
				al_draw_bitmap(draw->blob1, sim->blob[n].p.x, sim->blob[n].p.y, flag);
			else if (sim->blob[n].tipo == GrownBlob)
				al_draw_bitmap(draw->blob2, sim->blob[n].p.x, sim->blob[n].p.y, flag);
			else if (sim->blob[n].tipo == GoodOldBlob)
				al_draw_bitmap(draw->blob3, sim->blob[n].p.x, sim->blob[n].p.y, flag);
		}
	}


	//Dibujo de la comida
	for (n = 0; n < MAXFOOD; n++)
	{
		if (sim->comida[n].shown == true)
			al_draw_bitmap(draw->food, (sim->comida[n].hitbox.arribader.x) - (FOOD_SIZE), (sim->comida[n].hitbox.arribader.y) , 0);
	}


	post_draw(sim,draw);
}



void post_draw(simulation* sim, drawingData* draw)
{
	//boton de abrir y cerrar menu
	al_draw_bitmap(draw->bmenu, BUTTON1X, BUTTON1Y - BUTTON_SIZE, 0);

	//Ajuste de dibujo de la animacion de abrir y cerrar menu
	if (draw->offset > 0 && draw->menu == false)
		draw->offset -= 30 * SCREEN_SIZE;
	else if (draw->offset < (OFFSET * SCREEN_SIZE) && draw->menu == true)
		draw->offset += 30 * SCREEN_SIZE;

	al_set_target_bitmap(draw->buffer2);

	//fondo negro del menu
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//Regulador de velocidad
	al_draw_bitmap(draw->flecha,BUTTON3X , BUTTON3Y-BUTTON_SIZE, 0);
	al_draw_bitmap(draw->flecha, BUTTON4X, BUTTON4Y - BUTTON_SIZE, ALLEGRO_FLIP_VERTICAL);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), VELX, VELY , ALLEGRO_ALIGN_CENTER, "velocidad");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), VELX, VELY+20, ALLEGRO_ALIGN_CENTER, "%.0f%%", sim->velPorc*100);

	//Regulador de probabilidad de muerte
	al_draw_bitmap(draw->flecha, BUTTON5X, BUTTON5Y - BUTTON_SIZE, 0);
	al_draw_bitmap(draw->flecha, BUTTON6X, BUTTON6Y - BUTTON_SIZE, ALLEGRO_FLIP_VERTICAL);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), MUEX, MUEY-5, ALLEGRO_ALIGN_CENTER, "probabilidad");
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), MUEX, MUEY+10, ALLEGRO_ALIGN_CENTER, "de muerte");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), MUEX, MUEY + 27, ALLEGRO_ALIGN_CENTER, "%.0f%%", sim->deathChance * 100);

	//Regulador de cantidad de alimento
	al_draw_bitmap(draw->flecha, BUTTON7X, BUTTON7Y - BUTTON_SIZE, 0);
	al_draw_bitmap(draw->flecha, BUTTON8X, BUTTON8Y - BUTTON_SIZE, ALLEGRO_FLIP_VERTICAL);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), ALX, ALY-5, ALLEGRO_ALIGN_CENTER, "comida");
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), ALX , ALY+10, ALLEGRO_ALIGN_CENTER, "maxima");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), ALX, ALY + 27, ALLEGRO_ALIGN_CENTER, "%d", sim->foodCount);

	//Regulador de deteccion de comida
	al_draw_bitmap(draw->flecha, BUTTON9X, BUTTON9Y - BUTTON_SIZE, 0);
	al_draw_bitmap(draw->flecha, BUTTON10X, BUTTON10Y - BUTTON_SIZE, ALLEGRO_FLIP_VERTICAL);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), DETX, DETY-5, ALLEGRO_ALIGN_CENTER, "deteccion de"); 
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), DETX , DETY+10, ALLEGRO_ALIGN_CENTER, "comida");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), DETX, DETY + 27, ALLEGRO_ALIGN_CENTER, "%d%%", sim->smellRadius);

	//Regulador de aleatoriedad de giro
	al_draw_bitmap(draw->flecha, BUTTON11X, BUTTON11Y - BUTTON_SIZE, 0);
	al_draw_bitmap(draw->flecha, BUTTON12X, BUTTON12Y - BUTTON_SIZE, ALLEGRO_FLIP_VERTICAL);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), GIRX, GIRY-5, ALLEGRO_ALIGN_CENTER, "aleatoriedad");
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), GIRX , GIRY+10, ALLEGRO_ALIGN_CENTER, "de giro");
		al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), GIRX, GIRY + 27, ALLEGRO_ALIGN_CENTER, "%d", sim->randomJiggleLimit);

	//Texto informativo
	
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y, ALLEGRO_ALIGN_LEFT, "Blobs con vida:");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y +20, ALLEGRO_ALIGN_LEFT, "%d", countLiveBlobs(sim));

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y + 50, ALLEGRO_ALIGN_LEFT, "Comida actual:");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y + 70, ALLEGRO_ALIGN_LEFT, "%d", sim->foodShown);

	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y + 100, ALLEGRO_ALIGN_LEFT, "Tiempo");
	al_draw_text(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y + 120, ALLEGRO_ALIGN_LEFT, "de simulacion:");
	al_draw_textf(draw->font1, al_map_rgb(255, 255, 255), INFO_X, INFO_Y +140, ALLEGRO_ALIGN_LEFT, "%d seg", (int)(al_get_timer_count(draw->timer)/10));


	//info extra
	al_draw_bitmap(draw->moreinfo, BUTTON13X, BUTTON13Y - BUTTON_SIZE, 0);
	if (draw->info==true)
		al_draw_text(draw->font2, al_map_rgb(255, 255, 255), 40, 400, ALLEGRO_ALIGN_LEFT, "Realizado por Matias, Damian y Alejandro");

	//Dibujo de los 2 buffer en el display
	al_set_target_backbuffer(draw->display);
	al_draw_scaled_bitmap(draw->buffer2, 0, 0, OFFSET, LARGOMAX, 0, 0, OFFSET * SCREEN_SIZE, SCREEN_H, 0);
	al_draw_scaled_bitmap(draw->buffer,0,0,ANCHOMAX,LARGOMAX,draw->offset,0,SCREEN_W,SCREEN_H,0);
	
	al_flip_display();
}



void allegro_events(simulation* sim, drawingData* draw)
{
	ALLEGRO_EVENT ev;
	if (al_get_next_event(draw->event_queue, &ev)) //Toma un evento de la cola
	{
		if (ev.type == ALLEGRO_EVENT_TIMER)
			draw->redraw = true;

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )//Si se cierra el display o click de mouse cerrar
			draw->do_exit = true;


		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			draw->pointer_y = ev.mouse.y/SCREEN_SIZE;
			draw->pointer_x = ev.mouse.x/SCREEN_SIZE;
		}

		//deteccion de botnes
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (isButtonPress(draw, BUTTON1X, BUTTON1Y) && draw->menu == false)
				draw->menu = true;

			if (draw->menu == true)
			{
				if (isButtonPress(draw, BUTTON2X, BUTTON2Y))
					draw->menu = false;
				if (isButtonPress(draw, BUTTON3X, BUTTON3Y))
					sim->velPorc += 0.1;
				if (isButtonPress(draw, BUTTON4X, BUTTON4Y) )
					sim->velPorc -= 0.1;
				if(sim->velPorc < 0)
					sim->velPorc = 0;
				if (isButtonPress(draw, BUTTON5X, BUTTON5Y))
					sim->deathChance += 0.1;
				if (isButtonPress(draw, BUTTON6X, BUTTON6Y))
					sim->deathChance -= 0.1;
				if (sim->deathChance < 0)
					sim->deathChance = 0;
				if (isButtonPress(draw, BUTTON7X, BUTTON7Y))
					sim->foodCount += 1;
				if (isButtonPress(draw, BUTTON8X, BUTTON8Y) && (sim->foodCount > 0))
					sim->foodCount -= 1;
				if (isButtonPress(draw, BUTTON9X, BUTTON9Y))
					sim->smellRadius += 10;
				if (isButtonPress(draw, BUTTON10X, BUTTON10Y) && (sim->smellRadius > 0))
					sim->smellRadius -= 10;
				if (isButtonPress(draw, BUTTON11X, BUTTON11Y))
					sim->randomJiggleLimit += 1;
				if (isButtonPress(draw, BUTTON12X, BUTTON12Y) && (sim->randomJiggleLimit > 0))
					sim->randomJiggleLimit -= 1;

			}
			if (isButtonPress(draw, BUTTON13X, BUTTON13Y))
			{
				if (draw->info == false)
					draw->info = true;
				else if (draw->info == true)
					draw->info = false;
			}
				
		}
	}
}



bool isButtonPress(drawingData* draw, float abajoizqx , float abajoizqy ) {
	bool a;
		if (((draw->pointer_x) > (abajoizqx)) && ((draw->pointer_y) < (abajoizqy)) && ((draw->pointer_x) < (abajoizqx+BUTTON_SIZE)) && ((draw->pointer_y) > (abajoizqy - BUTTON_SIZE)))
			a = true;
		else a = false;

	return a;
}

int countLiveBlobs (simulation* sim)
{
	int n;
	int i=0;
	for (n = 0; n < MAXBLOB; n++)
	{
		if (!(sim->blob[n].dead))
			i++;
	}
	return i;
}

/*for (k = 0; k < 2.0; k++)
{
	if (((sim->blob[n].angle <= ((PI / 2) + k * 2.0 * PI)) && (sim->blob[n].angle >= (k * 2.0 * PI))) || ((sim->blob[n].angle >= (((3 / 2) * PI) + k * 2.0 * PI)) && (sim->blob[n].angle <= ((k + 1.0) * 2.0 * PI))))*/