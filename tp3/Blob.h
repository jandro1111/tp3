#pragma once
#ifndef BLOB_H
#define BLOB_H
#include"backend.h"
class Blob
{
public:
	Blob(Point,double,int,int,int);
	~Blob();
protected:

private:
	Point p;
	double angle;
	int food;
	int death;
	int tipo;//1 es chico 2 es medio y 3 es grande
};

#endif