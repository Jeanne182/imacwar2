#include <iostream>
#include "./../unites/unites.h"
#include "interface.h"
#include <stdlib.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
using namespace std;

void selectionCoordonnee(int* x, int* y, SDL_Event e, float aspectRatio, SDL_Surface* surface){
        printf("clic en (%d, %d)\n", (int)(1+10*e.button.x*aspectRatio/(float)surface->w), (int)(1+10*e.button.y/(float)surface->h));
}
