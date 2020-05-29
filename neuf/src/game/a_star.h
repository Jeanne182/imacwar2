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


bool verificationDansListe(list<Noeud*> liste, Noeud *noeud);
void choixCible(int xOrdi,int yOrdi, int *xCible, int *yCible, int map[10][10]);
void poids(Noeud *noeud, Noeud *currentNode, int xOrdi, int yOrdi, int xCible, int yCible);
void remove(list<Noeud> *list, Noeud *noeud);
void caseOptimaleAtteignable(int *x, int *y, int zoneDeplacement, list<Noeud*> chemin);
Noeud* a_star(int xOrdi,int yOrdi, int xCible, int yCible, int map[10][10]);

#endif
