#include "main.h"

VilleDataP initVilleData(int routeid, float temp) {
  VilleDataP V = NULL;
  V = malloc(sizeof(VilleData));
  V->route_id = routeid;
  V->dist_min = temp;
  V->dist_max = temp;
  V->somme = temp;
  V->total_stepid = 1;
  V->moyenne = 0;
  V->maxmin = 0;
  return V;
}

AVL *extractionDonnees(FILE *pFichier) {
  AVL *pArbre = NULL;
  char *line;
  char *Step_id;
  int *h = malloc(sizeof(int *));
  int routeid;
  float temp;
  char *token;

  line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  line = fgets(line, MAX_LINE_LENGTH, pFichier);
  line = fgets(line, MAX_LINE_LENGTH, pFichier);

  while (line != NULL) {
    routeid = atoi(strtok(line, ";"));

    token = strtok(NULL, ";");
    temp = atof(token);
    pArbre = insertionAVL(pArbre, routeid, temp, h);

    line = fgets(line, MAX_LINE_LENGTH, pFichier);
  }
  free(h);
  return pArbre;
}

AVL *maxmin(AVL *pArbre) {
  if (pArbre == NULL) {
    return NULL;
  }
  AVL *maxDroit = maxmin(pArbre->FDroit);
  AVL *maxGauche = maxmin(pArbre->FGauche);
  AVL *maxSousArbre = pArbre;
  if (maxGauche &&
      maxGauche->pVilleData->maxmin > maxSousArbre->pVilleData->maxmin) {
    maxSousArbre = maxGauche;
  }
  if (maxDroit &&
      maxDroit->pVilleData->maxmin > maxSousArbre->pVilleData->maxmin) {
    maxSousArbre = maxDroit;
  }
  return maxSousArbre;
}

int main(void) {
  FILE *fichier = NULL;
  AVL *pArbre = NULL;
  AVL *valeur;
  fichier = fopen("data_s.csv", "r");
  if (fichier == NULL) {
    printf("Erreur, fichier non chargé\n");
  } else {
    pArbre = extractionDonnees(fichier);
    for (int i = 1; i <= 50; i++) {
      valeur = maxmin(pArbre);
      printf("%d;%d;%.3f;%.3f;%.3f;%.3f\n", i, valeur->pVilleData->route_id,
             valeur->pVilleData->dist_min, valeur->pVilleData->moyenne,
             valeur->pVilleData->dist_max, valeur->pVilleData->maxmin);
      valeur->pVilleData->maxmin = 0;
    }
  }
  liberationMemoire(pArbre);
  fclose(fichier);

  return 0;
}
