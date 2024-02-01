#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arbreID{
    int Route_ID;
    struct arbreID* FGauche;
    struct arbreID* FDroit;
    int e;
} AVL_ID;

typedef struct {
    double key;
    int passage;
    int depart;
    char *ville;
    AVL_ID* id_passe;
} VilleData;

typedef struct arbre {
    VilleData *pVilleData;
    struct arbre *FGauche;
    struct arbre *FDroit;
    int e;
} AVL;


int max(int a, int b);

int min(int a, int b);

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

AVL *creerArbre(double key, char *ville, int cas, int route_ID);

AVL_ID *creerArbre_ID(int routeID);

AVL *insertionAVL(AVL *a, double key, char *ville, int cas, int *h, int route_ID);

AVL_ID *insertionAVL_ID(AVL_ID *a, int route_ID, int *h);

int recherche(AVL_ID* a, int route_ID);

AVL* extractionDonnees(FILE *pFichier);

void liberationRouteID(AVL_ID* pArbreID);

void liberationMemoire(AVL* pArbre);

AVL* extractionDonnees(FILE *pFichier);

AVL* MaxPassage(AVL *pArbre);

#endif //AVL_H