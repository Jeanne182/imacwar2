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
} Noeud;


bool verificationDansListe(list<Noeud*> liste, Noeud noeud);
list<Noeud*> a_star(Unite* uniteOrdi, Unite* uniteCible);

#endif
