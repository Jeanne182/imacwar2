#include "game/a_star.h"
#include "interface/interface.h"

using namespace std;

bool verificationDansListe(list<Noeud> liste, Noeud noeud){
  list<Noeud> copyList = liste;
  Noeud noeudFin;
  while(!copyList.empty()){
    noeudFin = copyList.back();
    if ( noeudFin.x == noeud.x && noeudFin.y == noeud.y){
      cout <<"Le noeud est dans la liste"<<endl;
     return true;
    }
    copyList.pop_back();
   }
   return false;
}

void choixCible(int xOrdi,int yOrdi, int *xCible, int *yCible, int map[10][10]){
  int xOptimal = -1;
  int yOptimal = -1;
  for(int i = 0; i<10; i++){
    for(int j=0; j<10; j++){
      if(map[j][i]==JOUEUR1){
        if(xOptimal==-1){
          xOptimal = i+1;
          yOptimal = j+1;
        }
        else{
          if(abs(xOptimal-xOrdi)+abs(yOptimal-yOrdi)>abs(i+1-xOrdi)+abs(j+1-yOrdi)){
            xOptimal = i+1;
            yOptimal = j+1;
          }
        }
      }
    }
  }
  *xCible = xOptimal;
  *yCible = yOptimal;
  cout<<"La cible a pour coordonnées : ("<<*xCible<<","<<*yCible<<")"<<endl;
}


void caseOptimaleAtteignable(int *x, int *y, int zoneDeplacement, list<Noeud> chemin){
  int xChemin = chemin.back().x;
  int yChemin = chemin.back().y;
  cout<<"X : " << xChemin <<" , Y : " << yChemin <<endl;
  while(abs(*x-xChemin)+abs(*y-yChemin) > zoneDeplacement){

    xChemin = chemin.back().x;
    yChemin = chemin.back().y;
    chemin.pop_back();
    cout<<"X3 : " << xChemin <<" Y3 : " << yChemin <<endl;
  }
  *x = xChemin;
  *y = yChemin;
  cout << "x et y séléctionnés : " << *x <<" , "<<*y<<endl;
}

