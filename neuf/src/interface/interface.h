/*

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

#include <stdlib.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

// Déclarations des variables


// Déclarations des structures

typedef struct Bouton{
  float r, g, b, x, y, hauteur, longueur, valeur;
} Bouton;

enum texturesCarte{
    PLAINE,
    EAU,
    ARBRE,
    JOUEUR1,
    JOUEUR2
  };

enum Boutons{
    RIEN,
    DEPLACEMENT,
    ATTAQUE,
    ABANDON
  };

enum Unites{
  HOBBIT,
  ELFE,
  NAIN,
  ORQUE,
  NAZGUL,
  SMEAGOL,
  HUMAN
};
//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* interface.cpp */
//int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int initialisationSDL(Game* game);
int finProgrammeSDL(Game* game);
//string texture_path(texturesCarte texture_value);
//void initTextures(Game* game);
void creationTexture(GLuint *texture, SDL_Surface* image);
void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);
void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);


/*sprites.cpp*/
void affichageUnite(Joueur joueur, Game* game);


/* boutons.cpp */
void bouton(Bouton bouton);
int testClicBouton(Game* game, Bouton bouton, SDL_Event e);
int selectionBouton(Game* game, SDL_Event e);




void initialisationTextures(GLuint textureCases[3], SDL_Surface* surfaceCases[3]);  //à placer
#endif
