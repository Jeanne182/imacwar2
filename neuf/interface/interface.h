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

void affichageTexture(GLuint texture, int longueur, int largeur);
void creationTexture(GLuint *texture, char* chemin_image);
int affichageInterface();

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

#endif
