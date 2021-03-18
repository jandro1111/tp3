// INCLUDES //
#include"backend.h"
// FUNCTIONS //
int parseCmdLine(int argc, char* argv[], int(*pCallback) (char*, char*)) {//cant de opciones +params o -1 en error
    int i = 1;//la primer palabra,con indice 0, es el nombre del programa, y esta no se cuenta
    int datos = 0;//params+opciones
    for (i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {//si hay opcion
            if (i != (argc - 1)) {//si no es el ultimo elemento que recibe
                if (argv[i][1] == NULL) {//si es una clave sin valor
                    return ERROR;
                }
                else {
                    if (pCallback(argv[i], argv[i + 1]) == 1) {//si esta todo bien..
                        ++datos;
                        ++i;//salteo el valor de la clave
                    }
                    else {//parsecallback tiro error
                        return ERROR;
                    }
                }
            }
            else {
                return ERROR;
            }
        }
        else {//encontre un parametro
            if (pCallback(NULL, argv[i]) == 1) {//si esta todo bien
                ++datos;
            }
            else {//parsecallback tiro error
                return ERROR;
            }
        }
    }
    return datos;
}
////////////////////////////////////////////////////////////
int parseCallback(char* key, char* value) {//0 si no es valido 1 si si

    if ((key == NULL)) {//es un parametro
        return OK;
    }
    else {//es una opcion
        return NOPARAM;//voy a hacer que no acepte opciones
        /*if (key[1] == NULL) {//clave vacia devuelve error
            return NOPARAM;
        }
        else {
            if (value == NULL) {//si el valor es null es una clave sin valor y devuelve error
                return NOPARAM;
            }
            else {
                return OK;
            }
        }
         */
    }
}
/// ////////////////////////////////////////////////////////////////////////////////////
double getDistanceBetweenPoints(Point* p1, Point* p2) {//calcula distancia entre dos puntos
    return (sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y)));
}
//////////////////////////////////////////////////////////////////////////
double getAngleBetweenPoitns(Point* p1, Point* p2) {//calcula el angulo entre dos puntos
    return(atan(getDistanceBetweenPoints(p1, p2)));
}
//////////////////////////////////////////////////////////////////////////
Point translatePoint(Point* p, double distance, double angle) {//traslada un punto una distancia en cierto angulo
    Point pmov;//math.h usa radianes
    pmov.x = ((p->x) + cos(angle));//(cos(angle)<0?-cos(angle): cos(angle))
    pmov.y = ((p->y) + sin(angle));//(sin(angle)<0?-sin(angle): sin(angle))
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
double getRectArea(Rect* r) { // calcula el �rea del rect�ngulo.
    double area;
    double base, altura;
    base = (r->abajizq.x + r->arribader.x);
    altura = (r->abajizq.y + r->arribader.y);
    area = base * altura;
    return area;

}
/////////////////////////////////////////////////////////////////////////
bool isPointInRect(Point* p, Rect* r) { //que determina si el punto p est� dentro de o en el borde del rect�ngulo r.
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Floor* createfloor(long largo, long ancho) {//crea el piso
    int i, j;
    Floor* piso = (Floor*)malloc(sizeof(Floor));
    if (piso != NULL) {
        piso->ancho = ancho;
        piso->largo = largo;
        piso->tiles = (bool*)malloc(sizeof(bool) * largo * ancho);
        if ((piso->tiles) != NULL) {
            for (i = 0; i < largo; ++i) {
                for (j = 0; j < ancho; ++j) {
                    *((piso->tiles) + j + i * ancho) = VACIO;
                }
            }
        }
    }
    else {
        free(piso);
        piso = NULL;
    }
    return piso;
}
/// ////////////////////////////////////////////////////////////
void deletefloor(Floor* f) {//borra el piso
    if (f) {
        if (f->tiles != NULL) {
            free(f->tiles);
        }
        free(f);
    }
    return;
}
////////////////////////////////////////////////////////////////
Blob* createblob(long largo, long ancho, long blobcant) {
    int i = 0;
    Blob* blob = (Blob*)malloc(sizeof(Blob) * blobcant);
    if (blob != NULL) {
        for (i = 0; i < blobcant; i++)
        {
            (blob + i)->x = (rand() % ancho + 0);
            (blob + i)->y = (rand() % largo + 0);
            (blob + i)->angle = (rand() % 360 + 0);//ahora lo paso a radianes pq math.h usa radianes
            (blob + i)->angle = (blob->angle * 2 * PI / 360);
        }

    }
    else {
        free(blob);
        blob = NULL;
    }
    return blob;
}
////////////////////////////////////////////////////////////////
void deleteRobot(Blob* b) {//borra los robots
    if (b) {
        free(b);
    }
    return;
}
/////////////////////////////////////////////////////////////////
void movrobot(Blob* blob_p, int b, long largo, long ancho, Floor* f) {
    Point aux;
    aux.x = (blob_p + b)->x;
    aux.y = (blob_p + b)->y;
    aux = translatePoint(&aux, DISTANCE, (blob_p + b)->angle);
    if ((aux.x < 0) || (aux.y < 0) || (aux.x > ancho) || (aux.y > largo)) {//si se sale del piso, randomizo direccion y el proximo turno lo hago avanzar
        (blob_p + b)->angle = (rand() % 360 + 0);//ahora lo paso a radianes pq math.h usa radianes
        (blob_p + b)->angle = ((blob_p + b)->angle * 2 * PI / 360);
    }
    else {
        (blob_p + b)->x = aux.x;
        (blob_p + b)->y = aux.y;
    }
    
    //el casteo de double a int redondea hacia abajo si es positivo y hacia arriba si es negativo
}