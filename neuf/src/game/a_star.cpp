#include "unites/unites.h"
#include "game/a_star.h"

using namespace std;

bool verificationDansListe(list<Noeud*> liste, Noeud noeud){
  list<Noeud*> copyList = liste;
  Noeud *noeudFin = (Noeud*)malloc(sizeof(Noeud));
  while(!copyList.empty()){
    *noeudFin = *copyList.back();
    if ( noeudFin->x == noeud.x && noeudFin->y == noeud.y){
      cout <<"Le noeud est dans la liste"<<endl;
     return true;
    }
    copyList.pop_back();
   }
   cout <<"Le noeud n'est pas dans la liste"<<endl;
   return false;
}

list<Noeud*> a_star(Unite* uniteOrdi, Unite* uniteCible){

  //Regarder noeuds voisins
  int xStart = uniteOrdi->coord[0];
  int yStart = uniteOrdi->coord[1];

  int xCible = uniteCible->coord[0];
  int yCible = uniteCible->coord[1];

  Noeud *startNode =(Noeud*)malloc(sizeof(Noeud));
  Noeud *endNode = (Noeud*)malloc(sizeof(Noeud));
  Noeud *currentNode = (Noeud*)malloc(sizeof(Noeud));
  startNode->x = xStart;
  startNode->y = yStart;
  startNode->volDoiseau = sqrt(pow(xStart-xCible,2) + pow(yStart-yCible,2));
  startNode->coutDeplacement = 0;
  startNode->somme = startNode->coutDeplacement + startNode->volDoiseau;

  cout <<"Distance vol d'oiseau startNode : " <<startNode->volDoiseau<<endl;

  endNode->x = uniteCible->coord[0];
  endNode->y = uniteCible->coord[1];

  *currentNode = *startNode;

  list<Noeud*> openList, closeList;

  //Placement du noeud de départ dans la closelist
  closeList.push_back(currentNode);

  //On place les noeuds voisins dans l'openList
  Noeud *noeudHaut = (Noeud*)malloc(sizeof(Noeud));
  Noeud *noeudBas = (Noeud*)malloc(sizeof(Noeud));
  Noeud *noeudDroite = (Noeud*)malloc(sizeof(Noeud));
  Noeud *noeudGauche = (Noeud*)malloc(sizeof(Noeud));
  Noeud *noeudFin = (Noeud*)malloc(sizeof(Noeud));

  Noeud *noeudQualite = (Noeud*)malloc(sizeof(Noeud));
  *noeudQualite = *startNode;

  while(currentNode->x != xCible || currentNode->y != yCible) {

    noeudHaut->x = xStart;
    noeudHaut->y = yStart - 1;

    noeudBas->x = xStart;
    noeudBas->y = yStart + 1;

    noeudDroite->x = xStart + 1;
    noeudDroite->y = yStart;

    noeudGauche->x = xStart - 1;
    noeudGauche->y = yStart;

    //On vérifie que les noeuds ne sont dans aucune liste
    if(!verificationDansListe(openList, *noeudHaut) && !verificationDansListe(closeList, *noeudHaut)){
      cout<<"yes"<<endl;
      openList.push_back(noeudHaut);
    }

    if(!verificationDansListe(openList, *noeudBas) && !verificationDansListe(closeList, *noeudBas)){
      openList.push_back(noeudBas);
    }

    if(!verificationDansListe(openList, *noeudGauche) && !verificationDansListe(closeList, *noeudGauche)/* && noeudHaut.terrain == PLAINE*/){
      openList.push_back(noeudGauche);
    }

    if(!verificationDansListe(openList, *noeudDroite) && !verificationDansListe(closeList, *noeudDroite)){
      openList.push_back(noeudDroite);
    }

    if(openList.empty()){
      cout <<"OpenList vide"<<endl;
      break;
    }


    int i=0; //A ENLEVER
    cout <<"Valeur qualité : " <<noeudQualite->somme<<endl<<endl;

    while(!openList.empty()){
      //coutDeplacement = cout du noeud parent
      *noeudFin = *openList.back();
      noeudFin->coutDeplacement = currentNode->coutDeplacement+1; //ERREUR ICI
      noeudFin->volDoiseau = sqrt(pow(noeudFin->x-xCible,2) + pow(noeudFin->y-yCible,2));
      noeudFin->somme = noeudFin->coutDeplacement + noeudFin->volDoiseau;

      cout<<"Noeud traité (x,y)= "<< noeudFin->x << noeudFin->y<<endl ;
      cout <<"coutDeplacement noeud fin : " <<noeudFin->coutDeplacement<<endl;
      cout <<"volDoiseau noeud fin : " <<noeudFin->volDoiseau<<endl;
      cout <<"Somme noeud fin : " <<noeudFin->somme<<endl;
      if(noeudFin->somme <= noeudQualite->somme){
        cout<<"Plus petite valeur trouvée"<<endl;
        *noeudQualite = *noeudFin;
      }

      cout <<"Valeur qualité : " <<noeudQualite->somme<<endl<<endl;
      openList.pop_back();
     }

    closeList.push_back(noeudQualite);

    *currentNode = *noeudQualite;

    cout<< "COORDONNEES CHEMIN : (" <<currentNode->x <<" , "<<currentNode->y<<" )"<<endl;

    i++;
    if(i==1){
      break;
    }//A enlever c'est pour les tests
  }

  return closeList;

  // list<Noeud*> test;
  // return test;

}
