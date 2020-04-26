/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

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
  float r, g, b, x, y, hauteur, longueur;
} Bouton;

// enum texturesCarte{
//     PLAINE,
//     EAU,
//     ARBRE
//   };


//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* interface.cpp */
//int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int initialisationSDL(GLuint* textureMap, SDL_Surface* surface);
int finProgrammeSDL(GLuint* textureMap);
//string texture_path(texturesCarte texture_value);
void creationTexture(GLuint *texture, char* chemin_image);
void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);
void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);


/* selection.cpp */
void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface);
int selectionIdUnite(int x, int y, Joueur joueur);



void affichageUnite(Joueur joueur, int longueurCarte, int largeurCarte);


/* boutons.cpp */
void bouton(Bouton bouton);

#endif
