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
    //game->map[yOld-1][xOld-1] = game->mapInit[yOld-1][xOld-1];
    if(game->mapInit[yOld-1][xOld-1]!=PLAINE && game->mapInit[yOld-1][xOld-1]!=PLAINECHG && game->mapInit[yOld-1][xOld-1]!=ARBRE2){
      game->mapObstacles[yOld-1][xOld-1] = OBSTACLE;
    }
    else{
      game->mapObstacles[yOld-1][xOld-1] = VIDE;
    }

  }

  unite->coord[0]=x;
  unite->coord[1]=y;
  // game->map[y-1][x-1] = tour;
  // game->mapObstacles[y-1][x-1] = OBSTACLE;
  game->mapObstacles[y-1][x-1] = tour;
}

int selectionIdUnite(int x, int y, Joueur joueur){
  for(int compteur = 0; compteur < joueur.nbUnitesInitial ; compteur++){
      if (joueur.unites[compteur].coord[0]==x && joueur.unites[compteur].coord[1]==y){
          return compteur;
      }
    }
    return -1;
}

// Fonction qui verifie si le joueura encore des unites a jouer
bool verificationUniteJouee(int tableau[10], int nbUnites){
  int compteur=0;
  for(int i=0 ; i<10 ; i++){
    if(tableau[i]==1){
      compteur++;
    }
  }
  if (compteur==nbUnites){
    return true;
  }
  return false;
}

// Fonction qui détermine la fin de tour
void verificationFinTour(Game* game, int nbUnites){
  if(verificationUniteJouee(game->uniteJouee, nbUnites)==true){
    passerTour(game);
  }
  else{
    game->choix = RIEN;
    game->etapeJeu = SELECTION_UNITE;
  }
}

// Fonction qui passe le toor au joueur suivant
void passerTour(Game* game){
  initialiseUniteJouee(game->uniteJouee);
  cout << "unites toutes jouees" << endl;
  game->etapeJeu=SELECTION_UNITE;
  game->choix = RIEN;
  if(game->tour == TOUR_JOUEUR2){
    game->tour = TOUR_JOUEUR1;
  }
  else{
    game->tour = TOUR_JOUEUR2;
  }

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
  if (game->mapObstacles[y-1][x-1]!=VIDE){
      return false;
  }
  return true;
}

// Vérifie que La créature à attaquer est bien une créature ennemie
bool verifUniteEnnemie(int tour, int map[10][10], int x,int y){
  if(map[y-1][x-1]!=tour){
    return false;
    cout << "probl ce n'est pas une unite ennemie" << endl;
  }
  cout<<"unite ennemie selectionnee"<<endl;
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
bool verificationZoneTir(Joueur joueur, int x, int y, int id){
  if(abs(x-joueur.unites[id].coord[0])+abs(y-joueur.unites[id].coord[1])>joueur.unites[id].zoneDeTir){
    cout<<"zone de tir fausse"<<endl;
    return false;

  }
  cout<<"zone de tir bonne"<<endl;
  return true;
}

bool verificationPrix(Joueur joueur, Unite unite){
  if(joueur.pieces - unite.prix >= 0){
    return true;
  }
  cout << "Pas assez de pieces pour l'acheter" << endl;
  return false;
}
