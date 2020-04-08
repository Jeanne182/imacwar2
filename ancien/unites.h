/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#ifndef UNITES_H
#define UNITES_H

//--------------- Declarations des structures et prototypes des fonctions concernant les unites ----------------//

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


// Prototypes des fonctions :

int reglesJeu();
int reglesNiveaux();
int jeuPartie(int niveau, int tailleGrille);
void gestionUnitesEnUnTour(Joueur* joueurTour, Joueur* joueurEnnemi, int tailleGrille);
void creationJoueurs(Joueur *joueur1, Joueur *joueur2, int niveauPartie);
void selectionUnite(Joueur *joueurTour, Joueur *joueurEnnemi, int tabID[nombreUnitesMAX], int tailleGrille);
void typeUnites(Joueur joueur, Unite *uniteJoueur);
int verificationZone(Joueur joueurTour, int x,int y, int tailleGrille, int zonePlacement);
int verificationCaseLibre(Joueur joueurTour, Joueur joueurEnnemi, int x,int y);
void deplacement(Joueur joueurTour, Joueur joueurEnnemi, int *xInitial, int *yInitial, int idUnite, int tailleGrille);
void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int *xSelection, int *ySelection, int tailleGrille);
int verifUniteEnnemie(Joueur joueurTour, Joueur joueurEnnemi, int xEnnemi, int yEnnemi);
void etatUnites(Joueur joueur, int idUnite);
void messageErreur(int entier);

#endif
