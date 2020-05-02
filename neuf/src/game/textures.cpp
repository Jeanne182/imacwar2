#include "interface/interface.h"

void initialisationTexturesCarte(GLuint textureCases[3], SDL_Surface* surfaceCases[3]){
    creationTexture(&textureCases[PLAINE], surfaceCases[PLAINE]);
    creationTexture(&textureCases[EAU], surfaceCases[EAU]);
    creationTexture(&textureCases[ARBRE], surfaceCases[ARBRE]);
}

void initialisationTexturesUnites(GLuint textureUnites[3], SDL_Surface* surfaceUnites[3], EnumUnites unite){
    creationTexture(&textureUnites[unite], surfaceUnites[unite]);
}