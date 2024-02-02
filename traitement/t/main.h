#ifndef MAIN_H
#define MAIN_H


#include "avl.h"
#define TAILLE_CHAR 85
#define MAX_LINE_LENGTH 200



typedef VilleData *VilleDataP;

VilleDataP initVilleData(float villeid, char *Ville, short route_ID);

float crypt(char* ville);

#endif //MAIN_H