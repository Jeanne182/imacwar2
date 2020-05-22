#include "unites/unites.h"
#include "game/a_star.h"

using namespace std;

bool verificationDansListe(list<Noeud*> liste, Noeud noeud){
  list<Noeud*> copyList = liste;
  Noeud *noeudFin;
  while(!copyList.empty()){
    noeudFin = *copyList.end();
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

  Noeud *startNode, *endNode, *currentNode;
  startNode = nullptr;
  endNode = nullptr;
  // startNode->x = xStart;
  // startNode->y = yStart;
  // startNode->volDoiseau = sqrt(pow(xStart-xCible,2) + pow(yStart-yCible,2));
  // startNode->coutDeplacement = 0;
  // startNode->somme = startNode->coutDeplacement + startNode->volDoiseau;

  // cout <<"Distance vol d'oiseau startNode : " <<startNode->volDoiseau<<endl;
  //
  // endNode->x = uniteCible->coord[0];
  // endNode->y = uniteCible->coord[1];
  //
  // *currentNode = *startNode;
  //
  // list<Noeud*> openList, closeList;
  //
  // //Placement du noeud de départ dans la closelist
  // closeList.push_back(currentNode);
  //
  // //On place les noeuds voisins dans l'openList
  // Noeud *noeudHaut, *noeudBas, *noeudDroite, *noeudGauche;
  // Noeud *noeudFin;
  // noeudFin = nullptr;
  // Noeud *noeudQualite = startNode;

  // while(currentNode->x != xCible || currentNode->y != yCible) {
  //
  //   noeudHaut->x = xStart;
  //   noeudHaut->y = yStart - 1;
  //
  //   noeudBas->x = xStart;
  //   noeudBas->y = yStart + 1;
  //
  //   noeudDroite->x = xStart + 1;
  //   noeudDroite->y = yStart;
  //
  //   noeudGauche->x = xStart - 1;
  //   noeudGauche->y = yStart;
  //
  //   //On vérifie que les noeuds ne sont dans aucune liste
  //   if(!verificationDansListe(openList, *noeudHaut) && !verificationDansListe(closeList, *noeudHaut)){
  //     openList.push_back(noeudHaut);
  //   }
  //
  //   if(!verificationDansListe(openList, *noeudBas) && !verificationDansListe(closeList, *noeudBas)){
  //     openList.push_back(noeudBas);
  //   }
  //
  //   if(!verificationDansListe(openList, *noeudGauche) && !verificationDansListe(closeList, *noeudGauche)/* && noeudHaut.terrain == PLAINE*/){
  //     openList.push_back(noeudGauche);
  //   }
  //
  //   if(!verificationDansListe(openList, *noeudDroite) && !verificationDansListe(closeList, *noeudDroite)){
  //     openList.push_back(noeudDroite);
  //   }
  //
  //   if(openList.empty()){
  //     cout <<"OpenList vide"<<endl;
  //     break;
  //   }
  //
  //   while(!openList.empty()){
  //     *noeudFin = *openList.back();
  //     noeudFin->coutDeplacement = noeudFin->coutDeplacement+1;
  //     noeudFin->volDoiseau = sqrt(pow(noeudFin->x-xCible,2) + pow(noeudFin->y-yCible,2));
  //     noeudFin->somme = noeudFin->coutDeplacement + noeudFin->volDoiseau;
  //     cout <<"Somme noeud fin : " <<noeudFin->volDoiseau<<endl;
  //     if(noeudFin->somme < noeudQualite->somme){
  //       *noeudQualite = *noeudFin;
  //     }
  //
  //     cout <<"Valeur qualité : " <<noeudQualite->somme<<endl;
  //     openList.pop_back();
  //    }
  //
  //   closeList.push_back(noeudQualite);
  //   *currentNode = *noeudQualite;
  //   cout<< "COORDONNEES CHEMIN : (" <<currentNode->x <<" , "<<currentNode->y<<endl;
  // }
  //
  // return closeList;

  list<Noeud*> test;
  return test;

}
