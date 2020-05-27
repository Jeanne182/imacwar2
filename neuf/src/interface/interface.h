/*

IMAC 1 - Projet Prog&Algo S1
*/

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

// Déclarations des variables
struct Game;
struct Joueur;

// Déclarations des structures

typedef struct Bouton{
  float r, g, b, x, y, hauteur, longueur, valeur;
} Bouton;

enum EnumFonds{
    MENUDEBUT=0,
    MENUNORMAL
  };

enum EnumObstacles{
    OBSTACLE=0,
    VIDE
  };

enum EnumTexturesCarte{
    PLAINE=0, //Steeve a dit d'init toutes les premieres enums a 0
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
    ARBRE9,
    JOUEUR1,
    JOUEUR2
  };

enum EnumBoutons{
    RIEN=0,//Steeve a dit d'init toutes les premieres enums a 0
    ACHAT,
    DEPLACEMENT,
    ATTAQUE,
    PASSER,
    MULTIJOUEURS,
    ORDI_MODE,
    CLIC
  };

enum EnumUnites{
    VIKINGMAN=0,//Steeve a dit d'init toutes les premieres enums a 0
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
//int affichageInterface();
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int initialisationSDL(Game* game);
int finProgrammeSDL(Game* game);
//string texture_path(texturesCarte texture_value);
void carre(float x, float y, Joueur joueur, int choix);
void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface);
void surbrillanceAchat(int type, Game game);

/*sprites.cpp*/
void affichageUnite(Joueur joueur, Game* game);


/* boutons.cpp */
void bouton(Bouton bouton);
void initBoutonUnites(Bouton bouton, float r, float g, float b, float a);
int testClicBouton(Game* game, Bouton bouton, SDL_Event e, int erreur);
int selectionBoutonMenu(Game* game, SDL_Event e);
int selectionBouton(Game* game, SDL_Event e);
int selectionBoutonUnite(Game* game, SDL_Event e);




/*textures.cpp*/

void initialisationTexturesCarte(GLuint textureCases[20], SDL_Surface* surfaceCases[20]);  //à placer
void initialisationTexturesUnites(GLuint textureUnites[10], SDL_Surface* surfaceUnites[10]);
void creationTexture(GLuint *texture, SDL_Surface* image);
void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y);

#endif
