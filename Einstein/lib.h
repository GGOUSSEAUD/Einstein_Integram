#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct cell{
  int ** tab;
  int mpotable;
};
typedef struct cell panier;
//affiche.c
void affiche(int,int);
void affiche_panier(panier,int);
void affichetab(int *,int);
void affiche_res(int **,int,int);
void affiche_panier_aux(panier,int,int);
//corps.c
panier remplir_maison(int[][6],int,int,int);
panier remplir_panier(panier,int*,int);
int * remplir_cond(int[][5],int);
bool verif_maison(int *,int[][6],int,int,int);
int tpuiss(int ,int );
int auxpuiss(int ,int ,int );
int * make_tabrang(panier, int, int);
int triangulaire(int*,int);
int ** track(int **,int **,int,int);
int enterzone(int **,int *,int);
int ** verif_quartier(panier,int[][5],int *,int,int,int);
panier epuration(panier,int *,int *,int,int,int);
