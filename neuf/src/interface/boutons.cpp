#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

void bouton(Bouton *bouton){
  float x = bouton->x;
  float y = bouton->y;
  float longueur = bouton->longueur;
  float hauteur = bouton->hauteur;
  float r = bouton->r;
  float g = bouton->g;
  float b = bouton->b;

  glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(r,g,b);
    glVertex2f(x, y);
    glVertex2f(x + longueur, y);
    glVertex2f(x + longueur, y + hauteur);
    glVertex2f(x, y + hauteur);
    glEnd();
  glPopMatrix();
}

int testClicBouton(Game* game, Bouton *bouton, SDL_Event e){
  selectionCoordonnee(&game->x, &game->y, e, game->surface);

  float newX = (float)(game->x - 1)/10;
  float newY = (float)(game->y - 1)/10;
  /*cout << newX <<endl;
  cout << newY <<endl;*/
  if(newX >= bouton->x && newX <= bouton->x + bouton->longueur && newY >= bouton->y && newY <= bouton->y + bouton->hauteur){
    return bouton->valeur;
  }
  return RIEN;
}

int selectionBouton(Game* game, SDL_Event e){ //Penser à rajouter tous les nouveaux boutons ici
  int valeurBouton;
  valeurBouton = testClicBouton(game, &game->boutonDeplacement, e);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, &game->boutonAttaque, e);
  }
  return valeurBouton;
}
