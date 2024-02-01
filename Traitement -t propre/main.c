#include "main.h"



VilleDataP initVilleData(double villeid, char *Ville, int route_ID) {
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




double crypt(char *ville) {
    double key = 0;
    if (ville == NULL) {
        exit(2);
    }
    int j = ville[0]/2;
    for (int i = 1; i <= strlen(ville); i++) {
        key += ((i)*ville[i-1] + (i*i-1)*ville[i-1] + (i*(i-5)*ville[i-1]) + (j*ville[i-1]) + (i*j) - (j*3));
    }
    return key;
}



int main(void) {
    FILE *fichier = NULL;
    AVL *pArbre = NULL;
    AVL* caseMax = NULL;
    printf("good\n");
    fichier = fopen("data.csv", "r");
    if (fichier == NULL) {
        printf("Erreur, fichier non chargé\n");
    }
    else {
        pArbre = extractionDonnees(fichier);
        for (int i = 0; i < 10; i++) {
            caseMax = MaxPassage(pArbre);
            printf("%s;%d;%d\n", caseMax->pVilleData->ville ,caseMax->pVilleData->passage, caseMax->pVilleData->depart);
            caseMax->pVilleData->passage = 0;
        }
    }
    caseMax = NULL;
    //liberationMemoire(pArbre);
    fclose(fichier);
    return 0;
}
