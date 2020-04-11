/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef GRILLE_H
#define GRILLE_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>


//--------------------- Declarations des prototypes des fonctions concernant la grille -----------------------//


// Prototypes des fonctions :

int affichageGrille();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

#endif
