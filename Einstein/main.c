#include"lib.h"

int main(){

  int nc=6,nm=5,w=15,wq=5,*rang,**res; //w=15 wq=5
  panier kagami_darius;
  int conditions[][6]=
    {
      { 0, 0,-9,-9,-9,-9},//Anglais rouge
      { 1,-9, 0,-9,-9,-9},//Suédois chiens
      { 2,-9,-9, 0,-9,-9},//Danois thé
      {-9, 1,-9, 1,-9,-9},//Vert café
      {-9,-9, 1,-9, 0,-9},//Pall Mall Oiseaux
      {-9, 3,-9,-9, 1,-9},//Jaune Dunhill
      {-9,-9,-9, 2,-9, 2},//Lait rang 2
      { 3,-9,-9,-9,-9, 0},//Norvégien rang 0
      {-9,-9,-9, 3, 3,-9},//Blue Master bière
      { 4,-9,-9,-9, 4,-9} //Allemand prince
    };
  int conditions_quartier[][5]=
    { 
      {1,1,2,1,1},//verte gauche blanche 
      {2,2,2,4,2},//Blend voisin chats
      {3,2,1,2,4},//Cheval voisin Dunhill
      {3,2,4,0,1},//Norvégien voisin bleue
      {2,2,4,4,3} //Blend voisin eau
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
