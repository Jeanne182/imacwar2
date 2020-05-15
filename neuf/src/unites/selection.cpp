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
    game->map[yOld-1][xOld-1] = game->mapInit[yOld-1][xOld-1];
  }
  //cout << x << endl;
  //cout << y << endl;
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
  if (joueur.id!=game->zonePlacement[y-1][x-1]){
    return false;
  }
  return true;
}

// Fonction qui verifie que la case est libre pour qu'un joueur puisse y mettre une unite, autrement dit que les coordonees ne sont pas deja utilisees
bool verificationCaseLibre(Game* game, int x,int y){
  if (game->map[y-1][x-1]!=PLAINE){
      return false;
  }
  return true;
}

// Vérifie que La créature à attaquer est bien une créature ennemie
bool verifUniteEnnemie(int tour, Game* game, int x,int y){
  if(game->map[y-1][x-1]!=tour){
    return false;
    cout << "probl vient unite ennemie" << endl;
  }
  return true;
}

// Vérifie que La créature a le droit de se déplacer à cet endroit là en fonction de ses caractéristiques
bool verificationDistance(Joueur joueur, int x, int y, int id, Game* game){
  if(abs(x-joueur.unites[id].coord[0])+abs(y-joueur.unites[id].coord[1])>joueur.unites[id].distance || x <1 || y <1 || x> game->longueurCarte || y> game->hauteurCarte){
    return false;
  }
  return true;
}

// Vérifie que La créature a le droit d'attaquer à cet endroit là en fonction de ses caractéristiques
bool verificationZoneTir(Joueur joueur, int x, int y, int id, Game* game){
  if(abs(joueur.unites[id].coord[0]-(x-1))+abs(joueur.unites[id].coord[1]-(y-1))>joueur.unites[id].zoneDeTir){
    return false;
  }
  return true;
}

bool verificationPrix(Joueur joueur, Unite unite){
  if(joueur.pieces - unite.prix >= 0){
    return true;
  }
  cout << "Pas assez de pieces pour l'acheter" << endl;
  return false;
}
