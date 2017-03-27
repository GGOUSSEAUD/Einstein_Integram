#include "lib.h"

void affiche(int nc,int nm){
  int i,j,tmp;
  for(i=0;i<tpuiss(nm,nc);i++){
    tmp=i;
    for(j=0;j<nc;j++){
      printf("%d ",tmp%nm);
      tmp /= nm;
    }
    printf("\n");
  }
}



void affiche_panier(panier kuroko,int nc){
  int i,j;
  for(i=0;i<kuroko.mpotable;i++){
    for(j=0;j<nc;j++){
      printf("%d ",kuroko.tab[j][i]);
    }
    printf("i==%d\n",i);
  }
  printf("Nombre de maison potable:%d\n",kuroko.mpotable);
}

void affichetab(int * tab,int nm){
  int i;
  for(i=0;i<nm;i++)
    printf("%d ",tab[i]);
  printf("\n");
}

void affiche_res(int ** tab,int nm,int nc){
  int i,j;
  for(i=0;i<nm;i++){
    for(j=0;j<nc;j++)
      printf("%d ",tab[j][i]);
  printf("\n");
  }
}


void affiche_panier_aux(panier kuroko,int nc,int ite){
  int i,j;
  for(i=0;i<ite;i++){
    for(j=0;j<nc;j++){
      printf("%d ",kuroko.tab[j][i]);
    }
    printf("i==%d\n",i);
  }
  printf("Nombre de maison potable:%d\n",kuroko.mpotable);
}
