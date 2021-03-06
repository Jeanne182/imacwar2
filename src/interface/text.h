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
    TEXTE_BOUTON_DEPLACEMENT = 0,
    TEXTE_BOUTON_ATTAQUE,
    TEXTE_BOUTON_ACHAT,
    TEXTE_BOUTON_PASSER,
    TEXTE_BOUTON1J,
    TEXTE_BOUTON2J,
    TEXTE_PV,
    TEXTE_FORCE,
    TEXTE_DEFENSE,
    TEXTE_ZONE,
    TEXTE_RANGE,
    TEXTE_PRIX,
    TEXTE_PIECESJ1,
    TEXTE_PIECESJ2,
    TEXTE_JOUEUR1,
    TEXTE_JOUEUR2,
    TEXTE_NOM_UNIT,
    TEXTE_PLACEMENT,
    TEXTE_CHOIX,
    TEXTE_SELECTION,
    TEXTE_ACTION,
    TEXTE_JOUEUR1_GAGNANT,
    TEXTE_JOUEUR2_GAGNANT,
    TEXTE_EGALITE,
    TEXTE_CARACTERISTIQUES,
    TEXTE_REJOUER,
    TEXTE_QUITTER,
    TEXTE_ATTAQUE,
    TEXTE_DEPLACEMENT,
    TEXTE_PV_PERDUS_J1,
    TEXTE_PV_PERDUS_J2,
    TEXTE_PV_PERDUS_JOUEUR,
    TEXTE_PV_PERDUS_ORDI
  };

  enum Polices{
    TITRES=0,
    SOUSTITRES,
    TITRE_MEDIUM,
    TITRES_BOUTONS,
    NORMAL
  };



//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/*text.cpp*/
void creationTexte(SDL_Surface* texte, TTF_Font* police, GLuint *textureTexte, char* contenu, SDL_Color couleur);
void initialisationTextes(SDL_Surface surfaceTextes[100], TTF_Font* policeTextes[100], GLuint textureTextes[100]);
void affichageTextureTextes(SDL_Surface* surface, GLuint texture, float x, float y); 
char* conversionTexteDyna(int valeur, char* phrase);
char* concatenation(char* phraseUn, char* phraseDeux);

#endif
