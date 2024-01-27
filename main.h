#ifndef TRAITEMENT__T_MAIN_H
#define TRAITEMENT__T_MAIN_H
#include <stdio.h>
#include <stdlib.h>
#define TAILLE_CHAR 150


typedef struct{
    char* ville;
    int passage;
    int depart;
}VilleData;

typedef struct arbre{
    VilleData* pVilleData;
    struct arbre* FGauche;
    struct arbre* FDroite;
}AVL;

typedef struct liste{
    VilleData* valeurVille;
    struct liste* suivant;
}Liste;

typedef VilleData* VilleDataP;

Liste* extractionDonnees(FILE* pFichier);

#endif //TRAITEMENT__T_MAIN_H
