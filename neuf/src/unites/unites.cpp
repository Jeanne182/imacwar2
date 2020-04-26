/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"


void placementUnite(Joueur *joueur, SDL_Event e, Game* game){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite.id =id;

      int x , y;
      selectionCoordonnee(&x,&y, e, game->surface);
      insertionCoordonnees(&unite, x, y);
      joueur->unites[id] = unite;
      joueur->nbUnites ++;
      joueur->nbUnitesInitial++;
    }
}


void placementUnitesJoueurs(Game* game, SDL_Event e){
  if (game->tour == 1){
    placementUnite(&game->joueur1, e, game);
    game->tour = 2;
  }
  else {
    placementUnite(&game->joueur2, e, game);
    game->tour = 1;
  }
}

void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){ // il y avait xInitial et yInitial mais on ne s'en servait nul part donc j'ai enlevé

  int xNew, yNew;
  selectionCoordonnee(&xNew,&yNew, e, game->surface);
  insertionCoordonnees(&joueur->unites[id], xNew, yNew);


  // Vérifie que la case est libre

  //Vérifie que La créature a le droit de se déplacer à cet endroit là en fonction de ses caractéristiques

  //if(abs(coordonneesJoueur[0]-*xInitial)+abs(coordonneesJoueur[1]-*yInitial)>joueurTour.unites[idUnite].distance || coordonneesJoueur[0] <1 || coordonneesJoueur[1] <1 || coordonneesJoueur[0]> tailleGrille || coordonneesJoueur[1]>tailleGrille){
  //else{

  //  }

} // fin deplacement()
