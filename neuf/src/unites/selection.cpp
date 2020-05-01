#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;


void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface){
  *x = e.button.x;
  *y = e.button.y;
  conversionOpenGLRepere(x, y, surface);
}

void insertionCoordonnees(Game* game, Unite* unite, int x, int y, int tour){
  if (game->etapeJeu != PLACEMENT_UNITES){
    int xOld = unite->coord[0];
    int yOld = unite->coord[1];
    game->map[yOld-1][xOld-1] = PLAINE;
  }

  unite->coord[0]=x;
  unite->coord[1]=y;
  game->map[y-1][x-1] = tour;
}

int selectionIdUnite(int x, int y, Joueur joueur){
  for(int compteur = 0; compteur < joueur.nbUnitesInitial ; compteur++){
      if (joueur.unites[compteur].coord[0]==x && joueur.unites[compteur].coord[1]==y){
          return compteur;
      }
    }
    return -1;
}


// Fonction qui, lors du placement des créatures en debut de partie, verifie que le joueur place bien ses créatures dans la zone qui lui est reservee
bool verificationZone(Joueur joueur, int x, int y, Game* game){
  if (joueur.id!=game->zonePlacement[x-1][y-1]){
    return false;
  }
  return true;
}

// Fonction qui verifie que la case est libre pour qu'un joueur puisse y mettre une unite, autrement dit que les coordonees ne sont pas deja utilisees
bool verificationCaseLibre(Joueur joueur, int x,int y){
  for(int i=0; i<joueur.nbUnitesInitial; i++){
    if (x==joueur.unites[i].coord[0] && y==joueur.unites[i].coord[1]){
        return false;
    }
  }
  return true;
}


// Vérifie que La créature a le droit de se déplacer à cet endroit là en fonction de ses caractéristiques
bool verificationDistance(Joueur joueur, int x, int y, int id, Game* game){
  if(abs(joueur.unites[id].coord[0]-(x-1))+abs(joueur.unites[id].coord[1]-(y-1))>joueur.unites[id].distance || joueur.unites[id].coord[0] <1 || joueur.unites[id].coord[1] <1 || joueur.unites[id].coord[0]> game->longueurCarte || joueur.unites[id].coord[1]> game->hauteurCarte){
    return false;
  }
  return true;
}
