#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

extern int frame;

// Déclarations des variables
struct Game;
struct Joueur;
struct Unite;

// Déclarations des structures et des enum

typedef struct Bouton{
  float r, g, b, a, x, y, hauteur, longueur, valeur;
} Bouton;

enum EnumFonds{
    IMG_MENUDEBUT=0,
    IMG_MENUNORMAL,
    IMG_MENU_FIN
  };

enum EnumObstacles{
    OBSTACLE=0,
    VIDE,
    JOUEUR1,
    JOUEUR2
  };

enum EnumTexturesCarte{
    PLAINE=0,
    PLAINECHG,
    EAU,
    EAUHG,
    EAUHD,
    EAUBD,
    EAUBG,
    ARBRE,
    ARBRE1,
    ARBRE2,
    ARBRE4,
    ARBRE5,
    ARBRE6,
    ARBRE7,
    ARBRE8,
    ARBRE9
  };

enum EnumBoutons{
    RIEN=0,
    ACHAT,
    DEPLACEMENT,
    ATTAQUE,
    PASSER,
    MULTIJOUEURS,
    ORDI_MODE,
    CLIC,
    REJOUER,
    QUITTER,
    UNITE_PAS_JOUEE
  };

enum EnumUnites{
    VIKINGMAN=0,
    VIKINGWOMAN,
    VIKINGBEAST,
    VIKINGWIZARD,
    VIKINGCHIEF,
    DEADMAN,
    DEADBEAST,
    DEADWIZARD,
    DEADKNIGHT,
    DEADCHIEF,
    SANS_TYPE
  };


//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//


/* interface.cpp */
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int initialisationSDL(Game* game);
void finJeu(Game* game);
int finProgrammeSDL(Game* game);
void carre(float x, float y, Joueur joueur, int choix);
void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);
void surbrillanceAchat(int type, Game* game);
void zoneSurbrillance(Joueur joueur, int id, int map[10][10], int choix, Game* game);


/* boutons.cpp */
void bouton(Bouton bouton);
void initBoutonUnites(Bouton bouton, float r, float g, float b, float a);
int testClicBouton(Game* game, Bouton bouton, SDL_Event e, int erreur);
int selectionBoutonMenu(Game* game, SDL_Event e);
int selectionBouton(Game* game, SDL_Event e);
int selectionBoutonUnite(Game* game, SDL_Event e);

/* affichage.cpp */
void affichage(Game* game);
void affichageCarte(Game* game);
void initialisationBoutons(Game* game);
void case_joueur(Joueur joueur, Game* game, int id, int i, int j, int idgame);
void case_survol(Joueur joueur, Game* game);
void etatUnite(Unite unite, Game* game);

/*textures.cpp*/
void initialisationTexturesCarte(GLuint textureCases[20], SDL_Surface* surfaceCases[20]);
void initialisationTexturesUnites(GLuint textureUnites[10], SDL_Surface* surfaceUnites[10]);
void creationTexture(GLuint *texture, SDL_Surface* image);
void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);


#endif
