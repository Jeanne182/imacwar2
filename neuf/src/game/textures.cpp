#include "interface/interface.h"
using namespace std;
void initialisationTexturesCarte(GLuint textureCases[20], SDL_Surface* surfaceCases[20]){
    creationTexture(&textureCases[PLAINE], surfaceCases[PLAINE]);
    creationTexture(&textureCases[PLAINECHG], surfaceCases[PLAINECHG]);
    creationTexture(&textureCases[EAU], surfaceCases[EAU]);
    creationTexture(&textureCases[ARBRE], surfaceCases[ARBRE]);
    creationTexture(&textureCases[ARBRE1], surfaceCases[ARBRE1]);
    creationTexture(&textureCases[ARBRE2], surfaceCases[ARBRE2]);
    creationTexture(&textureCases[ARBRE4], surfaceCases[ARBRE4]);
    creationTexture(&textureCases[ARBRE5], surfaceCases[ARBRE5]);
    creationTexture(&textureCases[ARBRE6], surfaceCases[ARBRE6]);
    creationTexture(&textureCases[ARBRE7], surfaceCases[ARBRE7]);
    creationTexture(&textureCases[ARBRE8], surfaceCases[ARBRE8]);
    creationTexture(&textureCases[ARBRE9], surfaceCases[ARBRE9]);
    creationTexture(&textureCases[EAUBD], surfaceCases[EAUBD]);
    creationTexture(&textureCases[EAUBG], surfaceCases[EAUBG]);
    creationTexture(&textureCases[EAUHG], surfaceCases[EAUHG]);
    creationTexture(&textureCases[EAUHD], surfaceCases[EAUHD]);

    SDL_FreeSurface(surfaceCases[PLAINE]);
    SDL_FreeSurface(surfaceCases[PLAINECHG]);
    SDL_FreeSurface(surfaceCases[EAU]);
    SDL_FreeSurface(surfaceCases[ARBRE]);
    SDL_FreeSurface(surfaceCases[ARBRE1]);
    SDL_FreeSurface(surfaceCases[ARBRE2]);
    SDL_FreeSurface(surfaceCases[ARBRE4]);
    SDL_FreeSurface(surfaceCases[ARBRE5]);
    SDL_FreeSurface(surfaceCases[ARBRE6]);
    SDL_FreeSurface(surfaceCases[ARBRE8]);
    SDL_FreeSurface(surfaceCases[ARBRE9]);
    SDL_FreeSurface(surfaceCases[EAUBD]);
    SDL_FreeSurface(surfaceCases[EAUBG]);
    SDL_FreeSurface(surfaceCases[EAUHG]);
    SDL_FreeSurface(surfaceCases[EAUHD]);
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

    SDL_FreeSurface(surfaceUnites[VIKINGMAN]);
    SDL_FreeSurface(surfaceUnites[VIKINGBEAST]);
    SDL_FreeSurface(surfaceUnites[VIKINGWOMAN]);
    SDL_FreeSurface(surfaceUnites[VIKINGWIZARD]);
    SDL_FreeSurface(surfaceUnites[VIKINGCHIEF]);
    SDL_FreeSurface(surfaceUnites[DEADBEAST]);
    SDL_FreeSurface(surfaceUnites[DEADKNIGHT]);
    SDL_FreeSurface(surfaceUnites[DEADWIZARD]);
    SDL_FreeSurface(surfaceUnites[DEADMAN]);
    SDL_FreeSurface(surfaceUnites[DEADCHIEF]);
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
  glColor3f(1,1,1);
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
