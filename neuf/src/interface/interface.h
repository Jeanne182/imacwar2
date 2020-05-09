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
struct Game;
struct Joueur;

// Déclarations des structures

typedef struct Bouton{
  float r, g, b, x, y, hauteur, longueur, valeur;
} Bouton;

enum EnumTexturesCarte{
    PLAINE,
    EAU,
    ARBRE,
    JOUEUR1,
    JOUEUR2
  };

//Pas ouf...
enum EnumBoutons{
    RIEN,
    DEPLACEMENT,
    ATTAQUE,
    ABANDON
  };

enum EnumUnites{
    HUMAN,
    HOBBIT,
    NAIN,
    ELFE,
    GANDALF,
    NAZGUL,
    ORQUE,
    URUK,
    SMEAGOL,
    SAROUMANE,
    SANS_TYPE
  };
//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* interface.cpp */
//int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int initialisationSDL(Game* game);
int finProgrammeSDL(Game* game);
//string texture_path(texturesCarte texture_value);
void carre(float x, float y, Joueur joueur);


void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);


/*sprites.cpp*/
void affichageUnite(Joueur joueur, Game* game);


/* boutons.cpp */
void bouton(Bouton bouton);
void initBoutonUnites(Bouton bouton);
int testClicBouton(Game* game, Bouton bouton, SDL_Event e);
int selectionBouton(Game* game, SDL_Event e);
int selectioBoutonUniteJ1(Game* game, SDL_Event e);
int selectioBoutonUniteJ2(Game* game, SDL_Event e);



/*textures.cpp*/

void initialisationTexturesCarte(GLuint textureCases[3], SDL_Surface* surfaceCases[3]);  //à placer
void initialisationTexturesUnites(GLuint textureUnites[10], SDL_Surface* surfaceUnites[10]);
void creationTexture(GLuint *texture, SDL_Surface* image);
void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);

#endif
