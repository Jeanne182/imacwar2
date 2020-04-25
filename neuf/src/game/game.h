#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

typedef struct Game {
  Joueur joueur1, joueur2;
  Bouton boutonDeplacement, boutonAttaque;
  int etapeJeu;
  int tour;
  SDL_Surface* surface;
  GLuint textureMap ;

  int longueurCarte, hauteurCarte;
  int window_width, window_height;
  int bit_per_pixel;
  float aspectRatio;

  Uint32 framerate_milliseconds;

  //A enlever ??
  int x , y;

} Game;

void initialisationGame(Game *game);
void gererClic(Game* game, SDL_Event e);

#endif
