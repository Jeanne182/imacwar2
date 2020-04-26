/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"


int main(){
  Game game;
  initialisationGame(&game);

  int loop = 1;

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      /* Placer ici le code de dessin */

      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

      glColor3f(1,1,1);

      for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
          switch(game.map[i][j]){
            case PLAINE:
            affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            //affichageTexture(game.textureMap,(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            break;

            case EAU:
            affichageTexture(game.textureCases[EAU],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            break;

            case ARBRE:
            affichageTexture(game.textureCases[ARBRE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            break;
          }

        }
      }

      //affichageTexture(game.textureMap,1,1,0,0);
      bouton(game.boutonDeplacement);
      affichageUnite(game.joueur1, game.longueurCarte, game.hauteurCarte);
      affichageUnite(game.joueur2, game.longueurCarte, game.hauteurCarte);

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

          switch(e.type) {
            case SDL_MOUSEBUTTONUP:

              gererClic(&game,e);
              break;

            default:
                  break;
          }
      }

      /* Calcul du temps ecoule */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* Si trop peu de temps s'est ecoule, on met en pause le programme */
      if(elapsedTime < game.framerate_milliseconds){
          SDL_Delay(game.framerate_milliseconds - elapsedTime);
      }
  }
  //finProgrammeSDL(&game.textureMap[PLAINE]);
  finProgrammeSDL(&game);

  return 0;

};
