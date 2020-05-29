#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <stdlib.h>


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

using namespace std;

// Délacrations des variables

// Déclarations des structures
enum EnumEtapesJeu{
  //MENU
  PLACEMENT_UNITES=0, //Steeve a dit d'init toutes les premieres enums a 0
  ACHAT_UNITE,
  CHOIX_EMPLACEMENT,
  TOURS_DE_JEU,
  TOUR_JOUEUR1,
  TOUR_JOUEUR2,
  SELECTION_UNITE,
  ACTIONS,
  FIN_JEU,
  MENU,
  };

typedef struct Game {
  Game();
  Joueur joueur1, joueur2;
  Unite unites[10];//Nain, Hobbit, Elfe, Humain, Gandalf, Orque, Smeagol, Urukhai, Nazgul, Saruman;
  Bouton boutonDeplacement, boutonAttaque, boutonPasser, boutonAchat, bouton1Joueur, bouton2Joueurs, boutonRejouer, boutonQuitter;
  Bouton boutonVikingBeast, boutonVikingWoman, boutonVikingWizard, boutonVikingMan, boutonVikingChief, boutonDeadBeast, boutonDeadKnight, boutonDeadWizard, boutonDeadMan, boutonDeadChief;
  int etapeJeu, modeJeu;
  int tour;
  int choix;
  int etapeAchatUnite;
  int achat_type;
  int uniteJouee[10]; // A CHANGER SI ON CHANGE LES SOUS

  SDL_Surface* surface;

  SDL_Surface* surfacebouton;
  GLuint texturebouton;

  SDL_Surface* surffond[3];
  GLuint textfond[3];

  SDL_Surface* surfaceCases[20];
  GLuint textureCases[20];

  SDL_Surface* surfaceUnites[10];
  GLuint textureUnites[10];

  //textes
  GLuint textureTextes[100];
  SDL_Surface surfaceTextes[100]; // parce que steevaditquevallaitmieux que ce soit pas un pointeur de surface
  TTF_Font* policeTextes[100];
  // SDL_Surface *texte;
  // TTF_Font *police;

  int longueurCarte, hauteurCarte;
  int window_width, window_height;
  int bit_per_pixel;
  float aspectRatio;

  Uint32 framerate_milliseconds;

  int mapInit[10][10];
  int map[10][10];
  int zonePlacement[10][10];
  int mapObstacles[10][10];



  //A enlever ??
  int x , y;
  int xSurvol, ySurvol;
  int id1, id2;
  int idUniteSurvolee;

} Game;


//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/* initialisation.cpp */
void initialisationGame(Game *game);
void initialisationDynamique(Game *game);
void enleveUnite(int map[10][10], Joueur joueur1, Joueur joueur2);

/* clics.cpp */
void gererClic(Game* game, SDL_Event e);
void case_rien(Game* game, SDL_Event e, Joueur joueur, int id);
void case_deplacement(Game* game, SDL_Event e);
void case_attaque(Game* game, SDL_Event e);

#endif
