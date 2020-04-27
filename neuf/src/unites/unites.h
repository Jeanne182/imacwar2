/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef UNITES_H
#define UNITES_H

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

// Declarations des constantes :

const int MAX=256;
const int vieU =100;
const int nombreUnitesMAX =15;

// Déclaration des structures :

struct Game;
typedef struct Unite{
  int id;
  int vie;
  int type;
  float force;
  float defense;
  float coord[MAX];
  int distance;
  int zoneDeTir;
  int prix;
  //img
} Unite;

typedef struct Joueur{
  int id;
  char pseudo[MAX];
  int pieces;
  Unite unites[nombreUnitesMAX];
  int nbUnites;
  int nbUnitesInitial;
} Joueur;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* selection.cpp */
void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface);
int selectionIdUnite(int x, int y, Joueur joueur);
void insertionCoordonnees(Unite* unite, int x, int y);

/* unites.cpp */
void placementUnite(Joueur *joueur, SDL_Event e, Game* game);
void placementUnitesJoueurs(Game* game, SDL_Event e);
void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game);




#endif
