#include "lib.h"


int auxpuiss(int n,int p,int acc){
  if(p == 0)
    return acc;
  return auxpuiss(n,(p - 1),(acc * n));
} 

int tpuiss(int n,int p){
  return auxpuiss(n,p,1);
}


panier remplir_maison(int cond[][6],int nc,int nm,int w){
  int i,j,tmp;
  panier hoop;
  int * maison;
  hoop.mpotable=0;
  maison=malloc(nc*sizeof(* maison));
  hoop.tab=malloc(nc*sizeof(* hoop.tab));
  for(i=0;i<nc;i++)
    hoop.tab[i]=malloc(300*sizeof(* hoop.tab[i]));
  for(i=0;i<tpuiss(nm,nc);i++){
    tmp=i;
    for(j=0;j<nc;j++){
      maison[j]=tmp%nm;
      tmp /= nm;
    }
    if(verif_maison(maison,cond,nc,nm,w)==1)
      hoop=remplir_panier(hoop,maison,nc);
  }
  return hoop;
}



panier remplir_panier(panier dunk,int * maison,int nc){
  int i;
  for(i=0;i<nc;i++){
    dunk.tab[i][dunk.mpotable]=maison[i];
  }
  dunk.mpotable++;
  return dunk;
}

int * remplir_cond(int cond_wq[][5],int k){
  int i,*toto;
  toto=malloc(sizeof(*toto)*5);
  for(i=0;i<5;i++){
    toto[i]=cond_wq[k][i];
  }
  return toto;
}

bool verif_maison(int * maison, int cond[][6],int nc,int nm,int w){
  int i,j,test,valid;
  for(i=0;i<w;i++){
    for(j=0,valid=0,test=1;j<nc;j++){
      if((cond[i][j]>=0) && (cond[i][j]!=maison[j]))
	test=0;
      if((cond[i][j]>=0) && (cond[i][j]==maison[j]))
	valid=1;
    }
    if(valid==1 && test==0)
      return 0;
  }
  return 1;
}

int * make_tabrang(panier p,int nc,int nm){
  int * tab;
  int i;
  tab=malloc(nm*sizeof(*tab));
  for(i=0;i<p.mpotable;i++)
    tab[p.tab[nc-1][i]]+=1;
  return tab;
}

    
int triangulaire(int * tab_rang,int h){
  if(h<=0)
    return 0;
  return tab_rang[h-1]+triangulaire(tab_rang,h-1);
}

int ** track(int ** tab,int ** tap,int nb_mtotal,int nc){
  int i,j,l;
  for(i=0,l=0;i<nb_mtotal;i++){
    if(tap[0][i]!=-1){
      for(j=0;j<nc;j++)
	tab[j][l]=tap[j][i];
      l++;
    }
  }
  return tab;
}

int * reversecond(int * cond){
  int tmp=cond[0];
  cond[0]=cond[2];
  cond[2]=tmp;
  tmp=cond[3];
  cond[3]=cond[4];
  cond[4]=tmp;
  if(cond[1]==1 || cond[1]==0)
    cond[1]=1-cond[1];
  return cond;
}

int enterzone(int ** akashi,int * tab_rang,int i){
  int ite;
  for(ite=triangulaire(tab_rang,i);ite<triangulaire(tab_rang,i+1);ite++){
    if(akashi[0][ite]!=-1)
      return ite;
  }
  printf("Problème ite");
  return 0;
}

