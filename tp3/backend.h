#pragma once
#ifndef BACKEND_H
#define BACKEND_H
// INCLUDE //
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <iomanip>
#include <random>
#include <iostream>
#include <vector>
// DEFINES //
using namespace std;
#define ANCHOMAX 900
#define LARGOMAX 420
#define NOPARAM 0
#define OK 1
#define ERROR1 -1
#define DISTANCE 1.0
#define PI 3.141592
#define VACIO 0
#define MAXBLOB 100
#define MAXFOOD 100
#define MAXSPEEDPOSIBLE 500
#define BLOB1_SIZE 40
#define BLOB2_SIZE 45
#define BLOB3_SIZE 80
#define FOOD_SIZE 20
#define UNMERGEABLETICKS 50

#define MOD(x) ( ( (x)>=0 ) ? (x) : (-(x)) )

//  STRUCT/CLASS  //
typedef int(*pCallback) (char*, char*, void* userData);

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	Point abajizq;
	Point arribader;
}Rect;

typedef struct {
	Point centro;
	Rect hitbox;// 20x20
	bool shown;
}Food;
// PROTOTIPOS //
int parseCmdLine(int argc, char* argv[], pCallback p, void* userData);
//separa parametros/opciones, devuelve la cantidad de opciones y parametros encontrados o un -1 en caso de error
int parseCallback(char* key, char* value, void* userData);//analiza parametros/opciones
double getRectArea(Rect* r); // calcula el área del rectángulo.
bool isPointInRect(Point* p, Rect* r); //que determina si el punto p está dentro de o en el borde del rectángulo r.
double getDistanceBetweenPoints(Point*, Point*);//calculo la distancia entre 2 puntos
double getAngleBetweenPoints(Point*, Point*);//calculo el angulo entre dos puntos
Point translatePoint(Point* p, double distance, double angle);//traslada un punto una distancia en cierto angulo
bool isPointEqual(Point* p1, Point* p2);//determina si dos puntos son iguales
int foodspawn(int,Food*,int);//decide si se genera uno de comida

#endif // !_BACKEND_H