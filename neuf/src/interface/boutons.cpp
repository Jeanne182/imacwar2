#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

void bouton(Bouton bouton){
  float x = bouton.x;
  float y = bouton.y;
  float longueur = bouton.longueur;
  float hauteur = bouton.hauteur;
  float r = bouton.r;
  float g = bouton.g;
  float b = bouton.b;

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


void initBoutonUnites(Bouton bouton){
  float x = bouton.x;
  float y = bouton.y;
  float longueur = bouton.longueur;
  float hauteur = bouton.hauteur;

  glPushMatrix();
    glBegin(GL_POLYGON);
    glColor4f(0,0,0,0);
    glVertex2f(x, y);
    glVertex2f(x + longueur, y);
    glVertex2f(x + longueur, y + hauteur);
    glVertex2f(x, y + hauteur);
    glEnd();
  glPopMatrix();
}

int testClicBouton(Game* game, Bouton bouton, SDL_Event e){
  selectionCoordonnee(&game->x, &game->y, e, game->surface);

  float newX = (float)(game->x - 1)/10;
  float newY = (float)(game->y - 1)/10;
  if(newX >= bouton.x && newX <= bouton.x + bouton.longueur && newY >= bouton.y && newY <= bouton.y + bouton.hauteur){
    return bouton.valeur;
  }
  return RIEN;
}

int selectionBouton(Game* game, SDL_Event e){
  int valeurBouton=RIEN;
  valeurBouton = testClicBouton(game, game->boutonDeplacement, e);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonAttaque, e);
  }
  return valeurBouton;
}

int selectioBoutonUniteJ1(Game* game, SDL_Event e){
  int valeurBouton = RIEN;
  valeurBouton = testClicBouton(game, game->boutonHumain, e);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonNain, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonHobbit, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonElfe, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonGandalf, e);
  }
  return valeurBouton;
}

int selectioBoutonUniteJ2(Game* game, SDL_Event e){
  int valeurBouton=RIEN;
  valeurBouton = testClicBouton(game, game->boutonOrque, e);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonSmeagol, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonUrukhai, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonNazgul, e);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonSaruman, e);
  }
  return valeurBouton;
}
