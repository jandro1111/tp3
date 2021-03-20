﻿// INCLUDES //
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
double getAngleBetweenPoints(Point* C, Point* B) {//calcula el angulo entre dos puntos

//   return(acos((p1->x*p2->x+p1->y*p2->y)/(sqrt((p2->x + p1->x) * (p2->x + p1->x) + (p2->y + p1->y) * (p2->y + p1->y)))));
//
//    double Ay = C->y + 10 * sin(angulo);
//    double Ax = C->x + 10 * cos(angulo);
//
//    // The atan2 functions return arctan y/x in the interval [−pi , +pi] radians
//    double Dir_C_to_A = atan2(Ay - C->y, Ax - C->x);
//    double Dir_C_to_B = atan2(B->y - C->y, B->x - C->x);
//    double Angle_ACB = Dir_C_to_A - Dir_C_to_B;
//
//    // Handle wrap around
//    /*if (Angle_ACB > PI) Angle_ACB -= 2*PI;
//    else if (Angle_ACB < -PI) Angle_ACB += 2*PI;*/
//    if (Angle_ACB < 0) {
//        Angle_ACB = -Angle_ACB;
//    }
//    // Answer is in the range of [-pi...pi]
//    return Angle_ACB;

    double angulo = (atan2(MOD(B->y - C->y), MOD(B->x - C->x)));

    if (B->y <= C->y && B->x >= C->x ) {            //1er cuadrante

        //En este caso el angulo es el correcto
    }
    else if (B->y <= C->y && B->x <= C->x) {        //2do cuadrante

        angulo = angulo + PI / 2;
    }
    else if (B->y >= C->y && B->x <= C->x) {        //3er cuadrante

        angulo = angulo + PI;
    }
    else if (B->y >= C->y && B->x >= C->x) {        //4to cuadrante

        angulo = angulo + 3 * PI / 2;
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
        if ((rand() % 100 + 1) <= 40) {//prob del 40% de generar una comida
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