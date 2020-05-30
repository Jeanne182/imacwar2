/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S2
*/

#ifndef JOEUR_ORDI_H
#define JOEUR_ORDI_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <list>
struct Joueur;
struct Game;
using namespace std;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/* joueur_ordi.cpp */
void choixCible(int xOrdi,int yOrdi, int *xCible, int *yCible, int map[10][10]);
void caseOptimaleAtteignable(int *x, int *y, int zoneDeplacement, Noeud* chemin);
bool cibleInZone(int xOrdi,int yOrdi, int xCible, int yCible, int zoneAttaque);
bool placementUniteOrdi(Joueur *joueur, int x, int y, Game* game, int typeUnite);
void choixActionsOrdi(Game *game);
void attaqueOrdi(Joueur *joueurTour, Joueur *joueurEnnemi, int id, int idEnnemi, Game* game);
void choixPlacementUniteOrdi(Game *game);
void deplacementOrdi(int xOrdi, int yOrdi, int xCible, int yCible, int idOrdi, Game* game);

#endif
