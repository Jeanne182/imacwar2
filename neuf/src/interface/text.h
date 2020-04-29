#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <SDL/SDL_ttf.h>

typedef struct Text {
    TTF_Font *font; // Police de caractère
    SDL_Surface *text; // Contenu du texte
    SDL_Color color; // Couleur du texte
    GLuint texture;
} Text;

//----------------------------------------------------------------- Prototypes des fonctions-------------------------------------------------------------//

/*text.cpp*/

void displayText(float posX, float posY);
void deleteText();
Text font(const char* fontPath, float size, SDL_Color color, const char* content);

#endif
