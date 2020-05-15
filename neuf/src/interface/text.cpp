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
  creationTexte(&textes[TEXTE_BOUTON_DEPLACEMENT], "src/fonts/SummitAttack.ttf", 65, "Déplacement", SDL_Color{255, 255, 255});
  creationTexte(&textes[TEXTE_BOUTON_ATTAQUE], "src/fonts/SummitAttack.ttf", 100, "Attaque", SDL_Color{255,255,255});
  creationTexte(&textes[TEXTE_BOUTON_ACHAT], "src/fonts/SummitAttack.ttf", 100, "Achat", SDL_Color{255,255,255});
}

void affichageTextureTextes(GLuint texture, float longueur, float largeur, float x, float y){
  glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glTexCoord2f(1, 1);
        glVertex2f(longueur + x, largeur + y);

        glTexCoord2f(0, 1);
        glVertex2f(x,largeur + y);

        glTexCoord2f(0, 0);
        glVertex2f(x, y);

        glTexCoord2f(1, 0);
        glVertex2f(longueur + x, y);

        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

// void affichageTextesStatiques(){
//
// }

//void texteEtatUnite()

// void deleteText(Text* text) {
//
// }
