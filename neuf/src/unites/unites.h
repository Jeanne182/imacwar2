/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef UNITES_H
#define UNITES_H

// Declarations des constantes :

const int MAX=256;
const int vieU =100;
const int nombreUnitesMAX =15;

// Déclaration des structures :

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
  char couleur[10];
  char pseudo[MAX];
  int pieces;
  Unite unites[nombreUnitesMAX];
  int nbUnites;
  int nbUnitesInitial;
} Joueur;

void placementUnitesJoueurs(Joueur *joueur);
void insertionCoordonnees(Unite* unite, int x, int y);

#endif
