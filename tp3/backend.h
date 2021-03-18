#pragma once
#ifndef BACKEND_H
#define BACKEND_H
// INCLUDE //
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
// DEFINES //
#define ANCHOMAX 900
#define LARGOMAX 420
#define NOPARAM 0
#define OK 1
#define ERROR -1
#define DISTANCE 1.0
#define PI 3.141592
#define VACIO 0
//  STRUCT/CLASS  //
typedef int(*pCallback) (char*, char*);
typedef struct {
	double x;
	double y;
} Point;
typedef struct {
	Point abajizq;
	Point arribader;
}Rect;
typedef struct {
	int largo;
	int ancho;
	bool* tiles;
}Floor;
typedef struct {
	double x;
	double y;
	double angle;
}Blob;
// PROTOTIPOS //
int parseCmdLine(int argc, char* argv[], int(*pCallback) (char*, char*));
//separa parametros/opciones, devuelve la cantidad de opciones y parametros encontrados o un -1 en caso de error
int parseCallback(char* key, char* value);//analiza parametros/opciones
double getRectArea(Rect* r); // calcula el área del rectángulo.
bool isPointInRect(Point* p, Rect* r); //que determina si el punto p está dentro de o en el borde del rectángulo r.
double getDistanceBetweenPoints(Point*, Point*);//calculo la distancia entre 2 puntos
double getAngleBetweenPoitns(Point*, Point*);//calculo el angulo entre dos puntos
Point translatePoint(Point* p, double distance, double angle);//traslada un punto una distancia en cierto angulo
bool isPointEqual(Point* p1, Point* p2);//determina si dos puntos son iguales
Floor* createfloor(long, long);//crea el piso en el heap
void deletefloor(Floor*);//borra el piso del heap
Blob* createblob(long largo, long ancho, long robotcant);//crea robots en el heap
void deleteRobot(Blob*);//borra el robot
void movrobot(Blob* blob_p, int robotcant, long largo, long ancho, Floor*);//mueve los robots y se fija que no se salgan del piso




#endif // !_BACKEND_H