list<Noeud> a_star(int xOrdi,int yOrdi, int xCible, int yCible, int map[10][10]){
  Noeud startNode;
  Noeud endNode;
  Noeud currentNode;
  startNode.x = xOrdi;
  startNode.y = yOrdi;
  startNode.volDoiseau = abs(xOrdi-xCible) + abs(yOrdi-yCible);
  startNode.coutDeplacement = 0;
  startNode.somme = startNode.coutDeplacement + startNode.volDoiseau;

  cout <<"Distance vol d'oiseau startNode : " <<startNode.volDoiseau<<endl;

  endNode.x = xOrdi;
  endNode.y = yOrdi;

  currentNode = startNode;

  list<Noeud> openList, closeList;
  list<Noeud> result;

  //Placement du noeud de départ dans la closelist
  closeList.push_back(currentNode);

  //On place les noeuds voisins dans l'openList




  Noeud noeudFin;

  Noeud noeudQualite;
  noeudQualite = startNode;
  int i =0;
  while(currentNode.x != xCible || currentNode.y != yCible) {
    i++;

    if(currentNode.x >0 && currentNode.x<=10 && currentNode.y-1>0 && currentNode.y-1<=10){
      Noeud noeudHaut;
      cout<<"Noeud haut"<<endl;
      noeudHaut.x = currentNode.x;
      noeudHaut.y = currentNode.y - 1;
      noeudHaut.terrain = map[noeudHaut.x-1][noeudHaut.y-1];
      if(!verificationDansListe(openList, noeudHaut) && !verificationDansListe(closeList, noeudHaut) && noeudHaut.terrain == PLAINE){
        cout<<"Noeud haut"<<endl;
        openList.push_back(noeudHaut);
      }
    }

    if(currentNode.x >0 && currentNode.x<=10 && currentNode.y+1>0 && currentNode.y+1<=10){
      cout<<"Noeud bas"<<endl;
      Noeud noeudBas;
      noeudBas.x = currentNode.x;
      noeudBas.y = currentNode.y + 1;
      noeudBas.terrain = map[noeudBas.x-1][noeudBas.y-1];
      if(!verificationDansListe(openList, noeudBas) && !verificationDansListe(closeList, noeudBas) && noeudBas.terrain == PLAINE){
        cout<<"Noeud bas"<<endl;
        openList.push_back(noeudBas);
      }
    }


    if(currentNode.x+1 >0 && currentNode.x+1<=10 && currentNode.y>0 && currentNode.y<=10){
      cout<<"Noeud droite"<<endl;
      Noeud noeudDroite;
      noeudDroite.x = currentNode.x + 1;
      noeudDroite.y = currentNode.y;
      noeudDroite.terrain = map[noeudDroite.x-1][noeudDroite.y-1];
      if(!verificationDansListe(openList, noeudDroite)&& !verificationDansListe(closeList, noeudDroite) && noeudDroite.terrain == PLAINE){
        cout<<"Noeud droite"<<endl;
        openList.push_back(noeudDroite);
      }
    }

    if(currentNode.x-1 >0 && currentNode.x-1<=10 && currentNode.y>0 && currentNode.y<=10){
      cout<<"Noeud gauche"<<endl;
      Noeud noeudGauche;
      noeudGauche.x = currentNode.x - 1;
      noeudGauche.y = currentNode.y;
      noeudGauche.terrain = map[noeudGauche.x-1][noeudGauche.y-1];
      if(!verificationDansListe(openList, noeudGauche) && !verificationDansListe(closeList, noeudGauche) && noeudGauche.terrain == PLAINE)/* && noeudHaut.terrain == PLAINE*/{
        cout<<"Noeud gauche"<<endl;
        openList.push_back(noeudGauche);
      }
    }

    if(openList.empty()){
      cout <<"OpenList vide"<<endl;
      break;
    }

    cout <<"Valeur qualité : " <<noeudQualite.somme<<endl<<endl;
    while(!openList.empty()){
      //coutDeplacement = cout du noeud parent
      noeudFin = openList.back();
      noeudFin.coutDeplacement = currentNode.coutDeplacement+1; //ERREUR ICI
      noeudFin.volDoiseau = abs(noeudFin.x-xCible) + abs(noeudFin.y-yCible);
      noeudFin.somme = noeudFin.coutDeplacement + noeudFin.volDoiseau;

      cout<<"Noeud traité (x,y)= "<< noeudFin.x << noeudFin.y<<endl ;
      cout << "xSource : "<<xCible<< "ySource : "<<yCible<<endl;
      cout <<"coutDeplacement noeud fin : " <<noeudFin.coutDeplacement<<endl;
      cout <<"volDoiseau noeud fin : " <<noeudFin.volDoiseau<<endl;
      cout <<"Somme noeud fin : " <<noeudFin.somme<<endl;
      if(noeudFin.somme <= noeudQualite.somme){
        cout<<"Plus petite valeur trouvée"<<endl;
        noeudQualite = noeudFin;
      }

      cout <<"Valeur qualité : " <<noeudQualite.somme<<endl<<endl;
      openList.pop_back();
     }

    Noeud noeudToAdd = noeudQualite;
    closeList.push_back(noeudQualite);
    result.push_back(noeudToAdd);

    currentNode = noeudQualite;

    cout<< "COORDONNEES CHEMIN : (" <<closeList.back().x <<" , "<<closeList.back().y<<")"<<endl;
  }

  // int xChemin, yChemin;
  // while(!closeList.empty()){
  //   xChemin = closeList.back().x;
  //   cout<<"X : " << xChemin;
  //   yChemin = closeList.back().y;
  //   cout<<" , Y : " << yChemin <<endl;
  //   cout<<closeList.size()<<endl;
  //   closeList.pop_back();
  // }

  return closeList;

}
