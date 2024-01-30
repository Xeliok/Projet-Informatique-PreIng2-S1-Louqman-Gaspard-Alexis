#include "main.h"

int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

void afficherFile(File *file) {
  for (int i = 0; i < file->size; i++) {
    printf("%d;", file->element[i]->route_id);
    printf("%.2f;", file->element[i]->dist_min);
    printf("%.2f;", file->element[i]->dist_max);
    printf("%.2f;", file->element[i]->moyenne);
    printf("%.2f\n", file->element[i]->maxmin);
  }
}

File *creerQueue(int capacity) {
  File *a = NULL;
  a = malloc(sizeof(File));
  a->element = NULL;
  a->front = -1;
  a->rear = -1;
  a->size = 0;
  a->capacity = capacity;
  return a;
}

void enqueue(File *queue, VilleData *value) {
  if (queue->size == queue->capacity) {
    // La file est pleine, libérer l'élément le plus ancien
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
  }

  if (queue->front == -1) {
    // La file est vide, initialiser les indices
    queue->front = 0;
    queue->rear = 0;
  } else {
    // Déplacer le pointeur de la fin vers l'élément suivant
    queue->rear = (queue->rear + 1) % queue->capacity;
  }

  // Ajouter l'élément à la file
  queue->element[queue->rear] = value;
  queue->size++;
}

AVL *rotationGauche(AVL *a) {
  AVL *pivot = a->FDroit;
  a->FDroit = pivot->FGauche;
  pivot->FGauche = a;
  int eq_a = a->e;
  int eq_p = pivot->e;
  a->e = eq_a - max(eq_p, 0) - 1;
  pivot->e = min(eq_a - 2, min((eq_a + (eq_p - 2)), eq_p - 1));
  a = pivot;
  return a;
}

AVL *rotationDroite(AVL *a) {
  AVL *pivot = a->FGauche;
  a->FGauche = pivot->FDroit;
  pivot->FDroit = a;
  int eq_a = a->e;
  int eq_p = pivot->e;
  a->e = eq_a - min(eq_p, 0) + 1;
  pivot->e = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
  a = pivot;
  return a;
}

AVL *doubleRotationGauche(AVL *a) {
  a->FDroit = rotationDroite(a->FDroit);
  return rotationGauche(a);
}

AVL *doubleRotationDroite(AVL *a) {
  a->FGauche = rotationGauche(a->FGauche);
  return rotationDroite(a);
}

AVL *equilibrerAVL(AVL *a) {
  if (a->e >= 2) {
    if (a->FDroit->e >= 0) {
      return rotationGauche(a);
    } else {
      return doubleRotationGauche(a);
    }
  } else if (a->e <= -2) {
    if (a->FGauche->e <= 0) {
      return rotationDroite(a);
    } else {
      return doubleRotationDroite(a);
    }
  }
  return a;
}

AVL *creerArbre(int routeid, float temp) {
  AVL *a = NULL;
  a = malloc(sizeof(AVL));
  VilleDataP v = initVilleData(routeid, temp);
  a->pVilleData = v;
  a->e = 0;
  a->FGauche = NULL;
  a->FDroit = NULL;
  return a;
}

AVL *comparaison(AVL *a, int routeid, float temp) {
  if (temp < a->pVilleData->dist_min) {
    a->pVilleData->dist_min = temp;
  }
  if (temp > a->pVilleData->dist_max) {
    a->pVilleData->dist_max = temp;
  }
  a->pVilleData->somme = a->pVilleData->somme + temp;
  a->pVilleData->total_stepid++;
  a->pVilleData->moyenne =
      (a->pVilleData->somme) / (a->pVilleData->total_stepid);
  a->pVilleData->maxmin = (a->pVilleData->dist_max) - (a->pVilleData->dist_min);
  return a;
}

AVL *insertionAVL(AVL *a, int routeid, float temp, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerArbre(routeid, temp);
  } else if (routeid < a->pVilleData->route_id) {
    a->FGauche = insertionAVL(a->FGauche, routeid, temp, h);
    *h = -*h;
  } else if (routeid > a->pVilleData->route_id) {
    a->FDroit = insertionAVL(a->FDroit, routeid, temp, h);
  } else {
    *h = 0;
    a = comparaison(a, routeid, temp);
    return a;
  }
  if (*h != 0) {
    a->e = a->e + *h;
    a = equilibrerAVL(a);
    if (a->e == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}