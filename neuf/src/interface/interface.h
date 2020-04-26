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
using namespace std;

typedef struct Bouton{
  float r, g, b, x, y, hauteur, longueur;
} Bouton;
//--------------------- Declarations des prototypes des fonctions concernant la grille -----------------------//

// enum texturesCarte{
//     PLAINE, 
//     EAU, 
//     ARBRE
//   };
  

// Prototypes des fonctions :

/*grille.cpp*/

void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);
void creationTexture(GLuint *texture, char* chemin_image);

/* interface.cpp */
//int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
//string texture_path(texturesCarte texture_value);

/* selection.cpp */
void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface);


int initialisationSDL(GLuint* textureMap, SDL_Surface* surface);
int finProgrammeSDL(GLuint* textureMap);

void affichageUnite(Joueur joueur, int longueurCarte, int largeurCarte);

void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);
int selectionIdUnite(int x, int y, Joueur joueur);

void bouton(Bouton bouton);

#endif