int ** verif_quartier(panier kise,int cond_quartier[][5],int * tab_rang,int nc,int nm,int wq){

  int nb_mtotal=kise.mpotable,** res,*cond,i,j,k,x,y,q,tmp,dunk,zone,violet;
  cond=malloc(sizeof(*cond)*5);
  res=malloc(sizeof(*res)*nc);
  for(i=0;i<nc;i++)
    res[i]=malloc(sizeof(* res[i])*nm);
  while(kise.mpotable>nm){
    //printf("bouclewhile\n");
    for(i=0;i<nm;i++){

      for(q=0;q<(nc-1);q++){ // si tu n'as que du vin, alors personne d'autre ne doit en avoir.
	zone=kise.tab[q][enterzone(kise.tab,tab_rang,i)];
	for(j=triangulaire(tab_rang,i),violet=0;j<triangulaire(tab_rang,i+1);j++){
	  if(kise.tab[q][j] != zone && kise.tab[q][j] != -1){
	    violet=1;
	    break;
	  }
	}
	if(violet==0){
	  printf("avant violet\n");
	  printf("zone = %d q= %d\n",zone,q);
	  for(x=0;x<nm;x++){
	    if(x != i){
	      for(j=triangulaire(tab_rang,x);j<triangulaire(tab_rang,x+1);j++){
		if(kise.tab[q][j] == zone){
		  for(y=0;y<nc;y++){
		    kise.tab[y][j]=-1;
		  }
		  kise.mpotable--;
		  printf("zone violette\n");
		}
	      }
	    }
	  }
	}
      }
      //printf("première boucle\n");
      for(k=0;k<wq;k++){
	//printf("boucle interne normale\n");
	cond=remplir_cond(cond_quartier,k);
	printf("exterieur i==%d\n",i);
	affichetab(cond,5);

	if(i==0 && (cond[1]==0)){//Si on est premier on peut pas etre a droite de
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	      printf("ici j==%d\n",j);
	    }
	  }
	}
	if(i==(nm-1) && (cond[1]==1)){//si on est dernier on peut pas etre a gauche de
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	      printf("la j==%d\n",j);
	    }
	  }
	}
	if(cond[1]==0 && i != (nm-1)){//si à droite de nous ya pas de vert, on est pas blanc(marche avec d'autre conditions du type)
	  dunk=0;
	  for(j=triangulaire(tab_rang,i+1);j<triangulaire(tab_rang,i+2);j++){
	    if(cond[0]==kise.tab[cond[3]][j]){
	      dunk=1;
	      break;
	    }
	  }
	  if(dunk==0){
	    for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	      if(cond[2]==kise.tab[cond[4]][j]){
		for(k=0;k<nc;k++)
		  kise.tab[k][j]=-1;
		kise.mpotable--;
		printf("je te dunk j==%d\n",j);
	      }
	    }
	  }
	}
	if(cond[1]==1 && i != 0){//pareil a gauche
	  dunk=0;
	  for(j=triangulaire(tab_rang,i-1);j<triangulaire(tab_rang,i);j++){
	    if(cond[0]==kise.tab[cond[3]][j]){
	      dunk=1;
	      break;
	    }
	  }
	  if(dunk==0){
	    for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	      if(cond[2]==kise.tab[cond[4]][j]){
		for(k=0;k<nc;k++)
		  kise.tab[k][j]=-1;
		kise.mpotable--;
		printf("3 points j==%d\n",j);
	      }
	    }
	  }
	}
	tmp=0;
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  printf("cond[0]=%d kise.tab[cond[3]][j]=%d j=%d\n",cond[0],kise.tab[cond[3]][j],j);
	  if(cond[0]!= kise.tab[cond[3]][j] && kise.tab[0][j]!=-1){
	    tmp=1;
	    break;
	  }
	}
	
	if(tmp==0)
	  kise=epuration(kise,tab_rang,cond,nm,nc,i);
      }
      //printf("apres epuration\n");
      for(k=0;k<wq;k++){
	cond=remplir_cond(cond_quartier,k);
	cond=reversecond(cond);
	printf("exterieur rivers   i==%d\n",i);
	affichetab(cond,5);
	if(i==0 && (cond[1]==0)){//Si on est premier on peut pas etre a droite de
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	      printf("ici(rivers) j==%d\n",j);
	    }
	  }
	}
	if(i==(nm-1) && (cond[1]==1)){//si on est dernier on peut pas etre a gauche de
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	      printf("la(rivers) j==%d\n",j);
	    }
	  }
	}
	if(cond[1]==0 && i != (nm-1)){//pareil à droite
	  dunk=0;
	  for(j=triangulaire(tab_rang,i+1);j<triangulaire(tab_rang,i+2);j++){
	    if(cond[0]==kise.tab[cond[3]][j]){
	      dunk=1;
	      break;
	    }
	  }
	  if(dunk==0){
	    for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	      if(cond[2]==kise.tab[cond[4]][j]){
		for(k=0;k<nc;k++)
		  kise.tab[k][j]=-1;
		kise.mpotable--;
		printf("je te dunk(rivers)\n");
	      }
	    }
	  }
	}
	if(cond[1]==1 && i != 0){//si ya pas de blanc à gauche, on est pas verte(marche avec d'autres cond)
	  dunk=0;
	  for(j=triangulaire(tab_rang,i-1);j<triangulaire(tab_rang,i);j++){
	    if(cond[0]==kise.tab[cond[3]][j]){
	      dunk=1;
	      break;
	    }
	  }
	  if(dunk==0){
	    for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	      if(cond[2]==kise.tab[cond[4]][j]){
		for(k=0;k<nc;k++)
		  kise.tab[k][j]=-1;
		kise.mpotable--;
		printf("3 points(rivers)\n");
	      }
	    }
	  }
	}
	tmp=0;
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  printf("cond[0]=%d kise.tab[cond[3]][j]=%d j=%d\n",cond[0],kise.tab[cond[3]][j],j);
	  //printf("je fais des -1 à l'envers\n");
	  if(cond[0]!= kise.tab[cond[3]][j] && kise.tab[0][j]!=-1){
	    tmp=1;
	    break;
	  }
	}
	if(tmp==0)
	  kise=epuration(kise,tab_rang,cond,nm,nc,i);
	//printf("après épuration à l'envers\n");
      }
    }
  }
  res=track(res,kise.tab,nb_mtotal,nc);
  return res;
}


