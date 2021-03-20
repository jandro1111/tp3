#pragma once
#ifndef BLOB_H
#define BLOB_H
#include"backend.h"
class Blob
{
public:
	Blob(int,int,double,int);
	~Blob();
	int setfood(int);//guarda comida en blob,y avisa si crece
	double getposx(void);//te dice donde esta el blob
	double getposy(void);//te dice donde esta el blob
	double getangle(void);//da el angulo del blob
	bool getdead(void);
	void setangle(bool);//cambia el angulo
	void setvel(double);
	void setpos(Point);//cambia la pos del blob
	void moveblob(void);//mueve el blob
	void blobdeath(double);//decide si vive o muere el blob
	void kill(void);//mata un blob
	void sethitbox(void);// cambio el hitbox, en funcion de la posicion y el tipo de blob
	void blobfeed(int,int,Food*);//hace que el blob se mueva hacia la comida
//protected:

//private:
	Point p;
	double angle;
	int food;
	int death;											//Para que sirve este?
	int tipo;			//1 es chico 2 es medio y 3 es grande
	int velocidad;										//Para que sirve este?
	bool dead;
	double vel;
	int velmax;
	Rect hitbox;
	//tipo 1 es de 40x40 5 de comida para generar otro
	//tipo 2 45x45 4 de comida para generar otro
	//tipo 3 80x80 3 de comida para generar otro
};

#endif