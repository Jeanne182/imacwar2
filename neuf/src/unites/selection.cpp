#include "unites/unites.h"
#include "interface/interface.h"



void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface){
  *x = e.button.x;
  *y = e.button.y;
  conversionOpenGLRepere(x, y, surface);
  //printf("clic en (%d, %d)\n", *x, *y);
}

void insertionCoordonnees(Unite* unite, int x, int y){
  unite->coord[0]=x;
  unite->coord[1]=y;
}

int selectionIdUnite(int x, int y, Joueur joueur){
  for(int compteur = 0; compteur < joueur.nbUnitesInitial ; compteur++){
      if (joueur.unites[compteur].coord[0]==x && joueur.unites[compteur].coord[1]==y){
          return compteur;
      }
    }
    return -1;
}
