#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#define TAILLE_CHAR 150
#define MAX_LINE_LENGTH 200

typedef struct {
    double key;
    int passage;
    int depart;
    char *ville;
    AVL_ID* id_passe;
} VilleData;

typedef VilleData *VilleDataP;

VilleDataP initVilleData(double villeid, char *Ville, int route_ID);

double crypt(char* ville);

#endif //MAIN_H