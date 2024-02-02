#include "main.h"



short max(short a, short b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

short min(short a, short b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

AVL *rotationGauche(AVL *a) {
    AVL *pivot = a->FDroit;
    a->FDroit = pivot->FGauche;
    pivot->FGauche = a;
    short eq_a = a->e;
    short eq_p = pivot->e;
    a->e = eq_a - max(eq_p, 0) - 1;
    pivot->e = min(eq_a - 2, min((eq_a + (eq_p - 2)), eq_p - 1));
    a = pivot;
    return a;
}

AVL_ID *rotationGauche_ID(AVL_ID *a) {
    AVL_ID *pivot = a->FDroit;
    a->FDroit = pivot->FGauche;
    pivot->FGauche = a;
    short eq_a = a->e;
    short eq_p = pivot->e;
    a->e = eq_a - max(eq_p, 0) - 1;
    pivot->e = min(eq_a - 2, min((eq_a + (eq_p - 2)), eq_p - 1));
    a = pivot;
    return a;
}

AVL *rotationDroite(AVL *a) {
    AVL *pivot = a->FGauche;
    a->FGauche = pivot->FDroit;
    pivot->FDroit = a;
    short eq_a = a->e;
    short eq_p = pivot->e;
    a->e = eq_a - min(eq_p, 0) + 1;
    pivot->e = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
    a = pivot;
    return a;
}

AVL_ID *rotationDroite_ID(AVL_ID *a) {
    AVL_ID *pivot = a->FGauche;
    a->FGauche = pivot->FDroit;
    pivot->FDroit = a;
    short eq_a = a->e;
    short eq_p = pivot->e;
    a->e = eq_a - min(eq_p, 0) + 1;
    pivot->e = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
    a = pivot;
    return a;
}

AVL *doubleRotationGauche(AVL *a) {
    a->FDroit = rotationDroite(a->FDroit);
    return rotationGauche(a);
}

AVL_ID *doubleRotationGauche_ID(AVL_ID *a) {
    a->FDroit = rotationDroite_ID(a->FDroit);
    return rotationGauche_ID(a);
}

AVL *doubleRotationDroite(AVL *a) {
    a->FGauche = rotationGauche(a->FGauche);
    return rotationDroite(a);
}

AVL_ID *doubleRotationDroite_ID(AVL_ID *a) {
    a->FGauche = rotationGauche_ID(a->FGauche);
    return rotationDroite_ID(a);
}

AVL *equilibrerAVL(AVL *a) {
    if (a->e >= 2) {
        if (a->FDroit->e >= 0) {
            return rotationGauche(a);
        }
        else {
            return doubleRotationGauche(a);
        }
    }
    else if (a->e <= -2) {
        if (a->FGauche->e <= 0) {
            return rotationDroite(a);
        }
        else {
            return doubleRotationDroite(a);
        }
    }
    return a;
}

AVL_ID *equilibrerAVL_ID(AVL_ID *a) {
    if (a->e >= 2) {
        if (a->FDroit->e >= 0) {
            return rotationGauche_ID(a);
        }
        else {
            return doubleRotationGauche_ID(a);
        }
    }
    else if (a->e <= -2) {
        if (a->FGauche->e <= 0) {
            return rotationDroite_ID(a);
        }
        else {
            return doubleRotationDroite_ID(a);
        }
    }
    return a;
}

AVL *creerArbre(float key, char *ville, short cas, short route_ID) {
    AVL *a = NULL;
    a = malloc(sizeof(AVL));
    VilleDataP v = initVilleData(key, ville, route_ID);
    a->pVilleData = v;
    a->e = 0;
    a->FGauche = NULL;
    a->FDroit = NULL;
    if (cas) {
        a->pVilleData->depart = 1;
        a->pVilleData->passage = 1;
    }
    else {
        a->pVilleData->passage = 1;
        a->pVilleData->depart = 0;
    }
    return a;
}

AVL_ID *creerArbre_ID(short routeID) {
    AVL_ID *a = NULL;
    a = malloc(sizeof(AVL_ID));
    a->Route_ID = routeID;
    a->e = 0;
    a->FGauche = NULL;
    a->FDroit = NULL;
    return a;
}

AVL_ID *insertionAVL_ID(AVL_ID *a, short route_ID, short *h) {
    if (a == NULL) {
        *h = 1;
        return creerArbre_ID(route_ID);
    }
    else if (route_ID < a->Route_ID) {
        a->FGauche = insertionAVL_ID(a->FGauche, route_ID, h);
        *h = -*h;
    }
    else if (route_ID > a->Route_ID) {
        a->FDroit = insertionAVL_ID(a->FDroit, route_ID, h);
    }
    else {
        *h = 0;
        return a;
    }
    if (*h != 0) {
        a->e = a->e + *h;
        a = equilibrerAVL_ID(a);
        if (a->e == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}

short recherche(AVL_ID* a, short route_ID) {
    if (a == NULL) {
        return 0; // La valeur n'est pas présente dans l'arbre
    }
    if (route_ID < a->Route_ID) {
        return recherche(a->FGauche, route_ID);
    }
    else if (route_ID > a->Route_ID) {
        return recherche(a->FDroit, route_ID);
    }
    else {
        return 1;
    }
}

AVL *insertionAVL(AVL *a, float key, char *ville, short cas, short *h, short route_ID, int* j) {
    if (a == NULL) {
        *h = 1;
        return creerArbre(key, ville, cas, route_ID);
    }
    else if (key < a->pVilleData->key) {
        a->FGauche = insertionAVL(a->FGauche, key, ville, cas, h, route_ID, j);
        *h = -*h;
    }
    else if (key > a->pVilleData->key) {
        a->FDroit = insertionAVL(a->FDroit, key, ville, cas, h, route_ID, j);
    }
    else {
        *h = 0;
        if(key == a->pVilleData->key && strcmp(ville,a->pVilleData->ville) != 0){
            key += 0.5;
            a = insertionAVL(a, key, ville, cas, h, route_ID, j);
        }
        else{
            if(!recherche(a->pVilleData->id_passe, route_ID)){
                if (cas) {
                    a->pVilleData->id_passe = insertionAVL_ID(a->pVilleData->id_passe, route_ID, j);
                    a->pVilleData->depart++;
                    a->pVilleData->passage++;
                }
                else {
                    a->pVilleData->id_passe = insertionAVL_ID(a->pVilleData->id_passe, route_ID, j);
                    a->pVilleData->passage++;
                }
                return a;
            }
            else if(recherche(a->pVilleData->id_passe, route_ID) && cas){
                a->pVilleData->id_passe = insertionAVL_ID(a->pVilleData->id_passe, route_ID, j);
                a->pVilleData->depart++;
                return a;
            }
        }
    }
    if (*h != 0) {
        a->e = a->e + *h;
        a = equilibrerAVL(a);
        if (a->e == 0) {
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}

void liberationRouteID(AVL_ID* pArbreID){
    if(pArbreID != NULL){
        liberationRouteID(pArbreID->FGauche);
        liberationRouteID(pArbreID->FDroit);
        free(pArbreID);
    }
}

void liberationMemoire(AVL* pArbre){
    if(pArbre != NULL){
        liberationMemoire(pArbre->FDroit);
        liberationMemoire(pArbre->FGauche);
        free(pArbre->pVilleData->ville);
        liberationRouteID(pArbre->pVilleData->id_passe);
        free(pArbre->pVilleData);
        free(pArbre);
    }
}

AVL *extractionDonnees(FILE *pFichier) {
    AVL *pArbre = NULL;
    char *line;
    char *Step_id;
    char* route_id;
    short num_route;
    short numID;
    short *h = malloc(sizeof(short *));
    short *j = malloc(sizeof(short *));
    float key;
    char *townA = malloc(sizeof(char) * MAX_LINE_LENGTH);
    char *townB = malloc(sizeof(char) * MAX_LINE_LENGTH);
    char *token;
    line = malloc(sizeof(char) * MAX_LINE_LENGTH);
    line = fgets(line, MAX_LINE_LENGTH, pFichier);
    line = fgets(line, MAX_LINE_LENGTH, pFichier);
    while (line != NULL) {
        route_id = strtok(line, ";");
        Step_id = strtok(NULL, ";");
        numID = atoi(Step_id);
        num_route = atoi(route_id);
        if (numID == 1) {
            token = strtok(NULL, ";");
            strcpy(townA, token);
            key = crypt(townA);
            pArbre = insertionAVL(pArbre, key, townA, 1, h, num_route, j);
            token = strtok(NULL, ";");
            strcpy(townB, token);
            key = crypt(townB);
            pArbre = insertionAVL(pArbre, key, townB, 0, h, num_route, j);
        }
        else {
            strtok(NULL, ";");
            token = strtok(NULL, ";");
            strcpy(townB, token);
            key = crypt(townB);
            pArbre = insertionAVL(pArbre, key, townB, 0, h, num_route, j);
        }
        line = fgets(line, MAX_LINE_LENGTH, pFichier);
    }
    return pArbre;
}

AVL* MaxPassage(AVL *pArbre) {
    if (pArbre == NULL) {
        return NULL;
    }
    AVL* maxDroit = MaxPassage(pArbre->FDroit);
    AVL* maxGauche = MaxPassage(pArbre->FGauche);
    AVL* maxSousArbre = pArbre;
    if (maxGauche && maxGauche->pVilleData->passage > maxSousArbre->pVilleData->passage){
        maxSousArbre = maxGauche;
    }
    if (maxDroit && maxDroit->pVilleData->passage > maxSousArbre->pVilleData->passage){
        maxSousArbre = maxDroit;
    }
    return maxSousArbre;
}
