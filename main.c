#include "main.h"

VilleDataP creerVilleData(char* pVille){
    VilleDataP V = NULL;
    V = malloc(sizeof(VilleData));
    V->ville = pVille;
    V->depart = 0;
    V->passage = 0;
    return V;
}


Liste* creerChainon(VilleData* pVilleData){
    Liste* chainon = NULL;
    chainon = malloc(sizeof(Liste));
    chainon->suivant = NULL;
    chainon->valeurVille = pVilleData;
    return chainon;
}

Liste* ajouterListe(VilleData* pVilleData, Liste* pListe){
    Liste* c = NULL;
    if(pListe == NULL){
        c = creerChainon(pVilleData);
    }
    else{
        c = creerChainon(pVilleData);
        c->suivant = pListe;
    }
    return c;
}


Liste* extractionDonnees(FILE* pFichier){
}





int main() {
    FILE* fichier = NULL;
    Liste* pListe = NULL;
    char chaine[TAILLE_CHAR] = "";
    fichier = fopen("data.csv", "r");
    if (fichier == NULL){
        printf("Erreur, fichier non chargé\n");
    }
    else{
        fgets(chaine, TAILLE_CHAR, fichier);
        printf("%s",chaine);
        //pListe = extractionDonnees(fichier);
    }
    fclose(fichier);
    return 0;
}
