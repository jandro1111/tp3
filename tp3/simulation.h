#include "Blob.h"
#include "backend.h"
class simulation {
public:

	void initSim(void);
	void runSim(void);

	Blob* blob;
	Food* comida;

	//Parametros que se definen pre-simulacion
	int modo;				//Modo de juego
	int velMax;				//Velocidad Maxima, parametro de antes de empezar la simulacion
	int blobsCantIni;

	int foodShown;	 

	//Parametros que se definen post-simulacion
	int smellRadius;
	double velPorc;			//Velocidad Porcentual, parametro que varia durante la simulacion
	int randomJiggleLimit;
	int foodCount;
	double deathChance;
};