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
  int idUnite;
  int vie;
  int type;
  float force;
  float defense;
  int coordUnite[MAX];
  int distance;
  int zoneDeTir;
  int prix;
  //img
} Unite;

typedef struct Joueur{
  int idJoueur;
  char couleur[10];
  char pseudo[MAX];
  int pieces;
  Unite unites[nombreUnitesMAX];
  int nbUnitesJoueur;
  int nbUnitesInitial;
} Joueur;

#endif
