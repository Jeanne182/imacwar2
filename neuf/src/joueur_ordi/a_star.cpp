#include "joueur_ordi/a_star.h"
#include "interface/interface.h"

using namespace std;


bool verificationDansListe(list<Noeud*> liste, Noeud *noeud){
  Noeud *noeudFin = NULL;
  while(!liste.empty()){
    noeudFin = liste.back();
    if ( noeudFin->x == noeud->x && noeudFin->y == noeud->y){
     return true;
    }
    liste.pop_back();
   }
   return false;
}


/* Pas utilisée mais utile pour repérer le chemin dans le terminal */
void affichageChemin(Noeud* chemin,int xOrdi,int yOrdi){
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
  noeud->coutDeplacement = currentNode->coutDeplacement + 1;
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
  list<Noeud*> openList, closeList;

  while(currentNode->x != xCible || currentNode->y != yCible) {

    /*--------------------------------CurrentNode mis dans closeList-------------------------------*/
    closeList.push_back(currentNode);

    /*------------------------Insertion des 4 noeuds voisins dans l'openList ----------------------*/

    Noeud* noeudHaut = new Noeud;
    noeudHaut->x = currentNode->x;
    noeudHaut->y = currentNode->y - 1;
    if(noeudHaut->x >0 && noeudHaut->x<=10 && noeudHaut->y>0 && noeudHaut->y<=10){
      noeudHaut->terrain = map[noeudHaut->y-1][noeudHaut->x-1];
      poids(noeudHaut, currentNode, xOrdi, yOrdi, xCible, yCible);
      if(!verificationDansListe(openList, noeudHaut) && !verificationDansListe(closeList, noeudHaut) && (noeudHaut->terrain == VIDE ||noeudHaut->terrain == JOUEUR1)){
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
        openList.push_front(noeudGauche);
      }
    }

    /*-------------------------------------Vérification OpenList vide ----------------------------*/
    if(openList.empty()){
      cout <<"OpenList vide"<<endl;
      *currentNode = startNode;
      return currentNode;
      // break;
    }

    /*----------------------------------- Parcourt de l'OpenList----------------------------------*/
    currentNode= openList.back();
    for(Noeud *noeud : openList){
      if(noeud->somme < currentNode->somme){
        currentNode = noeud;
      }
    }

    openList.remove(currentNode);

  }
  return currentNode;
}
