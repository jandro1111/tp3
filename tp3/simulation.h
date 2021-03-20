#include "Blob.h"

class simulation {
public:
	Blob* Blobs;

	//Parametros que se definen pre-simulacion
	int modo;				//Modo de juego
	int velMax;				//Velocidad Maxima, parametro de antes de empezar la simulacion
	int blobsCantIni;

	//Parametros que se definen post-simulacion
	int smellRadius;
	double velPorc;			//Velocidad Porcentual, parametro que varia durante la simulacion
	int randomJiggleLimit;
	int foodCount;
	double deadChance;
};