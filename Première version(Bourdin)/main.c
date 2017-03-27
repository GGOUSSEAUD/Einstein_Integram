#include"lib.h"

int main(){

  int nc=6,nm=5,w=14,wq=4,*rang,**res;
  panier kagami_darius;
  int conditions[][6]=
    {
      { 0, 0,-9,-9,-9,-9},
      { 1,-9, 0,-9,-9,-9},
      { 2,-9,-9, 0,-9,-9},
      { 3,-9,-9,-9, 0,-9},
      { 4,-9,-9,-9,-9, 0},
      {-9, 1,-9,-9, 1,-9},
      {-9,-9, 1, 1,-9,-9},
      {-9, 3,-9, 2,-9,-9},
      {-9,-9,-9,-9, 2, 2},
      {-9,-9,-9, 3, 3,-9}
    };
  int conditions_quartier[][5]=
    {
      {1,0,2,1,1},
      {4,2,4,0,1},
      {2,2,4,2,3},
      {3,2,2,2,3}
    };
  kagami_darius.mpotable=0;  
  /* printf("Rentrez le nombre de caractéristiques d'une maison\n"); */
  /* scanf("%d",&nc); */
  /* printf("\nRentrez le nombre de maison\n"); */
  /* scanf("%d",&nm); */
  /* printf("\nRentrez le nombre de conditions\n"); */
  /* scanf("%d",&w); */
  /* printf("\nRentrez le nombre de conditions de quartier\n"); */
  /* scanf("%d",&wq); */
  w-=wq;
  kagami_darius=remplir_maison(conditions,nc,nm,w);
  //affiche_panier(kagami_darius,nc);
  rang=make_tabrang(kagami_darius,nc,nm);
  //affichetab(rang,nm);
  res=verif_quartier(kagami_darius,conditions_quartier,rang,nc,nm,wq);
  affiche_res(res,nm,nc);
  return 0;
}
