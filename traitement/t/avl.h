#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arbreID{
    short Route_ID;
    struct arbreID* FGauche;
    struct arbreID* FDroit;
    short e;
} AVL_ID;

typedef struct {
    float key;
    short passage;
    short depart;
    char *ville;
    AVL_ID* id_passe;
} VilleData;

typedef struct arbre {
    VilleData *pVilleData;
    struct arbre *FGauche;
    struct arbre *FDroit;
    short e;
} AVL;


short max(short a, short b);

short min(short a, short b);

AVL *rotationGauche(AVL *a);

AVL_ID *rotationGauche_ID(AVL_ID *a);

AVL *rotationDroite(AVL *a);

AVL_ID *rotationDroite_ID(AVL_ID *a);

AVL *doubleRotationGauche(AVL *a);

AVL_ID *doubleRotationGauche_ID(AVL_ID *a);

AVL *doubleRotationDroite(AVL *a);

AVL_ID *doubleRotationDroite_ID(AVL_ID *a);

AVL *equilibrerAVL(AVL *a);

AVL_ID *equilibrerAVL_ID(AVL_ID *a);

AVL *creerArbre(float key, char *ville, short cas, short route_ID);

AVL_ID *creerArbre_ID(short routeID);

AVL *insertionAVL(AVL *a, float key, char *ville, short cas, short *h, short route_ID);

AVL_ID *insertionAVL_ID(AVL_ID *a, short route_ID, short *h);

short recherche(AVL_ID* a, short route_ID);

AVL* extractionDonnees(FILE *pFichier);

void liberationRouteID(AVL_ID* pArbreID);

void liberationMemoire(AVL* pArbre);

AVL* extractionDonnees(FILE *pFichier);

AVL* MaxPassage(AVL *pArbre);

#endif //AVL_H