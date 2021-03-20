////////////////////////////////////////////////
#include "Blob.h"

////////////////////////////////////////////////

Blob::Blob(int type,int modo,double velpor,int velmaxi) {
    p.x = (rand() % ANCHOMAX + 0);
    p.y = (rand() % LARGOMAX + 0);
    hitbox.abajizq.x = (p.x - 20);
    hitbox.arribader.x = (p.x + 20);
    hitbox.abajizq.y = (p.y - 20);
    hitbox.arribader.y = (p.y + 20);
    food = 0;
    angle = ((rand() % 360 + 0) * 2.0 * PI / 360.0);//ahora lo paso a radianes pq math.h usa radianes
    tipo = type;
    dead = false;
    if (modo == 1) {//
        vel = (velpor * velmaxi);
        velmax = velmaxi;
    }
    else {//modo 2
        velmax=(rand() % velmaxi + 1);
        vel = velmax * velpor;
    }
}
//
Blob::~Blob() {

}
//
bool Blob::getdead() {
    return dead;
}
//
int Blob::setfood(int f) {
    bool crece = false;
    food += f;
    switch (tipo) {
    case 1:
        if (food == 5) {
            crece = true;
        }
        break;
    case 2:
        if (food == 4) {
            crece = true;
        }
        break;
    case 3:
        if (food == 3) {
            crece = true;
        }
        break;
    default:
        break;
    }
    return crece;
}
//
double Blob::getposx() {
    return p.x;
}
//
double Blob::getposy() {
return p.y;
}
//
void Blob::setangle(bool comida) {
    if (comida == true) {//si hay comida cambio la direccion

    }   
}
///////
double Blob::getangle() {
    return angle;
}
///
void Blob::setpos(Point aux) {
    p = aux;
}
/// 
void Blob::moveblob(void) {
    Point auxp;
    double auxa;            //de que sirve esta?
    auxp.x = getposx();
    auxp.y = getposy();
    auxp = translatePoint(&auxp, vel , getangle() );

    //Me encargo de acomodar las posiciones para el caso de que se hayan ido de la pantalla
    if (auxp.x < 0) {//si no puedo ir mas a la izq salgo por la der
        auxp.x = -auxp.x;
        auxp.x += (ANCHOMAX - 1);
    }
    if (auxp.y < 0) {//si tengo que bajar y no puedo salgo por arriba
        auxp.y = -auxp.y;
        auxp.y += (LARGOMAX - 1);
    }      
    if (auxp.y > LARGOMAX) {//si tengo que subir y no puedo salgo por abajo
        auxp.y -= LARGOMAX;
    }
    if (auxp.x > ANCHOMAX) {//si no puedo ir mas a la der salgo ppor la izq
        auxp.x -= ANCHOMAX;
    }
    setpos(auxp);
    sethitbox();
}
//
void Blob::blobdeath(double prob) {
    double aux;
    aux = (double)(rand()) / ((double)(RAND_MAX / (1)));
    if (aux<prob||dead==true) {//se muere el blob
        dead = true;

    }
    else {//vive el blob
        dead = false;
    }
}
//
void Blob::setvel(double velpor) {
    vel = velmax * velpor;
}
//
void Blob::kill() {
    dead = true;
}
//
void Blob::sethitbox() {
    switch (tipo)
    {
    case 1:
        hitbox.abajizq.x = (p.x - 20);
        hitbox.arribader.x = (p.x + 20);
        hitbox.abajizq.y = (p.y - 20);
        hitbox.arribader.y = (p.y + 20);
        break;
    case 2:
        hitbox.abajizq.x = (p.x - 22.5);
        hitbox.arribader.x = (p.x + 22.5);
        hitbox.abajizq.y = (p.y - 22.5);
        hitbox.arribader.y = (p.y + 22.5);
        break;
    case 3:
        hitbox.abajizq.x = (p.x - 40);
        hitbox.arribader.x = (p.x + 40);
        hitbox.abajizq.y = (p.y - 40);
        hitbox.arribader.y = (p.y + 40);
        break;
    default:
        break;
    }
}
//
void Blob::blobfeed(int smellradio,int foodshown,Food*f) {
    bool comida = false;
    int i,aux;
    bool doonce = true;
    double distaux=-1;
    for (i = 0; i < foodshown; ++i) {
        if (getDistanceBetweenPoints(&(f+i)->centro,&p) < smellradio) {//si hay comida en el smell radio
            if (doonce == true) {
                distaux = getDistanceBetweenPoints(&(f + i)->centro, &p);
                aux = i;
                doonce = false;
            }
            if (getDistanceBetweenPoints(&(f + i)->centro, &p) < distaux) {//si encontre una comida mas cercana
                distaux = getDistanceBetweenPoints(&(f + i)->centro, &p);
                aux = i;
            }
        }
    }
    if (distaux == -1) {//si no encontre nada cerca del blob

    }
    else {//si encontre comida cerca del blob
        angle = getAngleBetweenPoitns(&(f + aux)->centro, &p);  //cambio el angulo
    }

}