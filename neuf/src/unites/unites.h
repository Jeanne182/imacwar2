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
#include <math.h>


using namespace std;
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
  char* nom;
} Unite;

typedef struct Joueur{
  int id;
  int pieces;
  Unite unites[nombreUnitesMAX];
  int nbUnites;
  int nbUnitesInitial;
  int tour;
} Joueur;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* selection.cpp */
void selectionCoordonnee(int* x, int* y, SDL_Event e, SDL_Surface* surface);
int selectionIdUnite(int x, int y, Joueur joueur);
void insertionCoordonnees(Game* game, Unite* unite, int x, int y, int tour);
bool verificationUniteJouee(int tableau[10], int nbUnites);
void verificationFinTour(Game* game, int nbUnites);
void passerTour(Game* game);
bool verificationZone(Joueur joueur, int x, int y, Game* game);
bool verificationCaseLibre(Game* game, int x,int y);
bool verificationDistance(Joueur joueur, int x, int y, int id, Game* game);
bool verifUniteEnnemie(int tour, int map[10][10], int x,int y);
bool verificationZoneTir(Joueur joueur, int x, int y, int id);
bool verificationPrix(Joueur joueur, Unite unite);

/* unites.cpp */
bool placementUnite(Joueur *joueur, SDL_Event e, Game* game, int typeUnite);
void placementUnitesJoueurs(Game* game, SDL_Event e);
void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game);
void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int id, SDL_Event e, Game* game);
void attaqueOrdi(Joueur *joueurTour, Joueur *joueurEnnemi, int id, int idEnnemi, Game* game);
void initialiseUniteJouee(int tableau[10]);
//void etatUnite(SDL_Event e, Game* game);
// void etatUnite(int id, Game* game);
void etatUnite(Unite unite, Game* game);

void zoneSurbrillance(Joueur joueur, int id, int map[10][10], int choix, Game* game);
bool placementUniteOrdi(Joueur *joueur, int x, int y, Game* game, int typeUnite);




#endif
