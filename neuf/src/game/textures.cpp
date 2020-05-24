#include "interface/interface.h"
using namespace std;
void initialisationTexturesCarte(GLuint textureCases[10], SDL_Surface* surfaceCases[10]){
    creationTexture(&textureCases[PLAINE], surfaceCases[PLAINE]);
    creationTexture(&textureCases[EAU], surfaceCases[EAU]);
    creationTexture(&textureCases[ARBRE], surfaceCases[ARBRE]);
    creationTexture(&textureCases[EAUBD], surfaceCases[EAUBD]);
    creationTexture(&textureCases[EAUBG], surfaceCases[EAUBG]);
    creationTexture(&textureCases[EAUHG], surfaceCases[EAUHG]);
    creationTexture(&textureCases[EAUHD], surfaceCases[EAUHD]);
}

void initialisationTexturesUnites(GLuint textureUnites[10], SDL_Surface* surfaceUnites[10]){
    creationTexture(&textureUnites[VIKINGMAN], surfaceUnites[VIKINGMAN]);
    creationTexture(&textureUnites[VIKINGBEAST], surfaceUnites[VIKINGBEAST]);
    creationTexture(&textureUnites[VIKINGWOMAN], surfaceUnites[VIKINGWOMAN]);
    creationTexture(&textureUnites[VIKINGWIZARD], surfaceUnites[VIKINGWIZARD]);
    creationTexture(&textureUnites[VIKINGCHIEF], surfaceUnites[VIKINGCHIEF]);
    creationTexture(&textureUnites[DEADBEAST], surfaceUnites[DEADBEAST]);
    creationTexture(&textureUnites[DEADKNIGHT], surfaceUnites[DEADKNIGHT]);
    creationTexture(&textureUnites[DEADWIZARD], surfaceUnites[DEADWIZARD]);
    creationTexture(&textureUnites[DEADMAN], surfaceUnites[DEADMAN]);
    creationTexture(&textureUnites[DEADCHIEF], surfaceUnites[DEADCHIEF]);
}

void creationTexture(GLuint *texture, SDL_Surface* image){

  //SDL_Surface* image = IMG_Load(chemin_image);

  if(image==NULL){
    printf("L'image de la carte n'a pas pu se charger");
    exit(1);
  }

    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int mode = GL_RGB;
    if(image->format->BytesPerPixel == 4) mode = GL_RGBA;
    else mode = GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void affichageTexture(GLuint texture, float longueur, float largeur, float x, float y){
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
