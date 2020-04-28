/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

bool placementUnite(Joueur *joueur, SDL_Event e, Game* game){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite.id =id;
      unite.distance=3;

      //MODIFIé AVEC STEEVE
      int x=0;
      int y=0;
      selectionCoordonnee(&x,&y, e, game->surface);
      cout << "x : " << x << " y : " << y << endl;
      if(verificationZone(*joueur, x, y, game)==true && verificationCaseLibre(*joueur, x, y)==true){
        insertionCoordonnees(&unite, x, y);
        joueur->unites[id] = unite;
        joueur->nbUnites ++;
        joueur->nbUnitesInitial++;
        return true;
      }
    }
    return false;
}


bool placementUnitesJoueurs(Game* game, SDL_Event e){
  if (game->tour == TOUR_JOUEUR1){
    if(placementUnite(&game->joueur1, e, game)==true){
      game->tour = TOUR_JOUEUR2;
      return true;
    }
  }
  else {
    if(placementUnite(&game->joueur2, e, game)==true){
      game->tour = TOUR_JOUEUR1;
      return true;
    }
  }
  return false;
}

void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){

  int xNew, yNew;
  selectionCoordonnee(&xNew,&yNew, e, game->surface);
  if(verificationCaseLibre(game->joueur1, xNew, yNew)==true && verificationCaseLibre(game->joueur2, xNew, yNew)==true && verificationDistance(*joueur, xNew, yNew, id, game)==true){
    insertionCoordonnees(&joueur->unites[id], xNew, yNew);
    cout << "case libre" << endl;
    if(game->tour == TOUR_JOUEUR2){
      game->tour = TOUR_JOUEUR1;
    }
    else{
      game->tour = TOUR_JOUEUR2;
    }
    game->choix = RIEN;
    game->etapeJeu = SELECTION_UNITE;
  }
  else{
    cout << "Cette case est déjà occupée, veuillez choisir une autre case OU Votre distance de déplacement n'est pas respectée" << endl;
  }
}
