/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "unites/unites.h"
#include "interface/interface.h"
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
  joueur1.nbUnitesInitial=0;
  joueur1.id = 1;

  Joueur joueur2;
  joueur2.nbUnites=0;
  joueur2.nbUnitesInitial=0;
  joueur2.id = 2;

  int etapeJeu = 0 ; //0 pour préparation, 1 pour attaque/déplacement
  int tour = 1;

  int x , y;
  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      /* Placer ici le code de dessin */

      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

      glColor3f(1,1,1);
      affichageTexture(textureMap,1,1);
      affichageUnite(joueur1, 10, 10, surface);
      affichageUnite(joueur2, 10, 10, surface);

      /* Echange du front et du back buffer : mise a jour de la fenetre */
      SDL_GL_SwapBuffers();
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
              //Première partie du jeu : placement des unités
              if (etapeJeu ==0){
                placementUnitesJoueurs(&joueur1, &joueur2, e, surface, &tour);
                if(joueur1.nbUnites==4 && joueur2.nbUnites==4){ //A CHANGER
                  etapeJeu++;
                }
              }

              //Partie du jeu où les joueurs attaquent et se déplacent
              else{
                //sélection des coordonnées d'une unité du joueur dont c'est le tour
                if(etapeJeu==1){
                  selectionCoordonnee(&x,&y, e, surface);
                  if((tour ==1 && selectionIdUnite(x, y, joueur1) != -1)
                          ||(tour ==2 && selectionIdUnite(x, y, joueur2) != -1)){
                    etapeJeu++;
                  }
                }
                //Le joueur choisi d'attquer ou de se déplacer
                else if(etapeJeu==2){
                  if (tour == 1){
                    int id1 = selectionIdUnite(x, y, joueur1);
                    deplacement(&joueur1, id1, x, y, e, surface);
                      tour = 2;
                  }
                  else{
                    int id2 = selectionIdUnite(x, y, joueur2);
                    deplacement(&joueur2, id2, x, y, e, surface);
                    tour = 1;
                  }
                  etapeJeu = 1;
                }
              }

              /*for (int i = 0; i<=3; i++){
                cout << i << " j1 = "<< joueur1.unites[i].coord[0]<<endl;
                cout << i << " j1 = "<< joueur1.unites[i].coord[1]<<endl;
              }
              for (int i = 0; i<=3; i++){
                cout << i << " j2 = "<< joueur2.unites[i].coord[0]<<endl;
                cout << i << " j2 = "<< joueur2.unites[i].coord[1]<<endl;
              }*/

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
