#include "main.h"



VilleDataP initVilleData(float villeid, char *Ville, short route_ID) {
    VilleDataP V = NULL;
    V = malloc(sizeof(VilleData));
    V->key = villeid;
    V->depart = 0;
    V->passage = 0;
    V->ville = malloc(sizeof(char) * MAX_LINE_LENGTH);
    V->id_passe = creerArbre_ID(route_ID);
    strcpy(V->ville, Ville);
    return V;
}




float crypt(char *ville) {
    float key = 0;
    if (ville == NULL) {
        exit(2);
    }
    short j = ville[0]/2;
    for (short i = 1; i <= strlen(ville); i++) {
        key += ((i)*ville[i-1] + (i*i-1)*ville[i-1] + (i*(i-5)*ville[i-1]) + (j*ville[i-1]) + (i*j) - (j*3));
    }
    return key;
}



int main(int argc, char* argv[]) {
    FILE *fichier = NULL;
    AVL *pArbre = NULL;
    AVL* caseMax = NULL;
    char* nomFichier = argv[1];
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur, fichier non chargé\n");
    }
    else {
        pArbre = extractionDonnees(fichier);
        for (short i = 0; i < 10; i++) {
            caseMax = MaxPassage(pArbre);
            printf("%s;%d;%d\n", caseMax->pVilleData->ville ,caseMax->pVilleData->passage, caseMax->pVilleData->depart);
            caseMax->pVilleData->passage = 0;
        }
    }
    caseMax = NULL;
    liberationMemoire(pArbre);
    fclose(fichier);
    return 0;
}