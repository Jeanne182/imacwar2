/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"

void placementUnite(Joueur *joueur, SDL_Event e, SDL_Surface* surface){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite.id =id;

      int x , y;
      selectionCoordonnee(&x,&y, e, surface);
      insertionCoordonnees(&unite, x, y);
      joueur->unites[id] = unite;
      joueur->nbUnites ++;
      joueur->nbUnitesInitial++;
    }
}


void placementUnitesJoueurs(Joueur *joueur1, Joueur *joueur2, SDL_Event e, SDL_Surface* surface, int* tour){
  if (*tour == 1){
    placementUnite(joueur1, e, surface);
    *tour = 2;
  }
  else {
    placementUnite(joueur2, e, surface);
    *tour = 1;
  }
}

void deplacement(Joueur* joueur, int id, int xInitial, int yInitial, SDL_Event e, SDL_Surface* surface){

  int xNew, yNew;
  selectionCoordonnee(&xNew,&yNew, e, surface);
  insertionCoordonnees(&joueur->unites[id], xNew, yNew);


  // Vérifie que la case est libre

  //Vérifie que La créature a le droit de se déplacer à cet endroit là en fonction de ses caractéristiques

  //if(abs(coordonneesJoueur[0]-*xInitial)+abs(coordonneesJoueur[1]-*yInitial)>joueurTour.unites[idUnite].distance || coordonneesJoueur[0] <1 || coordonneesJoueur[1] <1 || coordonneesJoueur[0]> tailleGrille || coordonneesJoueur[1]>tailleGrille){
  //else{

  //  }

} // fin deplacement()