panier epuration(panier aomine,int * tab_rang,int * cond,int nm,int nc,int rangcond){
  int i,j,k;
  printf("j'épure | rangcond==%d \n",rangcond);
  //////////////////////////////////////// DROITE ///////////////////////////////////
  printf("cond[1]==%d\n",cond[1]);
  if(cond[1]==0){
    for(i=0;i<nm;i++){ //pour tout les rangs
      if(i !=rangcond && i!=(rangcond-1)){//Rangdesmaisonsquivalidelacondition
	//pour les rangs faux
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[3]][j] == cond[0]|| aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rangs 3=rang_info1 4=rang_info2
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
	    printf("amp_droite_toutrang==%d i==%d j==%d\n",aomine.mpotable,i,j);
	  }
	}
      }
      if(i==rangcond-1){ //pour les maison de gauche
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[4]][j] != cond[2]){//suppression des maisons fausses de ces rang
	    if(aomine.tab[0][j] != -1){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_maison_droite==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
      }
      if(i==rangcond){ //pour les maison cond
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rang
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
	    printf("amp_droite_cond==%d i==%d j==%d\n",aomine.mpotable,i,j);
	  }
	}
      }
    }
  }
  /////////////////////////////////////////////// GAUCHE ///////////////////////////////////////////////
  if(cond[1]==1){
    for(i=0;i<nm;i++){ //pour tout les rangs
      if(i!=rangcond && i!=(rangcond+1)){//Rangdesmaisonsquivalidelacondition
	//pour les rangs faux
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[3]][j] == cond[0] || aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rangs 3=rang_info1 4=rang_info2
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
	    printf("amp_toutrang_gauche== %d i==%d j==%d\n",aomine.mpotable,i,j);
	  }
	}
      }
      if(i==rangcond+1){ //pour les maisons de droite
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[4]][j] != cond[2]){//suppression des maisons fausses de ces rang
	    if(aomine.tab[0][j] != -1){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_maison_gauche==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
      }
      if(i==rangcond){ //pour les maisons cond
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rang
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
	    printf("amp_gauche_cond==%d i==%d j==%d\n",aomine.mpotable,i,j);
	  }
	}
      }
    }   
  }
  
  /////////////////////////////////////////////// VOISIN /////////////////////  
  if(cond[1]==2){ //voisin
    printf("je suis dans voisin\n");
    /////////////////////////////////////////////////premiere
    if(rangcond==0){//premiere maison
      printf("je suis dans voisin premier\n");
      for(i=0;i<nm;i++){ //GAUCHE
	if(i!=rangcond && i!=(rangcond+1)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0] || aomine.tab[cond[4]][j] == cond[2]){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_toutrang_voisinpremier== %d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
	if(i==rangcond+1){ 
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[4]][j] != cond[2]){
	      if(aomine.tab[0][j] != -1){
		for(k=0;k<nc;k++){
		  aomine.tab[k][j]= -1;
		}
		aomine.mpotable--;
		printf("amp_maison_voisinpremier==%d i==%d j==%d\n",aomine.mpotable,i,j);
	      }
	    }
	  }
	}
	if(i==rangcond){ 
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[4]][j] == cond[2]){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_voisinpremier_cond==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
      }
    }
    //////////////////////////////////////////////// DERNIERE
    if(rangcond==(nm-1)){//derniere maison
      printf("je suis dans voisin dernier\n");
      for(i=0;i<nm;i++){ //pour tout les rangs
	if(i !=rangcond && i!=(rangcond-1)){//Rangdesmaisonsquivalidelacondition
	  //pour les rangs faux
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0]|| aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rangs 3=rang_info1 4=rang_info2
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_voisindernier_toutrang==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
	if(i==rangcond-1){ //pour les maison de gauche
	  for(j=triangulaire(tab_rang,i-1);j<triangulaire(tab_rang,i);j++){
	    if(aomine.tab[cond[4]][j] != cond[2]){//suppression des maisons fausses de ces rang
	      if(aomine.tab[0][j] != -1){
		for(k=0;k<nc;k++){
		  aomine.tab[k][j]= -1;
		}
		aomine.mpotable--;
		printf("amp_maison_voisindernier==%d i==%d j==%d\n",aomine.mpotable,i,j);
	      }
	    }
	  }
	}
	if(i==rangcond){ //pour les maison cond
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rang
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_voisindernier_cond==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
      }
    }
    /////////////////////////////////////////////NORMAL
    else{
      printf("je suis dans voisin normal\n");
      for(i=0;i<nm;i++){ //pour tout les rangs
	printf("je rentre dans la boucle de voisin\n");
	if((i != rangcond) && (i!=(rangcond-1)) && (i!=(rangcond+1))){//pour les rangs faux
	  printf("Woop! Dans la condition \n");
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    printf("aomine.tab[cond[3 | 4][j]== %d | %d cond[0]=%d cond[2]=%d\n",aomine.tab[cond[3]][j],aomine.tab[cond[4]][j],cond[0],cond[2]);
	    affichetab(cond,5);	  				
	    if((aomine.tab[cond[3]][j] == cond[0]) || (aomine.tab[cond[4]][j] == cond[2])){ //suppression des maisons fausses de ces rangs
	      printf("Hop! Deuxieme condition\n");
	      for(k=0;k<nc;k++){
		printf("je met des -1 à aux autres\n");
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_voisin_rang==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}	
	if(i==rangcond){ //pour les maison cond
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[4]][j] == cond[2]){//suppression des maisons fausses de ces rang
	      for(k=0;k<nc;k++)
		aomine.tab[k][j]= -1;
	      aomine.mpotable--;
	      printf("amp_voisin_cond==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
	if(i==rangcond+1||i==rangcond-1){//pour les voisins
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0]){
	      for(k=0;k<nc;k++){
		printf("je met des -1 à aux autres\n");
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	      printf("amp_voisin_voisins==%d i==%d j==%d\n",aomine.mpotable,i,j);
	    }
	  }
	}
      }
    }
  }
  affiche_panier_aux(aomine,nc,133);
  return aomine;
}
