/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S2
*/

#ifndef A_STAR_H
#define A_STAR_H


#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <list>
using namespace std;

typedef struct Noeud{
  int x, y;
  int coutDeplacement, volDoiseau, somme;
  int terrain;
  Noeud* parent;
  bool operator == (const Noeud &other){
    return this->x == other.x && this->y == other.y;
  };
} Noeud;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/* a_star.cpp */
bool verificationDansListe(list<Noeud*> liste, Noeud *noeud);
void poids(Noeud *noeud, Noeud *currentNode, int xOrdi, int yOrdi, int xCible, int yCible);
Noeud* a_star(int xOrdi,int yOrdi, int xCible, int yCible, int map[10][10]);
void affichageChemin(Noeud* chemin,int xCible,int yCible); 


#endif
