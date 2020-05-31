#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"
#include "joueur_ordi/a_star.h"
#include "joueur_ordi/joueur_ordi.h"
#include <cstring>


int main(){
  Game game;
  initialisationGame(&game);
  initialisationDynamique(&game);

  int loop = 1;

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      affichage(&game);

      if(game.tour == TOUR_JOUEUR2 && game.modeJeu == ORDI_MODE){
        if(game.etapeJeu==SELECTION_UNITE){
          game.etapeJeu=ACTIONS;
        }
        switch(game.etapeJeu){

        case PLACEMENT_UNITES:
        cout << "sousj1: " << game.joueur1.pieces << endl;
        cout << "sousj2: " << game.joueur2.pieces << endl;

          choixPlacementUniteOrdi(&game);
          break;
        case ACTIONS:
          choixActionsOrdi(&game);
          break;
        }

      }

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

          selectionCoordonnee(&game.xSurvol, &game.ySurvol, e, game.surface);
          game.idUniteSurvolee = selectionIdUnite(game.xSurvol, game.ySurvol,game.joueur1);
          if(game.idUniteSurvolee==-1){
            game.idUniteSurvolee = selectionIdUnite(game.xSurvol, game.ySurvol,game.joueur2);
          }

          switch(e.type) {
            case SDL_MOUSEBUTTONDOWN:
              if (e.button.button == SDL_BUTTON_LEFT){

                gererClic(&game,e);
              }

              break;

              case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE){
                  finJeu(&game);
                }
              break;
          }
      }


      /* Echange du front et du back buffer : mise a jour de la fenetre */
      SDL_GL_SwapBuffers();

      /* Calcul du temps ecoule */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* Si trop peu de temps s'est ecoule, on met en pause le programme */
      if(elapsedTime < game.framerate_milliseconds){
          SDL_Delay(game.framerate_milliseconds - elapsedTime);
      }
      //frame++;
  }


  return 0;

};
