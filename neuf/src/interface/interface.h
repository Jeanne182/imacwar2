/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>


//--------------------- Declarations des prototypes des fonctions concernant la grille -----------------------//


// Prototypes des fonctions :

/*grille.cpp*/
void affichageTexture(GLuint texture, float longueur, float largeur);
void creationTexture(GLuint *texture, char* chemin_image);

/* interface.cpp */
int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

/* selection.cpp */
void selectionCoordonnee(int* x, int* y, SDL_Event e, float aspectRatio, SDL_Surface* surface);


#endif
