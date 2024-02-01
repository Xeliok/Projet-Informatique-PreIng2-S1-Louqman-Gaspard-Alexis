#ifndef MAIN_H
#define MAIN_H


#include "avl.h"
#define TAILLE_CHAR 150
#define MAX_LINE_LENGTH 200



typedef VilleData *VilleDataP;

VilleDataP initVilleData(double villeid, char *Ville, int route_ID);

double crypt(char* ville);

#endif //MAIN_H