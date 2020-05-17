#include "unites/unites.h"
#include "interface/interface.h"
#include "interface/text.h"
#include <iostream>
using namespace std;

void creationTexte(SDL_Surface* texte, TTF_Font* police, GLuint *textureTexte, char* cheminFont, int taille, char* contenu, SDL_Color couleur) {
    // /* Chargement de la police */
    // police = TTF_OpenFont(cheminFont,taille);
    // /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    // texte = TTF_RenderUTF8_Blended(police, contenu, couleur); //cree une surface de taille variable en fonction du texte
    // creationTexture(textureTexte, texte);
    // cout<<texte->h<<endl;
    /* Chargement de la police */

    police = TTF_OpenFont(cheminFont,taille);

    SDL_Surface* sText =  TTF_RenderUTF8_Blended(police, contenu, couleur);

    if (sText == NULL){
      fprintf(stderr, "Echec de la création du texte");
      exit(EXIT_FAILURE);
    }

    // Uint32 rmask, gmask, bmask, amask; // Déclaration des masks
    //
    // #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    //     rmask = 0xff000000;
    //     gmask = 0x00ff0000;
    //     bmask = 0x0000ff00;
    //     amask = 0x000000ff;
    // #else
    //     rmask = 0x000000ff;
    //     gmask = 0x0000ff00;
    //     bmask = 0x00ff0000;
    //     amask = 0xff000000;
    // #endif

    creationTexture(textureTexte, sText);

    texte->w = sText->w; texte->h = sText->h;
    cout<<texte->h<<endl;
    cout<<texte->w<<endl;


    SDL_FreeSurface( sText );

}

void initialisationTextes(SDL_Surface* surfaceTextes, TTF_Font* police, GLuint textureTextes[100]){ //changer la taille du tableau
  //creationTexte(surfaceTextes, police, &textureTextes[TEXTE_BOUTON_DEPLACEMENT], "src/fonts/SummitAttack.ttf", 10, "Déplacement", SDL_Color{255, 255, 255});
  // creationTexte(&textes[TEXTE_BOUTON_ATTAQUE], "src/fonts/SummitAttack.ttf", 10, "Attaque", SDL_Color{255,255,255});
  // creationTexte(&textes[TEXTE_BOUTON_ACHAT], "src/fonts/SummitAttack.ttf", 10, "Achat", SDL_Color{255,255,255});
}

void affichageTextureTextes(SDL_Surface* surface, GLuint texture, float x, float y){ //, float longueur, float largeur, float x, float y
  float w = (float)surface->w/1000;
  float h = (float)surface->h/1000;
  glColor3f(1,1,1);
  glPushMatrix();
        glTranslatef(x,y,0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glTexCoord2f(1, 1);
        glVertex2f(w, h);

        glTexCoord2f(0, 1);
        glVertex2f(0,h);

        glTexCoord2f(0, 0);
        glVertex2f(0, 0);

        glTexCoord2f(1, 0);
        glVertex2f(w, 0);

        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

// char* conversionTexteDyna(char* text[]){
//   int a = 3;
//   string b = to_string(a);
//
//   char* text = (char*)b.c_str();
// }

// void affichageTextesStatiques(){
//
// }

//void texteEtatUnite()

// void deleteText(Text* text) {
//
// }
