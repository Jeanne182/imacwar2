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
          xOptimal = j+1;
          yOptimal = i+1;
        }
        else{
          if(abs(xOptimal-xOrdi)+abs(yOptimal-yOrdi)>abs(j+1-xOrdi)+abs(i+1-yOrdi)){
            xOptimal = j+1;
            yOptimal = i+1;
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
    chemin.pop_back();
    xChemin = chemin.back().x;
    yChemin = chemin.back().y;
    cout<<"X3 : " << xChemin <<" Y3 : " << yChemin <<endl;
  }
  *x = xChemin;
  *y = yChemin;
  cout << "x et y séléctionnés : " << *x <<" , "<<*y<<endl;
}

list<Noeud> a_star(int xOrdi,int yOrdi, int xCible, int yCible){

  //Regarder noeuds voisins

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
  Noeud noeudHaut;
  Noeud noeudBas;
  Noeud noeudDroite;
  Noeud noeudGauche;
  Noeud noeudFin;

  Noeud noeudQualite;
  noeudQualite = startNode;
  int i =0;
  while(currentNode.x != xCible || currentNode.y != yCible) {
    i++;

    noeudHaut.x = currentNode.x;
    noeudHaut.y = currentNode.y - 1;

    noeudBas.x = currentNode.x;
    noeudBas.y = currentNode.y + 1;

    noeudDroite.x = currentNode.x + 1;
    noeudDroite.y = currentNode.y;

    noeudGauche.x = currentNode.x - 1;
    noeudGauche.y = currentNode.y;

    //On vérifie que les noeuds ne sont dans aucune liste
    if(!verificationDansListe(openList, noeudHaut) && !verificationDansListe(closeList, noeudHaut)){
      cout<<"yes"<<endl;
      openList.push_back(noeudHaut);
    }

    if(!verificationDansListe(openList, noeudBas) && !verificationDansListe(closeList, noeudBas)){
      openList.push_back(noeudBas);
    }

    if(!verificationDansListe(openList, noeudGauche) && !verificationDansListe(closeList, noeudGauche))/* && noeudHaut.terrain == PLAINE*/{
      openList.push_back(noeudGauche);
    }

    if(!verificationDansListe(openList, noeudDroite)&& !verificationDansListe(closeList, noeudDroite)){
      openList.push_back(noeudDroite);
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
