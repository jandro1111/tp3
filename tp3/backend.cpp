// INCLUDES //
#include "backend.h"
#include "simulation.h"

// FUNCTIONS //

int parseCmdLine(int argc, char* argv[], pCallback p, void* userData) {

    int salida;
    int error = 0;
    int conteo = 0;
    int i = 1;

    while (i < argc && error == 0) {

        if (argv[i][0] == '-') {

            if ((i + 1) >= argc) {

                error = 1; //En este caso estarias poniendo una clave sin valor
            }
            else {

                if (p(argv[i], argv[i + 1], userData) == 0) {

                    error = 1;
                }
                else {
                    i++;
                    conteo++;
                }
            }
        }
        else {

            if (p(NULL, argv[i], userData) == 0) {

                error = 1;
            }
            else {

                ++conteo;
            }
        }

        i++;
    }

    if (error == 0) {

        salida = conteo;
    }
    else {

        salida = -1;
    }

    return salida;
}
//////////////////////////////////////////////////////////////////////////////////////

int parseCallback(char* key, char* value, void* userData) {

    int esCorrecto = 1;

    simulation* Simu = (simulation*)userData;

    if (key == NULL) {

        std::cout << "No se esperan parametros" << endl;
        esCorrecto = 0; 
    }
    else {
        if (!strcmp(key, "-modo")) {

            if (!strcmp(value, "1")) {

                Simu->modo = 1;
            }
            else if (!strcmp(value, "2")) {

                Simu->modo = 2;
            }
            else {
                printf("Error en el ingreso del modo\n");
                esCorrecto = 0;
            }
        }
        else if (!strcmp(key, "-blobscantini")) {

            if (atoi(value) > 0 && atoi(value) < MAXBLOB) {

                Simu->blobsCantIni = atoi(value);
            }
            else {
                printf("Error en el ingreso de la cantidad inicial de blobs\n");
                esCorrecto = 0;
            }
        }
        else if (!strcmp(key, "-velmax")) {

            if (atoi(value) > 0 && atoi(value) < MAXSPEEDPOSIBLE) {

                Simu->velMax = atoi(value);
            }
            else {

                printf("Error en el ingreso de la velocidadmaxima\n");
                esCorrecto = 0;
            }
        }
        else {

            printf("La opcion %s ingresada no es valida\n", key);
            esCorrecto = 0;
        }
    }

    return esCorrecto;
}

/// ////////////////////////////////////////////////////////////////////////////////////
double getDistanceBetweenPoints(Point* p1, Point* p2) {//calcula distancia entre dos puntos
    return (sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y)));
}
//////////////////////////////////////////////////////////////////////////
double getAngleBetweenPoints(Point* C, Point* B) {  //calcula el angulo entre dos puntos

    double angulo = (atan2(MOD(B->y - C->y), MOD(B->x - C->x)));

    if (B->y >= C->y && B->x <= C->x ) {            //1er cuadrante

        angulo = angulo + 3 * PI / 2;
    }
    else if (B->y >= C->y && B->x >= C->x) {        //2do cuadrante

        angulo = angulo + PI;
    }
    else if (B->y <= C->y && B->x >= C->x) {        //3er cuadrante

        angulo = angulo + PI / 2;
    }
    else if (B->y <= C->y && B->x <= C->x) {        //4to cuadrante

        //En este caso el angulo es el correcto        
    }

    return angulo;
}
//////////////////////////////////////////////////////////////////////////
Point translatePoint(Point* p, double distance, double angle) {//traslada un punto una distancia en cierto angulo
    Point pmov;//math.h usa radianes
    pmov.x = ( (p->x) + distance*cos(angle));//(cos(angle)<0?-cos(angle): cos(angle))
    pmov.y = ( (p->y) + distance*sin(angle));//(sin(angle)<0?-sin(angle): sin(angle))
    return pmov;
}
//////////////////////////////////////////////////////////////////////////
bool isPointEqual(Point* p1, Point* p2) {//determina si dos puntos son iguales
    bool p;
    double e = 0.0001;
    if (getDistanceBetweenPoints(p1, p2) > e) {//no son coincidentes
        p = false;
    }
    else {
        p = true;
    }
    return p;
}
//////////////////////////////////////////////////////////////////////////
double getRectArea(Rect* r) { // calcula el área del rectángulo.
    double area;
    double base, altura;
    base = (r->abajizq.x + r->arribader.x);
    altura = (r->abajizq.y + r->arribader.y);
    area = base * altura;
    return area;

}
/////////////////////////////////////////////////////////////////////////
bool isPointInRect(Point* p, Rect* r) { //que determina si el punto p está dentro de o en el borde del rectángulo r.
    bool a;
    if ((p->x) < (r->abajizq.x)) {//si esta mas izq que el punto mas izq esta fuera del rectangulo
        a = false;
    }
    else {
        a = true;
    }
    if ((p->y) < (r->abajizq.y)) {//si esta mas a la abajo que el punto mas abajo esta fuera del rectangulo
        a = false;
    }
    else {
        a = true;
    }
    if ((p->x) > (r->arribader.x)) {//si esta mas derecha que el punto mas derecha esta fuera del rectangulo
        a = false;
    }
    else {
        a = true;
    }
    if ((p->y) > (r->arribader.y)) {//si esta mas a la arriba que el punto mas arriba esta fuera del rectangulo
        a = false;
    }
    else {
        a = true;
    }
    return a;
}
//////////////////////////////////////////////////////////////////////////////////////
int foodspawn(int foodmax, Food* f,int foodshown) {
    int i;
    if (foodshown < foodmax) {//si puedo seguir generando comida
        if ((rand() % 100 + 1) <= FOODPORC) {//prob del 40% de generar una comida
            for (i = 0; i < MAXFOOD; ++i) {
                if ((f + i)->shown == false) {
                    (f + i)->shown = true;//empizo sin mostrar ninguna comida
                    (f + i)->centro.x = (rand() % ANCHOMAX + 0);
                    (f + i)->centro.y = (rand() % LARGOMAX + 0);
                    (f + i)->hitbox.abajizq.x = ((f + i)->centro.x - 10);
                    (f + i)->hitbox.arribader.x = ((f + i)->centro.x + 10);
                    (f + i)->hitbox.abajizq.y = ((f + i)->centro.y - 10);
                    (f + i)->hitbox.arribader.y = ((f + i)->centro.y + 10);
                    ++foodshown;
                    cout << "x"<<(f + i)->centro.x<<"y: " << (f + i)->centro.x << endl;
                    break;
                }
            }
        }
    }
    return foodshown;
}