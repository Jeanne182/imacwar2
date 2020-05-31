#include "joueur_ordi/a_star.h"
#include "interface/interface.h"

using namespace std;

bool verificationDansListe(list<Noeud*> liste, Noeud *noeud){
  // list<Noeud> copyList = liste;
  Noeud *noeudFin = NULL;
  while(!liste.empty()){
    noeudFin = liste.back();
    if ( noeudFin->x == noeud->x && noeudFin->y == noeud->y){
      // cout <<"Le noeud est dans la liste"<<endl;
     return true;
    }
    liste.pop_back();
   }
   return false;
}

void affichageChemin(Noeud* chemin,int xOrdi,int yOrdi){
  // int x = chemin.push_back().x;
  // int y = chemin.push_back().y;
  cout<< "Cible : ("<<chemin->x<<","<<chemin->y<<")";
  cout<<"Chemin prédéfini : ";
  cout<< "("<<chemin->x<<","<<chemin->y<<")";
  while(chemin->x != xOrdi && chemin->y != yOrdi){


    chemin=chemin->parent;
    cout<< "("<<chemin->x<<","<<chemin->y<<")";
  }
  cout<< "Ordi : ("<<chemin->x<<","<<chemin->y<<")";
  cout<<endl<<endl;
}


void poids(Noeud *noeud, Noeud *currentNode, int xOrdi, int yOrdi, int xCible, int yCible){
  noeud->coutDeplacement = currentNode->coutDeplacement + 1; //ERREUR ICI
  noeud->volDoiseau = abs(noeud->x-xCible) + abs(noeud->y-yCible);
  noeud->somme = noeud->coutDeplacement + noeud->volDoiseau;
  noeud->parent = currentNode;
}

