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
  // int xOrdi = 8;
  // int yOrdi = 1;
  // int xCible= 3;
  // int yCible =8;
  // Noeud* chemin = a_star(xOrdi,yOrdi, xCible, yCible, game.mapObstacles);
  // Noeud copy = *chemin;
  // cout<<"lastNode :("<<chemin->x<<"'"<<chemin->y<<")"<<endl;
  // cout<<"uniteOrdi :("<<xOrdi<<"'"<<yOrdi<<")"<<endl;
  //
  // cout<< "Last Node("<<chemin->x<<","<<chemin->y<<")";
  // cout<<"Chemin prédéfini : ";
  // cout<< "("<<chemin->x<<","<<chemin->y<<")";
  // while(chemin->x != xOrdi && chemin->y != yOrdi){
  //   chemin=chemin->parent;
  //
  // }
  // cout<<endl<<endl;

  // affichageChemin(&copy, xOrdi, yOrdi);

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
