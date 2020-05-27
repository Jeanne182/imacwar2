#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum Enum_Textes{
  TEXTE_BOUTON_DEPLACEMENT = 0, //Steeve a dit d'init toutes les premieres enums a 0
  TEXTE_BOUTON_ATTAQUE,
  TEXTE_BOUTON_ACHAT,
  TEXTE_BOUTON1J,
  TEXTE_BOUTON2J,
  TEXTE_PV,
  TEXTE_FORCE,
  TEXTE_DEFENSE,
  TEXTE_ZONE,
  TEXTE_RANGE,
  TEXTE_PRIX,
  TEXTE_PIECESJ1,
  TEXTE_PIECESJ2
  };

  enum Polices{
    TITRES=0, //Steeve a dit d'init toutes les premieres enums a 0
    SOUSTITRES,
    NORMAL
  };

// typedef struct Texte {
//     TTF_Font *font; // Police de caractère
//     SDL_Surface *text; // Contenu du texte
//     SDL_Color color; // Couleur du texte
//     GLuint texture;
// } Texte;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/*text.cpp*/
void creationTexte(SDL_Surface* texte, TTF_Font* police, GLuint *textureTexte, char* contenu, SDL_Color couleur);
void initialisationTextes(SDL_Surface surfaceTextes[100], TTF_Font* policeTextes[100], GLuint textureTextes[100]);

void affichageTextureTextes(SDL_Surface* surface, GLuint texture, float x, float y); //, float longueur, float largeur, float x, float y
char* conversionTexteDyna(int valeur, char* phrase);
#endif
