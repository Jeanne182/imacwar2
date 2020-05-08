#include "unites/unites.h"
#include "interface/interface.h"
#include "interface/text.h"
#include <iostream>

void creationTexte(GLuint *textureTexte, char* cheminFont, int taille, char* contenu, SDL_Color couleur) {
    /* Chargement de la police */
    TTF_Font* police = TTF_OpenFont(cheminFont,taille);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    SDL_Surface* texte = TTF_RenderUTF8_Blended(police, contenu, couleur);
    creationTexture(textureTexte, texte);
}

void initialisationTextes(GLuint textes[100]){ //changer la taille du tableau
  creationTexte(&textes[0], "src/fonts/SummitAttack.ttf", 65, "Déplacement", SDL_Color{255, 255, 255});
}

// void affichageTexte(){
//
// }
//
//
// void deleteText(Text* text) {
//
// }
