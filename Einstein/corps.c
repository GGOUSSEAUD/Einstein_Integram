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
  return 0;
}

int ** verif_quartier(panier kise,int cond_quartier[][5],int * tab_rang,int nc,int nm,int wq){

  int nb_mtotal=kise.mpotable,** res,*cond,i,j,k,x,y,q,tmp,dunk,zone,violet;
  cond=malloc(sizeof(*cond)*5);
  res=malloc(sizeof(*res)*nc);
  for(i=0;i<nc;i++)
    res[i]=malloc(sizeof(* res[i])*nm);
  while(kise.mpotable>nm){
    for(i=0;i<nm;i++){

      for(q=0;q<(nc-1);q++){ 
	zone=kise.tab[q][enterzone(kise.tab,tab_rang,i)];
	for(j=triangulaire(tab_rang,i),violet=0;j<triangulaire(tab_rang,i+1);j++){
	  if(kise.tab[q][j] != zone && kise.tab[q][j] != -1){
	    violet=1;
	    break;
	  }
	}
	if(violet==0){
	  for(x=0;x<nm;x++){
	    if(x != i){
	      for(j=triangulaire(tab_rang,x);j<triangulaire(tab_rang,x+1);j++){
		if(kise.tab[q][j] == zone){
		  for(y=0;y<nc;y++){
		    kise.tab[y][j]=-1;
		  }
		  kise.mpotable--;
		}
	      }
	    }
	  }
	}
      }
      for(k=0;k<wq;k++){
	cond=remplir_cond(cond_quartier,k);
	if(i==0 && (cond[1]==0)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	    }
	  }
	}
	if(i==(nm-1) && (cond[1]==1)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	    }
	  }
	}
	if(cond[1]==0 && i != (nm-1)){
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
	      }
	    }
	  }
	}
	if(cond[1]==1 && i != 0){
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
	      }
	    }
	  }
	}
	tmp=0;
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(cond[0]!= kise.tab[cond[3]][j] && kise.tab[0][j]!=-1){
	    tmp=1;
	    break;
	  }
	}
	
	if(tmp==0)
	  kise=epuration(kise,tab_rang,cond,nm,nc,i);
      }
      for(k=0;k<wq;k++){
	cond=remplir_cond(cond_quartier,k);
	cond=reversecond(cond);
	if(i==0 && (cond[1]==0)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	    }
	  }
	}
	if(i==(nm-1) && (cond[1]==1)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(kise.tab[cond[3]][j]==cond[0]){
	      for(k=0;k<nc;k++)
		kise.tab[k][j]=-1;
	      kise.mpotable--;
	    }
	  }
	}
	if(cond[1]==0 && i != (nm-1)){
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
	      }
	    }
	  }
	}
	if(cond[1]==1 && i != 0){
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
	      }
	    }
	  }
	}
	tmp=0;
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(cond[0]!= kise.tab[cond[3]][j] && kise.tab[0][j]!=-1){
	    tmp=1;
	    break;
	  }
	}
	if(tmp==0)
	  kise=epuration(kise,tab_rang,cond,nm,nc,i);
      }
    }
  }
  res=track(res,kise.tab,nb_mtotal,nc);
  return res;
}


panier epuration(panier aomine,int * tab_rang,int * cond,int nm,int nc,int rangcond){
  int i,j,k;
  if(cond[1]==0){
    for(i=0;i<nm;i++){
      if(i !=rangcond && i!=(rangcond-1)){
     
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[3]][j] == cond[0]|| aomine.tab[cond[4]][j] == cond[2]){
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
	  }
	}
      }
      if(i==rangcond-1){
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[4]][j] != cond[2]){
	    if(aomine.tab[0][j] != -1){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
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
	  }
	}
      }
    }
  }
  if(cond[1]==1){
    for(i=0;i<nm;i++){
      if(i!=rangcond && i!=(rangcond+1)){
	for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	  if(aomine.tab[cond[3]][j] == cond[0] || aomine.tab[cond[4]][j] == cond[2]){
	    for(k=0;k<nc;k++){
	      aomine.tab[k][j]= -1;
	    }
	    aomine.mpotable--;
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
	  }
	}
      }
    }   
  }
  
  if(cond[1]==2){
    if(rangcond==0){
      for(i=0;i<nm;i++){
	if(i!=rangcond && i!=(rangcond+1)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0] || aomine.tab[cond[4]][j] == cond[2]){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
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
	    }
	  }
	}
      }
    }
    if(rangcond==(nm-1)){
      for(i=0;i<nm;i++){
	if(i !=rangcond && i!=(rangcond-1)){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0]|| aomine.tab[cond[4]][j] == cond[2]){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	    }
	  }
	}
	if(i==rangcond-1){
	  for(j=triangulaire(tab_rang,i-1);j<triangulaire(tab_rang,i);j++){
	    if(aomine.tab[cond[4]][j] != cond[2]){
	      if(aomine.tab[0][j] != -1){
		for(k=0;k<nc;k++){
		  aomine.tab[k][j]= -1;
		}
		aomine.mpotable--;
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
	    }
	  }
	}
      }
    }
    else{
      for(i=0;i<nm;i++){
	if((i != rangcond) && (i!=(rangcond-1)) && (i!=(rangcond+1))){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if((aomine.tab[cond[3]][j] == cond[0]) || (aomine.tab[cond[4]][j] == cond[2])){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	    }
	  }
	}	
	if(i==rangcond){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[4]][j] == cond[2]){
	      for(k=0;k<nc;k++)
		aomine.tab[k][j]= -1;
	      aomine.mpotable--;
	    }
	  }
	}
	if(i==rangcond+1||i==rangcond-1){
	  for(j=triangulaire(tab_rang,i);j<triangulaire(tab_rang,i+1);j++){
	    if(aomine.tab[cond[3]][j] == cond[0]){
	      for(k=0;k<nc;k++){
		aomine.tab[k][j]= -1;
	      }
	      aomine.mpotable--;
	    }
	  }
	}
      }
    }
  }
  return aomine;
}
