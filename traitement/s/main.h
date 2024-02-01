
#ifndef TEST_CLION_MAIN_H
#define TEST_CLION_MAIN_H

#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_CHAR 150
#define MAX_LINE_LENGTH 200

typedef VilleData *VilleDataP;

VilleDataP initVilleData(int routeid, float temp);

AVL *extractionDonnees(FILE *pFichier);

#endif