Noeud* a_star(int xOrdi,int yOrdi, int xCible, int yCible, int map[10][10]){
  Noeud startNode;
  startNode.x = xOrdi;
  startNode.y = yOrdi;
  startNode.volDoiseau = abs(xOrdi-xCible) + abs(yOrdi-yCible);
  startNode.coutDeplacement = 0;
  startNode.somme = startNode.coutDeplacement + startNode.volDoiseau;
  startNode.parent = NULL;

  Noeud* currentNode;
  currentNode = &startNode;

  cout<<endl<<endl<<"A* : startNode: "<<currentNode->x<<" "<<currentNode->y<<" "<<endl;

  list<Noeud*> openList, closeList;

  int i = 0;
  while(currentNode->x != xCible || currentNode->y != yCible) {

    i++;

    /*--------------------------------CurrentNode mis dans closeList-----------------------------*/
    closeList.push_back(currentNode);
    cout<<"A* : currentNode: "<<currentNode->x<<" "<<currentNode->y<<" "<<endl;
    /*------------------------Insertion des 4 noeuds voisins dans l'openList ----------------------*/

    Noeud* noeudHaut = new Noeud;
    noeudHaut->x = currentNode->x;
    noeudHaut->y = currentNode->y - 1;
    if(noeudHaut->x >0 && noeudHaut->x<=10 && noeudHaut->y>0 && noeudHaut->y<=10){
      noeudHaut->terrain = map[noeudHaut->y-1][noeudHaut->x-1];
      poids(noeudHaut, currentNode, xOrdi, yOrdi, xCible, yCible);
      if(!verificationDansListe(openList, noeudHaut) && !verificationDansListe(closeList, noeudHaut) && (noeudHaut->terrain == VIDE ||noeudHaut->terrain == JOUEUR1)){
        // cout<<"noeudHaut:"<< noeudHaut->x<<" "<<noeudHaut->y;
        // cout<<" noeud parent Haut: ("<<noeudHaut->parent->x <<" , "<<noeudHaut->parent->y<<")"<<endl;

        openList.push_front(noeudHaut);
      }
    }

    Noeud *noeudBas= new Noeud;
    noeudBas->x = currentNode->x;
    noeudBas->y = currentNode->y + 1;
    if(noeudBas->x >0 && noeudBas->x<=10 && noeudBas->y>0 && noeudBas->y<=10){
      noeudBas->terrain = map[noeudBas->y-1][noeudBas->x-1];
      poids(noeudBas, currentNode, xOrdi, yOrdi, xCible, yCible);
      if(!verificationDansListe(openList, noeudBas) && !verificationDansListe(closeList, noeudBas) && (noeudBas->terrain == VIDE ||noeudBas->terrain == JOUEUR1)){
        // cout<<"noeudBas:"<< noeudBas->x<<" "<<noeudBas->y;
        // cout<<"noeud parent Bas: ("<<noeudBas->parent->x <<" , "<<noeudBas->parent->y<<")"<<endl;
        openList.push_front(noeudBas);
      }
    }

    Noeud *noeudDroite= new Noeud;
    noeudDroite->x = currentNode->x + 1;
    noeudDroite->y = currentNode->y;
    if(noeudDroite->x>0 && noeudDroite->x<=10 && noeudDroite->y>0 && noeudDroite->y<=10){
      noeudDroite->terrain = map[noeudDroite->y-1][noeudDroite->x-1];
      poids(noeudDroite, currentNode, xOrdi, yOrdi, xCible, yCible);
      if(!verificationDansListe(openList, noeudDroite)&& !verificationDansListe(closeList, noeudDroite) && (noeudDroite->terrain == VIDE ||noeudDroite->terrain == JOUEUR1)){
        // cout<<"noeudDroite:"<< noeudDroite->x<<" "<<noeudDroite->y;
        // cout<<"noeud parent Droite: ("<<noeudDroite->parent->x <<" , "<<noeudDroite->parent->y<<")"<<endl;
        openList.push_front(noeudDroite);
      }
    }

    Noeud *noeudGauche= new Noeud;
    noeudGauche->x = currentNode->x - 1;
    noeudGauche->y = currentNode->y;
    if(noeudGauche->x>0 && noeudGauche->x<=10 && noeudGauche->y>0 && noeudGauche->y<=10){
      noeudGauche->terrain = map[noeudGauche->y-1][noeudGauche->x-1];
      poids(noeudGauche, currentNode, xOrdi, yOrdi, xCible, yCible);
      if(!verificationDansListe(openList, noeudGauche) && !verificationDansListe(closeList, noeudGauche) &&  (noeudGauche->terrain == VIDE ||noeudGauche->terrain == JOUEUR1)){
        // cout<<"noeudGauche:"<< noeudGauche->x<<""<<noeudGauche->y;
        // cout<<"noeud parent Gauche: ("<<noeudGauche->parent->x <<" , "<<noeudGauche->parent->y<<")"<<endl;
        openList.push_front(noeudGauche);
      }
    }

    /*-------------------------------------Vérification OpenList vide -------------------------------------*/


    if(openList.empty()){
      cout <<"OpenList vide"<<endl;
      break;
    }

    /*----------------------------------- Parcourt de l'OpenList------------------------------*/
    // cout<< endl<<"COORDONNEES CHEMIN : (" <<currentNode->x <<" , "<<currentNode->y<<")"<<endl<<endl;
    if(i>1){
      // cout<<"PARENT CURRENT NODE : ("<<currentNode->parent->x <<" , "<<currentNode->parent->y<<")"<<endl ;
    }

    currentNode= openList.back();


    // list<Noeud*> copyList = openList;
    for(Noeud *noeud : openList){
      //noeudFin = copyList.back();
      // cout<<"Noeud traité (x,y)= "<< noeud->x << noeud->y<< " "<<"parent: ("<<noeud->parent->x <<" , "<<noeud->parent->y<<")"<<endl ;
      // cout << "xSource : "<<xCible<< "ySource : "<<yCible<<endl;
      // cout <<"coutDeplacement noeud fin : " <<noeudFin.coutDeplacement<<endl;
      // cout <<"volDoiseau noeud fin : " <<noeudFin.volDoiseau<<endl;
      // cout <<"Somme noeud fin : " <<noeudFin.somme<<endl;
      // cout <<"Somme currentNode : " <<currentNode->somme<<endl<<endl;
      if(noeud->somme < currentNode->somme){
        currentNode = noeud;
      }


    }

    openList.remove(currentNode);
    // while(!copyList.empty()){
    //
    //   noeudFin = copyList.back();
    //   cout<<"Noeud traité (x,y)= "<< noeudFin->x << noeudFin->y<< " "<<"parent: ("<<noeudFin.parent->x <<" , "<<noeudFin.parent->y<<")"<<endl ;
    //   // cout << "xSource : "<<xCible<< "ySource : "<<yCible<<endl;
    //   // cout <<"coutDeplacement noeud fin : " <<noeudFin.coutDeplacement<<endl;
    //   // cout <<"volDoiseau noeud fin : " <<noeudFin.volDoiseau<<endl;
    //   // cout <<"Somme noeud fin : " <<noeudFin.somme<<endl;
    //   // cout <<"Somme currentNode : " <<currentNode->somme<<endl<<endl;
    //   if(noeudFin.somme < currentNode->somme){
    //     currentNode = &noeudFin;
    //   }
    //
    //   copyList.pop_back();
    //
    // }

    /* -----------------------Pour retirer le noeud courant de l'openList -----------------------------------*/
     // list<Noeud> stock;
     // Noeud last = openList.back();
     // while(last->x != currentNode->x or last->y != currentNode->y){
     //   stock.push_back(last);
     //   //cout<<"(x,y) : "<<last->x<<" "<<last->y<<endl;
     //   openList.pop_back();
     //   last = openList.back();
     // }
     // openList.pop_back();
     // while(!stock.empty()){
     //   openList.push_back(stock.back());
     //   stock.pop_back();
     // }


    // cout<<"noeud parent : ("<<currentNode->parent->x <<" , "<<currentNode->parent->y<<")"<<endl<<endl;

  }
  // cout<< endl<<"COORDONNEES CHEMIN : (" <<currentNode->x <<" , "<<currentNode->y<<")"<<endl<<endl;
  // affichageChemin(currentNode,xCible,yCible);
  return currentNode;
}
