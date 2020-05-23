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

int testClicBouton(Game* game, Bouton bouton, SDL_Event e, int erreur){
  selectionCoordonnee(&game->x, &game->y, e, game->surface);

  float newX = (float)(game->x - 1)/10;
  float newY = (float)(game->y - 1)/10;
  if(newX >= bouton.x && newX <= bouton.x + bouton.longueur && newY >= bouton.y && newY <= bouton.y + bouton.hauteur){
      cout << "test clic bouton :" << bouton.valeur << endl;
    return bouton.valeur;
  }


  return erreur;
}

int selectionBouton(Game* game, SDL_Event e){
  int valeurBouton=RIEN;
  valeurBouton = testClicBouton(game, game->boutonDeplacement, e, RIEN);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonAttaque, e, RIEN);
  }
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->boutonAchat, e, RIEN);
  }
  return valeurBouton;
}

int selectionBoutonMenu(Game* game, SDL_Event e){
  int valeurBouton=RIEN;
  valeurBouton = testClicBouton(game, game->bouton1Joueur, e, RIEN);
  if (valeurBouton == RIEN){
    valeurBouton = testClicBouton(game, game->bouton2Joueurs, e, RIEN);
  }
  return valeurBouton;
}

int selectionBoutonUnite(Game* game, SDL_Event e){
  int valeurBouton = SANS_TYPE;
  if(game->tour == TOUR_JOUEUR1){
    valeurBouton = testClicBouton(game, game->boutonVikingMan, e, SANS_TYPE);
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonVikingBeast, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonVikingWoman, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonVikingWizard, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonVikingChief, e, SANS_TYPE);
    }
  }
  else{
    valeurBouton = testClicBouton(game, game->boutonDeadBeast, e, SANS_TYPE);
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonDeadKnight, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonDeadWizard, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonDeadMan, e, SANS_TYPE);
    }
    if (valeurBouton == SANS_TYPE){
      valeurBouton = testClicBouton(game, game->boutonDeadChief, e, SANS_TYPE);
    }
  }
  return valeurBouton;
}
