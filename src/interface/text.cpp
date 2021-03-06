#include "unites/unites.h"
#include "interface/interface.h"
#include "interface/text.h"
#include <iostream>

using namespace std;


void creationTexte(SDL_Surface* texte, TTF_Font* police, GLuint *textureTexte, char* contenu, SDL_Color couleur) {
    SDL_Surface* sText =  TTF_RenderUTF8_Blended(police, contenu, couleur);
    if (sText == NULL){
      fprintf(stderr, "Echec de la création du texte");
      exit(EXIT_FAILURE);
    }
    creationTexture(textureTexte, sText);
    texte->w = sText->w; texte->h = sText->h;
    SDL_FreeSurface(sText);
}


void initialisationTextes(SDL_Surface surfaceTextes[100], TTF_Font* policeTextes[100], GLuint textureTextes[100]){ //changer la taille du tableau
  creationTexte(&surfaceTextes[TEXTE_JOUEUR1], policeTextes[TITRES], &textureTextes[TEXTE_JOUEUR1], (char*)"Joueur 1", SDL_Color{1,74,199});
  creationTexte(&surfaceTextes[TEXTE_JOUEUR2],  policeTextes[TITRES], &textureTextes[TEXTE_JOUEUR2], (char*)"Joueur 2", SDL_Color{94, 0 ,46});
  creationTexte(&surfaceTextes[TEXTE_BOUTON_DEPLACEMENT], policeTextes[TITRES_BOUTONS], &textureTextes[TEXTE_BOUTON_DEPLACEMENT], (char*)"Déplacement", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_BOUTON_ATTAQUE],  policeTextes[TITRES_BOUTONS], &textureTextes[TEXTE_BOUTON_ATTAQUE], (char*)"Attaque", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_BOUTON_ACHAT],  policeTextes[TITRES_BOUTONS], &textureTextes[TEXTE_BOUTON_ACHAT], (char*)"Achat", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_BOUTON_PASSER],  policeTextes[TITRES_BOUTONS], &textureTextes[TEXTE_BOUTON_PASSER], (char*)"Passer le tour", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_BOUTON1J],  policeTextes[TITRES], &textureTextes[TEXTE_BOUTON1J], (char*)"1 joueur", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_BOUTON2J],  policeTextes[TITRES], &textureTextes[TEXTE_BOUTON2J], (char*)"2 joueurs", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_CHOIX],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_CHOIX], (char*)"Veuillez constituer votre armée", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_PLACEMENT],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_PLACEMENT], (char*)"Placez votre guerrier", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_SELECTION],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_SELECTION], (char*)"Sélectionnez un de vos guerriers", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_ACTION],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_ACTION], (char*)"Choisissez une action à effectuer", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_JOUEUR1_GAGNANT],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_JOUEUR1_GAGNANT], (char*)"Bravo, votre place est assurée au Valhalla, vous vous êtes bien battus guerriers !", SDL_Color{1,74,199});
  creationTexte(&surfaceTextes[TEXTE_JOUEUR2_GAGNANT],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_JOUEUR2_GAGNANT], (char*)"L'armée des morts a triomphé sur le Bien, Loki se repaît de cette victoire !", SDL_Color{94, 0 ,46});
  creationTexte(&surfaceTextes[TEXTE_EGALITE],  policeTextes[SOUSTITRES], &textureTextes[TEXTE_EGALITE], (char*)"Personne ne gagne aujourd'hui", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_CARACTERISTIQUES],  policeTextes[TITRE_MEDIUM], &textureTextes[TEXTE_CARACTERISTIQUES], (char*)"Caractéristiques de l'unité", SDL_Color{255,255,255});
  creationTexte(&surfaceTextes[TEXTE_REJOUER],  policeTextes[TITRES], &textureTextes[TEXTE_REJOUER], (char*)"Rejouer", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_QUITTER],  policeTextes[TITRES], &textureTextes[TEXTE_QUITTER], (char*)"Quitter", SDL_Color{63,63,63});
  creationTexte(&surfaceTextes[TEXTE_ATTAQUE],  policeTextes[TITRES], &textureTextes[TEXTE_ATTAQUE], (char*)"L'ennemi attaque", SDL_Color{255, 255 ,255}); //
  creationTexte(&surfaceTextes[TEXTE_DEPLACEMENT],  policeTextes[TITRES], &textureTextes[TEXTE_DEPLACEMENT], (char*)"L'ennemi se déplace", SDL_Color{255, 255 ,255}); //
}

void affichageTextureTextes(SDL_Surface* surface, GLuint texture, float x, float y){
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

char* conversionTexteDyna(int valeur, char* phrase){
    string str_valeur = to_string(valeur);
    char* chaine = (char*)str_valeur.c_str();
    char* result = concatenation(phrase, chaine);
    return result;
}

char* concatenation(char* phraseUn, char* phraseDeux){
  char * result;
  result=(char*)malloc(strlen(phraseUn)+1+strlen(phraseDeux)+1);
  strcpy(result,phraseUn);
  strcat(result, phraseDeux);
  return result;
}
