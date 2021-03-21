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
    sethitbox(auxp);    //Agregue esto para que me setee la hitbox nueva
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
void Blob::sethitbox(Point Auxp) {     
    switch (tipo)
    {
    case 1:
        hitbox.abajizq.x = (Auxp.x - 20);
        hitbox.arribader.x = (Auxp.x + 20);
        hitbox.abajizq.y = (Auxp.y - 20);
        hitbox.arribader.y = (Auxp.y + 20);
        break;
    case 2:
        hitbox.abajizq.x = (Auxp.x - 22.5);
        hitbox.arribader.x = (Auxp.x + 22.5);
        hitbox.abajizq.y = (Auxp.y - 22.5);
        hitbox.arribader.y = (Auxp.y + 22.5);
        break;
    case 3:
        hitbox.abajizq.x = (Auxp.x - 40);
        hitbox.arribader.x = (Auxp.x + 40);
        hitbox.abajizq.y = (Auxp.y - 40);
        hitbox.arribader.y = (Auxp.y + 40);
        break;
    default:
        break;
    }
}
//
void Blob::blobfeed(int smellradio,Food*f) {
    bool comida = false;
    int i,aux;
    bool doonce = true;
    double distaux=-1;
    for (i = 0; i < MAXFOOD; ++i) {
        if ((f + i)->shown == true) {
            if (getDistanceBetweenPoints(&(f + i)->centro, &p) < smellradio) {//si hay comida en el smell radio
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
    }
    if (distaux == -1) {//si no encontre nada cerca del blob

    }
    else {//si encontre comida cerca del blob
        angle = getAngleBetweenPoints(&(f + aux)->centro, &p);  //cambio el angulo
    }
}

int Blob::blobCrash(Blob* blobsArray, int blobIndex) {

    bool collision = false;
    int i;
    int BlobCrashedIndex;

    for (i = 0; (i < MAXBLOB) && (collision == false); i++) { //Checkeo colisiones con otros blobs
        if (i != blobIndex) {
            if (
                (hitbox.arribader.x > (blobsArray[i]).hitbox.abajizq.x) &&
                (hitbox.abajizq.x < (blobsArray[i]).hitbox.arribader.x) &&
                (hitbox.abajizq.y < (blobsArray[i]).hitbox.arribader.y) &&
                (hitbox.arribader.y > (blobsArray[i]).hitbox.abajizq.y))
            {
                if ( (tipo == (blobsArray[i]).tipo) && (tipo != 3) ) { //La colision solo se realizara si los blobs son del mismo tipo, y si son distintos del tipo 3
                        
                    BlobCrashedIndex = i;
                    collision = true;
                }
            }
        }
    }
    if (collision == true) {   //Si hubo una colision devuelvo el indice del blob con el cual colisione

        return BlobCrashedIndex;
    }
    else {                  //En el caso contrario devuelvo -1

        return -1;
    }
}
int Blob::foodCrash(Food* f, int foodShown) {

    bool collision = false;
    int i;
    int EatenIndex;

    for (i = 0; (i < MAXFOOD) && (collision == false); i++) { //Checkeo colisiones con otros blobs
        if ( (f + i)->shown == true) {
            if (
                (hitbox.arribader.x > (f[i]).hitbox.abajizq.x) &&
                (hitbox.abajizq.x < (f[i]).hitbox.arribader.x) &&
                (hitbox.abajizq.y < (f[i]).hitbox.arribader.y) &&
                (hitbox.arribader.y > (f[i]).hitbox.abajizq.y ))
            {
                EatenIndex = i;
                collision = true;
            }
        }
    }
    if (collision == true) {   //Si hubo una colision devuelvo el indice del blob con el cual colisione

        (f[EatenIndex]).shown = false;
        return EatenIndex;
    }
    else {                  //En el caso contrario devuelvo -1

        return -1;
    }
}
void Blob::blobEats(Food* f, int foodIndex) {

    //Hago el resto de las cosas

}
void Blob::blobMerge(Blob* blobsArray, int blobIndex) {

    (blobsArray[blobIndex]).dead = 1;   //A este lo mato, y al otro lo convierto en el tipo mas grande
                                         
    tipo++;
    sethitbox(p);
    vel = ((blobsArray[blobIndex]).vel + vel) / 2; 

    //Tambien tendriamos que asignarle la nueva direccion
}