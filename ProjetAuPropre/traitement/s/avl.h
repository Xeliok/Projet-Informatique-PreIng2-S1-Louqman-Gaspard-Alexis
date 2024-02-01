#ifndef TRAITEMENT__T_AVL_H
#define TRAITEMENT__T_AVL_H

typedef struct {
  int route_id;
  float dist_min;
  float dist_max;
  float somme;
  int total_stepid;
  float moyenne;
  float maxmin;
} VilleData;

typedef struct {
  VilleData** element;
  int front;
  int rear;
  int size;
  int capacity;
} File;

typedef struct arbre {
  VilleData *pVilleData;
  struct arbre *FGauche;
  struct arbre *FDroit;
  int e;
} AVL;

int max(int a, int b);

int min(int a, int b);

void afficherFile(File* file);

File* creerQueue(int capacity);

void enqueue(File* queue, VilleData* value);

void printQueue(File* queue);

void initializeQueue(File* file, int capacity);

AVL *rotationGauche(AVL *a);

AVL *rotationDroite(AVL *a);

AVL *doubleRotationGauche(AVL *a);

AVL *doubleRotationDroite(AVL *a);

AVL *equilibrerAVL(AVL *a);

AVL *creerArbre(int routeid, float temp);

AVL *comparaison(AVL *a, int routeid, float temp);

AVL *insertionAVL(AVL *a, int routeid, float temp, int *h);

#endif // TRAITEMENT__T_AVL_H