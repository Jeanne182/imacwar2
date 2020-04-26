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


// Délacrations des variables

// Déclarations des structures

typedef struct Game {
  Joueur joueur1, joueur2;
  Bouton boutonDeplacement, boutonAttaque;
  int etapeJeu;
  int tour;

  SDL_Surface* surface;

  SDL_Surface* surfaceCases[3];
  GLuint textureCases[3];


  int longueurCarte, hauteurCarte;
  int window_width, window_height;
  int bit_per_pixel;
  float aspectRatio;

  Uint32 framerate_milliseconds;

  int map[10][10];

  //A enlever ??
  int x , y;

} Game;


//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/* initialisation.cpp */
void initialisationGame(Game *game);

/* clics.cpp */
void gererClic(Game* game, SDL_Event e);

#endif
