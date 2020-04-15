/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "./../unites/unites.h"
#include "./../interface/interface.h"
using namespace std;

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 900;
static const unsigned int WINDOW_HEIGHT = 800;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;
static float aspectRatio;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(){
  SDL_Surface* surface;
  GLuint textureMap ;

  initialisationSDL(&textureMap,surface);

  reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
  /* Boucle principale */
  int loop = 1;

  Joueur joueur1;
  joueur1.nbUnites=0;
  int id1=0;
  Joueur joueur2;

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      /* Placer ici le code de dessin */

      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

      glColor3f(1,1,1);
      affichageTexture(textureMap,1,1);
      affichageUnite(joueur1, 10, 10, surface);



      /* Echange du front et du back buffer : mise a jour de la fenetre */
      SDL_GL_SwapBuffers();
      //glLoadIdentity();
      /* Boucle traitant les evenements */
      SDL_Event e;
      while(SDL_PollEvent(&e))
      {
          /* L'utilisateur ferme la fenetre : */
          if(e.type == SDL_QUIT)
          {
              loop = 0;
              break;
          }
          float aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
          switch(e.type) {
            case SDL_MOUSEBUTTONUP:

              Unite unite;
              unite.id =id1;

              int x , y;
              selectionCoordonnee(&x,&y, e, aspectRatio, surface);
              insertionCoordonnees(&unite, x, y);
              joueur1.unites[id1] = unite;
              joueur1.nbUnites ++;
              cout<<joueur1.unites[id1].coord[0]<<endl;
              cout<<joueur1.unites[id1].coord[1]<<endl;
              id1++;

              break;

            default:
                  break;
          }
      }

      /* Calcul du temps ecoule */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* Si trop peu de temps s'est ecoule, on met en pause le programme */
      if(elapsedTime < FRAMERATE_MILLISECONDS){
          SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
      }
  }
  finProgrammeSDL(&textureMap);


  return 0;

};
