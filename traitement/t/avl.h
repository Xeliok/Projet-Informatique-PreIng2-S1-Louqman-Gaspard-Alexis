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
} AVL_ID; //Structure qui stocke la liste des trajets pour lesquels une itération de la ville a déjà été enregistrée (toutes les fonctions dont les noms sont identique à celles de la structure AVL avec ID à la fin font la même chose pour cette structure)

typedef struct {
    float key;
    short passage;
    short depart;
    char *ville;
    AVL_ID* id_passe;
} VilleData; //Structure qui stocke toutes les informations propre a chaque ville (la présence de key nous permet de baser notre AVL sur une clé numérique propre a chaque ville)

typedef struct arbre {
    VilleData *pVilleData;
    struct arbre *FGauche;
    struct arbre *FDroit;
    short e;
} AVL; //Structure qui stocke les informations sur chaque ville (la valeur utilisée pour déterminer le positionement dans l'AVL est key de VilleData)


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

AVL *insertionAVL(AVL *a, float key, char *ville, short cas, short *h, short route_ID, short* j);

AVL_ID *insertionAVL_ID(AVL_ID *a, short route_ID, short *h);

short recherche(AVL_ID* a, short route_ID);

AVL* extractionDonnees(FILE *pFichier);

void liberationRouteID(AVL_ID* pArbreID);

void liberationMemoire(AVL* pArbre);

AVL* extractionDonnees(FILE *pFichier);

AVL* MaxPassage(AVL *pArbre);

#endif //AVL_H
