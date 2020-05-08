#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <SDL/SDL_ttf.h>

enum Enum_Textes{
  TEXTE_BOUTON_DEPLACEMENT,
  TEXTE_BOUTON_ATTAQUE
  };

typedef struct Texte {
    TTF_Font *font; // Police de caractère
    SDL_Surface *text; // Contenu du texte
    SDL_Color color; // Couleur du texte
    GLuint texture;
} Texte;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/*text.cpp*/
void creationTexte(GLuint *textureTexte, char* cheminFont, int taille, char* contenu, SDL_Color couleur);
void initialisationTextes(GLuint textes[100]);


#endif
